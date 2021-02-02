// in main window constructor:
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

