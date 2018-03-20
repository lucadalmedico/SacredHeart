#ifndef SEGRETERIA
#define SEGRETERIA

#include "Personale.h"

class Segreteria : public Personale {

public:
    Segreteria(const QString,const QString,const QDate ,const QString,const char,
               const double, const QString ="", const QString = "");
    ~Segreteria() = default;
    //Cerca Ottiene sia visite che donazioni
    list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>>&) const;
    //Cerca eventi di un paziente
    list<shared_ptr<Evento> > Ricerca(const list<shared_ptr<Evento> > &, const shared_ptr<Persona>&) const;

    //Azioni per eventi
    void AggiungiEvento(list<shared_ptr<Evento>>&,const shared_ptr<Evento>&) const;
    void RimuoviEvento(list<shared_ptr<Evento>>&,const shared_ptr<Evento>&) const;
    void ModificaAppuntamento(list<shared_ptr<Evento>>&,shared_ptr<Evento>&, const shared_ptr<Evento>&) const;
    //Azioni per pazienti
    void AggiungiPaziente(vector<shared_ptr<Persona>>&,const shared_ptr<Persona>&) const;
    void RimuoviPaziente(vector<shared_ptr<Persona>>&,const shared_ptr<Persona>&) const;
    void ModificaPaziente(shared_ptr<Persona> &, const shared_ptr<Persona> &, vector<shared_ptr<Persona>>&) const;
};


#endif // SEGRETERIA

