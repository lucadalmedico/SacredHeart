#ifndef SEGRETERIACONTROLLER_H
#define SEGRETERIACONTROLLER_H

#include "../View/SegreteriaWindow.h"
#include "PersonaleController.h"

class SegreteriaController : public PersonaleController{
    Q_OBJECT
private:
    shared_ptr<Segreteria> persona;
    unique_ptr<SegreteriaWindow> finestra;
public:
    SegreteriaController(const shared_ptr<Segreteria>&,const shared_ptr<Database>&);
    ~SegreteriaController();
protected slots:
    void InserisciPersona(const QString, const QString, const QString, const QDate, const char,
                          const QString, const bool);
    void InserisciEvento(const shared_ptr<Medico>&,const shared_ptr<Persona>&,const bool, const QDateTime,
                         const QString);
    void EliminaPersona(const int);
    void EliminaEvento(const int);
    void ModificaPaziente(shared_ptr<Persona>&,const QString, const QString, const QString, const QDate, const char,
                          const QString, const bool);
    void ModificaAppuntamento(shared_ptr<Evento>&,const shared_ptr<Medico>&,const shared_ptr<Persona>&,const QDateTime,
                        const QString);
    void CreaModificaEvento(const int);//crea finestra per modificare evento
    void Logout();
    void InformazioniPersonali();
    void CambioPassword(QString,QString,QString);
    void CambioId(QString);
};

#endif // SEGRETERIACONTROLLER_H
