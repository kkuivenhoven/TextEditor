#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QTabWidget>
#include <QTabBar>
#include <QtWidgets>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QDir>
#include <QStackedLayout>
#include <QWidget>
#include <QList>
#include <QHash>
#include <QLayout>
#include <QDialog>
#include <QLineEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QRegExp>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>
#include <QTextDocument>
#include <QGuiApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QEvent>
#include <QObject>

#include "mycustomwidget.h""

/* https://het.as.utexas.edu/HET/Software/html/richtext-syntaxhighlighter.html */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    // Q_OBJECT

    QTabBar *_tabBar;
    int _tabCount;
    QList<QString> _tabList;
    QList<QAction*> _menuActions;
    QTabWidget *_tabWidget;
    QMenu *_optionsMenu;
    QList<QWidget*> _windowList;
    QList<QVBoxLayout*> _vBoxList;
    int _windowCount;
    QHash<int, QTextEdit*> _textEditPerWindow;
    QHash<QWidget*, int> _totalParentWindows;
    QHash<int, QLineEdit*> _searchBarRecord;
    int _qMainWindowCount;

public:
    QHash<QWidget*, int> _totalWindows;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    // void closeEvent(QCloseEvent *event) override;

private slots:
    void on_saveFileButton_clicked();
    void on_quitButton_clicked();
    void on_textEdit_copyAvailable(bool b);
    void on_clear_text_click();
    void on_open_file_click();
    void on_click_create_new_file();
    void on_saveFileMenu_clicked();

    void on_searchReplace_clicked();
    void on_searchButton_clicked();
    void on_clearSearch_clicked();
    void on_wordCount_clicked();
    void on_wordCountMenu_clicked();

    void on_quitWindow_clicked();
    void onClickCreate_newQMainWindow();
    void onClickQMainWindowQuit();
    void onClickWordCount();
    void on_quitMenu_clicked();
    void on_searchReplaceMenu();

    void on_copy_text_click();

private:
    Ui::MainWindow *ui;
    QWidget* _getCurrentWindow(QAction *actionSender, QWidget *currentWindow);
    bool closeWindowEvent();

};

#endif // MAINWINDOW_H
