#include "PersonaleController.h"

PersonaleController::PersonaleController(const shared_ptr<Database> &y):dati(y){}

PersonaleController::~PersonaleController(){
    window.reset();
    dati.reset();
}

void PersonaleController::pazienti(){
    emit EmitPazienti(dati.get()->GetPazienti());
}


void PersonaleController::personale(){
    emit EmitDipendenti(dati.get()->GetPersonale());
}

void PersonaleController::visite(const shared_ptr<Personale> &persona){
    emit EmitVisite(persona.get()->Ricerca(dati.get()->GetAgenda()));
}

void PersonaleController::Informazioni(int x, int y, const shared_ptr<Personale> &persona){
    InfoPersona* finestra = nullptr;
    auto i = std::next(persona.get()->Ricerca(dati.get()->GetAgenda()).begin(),y);
    shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(*i); 
    shared_ptr<Donazione> donazione = std::dynamic_pointer_cast<Donazione>(*i);
    shared_ptr<Primario> primario = std::dynamic_pointer_cast<Primario>(persona);

    if(visita){
        if(x ==  2){
            shared_ptr<Persona> paziente (new Persona(visita->GetPaziente()));
            finestra = new InfoPersona(paziente,true);
        }
        if(x ==  3){
            bool MostraStipendio = (primario)? true : false;
            finestra = new InfoPersona(shared_ptr<Medico>(new Medico(visita->GetMedico())),MostraStipendio);
        }
    }else {
        if(donazione) {
            finestra = new InfoPersona(shared_ptr<Donatore>(new Donatore(donazione->GetDonatore())),true);
        }
    }
    if(donazione || x ==2) { // Aggiungo lista donazioni o visite del paziente
        shared_ptr<Persona> paziente = (donazione)? shared_ptr<Donatore>(new Donatore(donazione->GetDonatore())) :
                                                    shared_ptr<Persona>(new Persona(visita->GetPaziente()));
        list<shared_ptr<Evento>> lista = persona.get()->Ricerca(dati.get()->GetAgenda(),paziente);
        if(lista.size() > 0 ){
            QTableWidget* storico;
            QStringList header;

            if(donazione){
                finestra->AggiungiEvento(new QLabel("Donazioni: "));
                storico = new QTableWidget(lista.size(),3);
                header<<"Data"<<"Ora"<<"Descrizione";
                storico->setHorizontalHeaderLabels(header);
                int riga = 0;
                for( auto i = lista.begin(); i != lista.end(); ++i) {
                    storico->setCellWidget(riga,0,new QLabel((*i).get()->GetData().toString("dd/MM/yyyy")));
                    storico->setCellWidget(riga,1,new QLabel( (*i).get()->GetData().toString("hh:mm") ));
                    storico->setCellWidget(riga,2,new QLabel( (*i).get()->Descrizione() ));
                    ++riga;
                }
            }
            else{
                finestra->AggiungiEvento(new QLabel("Visite: "));
                storico = new QTableWidget(lista.size(),4);
                header<<"Data"<<"Ora"<<"Medico"<<"Descrizione";
                storico->setHorizontalHeaderLabels(header);
                int riga = 0;
                for( auto i = lista.begin(); i != lista.end(); ++i) {
                    storico->setCellWidget(riga,0,new QLabel((*i).get()->GetData().toString("dd/MM/yyyy")));
                    storico->setCellWidget(riga,1,new QLabel( (*i).get()->GetData().toString("hh:mm") ));
                    Medico medico = (std::dynamic_pointer_cast<Visita>(*i).get())->GetMedico();
                    storico->setCellWidget(riga,2,new QLabel( medico.Cognome() + " " + medico.Nome()));
                    storico->setCellWidget(riga,3,new QLabel( (*i).get()->Descrizione() ));
                    ++riga;
                }

            }
            storico->resizeColumnsToContents();
            storico->horizontalHeader()->setStretchLastSection(true);
            finestra->AggiungiEvento(storico);
        }
        lista.clear();
    }
    //Se è il primario a chiedere infomazioni su un medico aggiungo le visite del dipendente
    if(primario && visita && x == 3){
        list<shared_ptr<Evento>> lista =  primario.get()->Ricerca(dati.get()->GetAgenda()
                                        ,shared_ptr<Medico>(new Medico(visita->GetMedico())));

        if(lista.size() > 0 ){
            QTableWidget* storico;
            QStringList header;

            finestra->AggiungiEvento(new QLabel("Visite: "));
            storico = new QTableWidget(lista.size(),4);
            header<<"Data"<<"Ora"<<"Paziente"<<"Descrizione";
            storico->setHorizontalHeaderLabels(header);
            int riga = 0;
            for( auto i = lista.begin(); i != lista.end(); ++i) {
                storico->setCellWidget(riga,0,new QLabel((*i).get()->GetData().toString("dd/MM/yyyy")));
                storico->setCellWidget(riga,1,new QLabel( (*i).get()->GetData().toString("hh:mm") ));
                Persona paziente = (std::dynamic_pointer_cast<Visita>(*i).get())->GetPaziente();
                storico->setCellWidget(riga,2,new QLabel( paziente.Cognome() + " " + paziente.Nome()));
                storico->setCellWidget(riga,3,new QLabel( (*i).get()->Descrizione() ));
                ++riga;
            }
            storico->resizeColumnsToContents();
            storico->horizontalHeader()->setStretchLastSection(true);
            finestra->AggiungiEvento(storico);
        }
        lista.clear();

    }
    finestra->show();
}

