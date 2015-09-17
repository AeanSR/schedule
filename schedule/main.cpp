#include "schedule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	schedule w;
    w.show();
	return a.exec();
}
