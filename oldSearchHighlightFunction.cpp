    if(widget != nullptr) {
        textEdit = _textEditPerWindow[place];
        plainText = textEdit->toPlainText();

        /* int begin = 2;
        int end = 5;
        QTextCharFormat fmt;
        fmt.setBackground(Qt::yellow);
        QTextCursor cursor(textEdit->document());
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
        textEdit->setHtml("<a href='http://www.w3schools.com/'>Link!</a>aah");
        */

        // QStringList list = plainText.split(QRegExp("should"), QString::SkipEmptyParts);
        QStringList list = plainText.split(" ");
        QStringList alteredList;
        for(int i = 0; i < list.size(); i++) {
            if(list.at(i) == "should") {
                QString tmp = "<span style='color: red;'>";
                tmp += list.at(i);
                tmp += "</span>";
                alteredList << tmp;
            } else {
                alteredList << list.at(i);
            }
        }
        QString newList = alteredList.join(" ");
        textEdit->setHtml(newList);
        // QTextDocument *doc = textEdit->document();
        // HighLighter *highLighter = new HighLighter(textEdit->document());
        // QSyntaxHighlighter *synHigh = new QSyntaxHighlighter(doc);
        /* for(int i = 0; i < plainText.length(); i++) {
            if((i >= 5) && (i <= 10)) {
                // QSyntaxHighlighter::setFormat(i, 1, Qt::green);
                // synHigh->setFormat(i, 1, Qt::green);
            }
        }
        // textEdit->setPlainText(plainText);

        textEdit->setTextBackgroundColor(QColor(255,0,0));
        textEdit->setPlainText(" Only should be highlighted ");
        QList<QTextEdit::ExtraSelection> extraSelections;
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        extraSelections.append(selection);
        */

        /* QTextCharFormat myClassFormat;
        myClassFormat.setFontWeight(QFont::Bold);
        myClassFormat.setForeground(Qt::darkMagenta);

        QRegularExpression expression("should");
        QRegularExpressionMatchIterator i = expression.globalMatch(plainText);
        while(i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QSyntaxHighlighter::setFormat(match.capturedStart(), match.capturedLength(), &myClassFormat);
        }
        textEdit->mergeCurrentCharFormat(myClassFormat); */
    }
}
