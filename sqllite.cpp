#include "sqllite.h"
#include <QCoreApplication>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtWidgets/QApplication>
Sqllite::Sqllite() {
  //建立并打开数据库
  QSqlDatabase database;
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("MyDataBase.db");
  if (!database.open()) {
    qDebug() << "Error: Failed to connect database.";
  } else {
    qDebug() << "Succeed to connect database.";
  }

  //创建表格
  sql_query = new QSqlQuery;
  // sushe
  if (!sql_query->exec("create table sushe(susheid INTEGER primary key "
                       "autoincrement, louid int, "
                       "roomid int,score int)")) {
    qDebug() << "Error: Fail to create table.";
  } else {
    qDebug() << "Table created!";
  }
  // checks
  if (!sql_query->exec("create table checks(checkid INTEGER primary key "
                       "autoincrement,data data, "
                       "checkname string,department string)")) {
    qDebug() << "Error: Fail to create table.";
  } else {
    qDebug() << "Table created!";
  }
  // checkevent
  if (!sql_query->exec(
          "create table checkevent(checkeventid INTEGER primary key "
          "autoincrement,susheid INTEGER, "
          "score int,checkid INTEGER,checker string)")) {
    qDebug() << "Error: Fail to create table.";
  } else {
    qDebug() << "Table created!";
  }
  // checkdetail
  if (!sql_query->exec(
          "create table checkdetail(checkdetailid INTEGER primary key "
          "autoincrement,reason string, "
          "koufen int,checkeventid INTEGER);")) {
    qDebug() << "Error: Fail to create table.";
  } else {
    qDebug() << "Table created!";
  }
  // dafenevent_view
  if (!sql_query->exec(
          "CREATE VIEW dafenevent_view AS SELECT "
          "checkeventid,checkevent.susheid susheid,checkevent.score "
          "score,checkid,checker,louid,roomid FROM sushe,checkevent;")) {
    qDebug() << "Error: Fail to create table.";
  } else {
    qDebug() << "Table created!";
  }

  //
  /*
  // name text
  //插入数据
  if (!sql_query.exec("INSERT INTO student VALUES(1, \"Wang\", 23)")) {
    qDebug() << sql_query.lastError();
  } else {
    qDebug() << "inserted Wang!";
  }
  if (!sql_query.exec("INSERT INTO student VALUES(2, \"Li\", 23)")) {
    qDebug() << sql_query.lastError();
  } else {
    qDebug() << "inserted Li!";
  }

  //修改数据
  sql_query.exec("update student set name = \"QT\" where id = 1");
  if (!sql_query.exec()) {
    qDebug() << sql_query.lastError();
  } else {
    qDebug() << "updated!";
  }

  //查询数据
  sql_query.exec("select * from student");
  if (!sql_query.exec()) {
    qDebug() << sql_query.lastError();
  } else {
    while (sql_query.next()) {
      int id = sql_query.value(0).toInt();
      QString name = sql_query.value(1).toString();
      int age = sql_query.value(2).toInt();
      qDebug()
          << QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
    }
  }

  //删除数据
  sql_query.exec("delete from student where id = 1");
  if (!sql_query.exec()) {
    qDebug() << sql_query.lastError();
  } else {
    qDebug() << "deleted!";
  }

  //删除表格
  sql_query.exec("drop table student");
  if (sql_query.exec()) {
    qDebug() << sql_query.lastError();
  } else {
    qDebug() << "table cleared";
  }

  //关闭数据库
  database.close();
  return a.exec();
  */
}
