#include "mainwindow.h"
#include "ui_mainwindow.h"


// http://zetcode.com/gui/qt5/menusandtoolbars/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Untitled Document");
    _windowCount = 0;
    this->window()->setWindowState(Qt::WindowActive);

    _windowList.append(this->window());
    _totalWindows.insert(ui->centralWidget, _windowCount);
    _textEditPerWindow.insert(_windowCount, ui->textEdit);
    QLineEdit *searchBar = ui->searchBar;
    _searchBarRecord.insert(_windowCount, searchBar);
    _windowCount++;

    _optionsMenu = this->menuBar()->addMenu(tr("&Options"));
    QAction *clearText = _optionsMenu->addAction("Clear Text", this, SLOT(on_clear_text_click()));
    QAction *openFile = _optionsMenu->addAction("Open File", this, SLOT(on_open_file_click()));
    QAction *createNewFile = _optionsMenu->addAction("Create New File", this, SLOT(on_click_create_new_file()));
    QAction *saveFile = _optionsMenu->addAction("Save File", this, SLOT(on_pushButton_clicked()));

    // QAction *saveFile = _optionsMenu->addAction(tr("Save File"));
    // QAction *saveFile = _optionsMenu->addAction("Save File", this, SLOT(on_saveFileButton_clicked()));
    // connect(_optionsMenu, SIGNAL(triggered(QAction*)), SLOT(on_pushButton_clicked(QAction*)));
    // connect(saveFile, SIGNAL(triggered(QAction*)), SLOT(on_pushButton_clicked(QAction*)));
    // connect(saveFile, &QAction::triggered, this, &MainWindow::on_pushButton_clicked);
    // connect(saveFile, SIGNAL(QAction::triggered), this, SLOT(MainWindow::on_pushButton_clicked(QAction*)));


    this->menuBar()->addMenu(_optionsMenu);
    _menuActions.push_back(clearText);
    _menuActions.push_back(openFile);
    _menuActions.push_back(createNewFile);
    _menuActions.push_back(saveFile);
    this->menuBar()->addSeparator();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_quitButton_clicked() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    buttonSender->parentWidget()->window()->close();
}


// https://stackoverflow.com/questions/14835174/getting-the-text-from-a-qtextedit-inside-a-qwidget
// possibly has answer for adding a tabbed window as well
void MainWindow::on_saveFileButton_clicked() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(buttonSender->parentWidget());
    QWidget *widget = nullptr;
    int place;
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
    return;
}


// void MainWindow::on_pushButton_clicked(QAction *action) {
void MainWindow::on_pushButton_clicked() {
    // QMessageBox msgBox;
    // msgBox.setText("Shalom");
    // msgBox.exec();
    // QAction *actionSender = qobject_cast<QAction*>(sender());
    // QWidget *theParentWidget = actionSender->parentWidget();
    // QWidget *theParentWindow = theParentWidget->window();
    // QWidget *theWindow = QApplication::activeWindow();
    /* if(theWindow == theParentWindow) {
        QMessageBox msgBox;
        msgBox.setText("Shalom");
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setText("They are not the same");
        msgBox.exec();
    } */
    // QHash<QWidget*, int>::const_iterator i = _totalParentWindows.find(theParentWindow);
    // QHash<QWidget*, int>::const_iterator i = _totalWindows.find(action->parentWidget());
    // QHash<QWidget*, int>::const_iterator i = _totalWindows.find(theWindow);
    // QWidget *widget = nullptr;
    // int place;
    // if(i != _totalWindows.end()) {
    // if(i != _totalParentWindows.end()) {
       // widget = i.key();
       // place = i.value();
       // theWindow->close();
    // } else {
        // QMessageBox msgBox;
        // msgBox.setText("Shalom");
        // msgBox.exec();
    // }
    // theWindow->close();
    /* if(i == _totalParentWindows.end()) {
        theWindow->close();
        // QMessageBox msgBox;
        // msgBox.setText("Shalom");
        // msgBox.exec();
    } */
    /*
    if(widget != nullptr) {
        theWindow->close();
        /* QString filename = QFileDialog::getSaveFileName(widget, tr("Save File"),
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
        file.close(); */
    /* } else {
        QMessageBox msgBox;
        msgBox.setText("Unable to save the document. "
                       "Please try again.");
        msgBox.exec();
    } */
    // return;
}


