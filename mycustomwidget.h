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
#include <QWidgetList>


class MyCustomWidget : public QWidget
{
    Q_OBJECT

    QHash<int, QTextEdit*> _textEditPerWindow;
    QHash<int, QTextEdit*> _columnPerWindow;
    QHash<QWidget*, int> _totalWindows;
    QHash<int, QLineEdit*> _searchBarRecord;
    int _windowCount = 0;

public:
    MyCustomWidget(QWidget *parent = 0);

public slots:
    void quitProgram();
    void closeWindowOptionClicked();
    void searchBtnClicked();
    void clearBtnClicked();
    void createNewFileClicked();
    void wordCountClicked();
    void saveFileClicked();
    void openFileClicked();
    void searchReplaceClicked();
    void cutAndCopyToClipboardClicked();

private:
    QWidget* _getCurrentWindow(QAction *actionSender, QWidget *currentWindow);
    void _warningMessage(QWidget *widgetToClose);
    void _clearTextClicked();
    void _copyTextClicked();

};

#endif // MYCUSTOMWIDGET_H
