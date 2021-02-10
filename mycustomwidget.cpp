#include "mycustomwidget.h"

MyCustomWidget::MyCustomWidget(QWidget *parent) : QWidget(parent) {
    QWidget *window = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout();
    window->setLayout(vbox);

    QMenuBar *menu_bar = new QMenuBar(window);

    QMenu *optionsMenu = menu_bar->addMenu(tr("&Options"));
    QAction *quitMenuOption = optionsMenu->addAction("Quit", this, SLOT(quitOptionClicked()));
    QAction *createNewFile = optionsMenu->addAction("Create New File", this, SLOT(createNewFileClicked()));
    QAction *wordCount = optionsMenu->addAction("Word Count", this, SLOT(wordCountClicked()));
    QAction *clearText = optionsMenu->addAction("Clear Text", this, SLOT(clearTextClicked()));
    QAction *copyText = optionsMenu->addAction("Copy Text", this, SLOT(copyTextClicked()));
    QAction *saveFile = optionsMenu->addAction("Save File", this, SLOT(saveFileClicked()));
    QAction *openFile = optionsMenu->addAction("Open File", this, SLOT(openFileClicked()));
    QAction *searchReplaceMenuItem = optionsMenu->addAction("Search and Replace", this, SLOT(searchReplaceClicked()));

    menu_bar->addMenu(optionsMenu);
    vbox->addWidget(menu_bar);

    QLineEdit *searchBarEdit = new QLineEdit();
    vbox->addWidget(searchBarEdit);
    QPushButton *searchBtn = new QPushButton("&Search");
    vbox->addWidget(searchBtn);
    QPushButton *clearBtn = new QPushButton("&Clear");
    vbox->addWidget(clearBtn);
    QObject::connect(searchBtn, &QPushButton::released, this, &MyCustomWidget::searchBtnClicked);
    QObject::connect(clearBtn, &QPushButton::released, this, &MyCustomWidget::clearBtnClicked);

    QTextEdit *windowTextEdit = new QTextEdit();
    vbox->addWidget(windowTextEdit);
    _textEditPerWindow.insert(_windowCount, windowTextEdit);

    _totalWindows.insert(window, _windowCount);
    _searchBarRecord.insert(_windowCount, searchBarEdit);

    window->setWindowFlags(Qt::WindowMinimizeButtonHint);
    window->setWindowTitle("Untitled Document");
    window->show();
    window->setWindowState(Qt::WindowActive);

    _windowCount += 1;
}


void MyCustomWidget::createNewFileClicked() {
    MyCustomWidget *newWidget = new MyCustomWidget();
}


void MyCustomWidget::openFileClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    QTextEdit *textEdit;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        textEdit = _textEditPerWindow[place];
        QString contents;
        QString fileName = QFileDialog::getOpenFileName(currentWindow->parentWidget(),
                  tr("Open File"), QDir::homePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(currentWindow->parentWidget(), tr("Unable to open file"),
                     file.errorString());
            return;
        }
        while(!file.atEnd()) {
            QByteArray line = file.readLine();
            contents.append(line);
        }
        QString backSlash = "/";
        int backSlashLocation = fileName.lastIndexOf(backSlash);
        fileName.remove(0, backSlashLocation+1);

        QString contentsStr = QString::fromStdString(contents.toStdString());
        textEdit->setPlainText(contentsStr);
        widget->setWindowTitle(fileName);
    }
}


void MyCustomWidget::clearTextClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        if(widget != nullptr) {
            QTextEdit* textEdit = _textEditPerWindow[place];
            textEdit->clear();
        }
    }
}


void MyCustomWidget::wordCountClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    QTextEdit* textEdit;
    QString plainText;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        if(widget != nullptr) {
            textEdit = _textEditPerWindow[place];
            plainText = textEdit->toPlainText();
            plainText.replace("\n", " ");
            QStringList list = plainText.split(" ");
            int count = 0;
            for(int i = 0; i < list.size(); i++) {
                QString tmp = list.at(i);
                if(tmp.length() > 0) {
                    count += 1;
                }
            }
            QMessageBox msgBox;
            msgBox.setText("Word count is: " + QString::number(count));
            msgBox.exec();
        }
    }
}


