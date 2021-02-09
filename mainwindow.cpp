#include "mainwindow.h"
#include "ui_mainwindow.h"


// http://zetcode.com/gui/qt5/menusandtoolbars/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Untitled Document");
    _windowCount = 0;
    _qMainWindowCount = 0;
    this->window()->setWindowState(Qt::WindowActive);
    this->window()->setAccessibleName(QString::number(_windowCount));
    this->window()->setObjectName("HELLO 1");

    _windowList.append(this->window());
    // _totalWindows.insert(ui->centralWidget, _windowCount);
    _totalWindows.insert(this->window(), _windowCount);
    _textEditPerWindow.insert(_windowCount, ui->textEdit);
    QLineEdit *searchBar = ui->searchBar;
    _searchBarRecord.insert(_windowCount, searchBar);
    _windowCount++;

    // _optionsMenu = this->menuBar()->addMenu(tr("&Options"));
    QMenu *optionsMenu = this->menuBar()->addMenu(tr("&Options"));
    QAction *clearText = optionsMenu->addAction("Clear Text", this, SLOT(on_clear_text_click()));
    QAction *copyText = optionsMenu->addAction("Copy Text", this, SLOT(on_copy_text_click()));
    QAction *openFile = optionsMenu->addAction("Open File", this, SLOT(on_open_file_click()));
    QAction *createNewFile = optionsMenu->addAction("Create New File", this, SLOT(on_click_create_new_file()));
    QAction *saveFile = optionsMenu->addAction("Save File", this, SLOT(on_saveFileMenu_clicked()));
    QAction *wordCount = optionsMenu->addAction("Word Count", this, SLOT(on_wordCountMenu_clicked()));
    QAction *searchReplaceMenuItem = optionsMenu->addAction("Search and Replace", this, SLOT(on_searchReplaceMenu()));
    QAction *quitMenuItem = optionsMenu->addAction("Quit", this, SLOT(on_quitMenu_clicked()));
    // QAction *newQMainWindow = optionsMenu->addAction("New QMainWindow", this, SLOT(onClickCreate_newQMainWindow()));

    // QAction *saveFile = _optionsMenu->addAction(tr("Save File"));
    // QAction *saveFile = _optionsMenu->addAction("Save File", this, SLOT(on_saveFileButton_clicked()));
    // connect(_optionsMenu, SIGNAL(triggered(QAction*)), SLOT(on_pushButton_clicked(QAction*)));
    // connect(saveFile, SIGNAL(triggered(QAction*)), SLOT(on_pushButton_clicked(QAction*)));
    // connect(saveFile, &QAction::triggered, this, &MainWindow::on_pushButton_clicked);
    // connect(saveFile, SIGNAL(QAction::triggered), this, SLOT(MainWindow::on_pushButton_clicked(QAction*)));

    // this->menuBar()->addMenu(optionsMenu);
    /* _menuActions.push_back(clearText);
    _menuActions.push_back(openFile);
    _menuActions.push_back(createNewFile);
    _menuActions.push_back(saveFile);
    this->menuBar()->addSeparator(); */
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_quitButton_clicked() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    buttonSender->parentWidget()->window()->close();
}


void MainWindow::on_quitWindow_clicked() {
    QAction* action = qobject_cast<QAction*>(sender());
    action->parentWidget()->window()->close();
}


void MainWindow::on_quitMenu_clicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    QWidget *currentWindow = nullptr;
    int numActionWidgets = actionWidgets.length();
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        currentWindow = parent;
        if(parent->isWindow()) {
           QWidget *widgetTmp = parent;
           currentWindow = widgetTmp;
        }
    }
    currentWindow->parentWidget()->close();
}


