#ifndef CONNECTDIALOG_HH
#define CONNECTDIALOG_HH

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

private slots:
    void on_dbmsInp_currentIndexChanged(const QString &newDbms);
    void on_buttonBox_accepted();

private:
    Ui::ConnectDialog *ui;
    QString cDbms;
    bool hasHost;
    bool hasDatabase;
    bool hasUsername;
    bool hasPassword;

    void updateFields();
    bool sanityCheck(QStringList &error);
};

#endif // CONNECTDIALOG_HH
