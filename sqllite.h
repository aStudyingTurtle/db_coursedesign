#ifndef SQLLITE_H
#define SQLLITE_H
#include <QtSql/QSqlQuery>
class Sqllite {
public:
  QSqlQuery *sql_query;
  Sqllite();
  void flush();
};

#endif // SQLLITE_H