void PersonaleController::NuovoPaziente(){
    window.reset();
    window = unique_ptr<Window>(new NuovaPersona());
    connect(window.get(),SIGNAL(invioS(QString,QString,QString,QDate,char,QString,bool)),this,
            SLOT(InserisciPersona(QString,QString,QString,QDate,char,QString,bool)));
    window->show();
}

void PersonaleController::NuovoDipendente(){
    window.reset();
    window = unique_ptr<Window>(new NuovaPersona(true));
    connect(window.get(),SIGNAL(invioS(QString,QString,QString,QDate,char,QString,QString,QString,QString,double)),
            this,SLOT(InserisciDipendente(QString,QString,QString,QDate,char,QString,QString,QString,QString,double)));
    window->show();
}

void PersonaleController::NuovoAppuntamento(){
    window.reset();
    window = unique_ptr<Window>(new NuovoEvento(dati));
    connect(window.get(),SIGNAL(invio(const shared_ptr<Medico>&,const shared_ptr<Persona>&,const bool,const QDateTime,const QString)),
            this,SLOT(InserisciEvento(const shared_ptr<Medico>&,const shared_ptr<Persona>&,const bool,const QDateTime,const QString)));
    window->show();
}

void PersonaleController::Save(){
    dati.get()->Salva();
}

void PersonaleController::Update(){
    dati.get()->Carica();
    emit updateView();
}

void PersonaleController::CreaModificaPersona(int x, bool persona){
    window.reset();
    if(persona){
        if( x >= 0 && static_cast<unsigned int>(x) < dati.get()->GetPazienti().size()){
            window = unique_ptr<Window>(new ModificaPersona(dati.get()->GetPazienti().at(x)));
            connect(window.get(),SIGNAL(invioS(shared_ptr<Persona>&,const QString, const QString, const QString, const QDate,
                                               const char, const QString, const bool)),this,
                    SLOT(ModificaPaziente(shared_ptr<Persona>&,const QString, const QString, const QString, const QDate,
                                          const char, const QString, const bool)));
            window->show();
        }
    }
    else
        if( x >= 0 && static_cast<unsigned int>(x) < dati->GetPersonale().size()){
            window = unique_ptr<Window>(new ModificaPersona(dati.get()->GetPersonale().at(x)));
            connect(window.get(),SIGNAL(invioS(shared_ptr<Personale>&, const QString, const QString, const QString, const QDate,
                                               const char,const QString, const QString, const double)),this,
                    SLOT(ModificaDipendente(shared_ptr<Personale>&, const QString, const QString, const QString, const QDate,
                                            const char,const QString, const QString, const double)));
            window->show();
        }
}


void PersonaleController::CambioCredenziali(bool tipo){
    window.reset();
    if(tipo){
         window = unique_ptr<CambioChiavi>(new CambioChiavi(tipo));
         connect(window.get(),SIGNAL(Cambio(QString)),this,SLOT(CambioId(QString)));
    }
    else{
         window = unique_ptr<CambioChiavi>(new CambioChiavi(tipo));
         connect(window.get(),SIGNAL(Cambio(QString,QString,QString)),this,SLOT(CambioPassword(QString,QString,QString)));
    }
    window->show();
}


void PersonaleController::NewId(){CambioCredenziali(true);}

void PersonaleController::NewPw(){CambioCredenziali(false);}
