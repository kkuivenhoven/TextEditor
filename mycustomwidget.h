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


class MyCustomWidget : public QWidget
{
    Q_OBJECT

    QHash<int, QTextEdit*> _textEditPerWindow;
    QHash<QWidget*, int> _totalWindows;
    QHash<int, QLineEdit*> _searchBarRecord;
    int _windowCount = 0;

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

private:
    QWidget* _getCurrentWindow(QAction *actionSender, QWidget *currentWindow);

};

#endif // MYCUSTOMWIDGET_H