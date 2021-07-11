#ifndef DETAILRECORD_H
#define DETAILRECORD_H
#include <QSqlQuery>
#include <QWidget>
namespace Ui {
class DetailRecord;
}

class DetailRecord : public QWidget {
  Q_OBJECT

public:
  QSqlQuery *sql_query;
  int checkeventid = 0;
  void getCheckeventid(int checkeventid);
  void GetQuery(QSqlQuery *sql);
  explicit DetailRecord(QWidget *parent = nullptr);
  ~DetailRecord();

private slots:
  void on_pushButton_clicked();

private:
  Ui::DetailRecord *ui;
signals:
  void dofreshparent();
};

#endif // DETAILRECORD_H
