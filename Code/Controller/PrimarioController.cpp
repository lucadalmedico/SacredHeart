#include "PrimarioController.h"

PrimarioController::PrimarioController(const shared_ptr<Primario> &x, const shared_ptr<Database> &y)
    : PersonaleController(y), persona(x){
    finestra = unique_ptr<PrimarioWindow>(new PrimarioWindow(persona));
    connect(finestra.get(),SIGNAL(SegnaleInformazioni(int,int,const shared_ptr<Personale>)),this,
            SLOT(Informazioni(int,int,const shared_ptr<Personale>)));
    connect(finestra.get(),SIGNAL(NuovoPSignal()),this,SLOT(NuovoPaziente()));
    connect(finestra.get(),SIGNAL(NuovoDSignal()),this,SLOT(NuovoDipendente()));
    connect(finestra.get(),SIGNAL(NuovoESignal()),this,SLOT(NuovoAppuntamento()));
    connect(finestra.get(),SIGNAL(askV(const shared_ptr<Personale>&)),this,SLOT(visite(const shared_ptr<Personale>&)));
    connect(finestra.get(),SIGNAL(askP()),this,SLOT(pazienti()));
    connect(finestra.get(),SIGNAL(askD()),this,SLOT(personale()));
    connect(finestra.get(),SIGNAL(save()),this,SLOT(Save()));
    connect(finestra.get(),SIGNAL(modificaS(int,bool)),this,SLOT(CreaModificaPersona(int,bool)));
    connect(finestra.get(),SIGNAL(ModificaAppuntamento(int)),this,SLOT(CreaModificaEvento(int)));
    connect(finestra.get(),SIGNAL(deletePaziente(int)),this,SLOT(EliminaPersona(int)));
    connect(finestra.get(),SIGNAL(deleteDipendente(int)),this,SLOT(EliminaDipendente(int)));
    connect(finestra.get(),SIGNAL(deleteEvento(int)),this,SLOT(EliminaEvento(int)));
    connect(finestra.get(),SIGNAL(update()),this,SLOT(Update()));
    connect(finestra.get(),SIGNAL(log()),this,SLOT(Logout()));
    connect(finestra.get(),SIGNAL(pInfo()),this,SLOT(InformazioniPersonali()));
    connect(finestra.get(),SIGNAL(newId()),this,SLOT(NewId()));
    connect(finestra.get(),SIGNAL(newPw()),this,SLOT(NewPw()));
    connect(finestra.get(),SIGNAL(addPazienti()),this,SLOT(CaricaPazienti()));
    connect(finestra.get(),SIGNAL(addDipendenti()),this,SLOT(CaricaDipendenti()));
    connect(finestra.get(),SIGNAL(addEventi()),this,SLOT(CaricaEventi()));
    connect(finestra.get(),SIGNAL(Backup()),this,SLOT(Esporta()));
    connect(this,SIGNAL(EmitPazienti(const vector<shared_ptr<Persona>>&)),finestra.get(),
            SLOT(GetPazienti(const vector<shared_ptr<Persona>>&)));
    connect(this,SIGNAL(EmitVisite(const list<shared_ptr<Evento>>&)),finestra.get(),
            SLOT(GetVisite(const list<shared_ptr<Evento>>&)));
    connect(this,SIGNAL(EmitDipendenti(const vector<shared_ptr<Personale>>&)),finestra.get(),
            SLOT(GetDipendenti(const vector<shared_ptr<Personale>>&)));
    connect(this,SIGNAL(SegnaleModifiche(bool)),finestra.get(),SLOT(modifiche(bool)));
    connect(this,SIGNAL(updateView()),finestra.get(),SLOT(AggiornaViste()));
    visite(persona);
    finestra->show();
}

PrimarioController::~PrimarioController(){
    persona.reset();
    finestra.reset();
}

