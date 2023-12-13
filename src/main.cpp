#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>

int main(int argc, char *argv[]){
    setenv("FONTCONFIG_PATH","/etc/fonts",0);
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
