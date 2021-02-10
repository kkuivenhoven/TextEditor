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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
