#include "mainwindow.h"
#include "sushelist.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent, QSqlQuery *sql)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->GetQuery(sql);
  add_detail.Setdetailrecord(&detailrecord);
  QObject::connect(&detailrecord, SIGNAL(dofreshparent()), &add_detail,
                   SLOT(do_refresh()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_8_clicked() {
  sushelist.GetQuery(sql_query);
  detailrecord.GetQuery(sql_query);
  sushelist.flush();
  sushelist.show();
}
void MainWindow::GetQuery(QSqlQuery *sql) { this->sql_query = sql; }
void MainWindow::on_pushButton_7_clicked() {
  add_sushe.GetQuery(sql_query);
  add_sushe.show();
}
void MainWindow::flushtable() {
  QStandardItemModel *model1 = new QStandardItemModel(this);
  QStandardItemModel *model2 = new QStandardItemModel(this);
  model1->setColumnCount(4);
  model1->setHeaderData(0, Qt::Horizontal, "检查ID");
  model1->setHeaderData(1, Qt::Horizontal, "日期");
  model1->setHeaderData(2, Qt::Horizontal, "检查名");
  model1->setHeaderData(3, Qt::Horizontal, "检查部门");
  model2->setColumnCount(4);
  model2->setHeaderData(0, Qt::Horizontal, "记录ID");
  model2->setHeaderData(1, Qt::Horizontal, "宿舍");
  model2->setHeaderData(2, Qt::Horizontal, "检查人");
  model2->setHeaderData(3, Qt::Horizontal, "得分");
  sql_query->exec("select * from checks");
  int i = 0, j = 0;
  if (!sql_query->exec()) {
    qDebug() << sql_query->lastError();
  } else {
    while (sql_query->next()) {
      int checkid = sql_query->value(0).toInt();
      QString date = sql_query->value(1).toDate().toString("yyyy-MM-dd");
      QString checkname = sql_query->value(2).toString();
      QString department = sql_query->value(3).toString();
      model1->setItem(i, 0, new QStandardItem(QString::number(checkid)));
      model1->setItem(i, 1, new QStandardItem(date));
      model1->setItem(i, 2, new QStandardItem(checkname));
      model1->setItem(i, 3, new QStandardItem(department));
      i++;
    }
  }
  sql_query->exec(
      QString("select * from dafenevent_view where checkid=%1").arg(checksnow));
  if (!sql_query->exec()) {
    qDebug() << sql_query->lastError();
  } else {
    while (sql_query->next()) {
      int checkeventid = sql_query->value(0).toInt();
      QString room =
          sql_query->value(5).toString() + "#" + sql_query->value(6).toString();
      QString checker = sql_query->value(4).toString();
      QString score = QString::number(100 - sql_query->value(2).toInt());
      model2->setItem(j, 0, new QStandardItem(QString::number(checkeventid)));
      model2->setItem(j, 1, new QStandardItem(room));
      model2->setItem(j, 2, new QStandardItem(checker));
      model2->setItem(j, 3, new QStandardItem(score));
      j++;
    }
  }
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_2->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  model1->setRowCount(i);
  model2->setRowCount(j);
  ui->tableView->setModel(model1);
  ui->tableView_2->setModel(model2);
}

void MainWindow::on_pushButton_4_clicked() {
  int checksid = ui->lineEdit_2->text().toInt();
  this->checksnow = checksid;
  ui->lineEdit_2->clear();
  this->flushtable();
}

void MainWindow::on_pushButton_clicked() {
  // 7部门 9检查名
  if (!sql_query->exec(QString("INSERT INTO checks(data,checkname,department) "
                               "VALUES(\"%1\", \"%2\", \"%3\");")
                           .arg(ui->dateEdit->date().toString("yyyy/MM/dd"))
                           .arg(ui->lineEdit_9->text())
                           .arg(ui->lineEdit_7->text()))) {
    qDebug() << sql_query->lastError();
  } else {
    qDebug() << "inserted!";
  }
  ui->lineEdit_7->clear();
  ui->lineEdit_9->clear();
  this->flushtable();
}

void MainWindow::on_pushButton_3_clicked() {
  //楼4 房间5
  //检查id8 打分人6
  add_detail.GetQuery(sql_query);
  int louid = ui->lineEdit_4->text().toInt();
  ui->lineEdit_4->clear();
  int roomid = ui->lineEdit_5->text().toInt();
  ui->lineEdit_5->clear();
  int checkid = ui->lineEdit_8->text().toInt();
  ui->lineEdit_8->clear();
  QString checker = ui->lineEdit_6->text();
  ui->lineEdit_6->clear();
  int susheid = 0;
  sql_query->exec(QString("select * from sushe where louid=%1 and roomid=%2")
                      .arg(louid)
                      .arg(roomid));
  if (!sql_query->exec()) {
    qDebug() << sql_query->lastError();
    QMessageBox::information(this, "警告", "请检查宿舍是否存在!");
  } else {
    if (sql_query->next()) {
      susheid = sql_query->value(0).toInt();
      sql_query->exec(
          QString("INSERT INTO checkevent (susheid, checkid,checker) "
                  "VALUES (%1, %2, \"%3\");")
              .arg(susheid)
              .arg(checkid)
              .arg(checker));
      qDebug() << QString("INSERT INTO checkevent (susheid, checkid,checker) "
                          "VALUES (%1, %2, \"%3\");")
                      .arg(susheid)
                      .arg(checkid)
                      .arg(checker);
      sql_query->exec("select last_insert_rowid() from checkevent;");
      sql_query->first();
      int checkeventid = 0;
      checkeventid = sql_query->value(0).toInt();
      qDebug() << checkeventid;
      //下一步操作：向form传数据
      add_detail.Setinfo(checkeventid);
      add_detail.flushtable();
      this->flushtable();
      add_detail.show();
    } else {
      QMessageBox::information(this, "警告", "请检查宿舍是否存在!");
    }
  }
}

void MainWindow::on_pushButton_9_clicked() {
  int checkid = ui->lineEdit_10->text().toInt();
  ui->lineEdit_10->clear();
  sql_query->exec(QString("delete from checks where checkid=%1").arg(checkid));
  //  有点小问题，不过数据量不大，冗余可以接受
  this->flushtable();
}

void MainWindow::on_pushButton_5_clicked() {
  int checkeventid = ui->lineEdit_3->text().toInt();
  ui->lineEdit_3->clear();
  sql_query->exec(QString("delete from checkevent where checkeventid=%1")
                      .arg(checkeventid));
  this->flushtable();
}

void MainWindow::on_pushButton_6_clicked() {
  add_detail.GetQuery(sql_query);
  int checkeventid = ui->lineEdit_3->text().toInt();
  ui->lineEdit_3->clear();
  add_detail.Setinfo(checkeventid);
  add_detail.flushtable();
  add_detail.show();
}

void MainWindow::on_pushButton_2_clicked() {
  int score = ui->lineEdit->text().toInt();
  ui->lineEdit->clear();
  sql_query->exec(
      QString("select louid,roomid from sushe where score<%1").arg(score));
  QString res = "";
  while (sql_query->next()) {
    res += QString("%1#%2 ")
               .arg((sql_query->value(0).toInt()))
               .arg(sql_query->value(0).toInt());
  }
  QMessageBox::information(this, "结果", res);
}
