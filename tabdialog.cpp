#include "tabdialog.h"

TabDialog::TabDialog(const QString &fileName, QWidget *parent) : QDialog(parent)
{
    QFileInfo fileInfo(fileName);

    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
    tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permission"));
    tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Appolication"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
}
