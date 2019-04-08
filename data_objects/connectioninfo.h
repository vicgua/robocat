#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include <QObject>
#include <QString>

class ConnectionInfo {
    Q_GADGET
    Q_PROPERTY(QString dbDriver MEMBER dbDriver)
    Q_PROPERTY(QString hostname MEMBER hostname)
    Q_PROPERTY(QString database MEMBER database)
    Q_PROPERTY(QString username MEMBER username)
    Q_PROPERTY(QString password MEMBER password)
public:
    QString dbDriver;
    QString hostname;
    QString database;
    QString username;
    QString password;
};

#endif // CONNECTIONINFO_H
