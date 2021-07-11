#include "detailrecord.h"
#include "ui_detailrecord.h"
#include <QSqlError>
DetailRecord::DetailRecord(QWidget *parent)
    : QWidget(parent), ui(new Ui::DetailRecord) {
  ui->setupUi(this);
}

DetailRecord::~DetailRecord() { delete ui; }
void DetailRecord::getCheckeventid(int checkeventid) {
  qDebug() << checkeventid;
  this->checkeventid = checkeventid;
}
void DetailRecord::GetQuery(QSqlQuery *sql) { this->sql_query = sql; }

void DetailRecord::on_pushButton_clicked() {
  int score = ui->lineEdit->text().toInt();
  ui->lineEdit->clear();
  QString reason = ui->lineEdit_2->text();
  ui->lineEdit_2->clear();
  if (!sql_query->exec(
          QString("INSERT INTO checkdetail(reason,koufen,checkeventid) "
                  "VALUES(\"%1\", %2, %3);")
              .arg(reason)
              .arg(score)
              .arg(checkeventid))) {
    qDebug() << sql_query->lastError();
  } else {
    qDebug() << "inserted!";
  }
  emit dofreshparent();
  this->hide();
}