void PrimarioController::CreaModificaEvento(const int k){
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

void PrimarioController::InserisciPersona(const QString cognome, const QString nome, const QString cf,
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

void PrimarioController::InserisciDipendente(const QString cognome, const QString nome, const QString cf,
                                             const QDate data, const char sesso, const QString professione,
                                             const QString id, const QString pass, const QString stud,
                                             const double stip){
    unsigned int dimensioneIniziale = dati.get()->GetPersonale().size();
    if(professione == "Segreteria")
        persona.get()->Assunzione(shared_ptr<Segreteria>
                                  (new Segreteria(nome,cognome,data,cf,sesso,stip,id,pass)),dati.get()->GetPersonale());
    if(professione == "Medico")
        persona.get()->Assunzione(shared_ptr<Medico>
                                  (new Medico(nome,cognome,data,cf,sesso,stip,stud,id,pass)),dati.get()->GetPersonale());
    if(professione == "Primario")
        persona.get()->Assunzione(shared_ptr<Primario>
                                  (new Primario(nome,cognome,data,cf,sesso,stip,stud,id,pass)),dati->GetPersonale());
    if(dimensioneIniziale != dati.get()->GetPersonale().size())
        emit SegnaleModifiche(true);
    personale();
}

void PrimarioController::InserisciEvento(const shared_ptr<Medico>& medico, const shared_ptr<Persona>& paziente,
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

void PrimarioController::EliminaPersona(const int x){
    if( x >= 0 && static_cast<unsigned int>(x) < dati->GetPazienti().size()){
        unsigned int dimensioneIniziale = dati.get()->GetPazienti().size();
        persona->RimuoviPaziente(dati.get()->GetPazienti(),dati.get()->GetPazienti().at(x));
        if(dimensioneIniziale != dati.get()->GetPazienti().size())
            emit SegnaleModifiche(true);
        pazienti();
    }
}

void PrimarioController::EliminaDipendente(const int x){
    if( x >= 0 && static_cast<unsigned int>(x) < dati->GetPersonale().size()){
        unsigned int dimensioneIniziale = dati.get()->GetPersonale().size();
        persona.get()->Licenzia(dati.get()->GetPersonale().at(x),dati.get()->GetPersonale());
        if(dimensioneIniziale != dati.get()->GetPersonale().size())
            emit SegnaleModifiche(true);
        personale();
    }
}

void PrimarioController::EliminaEvento(const int x){
    if( x >= 0 && static_cast<unsigned int>(x) < persona.get()->Ricerca(dati.get()->GetAgenda()).size()){
        unsigned int dimensioneIniziale = dati.get()->GetAgenda().size();
        auto i = std::next(persona.get()->Ricerca(dati.get()->GetAgenda()).begin(),x);
        persona.get()->RimuoviEvento(dati.get()->GetAgenda(),*i);
        if(dimensioneIniziale != dati.get()->GetAgenda().size())
            emit SegnaleModifiche(true);
        visite(persona);
    }
}

void PrimarioController::ModificaPaziente(shared_ptr<Persona> &vecchio, const QString cogn, const QString nome,
                                          const QString cf, const QDate data, const char sx, const QString gruppo,
                                          const bool fattore){
    if(gruppo != "")
        persona.get()->ModificaPaziente(vecchio,shared_ptr<Donatore>(new Donatore(nome,cogn,data,cf,sx,gruppo,fattore)),
                                        dati.get()->GetPazienti());
    else
        persona.get()->ModificaPaziente(vecchio,shared_ptr<Persona>(new Persona(nome,cogn,data,cf,sx)),dati.get()->GetPazienti());
    emit SegnaleModifiche(true);
    pazienti();
}

void PrimarioController::ModificaDipendente(shared_ptr<Personale> &vecchio, const QString cogn, const QString nome,
                                            const QString cf, const QDate data, const char sx, const QString prof,
                                            const QString stud, const double stip) {

    if(prof == "Primario")
        persona.get()->ModificaDipendente(vecchio,shared_ptr<Primario>(
                                              new Primario(nome,cogn,data,cf,sx,stip,stud)),dati.get()->GetPersonale());
    else if( prof == "Medico")
            persona.get()->ModificaDipendente(vecchio,shared_ptr<Medico>(
                                                  new Medico(nome,cogn,data,cf,sx,stip,stud)),dati.get()->GetPersonale());
    else if( prof == "Segreteria")
            persona.get()->ModificaDipendente(vecchio,shared_ptr<Segreteria>(
                                                  new Segreteria(nome,cogn,data,cf,sx,stip)),dati.get()->GetPersonale());

    emit SegnaleModifiche(true);
    personale();
}

void PrimarioController::ModificaAppuntamento(shared_ptr<Evento> &evento, const shared_ptr<Medico> &medico,
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

void PrimarioController::Logout(){
    finestra->close();
    emit log();
}

void PrimarioController::InformazioniPersonali(){
    InfoPersona* infoP = new InfoPersona(persona,true,true);
    infoP->show();
}
void PrimarioController::CambioId(QString i){
    if( persona.get()->ControlloUsername(i,dati.get()->GetPersonale())){
        persona.get()->CambioUsername(i);
        dati.get()->Salva();
    }
    else
        finestra.get()->Error("Operazione fallita: Username attualmente uso");
}

void PrimarioController::CambioPassword(QString o, QString n1, QString n2){
    persona.get()->CambioPassword(o,n1,n2);
    dati.get()->Salva();
}

void PrimarioController::CaricaPazienti(){
    QString filename = finestra.get()->GetFile();
    if (!filename.isEmpty()) {
        unsigned int prima = dati.get()->GetPazienti().size();
        dati.get()->AggiungiPazienti(filename);
        if( prima < dati.get()->GetPazienti().size())
            emit SegnaleModifiche(true);
        pazienti();
    }
}

void PrimarioController::CaricaDipendenti(){
    QString filename = finestra.get()->GetFile();
    if (!filename.isEmpty()) {
        unsigned int prima = dati.get()->GetPersonale().size();
        dati.get()->AggiungiDipendenti(filename);
        if( prima < dati.get()->GetPersonale().size())
            emit SegnaleModifiche(true);
        personale();
    }
}

void PrimarioController::CaricaEventi(){
    QString filename = finestra.get()->GetFile();
    if (!filename.isEmpty()) {
        unsigned int prima = dati.get()->GetAgenda().size();
        dati.get()->AggiungiEventi(filename);
        if( prima < dati.get()->GetAgenda().size())
            emit SegnaleModifiche(true);
        visite(persona);
    }
}

void PrimarioController::Esporta(){
    QString filename = finestra.get()->GetFolder();
    if (!filename.isEmpty()) {
        dati.get()->Esporta(filename);
    }
}

