#include "ModificaPersona.h"

ModificaPersona::ModificaPersona(const shared_ptr<Persona> &x) : persona(x){
    setWindowTitle("Modifica persona - SacredHeart");
    setWindowIcon(QIcon(":modifica"));

    invia->setText("Modifica");
    connect(invia,SIGNAL(clicked()),this,SLOT(Invio()));

    cognome->setText(persona->Cognome());
    nome->setText(persona->Nome());
    codiceFiscale->setText(persona->CodiceFiscale());
    data->setDate(persona->DataNascita());

    if( persona.get()->Sesso() == 'M')
        sessoM->setChecked(true);
    else
        sessoF->setChecked(true);

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
    shared_ptr<Personale> personale = std::dynamic_pointer_cast<Personale>(persona);
    if(personale){

        stipendio->setText(QString::number(personale.get()->Stipendio()));
        layout->addWidget(stipendioL,cl,0);
        layout->addWidget(stipendio,cl,1,1,-1);
        ++cl;
        layout->addWidget(studioL,cl,0);
        layout->addWidget(studio,cl,1,1,-1);
        ++cl;
        shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(persona);
        if(medico){
            if(std::dynamic_pointer_cast<Primario>(medico))
                professione->setCurrentIndex(2);
            else
                professione->setCurrentIndex(0);
            studio->setText(medico.get()->Studio());
        }
        else{
            studio->setEnabled(false);
            if(std::dynamic_pointer_cast<Segreteria>(personale)){
                professione->setCurrentIndex(1);
            }
        }
        layout->addWidget(professioneL,cl,0);
        layout->addWidget(professione,cl,1,1,-1);
        cl++;
    }
    else{

        layout->addWidget(donatoreL,cl,0);
        layout->addWidget(donatore,cl,1);
        ++cl;

        layout->addWidget(gruppoL,cl,0);
        layout->addWidget(gruppo,cl,1,1,-1);
        ++cl;

        layout->addWidget(fattoreL,cl,0);
        layout->addWidget(fattore,cl,1,1,-1);
        ++cl;

        shared_ptr<Donatore> donatoreP = std::dynamic_pointer_cast<Donatore>(persona);
        if(donatoreP){
            donatore->setChecked(true);
            if(donatoreP->GetGruppoSanguigno().Gruppo() == "A")
                gruppo->setCurrentIndex(0);
            if(donatoreP->GetGruppoSanguigno().Gruppo() == "B")
                gruppo->setCurrentIndex(1);
            if(donatoreP->GetGruppoSanguigno().Gruppo() == "AB")
                gruppo->setCurrentIndex(2);
            if(donatoreP->GetGruppoSanguigno().Gruppo() == "O")
                gruppo->setCurrentIndex(3);
            fattore->setCurrentIndex(donatoreP.get()->GetGruppoSanguigno().Fattore());

        }else{
            gruppo->setEnabled(false);
            fattore->setEnabled(false);
        }

    }
    layout->setContentsMargins(60,50,60,0);
    layout->addWidget(invia,cl,0,Qt::AlignLeft);
    layout->addWidget(annulla,cl,1,Qt::AlignLeft);
    Disegna();

}

ModificaPersona::~ModificaPersona(){
    persona.reset();
}

void ModificaPersona::Invio(){
    char sesso = (sessoM->isChecked())? 'M' : 'F';
    shared_ptr<Personale> personale = std::dynamic_pointer_cast<Personale>(persona);
    if(personale) { //Personale
        QString stud = (studio)? studio->text() : "";
        emit invioS(personale,cognome->text(),nome->text(),codiceFiscale->text(),data->date(),
                    sesso,professione->currentText(),stud,stipendio->text().toDouble());
        close();
    }
    else {// Paziente
        bool f = (fattore && fattore->currentText() == "Positivo")? true : false;
        QString g = ( donatore->isChecked() )? gruppo->currentText() : "";
        emit invioS(persona,cognome->text(),nome->text(),codiceFiscale->text(),data->date(),sesso,g,f);
        close();
    }
}
