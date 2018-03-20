#include "Primario.h"

Primario::Primario(const QString nm, const QString cgn, const QDate ns, const QString cf,
                   const char ss, const double stip, const QString stud,
                   const QString user, const QString pass
                   )
    : Medico(nm,cgn,ns,cf,ss,stip,stud,user,pass){ }

/***********************
    METODI DI RICERCA
***********************/

list<shared_ptr<Evento> > Primario::Ricerca(const list<shared_ptr<Evento> > &x) const {
    Functor helper(4); // può cercare tutte le visite
    list<shared_ptr<Evento>> risultato;
    shared_ptr<Primario> primario (new Primario(*this));
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,primario)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}

list<shared_ptr<Evento> > Primario::Ricerca(const list<shared_ptr<Evento>> &x,
                                                   const shared_ptr<Medico> &dip) const {
    Functor helper(2); // può cercare le visite di un suo dipendente
    list<shared_ptr<Evento>> risultato;
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,dip)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}

list<shared_ptr<Evento>> Primario::Ricerca(const list<shared_ptr<Evento>> &x,
                                                  const shared_ptr<Persona> &paziente) const {
    Functor helper(6); // può cercare le visite o donazioni di un paziente
    list<shared_ptr<Evento>> risultato;
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,paziente)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}

/**************************
    METODI PER I DIPENDENTI
****************************/
void Primario::Assunzione(const shared_ptr<Personale> &dip, vector<shared_ptr<Personale> > &x) const{
    //Cerco che non sia già presente
    bool trovato = false;
    for( auto i = x.begin(); !trovato && i != x.end(); ++i){
        if( *i->get() == *dip.get() || (*i).get()->Username() == dip.get()->Username()) {
            trovato = true;
        }
    }
    if(!trovato){ //inserimento
        x.push_back(dip);
    }
}

void Primario::Licenzia(const shared_ptr<Personale>& dip, vector<shared_ptr<Personale> > &x) const{
    auto i = std::find(x.begin(),x.end(),dip);
    x.erase(i);
}
void Primario::ModificaDipendente(shared_ptr<Personale>& vecchio, shared_ptr<Personale>nuovo,
                                  vector<shared_ptr<Personale> > &x) const {
    if( vecchio != nuovo) {
        auto i = std::find(x.begin(),x.end(),vecchio);
        if(i != x.end()){
            vecchio.get()->CopiaCredenziali(nuovo);
            vecchio.reset();
            *i = nuovo;
        }
    }
}

/**************************
    METODI PER GLI EVENTI
****************************/

void Primario::AggiungiEvento(list<shared_ptr<Evento> > &agenda, const shared_ptr<Evento> &evento) const{
    //cerco non sia già presente
    bool trovato = false;
    for( auto i = agenda.begin(); !trovato && i != agenda.end();++i){
        if( *(*i).get()== *evento.get() )
            trovato = true;
    }
    if( !trovato )
        agenda.push_back(evento);
}

void Primario::RimuoviEvento(list<shared_ptr<Evento> > &agenda, const shared_ptr<Evento> &evento) const{
    agenda.remove(evento);
}

void Primario::ModificaAppuntamento(list<shared_ptr<Evento>>& lista, shared_ptr<Evento> &vecchio,
                        const shared_ptr<Evento> &nuovo) const{
    if( vecchio != nuovo) {
        auto p = std::find(lista.begin(),lista.end(),vecchio);
        if ( p != lista.end() ) {
            vecchio.reset();
            *p = nuovo;
        }
    }
}

/**************************
    METODI PER I PAZIENTI
****************************/

void Primario::AggiungiPaziente(vector<shared_ptr<Persona> > &pazienti, const shared_ptr<Persona> &nuovo) const{
    //cerco non sia già presente
    bool trovato = false;
    for( auto i = pazienti.begin(); !trovato && i != pazienti.end();++i){
        if( (*i).get() == nuovo.get())
            trovato = true;
    }
    if(!trovato)
        pazienti.push_back(nuovo);
}


void Primario::RimuoviPaziente(vector<shared_ptr<Persona> > &pazienti, const shared_ptr<Persona> &vecchio) const{
    auto i = std::find(pazienti.begin(),pazienti.end(),vecchio);
    pazienti.erase(i);
}
void Primario::ModificaPaziente(shared_ptr<Persona>& vecchio,const shared_ptr<Persona>& nuovo,
                                vector<shared_ptr<Persona> > &pazienti) const{
    if( vecchio != nuovo) {
        auto i = std::find(pazienti.begin(),pazienti.end(),vecchio);
        if(i != pazienti.end()){
            vecchio.reset();
            *i = nuovo;
        }
    }
}
