#ifndef SERVERLOGENTITIES_H
#define SERVERLOGENTITIES_H

#include <QtSql/QSqlDatabase>
#include <QList>
#include "logentity.h"

class ServerLogEntities
{
public:
    ServerLogEntities();
    ~ServerLogEntities();
    const int open();
    void close();

    QList<LogEntity *> m_logsList;
    int logsListSize() {return m_logsList.size();}

private:
    QSqlDatabase m_db;
};

#endif // SERVERLOGENTITIES_H
