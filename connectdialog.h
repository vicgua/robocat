#ifndef CONNECTDIALOG_HH
#define CONNECTDIALOG_HH

#include <QDialog>
#include "data_objects/connectioninfo.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

signals:
    void databaseSet(const ConnectionInfo &ci);

private:
    Ui::ConnectDialog *ui;
    QString cDriver;
    bool hasHost;
    bool hasDatabase;
    bool hasUsername;
    bool hasPassword;

    void updateFields();
    bool sanityCheck(QStringList &errors) const;

private slots:
    void on_dbmsInp_currentIndexChanged(const QString &newDbms);
    void on_buttonBox_accepted();
};

#endif // CONNECTDIALOG_HH
