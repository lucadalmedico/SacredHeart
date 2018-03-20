#ifndef MEDICOCONTROLLER_H
#define MEDICOCONTROLLER_H

#include "../View/MedicoWindow.h"
#include "PersonaleController.h"

class MedicoController : public PersonaleController {
    Q_OBJECT
private:
    shared_ptr<Medico> persona;
    unique_ptr<MedicoWindow> finestra;
public:
    MedicoController(const shared_ptr<Medico>& ,const shared_ptr<Database>&);
    ~MedicoController();
protected slots:
    void Informazioni(const int);//da informazioni base del paziente e delle visite passate
    void InformazioniPersonali();
    void CambioPassword(QString,QString,QString);
    void CambioId(QString);
    void Logout();

};

#endif // MEDICOCONTROLLER_H
