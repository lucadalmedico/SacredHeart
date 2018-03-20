#include "Window.h"

Window::Window(){
    layout = new QGridLayout();
    central = new QWidget;
    setGeometry(0,0,800,600);
    setFont(QFont("Verdana"));
    setMinimumSize(500,500);
    setWindowTitle("SacredHeart");
    setWindowIcon(QIcon(":logo"));
    Centra();
}

Window::~Window(){

    while(layout->count() > 0 ) // Elimina widget rimanenti in layout
        delete layout->takeAt(0);

    delete layout;
    delete central;
}

void Window::Disegna(){
    central->setLayout(layout);
    setCentralWidget(central);
}

void Window::Centra(){
       int width = frameGeometry().width();
       int height = frameGeometry().height();

       QDesktopWidget wid;

       int screenWidth = wid.screen()->width();
       int screenHeight = wid.screen()->height();

       int x=static_cast<int>((screenWidth-width)/2);
       int y=static_cast<int>((screenHeight-height)/2);

       move(x,y);
}

void Window::Error(const QString x) const{
    QMessageBox errore;
    errore.setWindowIcon(QIcon(":errore"));
    errore.setIcon(QMessageBox::Critical);
    errore.setWindowTitle("Errore");
    errore.setText(x);
    errore.setStandardButtons(QMessageBox::Ok);
    errore.setDefaultButton(QMessageBox::Ok);
    errore.exec();
}
