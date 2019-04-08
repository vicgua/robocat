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
        cDriver = "QPSQL";
        hasHost = true;
        hasDatabase = true;
        hasUsername = true;
        hasPassword = true;
    } else if (newDbms == "SQLite") {
        cDriver = "QSQLITE";
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
    ConnectionInfo ci;
    ci.dbDriver = cDriver;
    ci.hostname = ui->hostInp->text();
    ci.database = ui->dbInp->text();
    ci.username = ui->userInp->text();
    ci.password = ui->passwordInp->text();
    close();
    emit databaseSet(ci);
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
