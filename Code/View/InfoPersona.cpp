#include "InfoPersona.h"
InfoPersona::InfoPersona(const shared_ptr<Persona> &persona, bool permesso, bool username){
    setWindowTitle("Informazioni " + persona.get()->Cognome() + " " +
                   persona.get()->Nome() + " - SacredHeart");
    setWindowIcon(QIcon(":info"));
    setGeometry(0,0,500,500);Centra();

    cognome = new QLabel("Cognome:  " + persona.get()->Cognome());
    nome = new QLabel("Nome:  " + persona.get()->Nome());
    data = new QLabel("Data di nascita:  " + persona.get()->DataNascita().toString("dd/MM/yyyy"));
    cf = new QLabel("Codice Fiscale:  " + persona.get()->CodiceFiscale());
    sesso = new QLabel("Sesso:  " + static_cast<QString>(persona.get()->Sesso()) );

    gruppo = nullptr;
    stipendio = nullptr;
    studio = nullptr;
    prof = nullptr;
    id = nullptr;

    layout->addWidget(cognome,0,0);
    layout->addWidget(nome,1,0);
    layout->addWidget(data,2,0);
    layout->addWidget(cf,3,0);
    layout->addWidget(sesso,4,0);

    shared_ptr<Donatore> donatore = std::dynamic_pointer_cast<Donatore>(persona);
    if(donatore){
        gruppo = new QLabel("Gruppo sanguigno:  " + donatore.get()->GetGruppoSanguigno().GruppoCompleto());
        layout->addWidget(gruppo,5,0);
    }
    donatore.reset();
    shared_ptr<Personale> personale = std::dynamic_pointer_cast<Personale>(persona);
    if(personale){
        int cl =5;
        if(username){
            id = new QLabel("Username: " + personale.get()->Username());
            layout->addWidget(id,cl,0);
            ++cl;
        }
        QString professione = "";
        if(permesso){
            stipendio = new QLabel("Stipendio:  " + QString::number(personale.get()->Stipendio()));
            layout->addWidget(stipendio,cl,0);
            ++cl;
        }
        shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(persona);
        if(medico){
            if(std::dynamic_pointer_cast<Primario>(medico))
                professione = "Primario";
            else
                professione = "Medico";
            studio = new QLabel("Studio:  " + medico.get()->Studio());
            layout->addWidget(studio,cl,0);
            ++cl;
        }
        else
            if(std::dynamic_pointer_cast<Segreteria>(personale))
                professione = "Segreteria";
        prof = new QLabel("Professione:  " + professione);
        layout->addWidget(prof,cl,0);
    }
    personale.reset();
    layout->setContentsMargins(30,20,30,0);

    Disegna();
    setAttribute(Qt::WA_DeleteOnClose);
}

InfoPersona::~InfoPersona(){
    delete cognome;
    delete nome;
    delete data;
    delete cf;
    delete sesso;
    delete gruppo;
    delete id;
    delete stipendio;
    delete studio;
    delete prof;
}

void InfoPersona::AggiungiEvento(QWidget *x) {
    layout->addWidget(x);
}
