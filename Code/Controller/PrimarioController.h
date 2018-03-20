#ifndef PRIMARIOCONTROLLER_H
#define PRIMARIOCONTROLLER_H

#include "../View/PrimarioWindow.h"
#include "PersonaleController.h"

class PrimarioController : public PersonaleController{
    Q_OBJECT
public:
    PrimarioController(const shared_ptr<Primario>&,const shared_ptr<Database>&);
    ~PrimarioController();
private:
    shared_ptr<Primario> persona;
    unique_ptr<PrimarioWindow> finestra;
protected slots:
    void InserisciPersona(const QString, const QString, const QString, const QDate, const char, const QString, const bool);
    void InserisciDipendente(const QString,const QString,const QString,const QDate,const char,const QString,const QString,
                             const QString,const QString,const double);
    void InserisciEvento(const shared_ptr<Medico>&,const shared_ptr<Persona>&,const bool, const QDateTime,const QString);
    void EliminaPersona(const int);
    void EliminaDipendente(const int);
    void EliminaEvento(const int);
    void ModificaPaziente(shared_ptr<Persona>&,const QString, const QString, const QString, const QDate, const char,
                          const QString, const bool);
    void ModificaDipendente(shared_ptr<Personale>&, const QString, const QString, const QString, const QDate, const char,
                            const QString, const QString, const double);
    void ModificaAppuntamento(shared_ptr<Evento>&,const shared_ptr<Medico>&,const shared_ptr<Persona>&,const QDateTime,const QString);
    void CreaModificaEvento(const int);//crea finestra per modificare evento
    void CaricaPazienti();//Aggiungi pazienti da file
    void CaricaDipendenti();//Aggiungi dipendenti da file
    void CaricaEventi();//Aggiungi eventi da file
    void Esporta();//Esporta tutti i dati in una cartella

    void Logout();
    void InformazioniPersonali();
    void CambioPassword(QString,QString,QString);
    void CambioId(QString);
};

#endif // PRIMARIOCONTROLLER_H
