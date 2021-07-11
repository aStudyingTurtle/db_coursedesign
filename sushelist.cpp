#include "sushelist.h"
#include "ui_sushelist.h"
#include <QSqlError>
#include <QStandardItemModel>
Sushelist::Sushelist(QWidget *parent) : QWidget(parent), ui(new Ui::Sushelist) {
  ui->setupUi(this);
}

Sushelist::~Sushelist() { delete ui; }
void Sushelist::flush() {
  QStandardItemModel *model = new QStandardItemModel(this);
  /*设置列字段名*/
  model->setColumnCount(4);
  model->setHeaderData(0, Qt::Horizontal, "宿舍号");
  model->setHeaderData(1, Qt::Horizontal, "楼号");
  model->setHeaderData(2, Qt::Horizontal, "房间号");
  model->setHeaderData(3, Qt::Horizontal, "上次得分");
  sql_query->exec("select * from sushe");
  int i = 0;
  if (!sql_query->exec()) {
    qDebug() << sql_query->lastError();
  } else {
    while (sql_query->next()) {
      int susheid = sql_query->value(0).toInt();
      int roomid = sql_query->value(1).toInt();
      int louid = sql_query->value(2).toInt();
      int score = sql_query->value(3).toInt();
      model->setItem(i, 0, new QStandardItem(QString::number(susheid)));
      model->setItem(i, 1, new QStandardItem(QString::number(roomid)));
      model->setItem(i, 2, new QStandardItem(QString::number(louid)));
      model->setItem(i, 3, new QStandardItem(QString::number(score)));
      i++;
    }
  }
  model->setRowCount(i);
  ui->tableView->setModel(model);
}
void Sushelist::GetQuery(QSqlQuery *sql) { this->sql_query = sql; }
