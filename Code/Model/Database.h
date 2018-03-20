#ifndef DATABASE
#define DATABASE

#include "Primario.h"
#include "Visita.h"
#include "Segreteria.h"

#include <QtXml>

class Database {
private:

    list<shared_ptr<Evento>> appuntamenti;
    vector<shared_ptr<Personale>> personale;
    vector<shared_ptr<Persona>> pazienti;
    //Caricamenti di default
    void LoadAgenda();
    void LoadPersonale();
    void LoadPazienti();
    //Caricamenti da file
    void LoadPersonale(QFile*);
    void LoadAgenda(QFile*);
    void LoadPazienti(QFile*);
    //Chiusura di default
    void CloseAgenda() const;
    void ClosePersonale() const;
    void ClosePazienti() const;
    //Chiusura su file
    void CloseAgenda(QFile*) const;
    void ClosePersonale(QFile*) const;
    void ClosePazienti(QFile*) const;
    QString Datapath() const;// percorso di default ( dove si trova l'eseguibile)
    static bool OrdinaPersone(const shared_ptr<Persona>&,const shared_ptr<Persona>&);
    static bool OrdinaEventi(const shared_ptr<Evento>&,const shared_ptr<Evento>&);
    bool PersonaPresente(const shared_ptr<Persona>&) const;
    bool PersonalePresente(const shared_ptr<Personale>&) const;
    bool EventoPresente(const shared_ptr<Evento>&)const;
public:
    Database();
    ~Database();
    void Salva();
    void Carica();//pulisce il database e ricarica tutti i dati
    void CaricaDati();//carica solamente i pazienti e gli appuntamenti
    //importo da file
    void AggiungiPazienti(QString);
    void AggiungiDipendenti(QString);
    void AggiungiEventi(QString);
    void Esporta(QString) const;//esporta tutti i file su cartella
    void Pulisci();//elimina tutti i dati

    list<shared_ptr<Evento>> &GetAgenda();
    vector<shared_ptr<Personale>>& GetPersonale();
    vector<shared_ptr<Persona>>& GetPazienti();

    //Ritorna il dipendente dato il suo username e la sua password
    shared_ptr<Personale> Login(const QString,const QString) const;
};

#endif // DATABASE

