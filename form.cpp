#include "form.h"
#include "ui_form.h"
#include <QMessageBox>
#include <QString>
Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}

Form::~Form() { delete ui; }
void Form::GetQuery(QSqlQuery *sql) { this->sql_query = sql; }

void Form::on_pushButton_clicked() {
  int louid = ui->lineEdit->text().toInt();
  int roomid = ui->lineEdit_2->text().toInt();
  sql_query->exec(QString("INSERT INTO sushe (louid, roomid) VALUES (%1, %2);")
                      .arg(QString::number(louid))
                      .arg(QString::number(roomid)));
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  this->hide();
  QMessageBox::information(this, "成功", "添加成功!");
}
