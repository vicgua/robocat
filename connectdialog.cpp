#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    on_dbmsInp_currentIndexChanged(ui->dbmsInp->currentText());
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_dbmsInp_currentIndexChanged(const QString &newDbms)
{
    if (newDbms == "PostgreSQL") {
        cDbms = "QPSQL";
        hasHost = true;
        hasDatabase = true;
        hasUsername = true;
        hasPassword = true;
    } else if (newDbms == "SQLite") {
        cDbms = "QSQLITE";
        hasHost = false;
        hasDatabase = true;
        hasUsername = false;
        hasPassword = false;
    } else {
        QDebug(QtFatalMsg) << "Invalid DBMS: " << newDbms;
        throw "Invalid DBMS";
    }
    updateFields();
}

void ConnectDialog::on_buttonBox_accepted()
{
    QStringList errors;
    if (!sanityCheck(errors)) {
        QDebug(QtWarningMsg) << "Failed sanity check:";
        foreach (const auto &err, errors) {
            QDebug(QtWarningMsg) << err;
        }
        QMessageBox errorDialog(this);
        errorDialog.setIcon(QMessageBox::Warning);
        if (errors.length() == 1) {
            errorDialog.setText(errors.at(0));
        } else {
            QString msg("S'han detectat els següents errors:\n - ");
            msg.append(errors.join("\n - "));
            errorDialog.setText(msg);
        }
        errorDialog.exec();
        return;
    }
    close();
    emit accepted();
}

void ConnectDialog::updateFields()
{
    ui->hostLab->setEnabled(hasHost);
    ui->hostInp->setEnabled(hasHost);

    ui->dbLab->setEnabled(hasDatabase);
    ui->dbInp->setEnabled(hasDatabase);

    ui->userLab->setEnabled(hasUsername);
    ui->userInp->setEnabled(hasUsername);

    ui->passwordLab->setEnabled(hasPassword);
    ui->passwordInp->setEnabled(hasPassword);
}

bool ConnectDialog::sanityCheck(QStringList &error)
{
    bool ok = true;
    if (hasHost && ui->hostInp->text().isEmpty()) {
        ok = false;
        error.append("`Host` buit però necessari");
    }
    if (hasDatabase && ui->dbInp->text().isEmpty()) {
        ok = false;
        error.append("`Base de dades` buida però necessària");
    }
    if (hasUsername && ui->userInp->text().isEmpty()) {
        ok = false;
        error.append("`Nom d'usuari` buit però necessari");
    }
    // La contrasenya pot no ser necessària
    return ok;
}
