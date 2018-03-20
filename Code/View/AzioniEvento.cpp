#include "AzioniEvento.h"

AzioniEvento::AzioniEvento(const shared_ptr<Database> &x) : dati(x){
    invia = new QPushButton;
    annulla = new QPushButton("Annulla");
    setGeometry(0,0,500,500);Centra();
    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));

    donazione = new QCheckBox;
    connect(donazione,SIGNAL(toggled(bool)),this,SLOT(CambioTipoPaziente(bool)));

    medici = new QComboBox;
    pazienti = new QComboBox;

    descrizione = new QLineEdit;
    data = new QDateEdit;
    data->setDisplayFormat("dd/MM/yyyy");
    data->setCalendarPopup(true);
    data->setMinimumDate(QDate::currentDate());
    time = new QTimeEdit;
    time->setDisplayFormat("hh:mm");

    medico = new QLabel("Medico: ");
    paziente = new QLabel("Paziente: ");
    dona = new QLabel("Donazione?");
    desc = new QLabel("Descrizione:");
    datal = new QLabel("Data: ");
    timel = new QLabel("Ora: ");
}

AzioniEvento::~AzioniEvento(){
    delete medico;
    medici->clear();
    delete medici;
    delete paziente;
    pazienti->clear();
    delete pazienti;
    delete donazione;
    delete invia;
    delete annulla;
    delete dona;
    delete desc;
    delete datal;
    delete data;
    delete descrizione;
    delete time;
    delete timel;

    mediciList.clear();
    supporto.clear();
    dati.reset();
}

void AzioniEvento::CambioTipoPaziente(bool x){
    if(x){
        medico->setVisible(false);
        medici->setVisible(false);
        SoloDonatori();
        paziente->setText("Donatore: ");
    }
    else{
        medico->setVisible(true);
        medici->setVisible(true);
        TuttiPazienti();
        paziente->setText("Paziente: ");
    }
}

void AzioniEvento::TuttiPazienti(){
    if( !pazienti->size().isEmpty())
        pazienti->clear();
    Carica();
}

void AzioniEvento::SoloDonatori() {
    if( !pazienti->size().isEmpty())
        pazienti->clear();
    Carica(true);
}

void AzioniEvento::Carica(bool x){
    supporto.clear();
    for( auto i = dati.get()->GetPazienti().begin(); i != dati.get()->GetPazienti().end(); ++i){
        if(( x && std::dynamic_pointer_cast<Donatore>(*i)) || !x){
            supporto.push_back(*i);
            pazienti->addItem( (*i).get()->Cognome() + " " + (*i).get()->Nome());
        }
    }
}

void AzioniEvento::SoloMedici(){
    mediciList.clear();
    //Inserisco tutti i medici e imposto l' indice del QComboBox con il medico della visita
    for( auto i = dati.get()->GetPersonale().begin(); i != dati.get()->GetPersonale().end(); ++i){
        if(std::dynamic_pointer_cast<Medico>(*i)){
            mediciList.push_back(*i);
            medici->addItem( (*i).get()->Cognome() + " " + (*i).get()->Nome());
        }
    }
}
