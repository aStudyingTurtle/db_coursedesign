#include "formdetail.h"
#include "ui_formdetail.h"
#include <QMessageBox>
#include <QSqlError>
#include <QStandardItemModel>
FormDetail::FormDetail(QWidget *parent)
    : QWidget(parent), ui(new Ui::FormDetail) {
  ui->setupUi(this);
  susheid = 0;
  checkid = 0;
  checker = new QString("");
}
void FormDetail::Setdetailrecord(DetailRecord *detailrecord) {
  this->detailrecord = detailrecord;
}
void FormDetail::flushtable() {
  QStandardItemModel *model = new QStandardItemModel(this);
  model->setColumnCount(3);
  model->setHeaderData(0, Qt::Horizontal, "记录ID");
  model->setHeaderData(1, Qt::Horizontal, "扣分原因");
  model->setHeaderData(2, Qt::Horizontal, "扣分");
  sql_query->exec(QString("select * from checkdetail where checkeventid=%1")
                      .arg(this->checkeventid));
  int i = 0;
  if (!sql_query->exec()) {
    qDebug() << sql_query->lastError();
  } else {
    while (sql_query->next()) {
      int checkcontextid = sql_query->value(0).toInt();
      QString reason = sql_query->value(1).toString();
      int score = sql_query->value(2).toInt();
      model->setItem(i, 0, new QStandardItem(QString::number(checkcontextid)));
      model->setItem(i, 1, new QStandardItem(reason));
      model->setItem(i, 2, new QStandardItem(QString::number(score)));
      i++;
    }
  }
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  model->setRowCount(i);
  ui->tableView->setModel(model);
}
FormDetail::~FormDetail() { delete ui; }
void FormDetail::GetQuery(QSqlQuery *sql) { this->sql_query = sql; }
void FormDetail::Setinfo(int susheid, int checkid, QString *checker) {
  this->susheid = susheid;
  this->checkid = checkid;
  this->checker = checker;
  this->flag = 1;
}
void FormDetail::do_refresh() { this->flushtable(); }
void FormDetail::Setinfo(int checkdetailid) {
  this->checkeventid = checkdetailid;
  this->flag = 2;
}

void FormDetail::on_pushButton_2_clicked() { this->hide(); }

void FormDetail::on_pushButton_clicked() {
  detailrecord->getCheckeventid(checkeventid);
  detailrecord->GetQuery(sql_query);
  detailrecord->show();
}

void FormDetail::on_pushButton_3_clicked() {
  int checkdetailid = ui->lineEdit->text().toInt();
  ui->lineEdit->clear();
  if (sql_query->exec(QString("delete from checkdetail where checkdetailid=%1;")
                          .arg(checkdetailid))) {
    QMessageBox::information(this, "通知", "删除成功!");
  } else {
    QMessageBox::information(this, "通知", "删除失败!");
  }
  this->flushtable();
}
