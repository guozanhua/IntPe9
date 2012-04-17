#include <QtGui/QApplication>
#include <QCleanlooksStyle>
#include "Views\Main.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QCleanlooksStyle); //FANCY!
	MainGui mainGui;
	QObject::connect(&a, SIGNAL(aboutToQuit()), &mainGui, SLOT(closing()));
	mainGui.show();
	return a.exec();
}
