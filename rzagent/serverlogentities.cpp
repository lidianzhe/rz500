#include "serverlogentities.h"

#include <QCoreApplication>
#include <QtDebug>
#include <QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QStringList>

ServerLogEntities::ServerLogEntities()
{

}

ServerLogEntities::~ServerLogEntities()
{
    if (m_logsList.size() != 0) {
        for (int i = 0; i < m_logsList.size(); i++) {
            delete m_logsList.at(i);
        }
        m_logsList.clear();
    }
}

const int ServerLogEntities::open()
{
    qDebug() << "DataBase::open() called";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
#if defined(DESKTOP)
    m_db.setDatabaseName("~/ServiceLog.db");
#else
    m_db.setDatabaseName("/usr/local/share/CMITECH/ServiceLog.db");
#endif

    if(!m_db.open()){
        qDebug()<<"open DataBase fail:"<<m_db.lastError().databaseText();
        return m_db.lastError().number();
    }
    return 0;
}
