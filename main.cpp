#include "mainwindow.h"
#include "sqllite.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "dbdesigner_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  Sqllite sql;
  MainWindow w(nullptr, sql.sql_query);
  w.GetQuery(sql.sql_query);
  w.flushtable();
  w.show();
  return a.exec();
}