void MainWindow::on_copy_text_click() {
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


void MainWindow::on_saveFileMenu_clicked() {
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


void MainWindow::on_textEdit_copyAvailable(bool b) {
}


void MainWindow::on_clear_text_click() {
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


void MainWindow::on_open_file_click() {
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


/* https://stackoverflow.com/questions/7284509/adding-slots-to-automatically-created-menu-items */
/* https://schneide.blog/2010/07/26/non-trivial-custom-data-in-qactions/ */
/* https://www.qtcentre.org/threads/12101-setData() */
void MainWindow::onClickCreate_newQMainWindow() {
    QMainWindow *mainWindow = new QMainWindow(this);

    QMenuBar *menu_bar = new QMenuBar(mainWindow);
    QMenu *optionsMenu = menu_bar->addMenu("&Options");
    QAction *quitQMainWindow = new QAction("Quit QMainWindow");
    QAction *wordCount = new QAction("Word Count");

    menu_bar->addAction(quitQMainWindow);
    menu_bar->addAction(wordCount);
    connect(quitQMainWindow, SIGNAL(triggered(bool)), this, SLOT(onClickQMainWindowQuit()));
    connect(wordCount, SIGNAL(triggered(bool)), this, SLOT(onClickWordCount()));
    mainWindow->setMenuBar(menu_bar);
    mainWindow->setObjectName("HELLO 2");

    QTextEdit *windowTextEdit = new QTextEdit(mainWindow);

    mainWindow->show();
    int count = 0;
    count += 1;

    _qMainWindowCount += 1;
}


void MainWindow::onClickWordCount() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    QWidget *currentWindow = nullptr;
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        if(parent->isWindow()) {
           QWidget *widgetTmp = parent;
           currentWindow = widgetTmp;
        }
    }
    QWidget *widget = nullptr;
    int place;
    QTextEdit* textEdit;
    QString plainText;
    if(currentWindow != nullptr) {
        QHash<QWidget*, int>::const_iterator i = _totalWindows.find(currentWindow);
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
    } else {
        QMessageBox msgBox;
        msgBox.setText(" current window is null ptr");
        msgBox.exec();
    }
}


void MainWindow::on_wordCountMenu_clicked() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    QWidget *currentWindow = nullptr;
    int numActionWidgets = actionWidgets.length();
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        currentWindow = parent;
        if(parent->isWindow()) {
           QWidget *widgetTmp = parent;
           currentWindow = widgetTmp;
        }
    }
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


// https://stackoverflow.com/questions/4046839/how-to-get-sender-widget-with-a-signal-slot-mechanism
void MainWindow::onClickQMainWindowQuit() {
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        if(parent->isWindow()) {
           QWidget *widgetTmp = parent;
           int so = 1;
           so += 1;
           widgetTmp->close();
        }
    }
    int count = 0;
    count += 1;
}


QWidget* MainWindow::_getCurrentWindow(QAction *actionSender, QWidget *currentWindow) {
    QList<QWidget*> actionWidgets = actionSender->associatedWidgets();
    for(int i = 0; i < actionWidgets.length(); i++) {
        QWidget *tmp = actionWidgets.at(i);
        QWidget *parent = tmp->parentWidget();
        currentWindow = parent;
    }
    return currentWindow;
}


void MainWindow::on_searchReplaceMenu() {
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


void MainWindow::on_click_create_new_file() {
    QWidget *window = new QWidget;
    window->setAccessibleName(QString::number(_windowCount));
    window->setObjectName("HELLO 2");

    QVBoxLayout *vbox = new QVBoxLayout();
    window->setLayout(vbox);

    QMenuBar *menu_bar = new QMenuBar(window);

    QMenu *optionsMenu = menu_bar->addMenu(tr("&Options"));
    QAction *clearText = optionsMenu->addAction("Clear Text", this, SLOT(on_clear_text_click()));
    QAction *copyText = optionsMenu->addAction("Copy Text", this, SLOT(on_copy_text_click()));
    QAction *openFile = optionsMenu->addAction("Open File", this, SLOT(on_open_file_click()));
    QAction *createNewFile = optionsMenu->addAction("Create New File", this, SLOT(on_click_create_new_file()));
    QAction *saveFile = optionsMenu->addAction("Save File", this, SLOT(on_saveFileMenu_clicked()));
    QAction *wordCount = optionsMenu->addAction("Word Count", this, SLOT(on_wordCountMenu_clicked()));
    QAction *searchReplaceMenuItem = optionsMenu->addAction("Search and Replace", this, SLOT(on_searchReplaceMenu()));
    QAction *quitMenuOption = optionsMenu->addAction("Quit", this, SLOT(on_quitMenu_clicked()));

    menu_bar->addMenu(optionsMenu);
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
    window->setAccessibleName(QString::number(_windowCount));
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
