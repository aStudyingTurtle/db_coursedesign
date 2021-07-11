#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtSql/QSqlQuery>
namespace Ui {
class Form;
}

class Form : public QWidget {
  Q_OBJECT

public:
  QSqlQuery *sql_query;
  void GetQuery(QSqlQuery *sql);
  explicit Form(QWidget *parent = nullptr);
  ~Form();

private slots:
  void on_pushButton_clicked();

private:
  Ui::Form *ui;
};

#endif // FORM_H
