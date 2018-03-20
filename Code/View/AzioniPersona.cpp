#include "AzioniPersona.h"

AzioniPersona::AzioniPersona(){
    setGeometry(0,0,500,500);Centra();
    invia = new QPushButton;
    annulla = new QPushButton("Annulla");

    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));


    sessoM = new QCheckBox("M");
    sessoM->setChecked(true); //Impostazione di default
    sessoF =  new QCheckBox("F");
    connect(sessoM,SIGNAL(toggled(bool)),this,SLOT(CambioSM(bool)));
    connect(sessoF,SIGNAL(toggled(bool)),this,SLOT(CambioSF(bool)));


    cognomeL = new QLabel("Cognome: ");
    nomeL = new QLabel("Nome: ");
    codiceFiscaleL = new QLabel("Codice fiscale: ");
    dataL = new QLabel("Data di nascita: ");

    sessoL = new QLabel("Sesso: ");
    gruppoL = new QLabel("Gruppo sanguigno:  ");
    fattoreL = new QLabel("Fattore:  ");

    professioneL = new QLabel("Professione:  ");
    stipendioL = new QLabel("Stipendio:  ");
    studioL = new QLabel("Studio:  ");

    cognome = new QLineEdit;
    nome = new QLineEdit;
    codiceFiscale = new QLineEdit;
    data = new QDateEdit;
    data->setDisplayFormat("dd/MM/yyyy");
    data->setMaximumDate(QDate::currentDate());
    data->setCalendarPopup(true);

    gruppo = new QComboBox;
    gruppo->addItem("A");
    gruppo->addItem("B");
    gruppo->addItem("AB");
    gruppo->addItem("O");

    fattore = new QComboBox;    
    fattore->addItem("Negativo");
    fattore->addItem("Positivo");

    professione = new QComboBox;
    professione->addItem("Medico");
    professione->addItem("Segreteria");
    professione->addItem("Primario");
    connect(professione,SIGNAL(currentIndexChanged(QString)),this,SLOT(CambioPersonale(QString)));

    stipendio = new QLineEdit;;
    studio = new QLineEdit;;


    donatoreL = new QLabel("Donatore?");
    donatore = new QCheckBox;
    connect(donatore,SIGNAL(clicked(bool)),this,SLOT(CambioDonatore()));

}

AzioniPersona::~AzioniPersona(){
    delete invia;
    delete annulla;

    delete cognome;
    delete nome;
    delete codiceFiscale;
    delete data;
    delete sessoM;
    delete sessoF;
    gruppo->clear();
    delete gruppo;
    fattore->clear();
    delete fattore;
    professione->clear();
    delete professione;
    delete stipendio;
    delete studio;

    delete cognomeL;
    delete nomeL;
    delete codiceFiscaleL;
    delete dataL;
    delete sessoL;
    delete gruppoL;
    delete fattoreL;

    delete professioneL;
    delete stipendioL;
    delete studioL;


    delete donatore;
    delete donatoreL;
}

void AzioniPersona::CambioSM(bool x){
    if(x){
        sessoF->setChecked(false);
    }
    else {
       sessoF->setChecked(true);
    }
}
void AzioniPersona::CambioSF(bool x){
    if(x){
        sessoM->setChecked(false);
    }
    else {
       sessoM->setChecked(true);
    }
}

void AzioniPersona::CambioPersonale(QString x){
    if(x == "Medico" || x == "Primario"){
        studio->setDisabled(false);
    }
    else{
        studio->setDisabled(true);
    }

}


void AzioniPersona::CambioDonatore(){
    if(donatore->isChecked()){
        gruppo->setDisabled(false);
        fattore->setDisabled(false);
    }
    else{
        gruppo->setDisabled(true);
        fattore->setDisabled(true);
    }
}
