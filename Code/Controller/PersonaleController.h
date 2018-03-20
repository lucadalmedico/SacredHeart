#ifndef PERSONALECONTROLLER_H
#define PERSONALECONTROLLER_H

#include "../Model/Database.h"
#include "../View/PersonaleWindow.h"
#include "../View/InfoPersona.h"
#include "../View/NuovaPersona.h"
#include "../View/NuovoEvento.h"
#include "../View/ModificaPersona.h"
#include "../View/ModificaEvento.h"
#include "../View/CambioChiavi.h"

class PersonaleController : public QObject{
    Q_OBJECT
protected:
    unique_ptr<Window> window;//finestra ausiliaria (usata per modifica/nuovo/cambio chiavi)
    shared_ptr<Database> dati;

    void CambioCredenziali(bool);//crea finestra per cambio chiavi
                                 //true = cambio id | false = cambio password
public:
    PersonaleController(const shared_ptr<Database>&);
    virtual ~PersonaleController();
protected slots:
    void pazienti();//Da alla view i dati dei pazienti
    void personale();//Da alla view i dati dei dipendenti
    void visite(const shared_ptr<Personale>&);//Da alla view i dati delle visite secodo i diritti dell'utente
    void Informazioni(int,int,const shared_ptr<Personale>&);//crea finestra per le informazioni
                                                //di un paziente o un medico in un evento a seconda dei permessi dell' utente
    void CreaModificaPersona(int,bool);//crea finestra per modificare persona: true = paziente | false = personale
    void Save();//salva i dati
    void Update();//ricarica i dati
    void NuovoPaziente();//crea finestra per inserire un paziente
    void NuovoDipendente();//crea finestra per inserire un dipendente
    void NuovoAppuntamento();  //crea finestra per inserire un evento
    void NewId();//chiama CambioCredenziali(true)
    void NewPw();//chiama CambioCredenziali(false)

    virtual void InformazioniPersonali() = 0;//crea finestra con le informazioni personali
    virtual void Logout() = 0;//effettua il logout
    virtual void CambioPassword(QString,QString,QString) = 0; //cambia la password dell'utente
    virtual void CambioId(QString) = 0;//cambia l'id dell'utente
signals:
    void EmitPazienti(const vector<shared_ptr<Persona>>&);
    void EmitDipendenti(const vector<shared_ptr<Personale>>&);
    void EmitVisite(const list<shared_ptr<Evento>>&);
    void SegnaleModifiche(bool);
    void updateView();
    void log();
};

#endif // PERSONALECONTROLLER_H
