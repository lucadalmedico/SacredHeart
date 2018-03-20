#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QFormLayout>
#include "Window.h"

class LoginWindow :public Window{
     Q_OBJECT
private:
    QFormLayout* form;
    QPushButton* login;
    QLineEdit* username;
    QLineEdit* password;
public:
    LoginWindow();
    ~LoginWindow();
    void Pulisci(); //"Pulisce" i QLineEdit
private slots:
    void Invia();//emette il segnale inoltro
signals:
    void Inoltro(const QString,const QString);//Invia al controller per trovare utente con username e password
};


#endif // LOGINWINDOW_H