void MainWindow::on_textEdit_copyAvailable(bool b) {
}


void MainWindow::on_clear_text_click() {
    ui->textEdit->clear();
}


void MainWindow::on_open_file_click() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *theParentWidget = actionSender->parentWidget();
    QWidget *theParentWindow = theParentWidget->window();
    QByteArray contents;
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(theParentWindow);
    QWidget *widget = nullptr;
    int place;
    if(i != _totalWindows.end()) {
       widget = i.key();
       place = i.value();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Shalom");
        msgBox.exec();
    }

    /*
    // QString fileName = QFileDialog::getOpenFileName(this,
    QString fileName = QFileDialog::getOpenFileName(theParentWindow,
                          tr("Open File"), QDir::homePath());
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        // QMessageBox::information(this, tr("Unable to open file"),
        QMessageBox::information(theParentWindow, tr("Unable to open file"),
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
    ui->textEdit->setPlainText(contentsStr);
    this->setWindowTitle(fileName);
    */
}


void MainWindow::on_click_create_new_file() {
    QWidget *window = new QWidget;
    window->setAccessibleName(QString::number(_windowCount));
    QVBoxLayout *vbox = new QVBoxLayout();
    window->setLayout(vbox);
    QMenuBar *menu_bar = new QMenuBar();
    menu_bar->addMenu(_optionsMenu);
    vbox->addWidget(menu_bar);
    QLineEdit *searchBarEdit = new QLineEdit();
    vbox->addWidget(searchBarEdit);
    QPushButton *searchBtn = new QPushButton("&Search");
    vbox->addWidget(searchBtn);
    QPushButton *clearBtn = new QPushButton("&Clear");
    vbox->addWidget(clearBtn);
    QObject::connect(searchBtn, &QPushButton::released, this, &MainWindow::on_searchButton_clicked);
    QObject::connect(clearBtn, &QPushButton::released, this, &MainWindow::on_clearSearch_clicked);

    QTextEdit *windowTextEdit = new QTextEdit();
    vbox->addWidget(windowTextEdit);
    QPushButton *quitButton = new QPushButton("&Quit");
    quitButton->setObjectName(QString::number(_windowCount));

    QPushButton *wordCountBtn = new QPushButton("&Word Count");
    vbox->addWidget(wordCountBtn);
    QObject::connect(wordCountBtn, &QPushButton::released, this, &MainWindow::on_wordCount_clicked);

    QPushButton *saveFileButton = new QPushButton("&Save File");
    QPushButton *searchReplaceButton = new QPushButton("&Search and Replace");
    QObject::connect(quitButton, &QPushButton::released, this, &MainWindow::on_quitButton_clicked);
    QObject::connect(saveFileButton, &QPushButton::released, this, &MainWindow::on_saveFileButton_clicked);
    QObject::connect(searchReplaceButton, &QPushButton::released, this, &MainWindow::on_searchReplace_clicked);
    vbox->addWidget(quitButton);
    vbox->addWidget(saveFileButton);
    vbox->addWidget(searchReplaceButton);
    window->setWindowTitle("Untitled Document");
    window->show();
    window->setWindowState(Qt::WindowActive);

    _windowCount++;
    _windowList.append(window);

    _textEditPerWindow.insert(_windowCount, windowTextEdit);
    _totalWindows.insert(window, _windowCount);
    _searchBarRecord.insert(_windowCount, searchBarEdit);
    QWidget* tmpWidget = windowTextEdit->parentWidget();
    _totalParentWindows.insert(tmpWidget->window(), _windowCount);
}


void MainWindow::on_searchReplace_clicked() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(buttonSender->parentWidget());
    QWidget *widget = nullptr;
    int place;
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


void MainWindow::on_searchButton_clicked() {
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


void MainWindow::on_clearSearch_clicked() {
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


void MainWindow::on_wordCount_clicked() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    QHash<QWidget*, int>::const_iterator i = _totalWindows.find(buttonSender->parentWidget());
    QWidget *widget = nullptr;
    int place;
    QTextEdit* textEdit;
    QString plainText;
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


/* https://stackoverflow.com/questions/3860112/multiple-github-accounts-on-the-same-computer */
