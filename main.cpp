#include <QApplication>
#include "qmain.h"
#include <cxxtools/loginit.h>
#include <cxxtools/log.h>
log_define("qvido.main")

int main(int argc, char *argv[])
{
	log_init();
	log_debug("launching with arguments" << argv[1] );
	if (argc == 2)
	{
		QApplication app(argc, argv);

		QMain QMain(argv[1]);
    QMain.show();
    return app.exec();
	}else{
		std::cout << "usage: " << argv[0] << " [PATH TO ZIM FILE]" << std::endl;
	}
}
