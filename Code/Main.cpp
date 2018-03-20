#include <QApplication>
#include "Controller/LoginController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    shared_ptr<Database> archivio = std::make_shared<Database>(Database());
    LoginController login(archivio);
    archivio.reset();
    return app.exec();
}