void MyCustomWidget::searchBtnClicked() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(buttonSender->parentWidget());
    QWidget *widget = nullptr;
    int place;
    QTextEdit* textEdit;
    QLineEdit* lineEdit;
    QString plainText;
    if(i != _totalWindows.end()) {
        widget = i.key();
        place = i.value();
    }
    if(widget != nullptr) {
        textEdit = _textEditPerWindow[place];
        plainText = textEdit->toPlainText();

        plainText.replace("\n", " RePlAcE_tHiS ");
        lineEdit = _searchBarRecord[place];
        QString wordToHighLight = lineEdit->text().trimmed();

        QStringList list = plainText.split(" ");
        QStringList alteredList;
        for(int i = 0; i < list.size(); i++) {
            if(list.at(i) != "RePlAcE_tHiS") {
                if(list.at(i) == wordToHighLight) {
                    QString tmp = "<span style='background-color: red;'>";
                    tmp += list.at(i);
                    tmp += "</span>";
                    alteredList << tmp;
                } else {
                    alteredList << list.at(i);
                }
            } else {
                alteredList << "<br>";
            }
        }
        QString newList = alteredList.join(" ");
        textEdit->setHtml(newList);
    }
}


void MyCustomWidget::clearBtnClicked() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(buttonSender->parentWidget());
    QWidget *widget = nullptr;
    int place;
    QTextEdit* textEdit;
    QLineEdit* lineEdit;
    QString plainText;
    if(i != _totalWindows.end()) {
       widget = i.key();
       place = i.value();
    }
    if(widget != nullptr) {
        textEdit = _textEditPerWindow[place];
        plainText = textEdit->toPlainText();
        lineEdit = _searchBarRecord[place];
        QString wordToHighLight = lineEdit->text();

        QStringList list = plainText.split(" ");
        QStringList alteredList;
        for(int i = 0; i < list.size(); i++) {
            if(list.at(i) == wordToHighLight) {
                QString tmp = "<span style='background-color: none;'>";
                tmp += list.at(i);
                tmp += "</span>";
                alteredList << tmp;
            } else {
                alteredList << list.at(i);
            }
        }
        QString newList = alteredList.join(" ");
        textEdit->setHtml(newList);
    }
}


void MyCustomWidget::quitOptionClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    if(currentWindow != nullptr) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Text Editor",
                                    tr("Are you sure you want to exit \nthe Text Editor application?\n"),
                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                    QMessageBox::Yes);
        if(resBtn == QMessageBox::Yes) {
            currentWindow->parentWidget()->close();
        }
    }
}


void MyCustomWidget::copyTextClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        if(widget != nullptr) {
            QTextEdit* textEdit = _textEditPerWindow[place];
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(textEdit->toPlainText());
        }
    }
}


void MyCustomWidget::saveFileClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        if(widget != nullptr) {
            QString filename = QFileDialog::getSaveFileName(widget, tr("Save File"),
                widget->windowTitle());
            QFile file(filename);
            if(!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(widget, tr("Unable to open file"),
                 file.errorString());
                return;
            }
            QTextEdit* textEdit = _textEditPerWindow[place];
            QString plainText = textEdit->toPlainText();
            QTextStream out(&file);
            out << plainText;
            file.close();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Unable to save the document. "
                       "Please try again.");
            msgBox.exec();
        }
    }
}


void MyCustomWidget::searchReplaceClicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *currentWindow = nullptr;
    currentWindow = _getCurrentWindow(actionSender, currentWindow);
    QWidget *widget = nullptr;
    int place;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow->parentWidget());
        if(i != _totalWindows.end()) {
           widget = i.key();
           place = i.value();
        }
        if(widget != nullptr) {
            QTextEdit* textEdit = _textEditPerWindow[place];
            QString plainText = textEdit->toPlainText();
            QDialog *dialog = new QDialog(widget);
            QFormLayout form(dialog);
            form.addRow(new QLabel("User input: "));
            QString value1 = QString(" Value1: ");
            QLineEdit *spinBox1 = new QLineEdit(dialog);
            form.addRow(value1, spinBox1);
            QString value2 = QString(" Value2: ");
            QLineEdit *spinBox2 = new QLineEdit(dialog);
            form.addRow(value2, spinBox2);
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                           Qt::Horizontal, dialog);
            form.addRow(&buttonBox);
            QObject::connect(&buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
            QObject::connect(&buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
            if(dialog->exec() == QDialog::Accepted) {
                QString textOne = spinBox1->text();
                QString textTwo = spinBox2->text();
                plainText.replace(textOne, textTwo);
                textEdit->setPlainText(plainText);
            } else {
                dialog->close();
            }
        } else {
            QMessageBox msgBox;
            msgBox.setText("Unable to search and replace for this word."
                       "Please try again.");
            msgBox.exec();
        }
    }
}


QWidget* MyCustomWidget::_getCurrentWindow(QAction *actionSender, QWidget *currentWindow) {
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        currentWindow = parent;
    }
    return currentWindow;
}
