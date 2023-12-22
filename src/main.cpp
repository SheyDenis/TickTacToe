#include "mainwindow.h"
#include <cstdlib>
#include <QApplication>

int main(int argc, char* argv[]) {
  setenv("FONTCONFIG_PATH", "/etc/fonts", 0);
  QApplication a(argc, argv);
  ticktactoe::MainWindow w;
  w.show();

  return QApplication::exec();
}
