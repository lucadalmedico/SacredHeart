#include "Segreteria.h"

Segreteria::Segreteria(const QString nm, const QString cgn, const QDate ns, const QString cf,
                       const char ss, const double stip, const QString user, const QString pass)
    : Personale(nm,cgn,ns,cf,ss,stip,user,pass) { }

list<shared_ptr<Evento>> Segreteria::Ricerca(const list<shared_ptr<Evento>> &x,
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

list<shared_ptr<Evento>> Segreteria::Ricerca(const list<shared_ptr<Evento>> &x) const{
    Functor helper(4); // può cercare tutti gli appuntamenti successivi a ieri
    list<shared_ptr<Evento>> risultato;
    shared_ptr<Segreteria> segreteria (new Segreteria(*this));
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,segreteria)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}

/**************************
    METODI PER GLI EVENTI
****************************/

void Segreteria::AggiungiEvento(list<shared_ptr<Evento> > &agenda, const shared_ptr<Evento> &evento) const{
    //cerco non sia già presente
    bool trovato = false;
    for( auto i = agenda.begin(); !trovato && i != agenda.end();++i){
        if( *(*i).get()== *evento.get() )
            trovato = true;
    }
    if( !trovato )
        agenda.push_back(evento);
}

void Segreteria::RimuoviEvento(list<shared_ptr<Evento> > &agenda, const shared_ptr<Evento> &evento) const{
    agenda.remove(evento);
}

void Segreteria::ModificaAppuntamento(list<shared_ptr<Evento>>& lista, shared_ptr<Evento> &vecchio,
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

void Segreteria::AggiungiPaziente(vector<shared_ptr<Persona> > &pazienti, const shared_ptr<Persona> &nuovo) const{
    //cerco non sia già presente
    bool trovato = false;
    for( auto i = pazienti.begin(); !trovato && i != pazienti.end();++i){
        if( (*i).get() == nuovo.get())
            trovato = true;
    }
    if(!trovato)
        pazienti.push_back(nuovo);
}


void Segreteria::RimuoviPaziente(vector<shared_ptr<Persona> > &pazienti, const shared_ptr<Persona> &vecchio) const{
    auto i = std::find(pazienti.begin(),pazienti.end(),vecchio);
    pazienti.erase(i);
}
void Segreteria::ModificaPaziente(shared_ptr<Persona>& vecchio,const shared_ptr<Persona>& nuovo,
                                  vector<shared_ptr<Persona> > &pazienti) const{
    if( vecchio != nuovo) {
        auto i = std::find(pazienti.begin(),pazienti.end(),vecchio);
        if(i != pazienti.end()){
            vecchio.reset();
            *i = nuovo;
        }
    }
}


