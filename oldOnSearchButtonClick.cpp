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
        lineEdit = _searchBarRecord[place];
        QString wordToHighLight = lineEdit->text();

        QStringList list = plainText.split(" ");
        QStringList trimmedList;
        for(int i = 0; i < list.size(); i++) {
            QString tmp = list.at(i);
            trimmedList << tmp.trimmed();
        }
        QStringList alteredList;
        for(int i = 0; i < trimmedList.size(); i++) {
            if(trimmedList.at(i) == wordToHighLight.trimmed()) {
                QString tmp = "<span style='background-color: red;'>";
                tmp += trimmedList.at(i);
                tmp += "</span>";
                alteredList << tmp;
            } else {
                alteredList << trimmedList.at(i);
            }
        }
        QString newList = alteredList.join(" ");
        textEdit->setHtml(newList);
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
        lineEdit = _searchBarRecord[place];
        QString wordToHighLight = lineEdit->text();

        QStringList list = plainText.split(" ");
        QStringList alteredList;
        for(int i = 0; i < trimmedList.size(); i++) {
            if(trimmedList.at(i) == wordToHighLight.trimmed()) {
                QString tmp = "<span style='background-color: red;'>";
                tmp += trimmedList.at(i);
                tmp += "</span>";
                alteredList << tmp;
            } else {
                alteredList << trimmedList.at(i);
            }
        }
        QString newList = alteredList.join(" ");
        textEdit->setHtml(newList);
    }
}
