#include "SegreteriaController.h"

SegreteriaController::SegreteriaController(const shared_ptr<Segreteria> &x, const shared_ptr<Database> &y)
    : PersonaleController(y), persona(x){
    finestra = unique_ptr<SegreteriaWindow>(new SegreteriaWindow(persona));
    connect(finestra.get(),SIGNAL(SegnaleInformazioni(int,int,const shared_ptr<Personale>)),this,
            SLOT(Informazioni(int,int,const shared_ptr<Personale>)));
    connect(finestra.get(),SIGNAL(NuovoPSignal()),this,SLOT(NuovoPaziente()));
    connect(finestra.get(),SIGNAL(NuovoESignal()),this,SLOT(NuovoAppuntamento()));
    connect(finestra.get(),SIGNAL(askV(const shared_ptr<Personale>&)),this,SLOT(visite(const shared_ptr<Personale>&)));
    connect(finestra.get(),SIGNAL(askP()),this,SLOT(pazienti()));
    connect(finestra.get(),SIGNAL(save()),this,SLOT(Save()));
    connect(finestra.get(),SIGNAL(modificaS(int,bool)),this,SLOT(CreaModificaPersona(int,bool)));
    connect(finestra.get(),SIGNAL(ModificaAppuntamento(int)),this,SLOT(CreaModificaEvento(int)));
    connect(finestra.get(),SIGNAL(deletePaziente(int)),this,SLOT(EliminaPersona(int)));
    connect(finestra.get(),SIGNAL(deleteEvento(int)),this,SLOT(EliminaEvento(int)));
    connect(finestra.get(),SIGNAL(update()),this,SLOT(Update()));
    connect(finestra.get(),SIGNAL(log()),this,SLOT(Logout()));
    connect(finestra.get(),SIGNAL(pInfo()),this,SLOT(InformazioniPersonali()));
    connect(finestra.get(),SIGNAL(newId()),this,SLOT(NewId()));
    connect(finestra.get(),SIGNAL(newPw()),this,SLOT(NewPw()));
    connect(this,SIGNAL(EmitPazienti(const vector<shared_ptr<Persona>>&)),finestra.get(),
            SLOT(GetPazienti(const vector<shared_ptr<Persona>>&)));
    connect(this,SIGNAL(EmitVisite(const list<shared_ptr<Evento>>&)),finestra.get(),
            SLOT(GetVisite(const list<shared_ptr<Evento>>&)));
    connect(this,SIGNAL(SegnaleModifiche(bool)),finestra.get(),SLOT(modifiche(bool)));
    connect(this,SIGNAL(updateView()),finestra.get(),SLOT(AggiornaViste()));
    visite(persona);
    finestra->show();
}

SegreteriaController::~SegreteriaController(){
    persona.reset();
    finestra.reset();
}

void SegreteriaController::CreaModificaEvento(const int k){
    if(persona.get()->Ricerca(dati.get()->GetAgenda()).size() > static_cast<unsigned int>(k)){
        if(window.get())
            window.reset();
        auto i = std::next(persona.get()->Ricerca(dati.get()->GetAgenda()).begin(),k);
        if(*i){
            window = unique_ptr<Window>(new ModificaEvento(dati,*i));
            connect(window.get(),SIGNAL(invio(shared_ptr<Evento>&,const shared_ptr<Medico>&,
                                              const shared_ptr<Persona>&,const QDateTime,const QString)),this,
                    SLOT(ModificaAppuntamento(shared_ptr<Evento>&,const shared_ptr<Medico>&,const shared_ptr<Persona>&,
                                        const QDateTime,const QString)));
            window->show();
        }
    }
}

void SegreteriaController::InserisciPersona(const QString cognome, const QString nome, const QString cf,
                                            const QDate data, const char sesso, const QString gruppo, const bool fattore){
    unsigned int dimensioneIniziale = dati.get()->GetPazienti().size();
    if(gruppo != "")
        persona.get()->AggiungiPaziente(dati.get()->GetPazienti(),shared_ptr<Donatore>(
                                            new Donatore(nome,cognome,data,cf,sesso,gruppo,fattore)));
    else
        persona.get()->AggiungiPaziente(dati.get()->GetPazienti(),shared_ptr<Persona>(
                                            new Persona(nome,cognome,data,cf,sesso)));
    if(dimensioneIniziale != dati.get()->GetPazienti().size())
        emit SegnaleModifiche(true);
    pazienti();
}

