#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "form.h"
#include "formdetail.h"
#include "sushelist.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  Sushelist sushelist;
  Form add_sushe;
  FormDetail add_detail;
  int checksnow = 0;

public:
  DetailRecord detailrecord;
  QSqlQuery *sql_query;
  MainWindow(QWidget *parent = nullptr, QSqlQuery *sql = nullptr);
  ~MainWindow();
  void GetQuery(QSqlQuery *sql);
  void flushtable();

private slots:
  void on_pushButton_8_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
