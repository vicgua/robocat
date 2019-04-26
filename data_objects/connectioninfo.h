#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include <QString>

struct ConnectionInfo {
    QString dbDriver;
    QString hostname;
    int port;
    QString database;
    QString username;
    QString password;
};

#endif // CONNECTIONINFO_H
