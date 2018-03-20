#include "ModificaEvento.h"

ModificaEvento::ModificaEvento(const shared_ptr<Database> &x, const shared_ptr<Evento> y)
    : AzioniEvento(x),evento(y){

    setWindowTitle("Modifica appuntamento - SacredHeart");
    setWindowIcon(QIcon(":modifica"));
    invia->setText("Modifica");

    connect(invia,SIGNAL(clicked()),this,SLOT(Invio()));

    descrizione->setText(evento.get()->Descrizione());
    data->setDate(evento.get()->GetData().date());
    time->setTime(evento.get()->GetData().time());

    //Set pazienti e medici
    bool fine = false;
    shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(evento);
    if(visita){
        SoloMedici();
        //Imposto l' indice del QComboBox con il medico della visita
        for(int i = 0 ;!fine && i < medici->count(); ++i)
            if( medici->itemText(i) == (visita.get()->GetMedico().Cognome() + " " +
                                        visita.get()->GetMedico().Nome()) ){
                medici->setCurrentIndex(i);
                fine =true;
            }
        layout->addWidget(medico,0,0,Qt::AlignCenter);
        layout->addWidget(medici,0,1);
        TuttiPazienti();
        int p = 0;fine = false;
        //Imposto l' indice del QComboBox con il paziente della visita
        for(auto i = supporto.begin();!fine && i != supporto.end(); ++i){
            if( (*i).get()->CodiceFiscale() == visita.get()->GetPaziente().CodiceFiscale()){
                pazienti->setCurrentIndex(p);
                fine = true;
            }
            ++p;
        }
    }
    visita.reset();

    shared_ptr<Donazione> donazione = std::dynamic_pointer_cast<Donazione>(evento);
    if(donazione){
        SoloDonatori();
        int p = 0;
        //Imposto l' indice del QComboBox con il donatore della visita
        for(auto i = supporto.begin(); i != supporto.end(); ++i){
            if( (*i).get()->CodiceFiscale() == donazione.get()->GetDonatore().CodiceFiscale())
                pazienti->setCurrentIndex(p);
            ++p;
        }
    }

    donazione.reset();
    layout->addWidget(paziente,1,0,Qt::AlignCenter);
    layout->addWidget(pazienti,1,1);

    layout->addWidget(datal,2,0,Qt::AlignCenter);
    layout->addWidget(data,2,1);

    layout->addWidget(timel,3,0,Qt::AlignCenter);
    layout->addWidget(time,3,1);

    layout->addWidget(desc,4,0,Qt::AlignCenter);
    layout->addWidget(descrizione,4,1);

    layout->addWidget(invia,5,0,Qt::AlignLeft);
    layout->addWidget(annulla,5,1,Qt::AlignLeft);
    Disegna();

}

ModificaEvento::~ModificaEvento(){
    evento.reset();
}
void ModificaEvento::Invio(){
    shared_ptr<Medico> medico = (std::dynamic_pointer_cast<Visita>(evento))?
                std::dynamic_pointer_cast<Medico>(mediciList.at(medici->currentIndex())) : nullptr;
    QDateTime orario(data->date(),time->time());
    emit invio(evento,medico,supporto.at(pazienti->currentIndex()),orario,descrizione->text());
    close();
}
