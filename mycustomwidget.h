#ifndef MYCUSTOMWIDGET_H
#define MYCUSTOMWIDGET_H


#include <QWidget>
#include <QCloseEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QObject>
#include <QMouseEvent>
#include <QHash>
#include <QApplication>
#include <QClipboard>
#include <QFileDialog>
#include <QTextStream>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QString>
#include <QScrollBar>
#include <QTableView>
#include <QAbstractItemView>
#include <QTableWidget>
#include <QPlainTextEdit>


class MyCustomWidget : public QWidget
{
    Q_OBJECT

    QHash<int, QTextEdit*> _textEditPerWindow;
    QHash<int, QTextEdit*> _columnPerWindow;
    QHash<QWidget*, int> _totalWindows;
    QHash<int, QLineEdit*> _searchBarRecord;
    int _windowCount = 0;
    QString _lineNumbers = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";

public:
    MyCustomWidget(QWidget *parent = 0);

public slots:
    void quitOptionClicked();
    void searchBtnClicked();
    void clearBtnClicked();
    void createNewFileClicked();
    void wordCountClicked();
    void clearTextClicked();
    void copyTextClicked();
    void saveFileClicked();
    void openFileClicked();
    void searchReplaceClicked();
    void cutAndCopyToClipboardClicked();

private:
    QWidget* _getCurrentWindow(QAction *actionSender, QWidget *currentWindow);

};

#endif // MYCUSTOMWIDGET_H
