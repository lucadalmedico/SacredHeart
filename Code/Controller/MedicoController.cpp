#include "MedicoController.h"

MedicoController::MedicoController(const shared_ptr<Medico> &x, const shared_ptr<Database> &y)
    : PersonaleController(y), persona(x){
    finestra = unique_ptr<MedicoWindow>(new MedicoWindow(persona));
    connect(finestra.get(),SIGNAL(SegnaleInformazioni(int)),this,SLOT(Informazioni(int)));
    connect(this,SIGNAL(EmitVisite(list<shared_ptr<Evento>>)),finestra.get(),
            SLOT(GetVisite(list<shared_ptr<Evento>>)));

    connect(finestra.get(),SIGNAL(update()),this,SLOT(Update()));
    connect(finestra.get(),SIGNAL(log()),this,SLOT(Logout()));
    connect(finestra.get(),SIGNAL(pInfo()),this,SLOT(InformazioniPersonali()));
    connect(finestra.get(),SIGNAL(newId()),this,SLOT(NewId()));
    connect(finestra.get(),SIGNAL(newPw()),this,SLOT(NewPw()));
    connect(this,SIGNAL(EmitVisite(list<shared_ptr<Evento>>)),finestra.get(),
            SLOT(GetVisite(list<shared_ptr<Evento>>)));

    connect(this,SIGNAL(updateView()),finestra.get(),SLOT(AggiornaViste()));

    visite(persona);
    finestra->show();
}

MedicoController::~MedicoController(){
    persona.reset();
    finestra.reset();
}

void MedicoController::Informazioni(const int y){

    InfoPersona* window = nullptr;
    auto k = std::next(persona.get()->Ricerca(dati.get()->GetAgenda()).begin(),y);
    shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(*k);
    shared_ptr<Persona> paziente (new Persona(visita->GetPaziente()));
    window = new InfoPersona(paziente);
    list<shared_ptr<Evento>> lista = persona.get()->Ricerca(dati->GetAgenda(),paziente);
    if(lista.size() > 0 ){
        QTableWidget* storico;
        QStringList header;
        window->AggiungiEvento(new QLabel("Visite: "));
        storico = new QTableWidget(lista.size(),4);
        header<<"Data"<<"Ora"<<"Medico"<<"Descrizione";
        storico->setHorizontalHeaderLabels(header);
        int riga = 0;
        for( auto i = lista.begin(); i != lista.end(); ++i) {
            storico->setCellWidget(riga,0,new QLabel((*i).get()->GetData().toString("dd/MM/yyyy")));
            storico->setCellWidget(riga,1,new QLabel( (*i).get()->GetData().toString("hh:mm") ));
            shared_ptr<Visita> help = std::dynamic_pointer_cast<Visita>(*i);
            storico->setCellWidget(riga,2,new QLabel( help.get()->GetMedico().Cognome() + " " +
                                                      help.get()->GetMedico().Nome()));
            storico->setCellWidget(riga,3,new QLabel( (*i).get()->Descrizione() ));
            ++riga;
            visita.reset();
        }
        storico->resizeColumnsToContents();
        storico->horizontalHeader()->setStretchLastSection(true);
        window->AggiungiEvento(storico);
    }
    window->show();
    visita.reset();
    paziente.reset();
}

void MedicoController::InformazioniPersonali(){
    InfoPersona* infoP = new InfoPersona(persona,true,true);
    infoP->show();
}
void MedicoController::CambioId(QString i){
    if( persona.get()->ControlloUsername(i,dati.get()->GetPersonale())){
        persona.get()->CambioUsername(i);
        dati.get()->Salva();
    }else
        finestra.get()->Error("Operazione fallita: Username attualmente uso");
}

void MedicoController::CambioPassword(QString o, QString n1, QString n2){
    persona.get()->CambioPassword(o,n1,n2);
    dati.get()->Salva();
}

void MedicoController::Logout(){
    finestra->close();
    emit log();
}
