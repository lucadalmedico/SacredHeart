#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "../View/LoginWindow.h"

#include "MedicoController.h"
#include "SegreteriaController.h"
#include "PrimarioController.h"

class LoginController : public QObject{
    Q_OBJECT
private:
    shared_ptr<Database> dati;
    unique_ptr<LoginWindow> login;//finestra di login
    unique_ptr<PersonaleController> window;//finesta dell' utnte
public:
    LoginController(const shared_ptr<Database>&);
    ~LoginController();
private slots:
    void Controllo(const QString,const QString);//crea la finestra adeguata dati username e password di un dipendente
    void Logout();

};

#endif // LOGINCONTROLLER_H
