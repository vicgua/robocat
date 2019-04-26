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
        if (cDriver == "PSQL") return;
        cDriver = "QPSQL";
        hasHost = true;
        hasPort = true;
        hasDatabase = true;
        hasUsername = true;
        hasPassword = true;
    } else if (newDbms == "SQLite") {
        if (cDriver == "QSQLITE") return;
        cDriver = "QSQLITE";
        hasHost = false;
        hasPort = false;
        hasDatabase = true;
        hasUsername = false;
        hasPassword = false;
    } else {
        qFatal("Invalid DBMS: %s", newDbms.toLatin1().constData());
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
    ci.port = ui->portInp->value();
    ci.database = ui->dbInp->text();
    ci.username = ui->userInp->text();
    ci.password = ui->passwordInp->text();
    emit databaseSet(ci);
    emit accept();
}

void ConnectDialog::updateFields()
{
    ui->hostLab->setEnabled(hasHost);
    ui->hostInp->setEnabled(hasHost);

    ui->portLab->setEnabled(hasPort);
    ui->portInp->setEnabled(hasPort);

    ui->dbLab->setEnabled(hasDatabase);
    ui->dbInp->setEnabled(hasDatabase);

    ui->userLab->setEnabled(hasUsername);
    ui->userInp->setEnabled(hasUsername);

    ui->passwordLab->setEnabled(hasPassword);
    ui->passwordInp->setEnabled(hasPassword);

    if (cDriver == "QPSQL" && ui->dbInp->text() == "robocat.db") {
        ui->dbInp->setText("robocat");
    } else if (cDriver == "QSQLITE" && ui->dbInp->text() == "robocat") {
        ui->dbInp->setText("robocat.db");
    }
}

bool ConnectDialog::sanityCheck(QStringList &errors) const
{
    bool ok = true;
    if (hasHost && ui->hostInp->text().isEmpty()) {
        ok = false;
        errors.append("`Host` buit però necessari");
    }
    if (hasDatabase && ui->dbInp->text().isEmpty()) {
        ok = false;
        errors.append("`Base de dades` buida però necessària");
    }
    if (hasUsername && ui->userInp->text().isEmpty()) {
        ok = false;
        errors.append("`Nom d'usuari` buit però necessari");
    }
    // La contrasenya pot no ser necessària
    return ok;
}
