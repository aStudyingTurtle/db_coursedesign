#ifndef SUSHELIST_H
#define SUSHELIST_H

#include <QWidget>
#include <QtSql/QSqlQuery>
namespace Ui {
class Sushelist;
}

class Sushelist : public QWidget {
  Q_OBJECT

public:
  QSqlQuery *sql_query;
  void flush();
  explicit Sushelist(QWidget *parent = nullptr);
  ~Sushelist();
  void GetQuery(QSqlQuery *sql);

private:
  Ui::Sushelist *ui;
};

#endif // SUSHELIST_H
