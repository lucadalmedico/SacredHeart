#include "NuovaPersona.h"

NuovaPersona::NuovaPersona(bool ps) : personale(ps){
    QString titolo = (personale)? "Nuovo dipendente" : "Nuovo paziente";
    setWindowTitle(titolo + " - SacredHeart");
    setWindowIcon(QIcon(":aggiungi"));

    invia->setText("Aggiungi");
    connect(invia,SIGNAL(clicked()),this,SLOT(Invio()));

    layout->addWidget(cognomeL,0,0);
    layout->addWidget(cognome,0,1,1,-1);
    layout->addWidget(nomeL,1,0);
    layout->addWidget(nome,1,1,1,-1);
    layout->addWidget(dataL,2,0);
    layout->addWidget(data,2,1);
    layout->addWidget(codiceFiscaleL,3,0);
    layout->addWidget(codiceFiscale,3,1,1,-1);
    layout->addWidget(sessoL,4,0);
    layout->addWidget(sessoM,4,1,Qt::AlignLeft);
    layout->addWidget(sessoF,4,1,Qt::AlignCenter);

    int cl = 5;

    if(personale){
        donatore = nullptr;
        donatoreL = nullptr;

        layout->addWidget(stipendioL,cl,0);
        layout->addWidget(stipendio,cl,1,1,-1);
        ++cl;


        layout->addWidget(studioL,cl,0);
        layout->addWidget(studio,cl,1,1,-1);
        ++cl;


        username = new QLineEdit;
        password1 = new QLineEdit;
        password1->setEchoMode(QLineEdit::Password);
        password2 = new QLineEdit;
        password2->setEchoMode(QLineEdit::Password);

        idL = new QLabel("Username: ");

        layout->addWidget(idL,cl,0);
        layout->addWidget(username,cl,1);
        cl++;

        ps1 = new QLabel("Password: ");
        layout->addWidget(ps1,cl,0);
        layout->addWidget(password1,cl,1);
        cl++;

        ps2 = new QLabel("Ripeti password: ");
        layout->addWidget(ps2,cl,0);
        layout->addWidget(password2,cl,1);
        cl++;

        layout->addWidget(professioneL,cl,0);
        layout->addWidget(professione,cl,1);
        cl++;

    }
    else{
        username = nullptr;
        password1 = nullptr;
        password2 = nullptr;
        idL = nullptr;
        ps1 = nullptr;
        ps2 = nullptr;

        gruppo->setDisabled(true);
        fattore->setDisabled(true);
        layout->addWidget(donatoreL,cl,0);
        layout->addWidget(donatore,cl,1);
        cl++;

        layout->addWidget(gruppoL,cl,0);
        layout->addWidget(gruppo,cl,1,1,-1);
        ++cl;
        layout->addWidget(fattoreL,cl,0);
        layout->addWidget(fattore,cl,1,1,-1);
        ++cl;

    }
    layout->addWidget(invia,cl,0,Qt::AlignLeft);
    layout->addWidget(annulla,cl,1,Qt::AlignLeft);
    Disegna();
}

NuovaPersona::~NuovaPersona(){
    delete username;
    delete password1;
    delete password2;

    delete idL;
    delete ps1;
    delete ps2;
}



void NuovaPersona::Invio(){
    if(cognome->text() == "" || nome->text() == "" || codiceFiscale->text() == ""){
        Error("Campi indispensabili vuoti");
    }else{
        char sesso = (sessoM->isChecked())? 'M' : 'F';
            if(personale){
                if(password1->text() != password2->text())
                    Error("Password non coincidono");
                else
                    emit invioS(cognome->text(),nome->text(),codiceFiscale->text(),data->date(),
                                sesso,professione->currentText(),username->text(),password1->text(),studio->text(),
                                (stipendio->text().toDouble()));
                    close();
            }
            else{
                bool f = (fattore->currentText() == "Positivo");
                QString NomeGruppo = (donatore->isChecked())? gruppo->currentText() : "";
                emit invioS(cognome->text(),nome->text(),codiceFiscale->text(),data->date(),sesso,NomeGruppo,f);
                close();
            }
    }
}

