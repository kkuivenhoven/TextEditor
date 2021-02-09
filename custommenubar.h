#ifndef CUSTOMMENUBAR_H
#define CUSTOMMENUBAR_H
#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QPoint>
#include "mainwindow.h"

class CustomMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit CustomMenuBar(int qMainWindowCount);

private slots:
    void onClickQMainWindow(QAction* action);
};

#endif // CUSTOMMENUBAR_H
