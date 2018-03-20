#ifndef PRIMARIO
#define PRIMARIO
#include "Medico.h"

class Primario : public Medico {
public:
    Primario(const QString,const QString,const QDate,const QString,const char,
             const double,const QString, const QString ="", const QString = "");
    ~Primario() = default;

    //Ottiene tutte le visite
    list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>>&) const;
    //Cerca le visite di un suo dipendente
    list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>> &, const shared_ptr<Medico>&) const;
    //Cerca eventi di un paziente
    list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>> &, const shared_ptr<Persona>&) const;

    //Azioni per dipendenti
    void Assunzione(const shared_ptr<Personale>&, vector<shared_ptr<Personale>>&) const;
    void Licenzia(const shared_ptr<Personale>&, vector<shared_ptr<Personale>>&) const;
    void ModificaDipendente(shared_ptr<Personale>&, shared_ptr<Personale>, vector<shared_ptr<Personale>>&) const;
    //Azioni per eventi
    void AggiungiEvento(list<shared_ptr<Evento>>&,const shared_ptr<Evento>&) const;
    void RimuoviEvento(list<shared_ptr<Evento>>&,const shared_ptr<Evento>&) const;
    void ModificaAppuntamento(list<shared_ptr<Evento>>&,shared_ptr<Evento>&, const shared_ptr<Evento>&) const;
    //Azioni per pazienti
    void AggiungiPaziente(vector<shared_ptr<Persona>>&,const shared_ptr<Persona>&) const;
    void RimuoviPaziente(vector<shared_ptr<Persona>>&,const shared_ptr<Persona>&) const;
    void ModificaPaziente(shared_ptr<Persona> &, const shared_ptr<Persona> &, vector<shared_ptr<Persona>>&) const;
};

#endif // PRIMARIO