void SegreteriaController::InserisciEvento(const shared_ptr<Medico>& medico, const shared_ptr<Persona>& paziente,
                                           const bool donazione, const QDateTime data, const QString descrizione){
    unsigned int dimensioneIniziale = dati.get()->GetAgenda().size();
    if(donazione){
        shared_ptr<Donatore> donatore = std::dynamic_pointer_cast<Donatore>(paziente);
        if(donatore)
            persona->AggiungiEvento(dati.get()->GetAgenda(),shared_ptr<Donazione>(
                                  new Donazione(*donatore.get(),data,descrizione)));
    }else{
        if(medico && paziente)
        persona.get()->AggiungiEvento(dati.get()->GetAgenda(),shared_ptr<Visita>(
                                    new Visita(data,*medico.get(),*paziente.get(),descrizione)));
    }
    if(dimensioneIniziale != dati.get()->GetAgenda().size())
        emit SegnaleModifiche(true);
    visite(persona);
}

void SegreteriaController::EliminaPersona(const int x){
    if( x >= 0 && static_cast<unsigned int>(x) < dati->GetPazienti().size()){
        unsigned int dimensioneIniziale = dati.get()->GetPazienti().size();
        persona->RimuoviPaziente(dati.get()->GetPazienti(),dati.get()->GetPazienti().at(x));
        if(dimensioneIniziale != dati.get()->GetPazienti().size())
            emit SegnaleModifiche(true);
        pazienti();
    }
}


void SegreteriaController::EliminaEvento(const int x){
    if( x >= 0 && static_cast<unsigned int>(x) < persona.get()->Ricerca(dati.get()->GetAgenda()).size()){
        unsigned int dimensioneIniziale = dati.get()->GetAgenda().size();
        auto i = std::next(persona.get()->Ricerca(dati.get()->GetAgenda()).begin(),x);
        persona.get()->RimuoviEvento(dati.get()->GetAgenda(),*i);
        if(dimensioneIniziale != dati.get()->GetAgenda().size())
            emit SegnaleModifiche(true);
        visite(persona);
    }
}

void SegreteriaController::ModificaPaziente(shared_ptr<Persona> &vecchio, const QString cogn, const QString nome, const QString cf,
                                            const QDate data, const char sx, const QString gruppo, const bool fattore){
    if(gruppo != "")
        persona.get()->ModificaPaziente(vecchio,shared_ptr<Donatore>(
                                            new Donatore(nome,cogn,data,cf,sx,gruppo,fattore)),dati.get()->GetPazienti());
    else
        persona.get()->ModificaPaziente(vecchio,shared_ptr<Persona>(
                                            new Persona(nome,cogn,data,cf,sx)),dati.get()->GetPazienti());
    emit SegnaleModifiche(true);
    pazienti();
}

void SegreteriaController::ModificaAppuntamento(shared_ptr<Evento> &evento, const shared_ptr<Medico> &medico,
                                          const shared_ptr<Persona> &paziente, const QDateTime data, const QString desc){
    bool fine = false;
    if(std::dynamic_pointer_cast<Visita>(evento)){
        if( medico && paziente){
            persona.get()->ModificaAppuntamento(dati.get()->GetAgenda(),evento,shared_ptr<Visita>(
                                        new Visita(data,*medico.get(),*paziente.get(),desc)));
            fine = true;
        }
    }
    if(std::dynamic_pointer_cast<Donazione>(evento)){
        shared_ptr<Donatore> donatore = std::dynamic_pointer_cast<Donatore>(paziente);
        if(donatore){
            persona.get()->ModificaAppuntamento(dati.get()->GetAgenda(),evento,shared_ptr<Donazione>(
                                        new Donazione(*donatore.get(),data,desc)));
            fine = true;
        }
        donatore.reset();

    }
    evento.reset();
    if(fine)
        emit SegnaleModifiche(true);
    visite(persona);
}

void SegreteriaController::Logout(){
    finestra->close();
    emit log();
}

void SegreteriaController::InformazioniPersonali(){
    InfoPersona* infoP = new InfoPersona(persona,true,true);
    infoP->show();
}
void SegreteriaController::CambioId(QString i){
    if( persona.get()->ControlloUsername(i,dati.get()->GetPersonale())){
        persona.get()->CambioUsername(i);
        dati.get()->Salva();
    }
    else
        finestra.get()->Error("Operazione fallita: Username attualmente uso");
}

void SegreteriaController::CambioPassword(QString o, QString n1, QString n2){
    persona.get()->CambioPassword(o,n1,n2);
    dati.get()->Salva();
}
