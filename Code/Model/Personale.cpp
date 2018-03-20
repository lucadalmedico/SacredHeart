#include "Personale.h"
#include "Visita.h"

Personale::Personale(const QString nm, const QString cgn, const QDate ns, const QString cf, const char ss,
                     const double stip, const QString user, const QString pass)
    : Persona(nm,cgn,ns,cf,ss), stipendio (stip),id(user),password(pass) { }

double Personale::Stipendio() const {
    return stipendio;
}

QString Personale::Username() const {
    return id;
}

void Personale::CambioPassword(const QString vecchia, const QString nuova1, const QString nuova2){
    if(nuova1 == nuova2 && nuova1 != vecchia && vecchia == password)
        password = nuova1;
}

void Personale::CambioUsername(const QString nuovo) {
    id = nuovo;
}

bool Personale::ControlloUsername(const QString us, const vector<shared_ptr<Personale> > & personale) const{
    bool risultato = true;
    for( auto i = personale.begin(); risultato && i != personale.end(); ++i) {
        if ( (*i).get()->Username() == us ) risultato = false;
    }
    return risultato;
}

void Personale::CopiaCredenziali(shared_ptr<Personale>& nuovo) const {
    if( nuovo.get()->Username() == ""){ //utente appena inserito
        nuovo.get()->CambioPassword("",password,password);
        nuovo.get()->CambioUsername(id);
    }
}




Personale::Functor::Functor(int x) : tipo(x) {}

bool Personale::Functor::operator ()(const shared_ptr<Evento>& evento, const shared_ptr<Persona> &persona) const {
    switch (tipo) {
    case -1: // nessun accesso all'archivio
        return false;
        break;
    case 0: // accesso a tutti gli appuntamenti
        return true;
        break;
    case 1: { // accesso a solo le donazioni
        return (std::dynamic_pointer_cast<Donazione>(evento)).get() &&
                (std::dynamic_pointer_cast<const Donatore>(persona)).get();
        break;
    }
    case 2:{ // accesso alle visite di un solo Medico
         shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(evento);
         shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(persona);
         return visita && medico && *medico.get() == visita->GetMedico();
         visita.reset();
         medico.reset();
         break;
    }
    case 3:{ //accesso alle visite di un solo Medico successive a ieri
        shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(evento);
        shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(persona);
        return visita && medico && visita->GetData().date() >= QDate::currentDate() &&
                *medico.get() == visita->GetMedico();
        visita.reset();
        medico.reset();
        break;
    }
    case 4:{ //accesso agli eventi recenti
        return evento->GetData().date() >= QDate::currentDate();
        break;
    }
    case 5:{ // accesso alle visite di un paziente
        shared_ptr<Visita> visita =std::dynamic_pointer_cast<Visita>(evento);
        return visita && *persona.get() == visita->GetPaziente();
        visita.reset();
        break;
    }
    case 6:{//accesso a tutti gli eventi di un paziente
        shared_ptr<Donazione> donazione = std::dynamic_pointer_cast<Donazione>(evento);
        shared_ptr<Visita> visita = std::dynamic_pointer_cast< Visita>(evento);
        return (donazione && donazione->GetDonatore() == *persona.get()) ||
                (visita && *persona.get() == visita->GetPaziente());
        visita.reset();
        donazione.reset();
        break;
    }
    case 7:{ // accesso alle donazioni di un donatore
        shared_ptr<Donazione> donazione =std::dynamic_pointer_cast<Donazione>(evento);
        shared_ptr<Donatore> donatore = std::dynamic_pointer_cast<Donatore>(persona);
        return donazione && *donatore.get() == donazione.get()->GetDonatore();
        donatore.reset();
        donazione.reset();
        break;
    }
    }
    return false;
}


