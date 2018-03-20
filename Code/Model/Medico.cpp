#include "Medico.h"

Medico::Medico(const QString nm, const QString cgn, const QDate ns, const QString cf,
               const char ss, const double stip, const QString stud , const QString user, const QString pass )
    : Personale(nm,cgn,ns,cf,ss,stip,user,pass),studio(stud){ }

QString Medico::Studio() const {
    return studio;
}

list<shared_ptr<Evento>> Medico::Ricerca(const list<shared_ptr<Evento> > &x) const {
    Functor helper(3); // può cercare solo le sue visite
    list<shared_ptr<Evento>> risultato;
    shared_ptr<Medico> medico (new Medico(*this));
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,medico)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}

list<shared_ptr<Evento> > Medico::Ricerca(const list<shared_ptr<Evento> > &x,
                                                 const shared_ptr<Persona>& paziente) const {
    Functor helper(5); // può cercare le visite di un paziente
    list<shared_ptr<Evento>> risultato;
    for ( auto i = x.begin() ; i != x.end(); ++i ){
        if(helper(*i,paziente)){
            risultato.push_back(*i);
        }
    }
    return risultato;
}
