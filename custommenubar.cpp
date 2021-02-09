#include "custommenubar.h"


CustomMenuBar::CustomMenuBar(int qMainWindowCount) {
    /* addMenu("Test");
    addMenu("1");
    addMenu("2");
    addMenu("3");
    addAction("okay"); */
    QMenu *newMenu = new QMenu("Options");
    QAction *action = newMenu->addAction("Quit QMainWindow", this, SLOT(onClickQMainWindow(QAction*)));
    action->setData(qMainWindowCount);
    newMenu->addAction("TestTwo");
    addMenu(newMenu);
}


/* https://stackoverflow.com/questions/14389058/is-there-a-way-to-know-what-activated-qaction */
/* https://www.qtcentre.org/threads/14603-Problem-to-recover-an-object-via-a-QAction */
void CustomMenuBar::onClickQMainWindow(QAction* action) {
    QMessageBox msgBox;
    msgBox.setText(" hello im working ");
    msgBox.exec();
    // action->parentWidget()->window()->close();
    /*
    QAction *actionSender = qobject_cast<QAction*>(sender());
    QWidget *parentWidget = actionSender->parentWidget();
    QWidget *window = parentWidget->window();
    int count = 0;
    count += 1;
    window->close();
    */
}

