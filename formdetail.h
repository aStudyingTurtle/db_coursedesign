#ifndef FORMDETAIL_H
#define FORMDETAIL_H
#include "detailrecord.h"
#include <QString>
#include <QWidget>
#include <QtSql/QSqlQuery>
namespace Ui {
class FormDetail;
}

class FormDetail : public QWidget {
  Q_OBJECT
private:
  DetailRecord *detailrecord = nullptr;

public:
  int score = 0;
  int susheid;
  int checkid;
  int checkeventid = 0;
  int flag = 1;
  QString *checker;
  QSqlQuery *sql_query;
  void GetQuery(QSqlQuery *sql);
  explicit FormDetail(QWidget *parent = nullptr);
  ~FormDetail();
  void Setinfo(int susheid, int checkid, QString *checker);
  void Setinfo(int checkeventid);
  void flushtable();
  void Setdetailrecord(DetailRecord *detailrecord);
private slots:
  void do_refresh();

  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

private:
  Ui::FormDetail *ui;
};

#endif // FORMDETAIL_H
