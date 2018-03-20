#include "NuovoEvento.h"

NuovoEvento::NuovoEvento(const shared_ptr<Database> &x) : AzioniEvento(x){
    setWindowTitle("Nuovo appuntamento - SacredHeart");
    setWindowIcon(QIcon(":aggiungi"));
    invia->setText("Aggiungi");

    connect(invia,SIGNAL(clicked()),this,SLOT(invio()));

    SoloMedici();
    TuttiPazienti();

    layout->addWidget(medico,0,0,Qt::AlignCenter);
    layout->addWidget(medici,0,1);

    layout->addWidget(paziente,1,0,Qt::AlignCenter);
    layout->addWidget(pazienti,1,1);
    connect(pazienti,SIGNAL(currentIndexChanged(int)),this,SLOT(PrimaDataDisponibile(int)));

    layout->addWidget(dona,2,0,Qt::AlignRight);
    layout->addWidget(donazione,2,1);

    layout->addWidget(datal,3,0,Qt::AlignCenter);
    layout->addWidget(data,3,1);

    layout->addWidget(timel,4,0,Qt::AlignCenter);
    layout->addWidget(time,4,1);

    layout->addWidget(desc,5,0,Qt::AlignCenter);
    layout->addWidget(descrizione,5,1);

    layout->addWidget(invia,6,0,Qt::AlignLeft);
    layout->addWidget(annulla,6,1,Qt::AlignLeft);
    Disegna();
}

void NuovoEvento::invio(){
    shared_ptr<Medico> medico = (!donazione->isChecked())?
                std::dynamic_pointer_cast<Medico>(mediciList.at(medici->currentIndex())) : nullptr;
    QDateTime orario(data->date(),time->time());
    emit invio(medico,supporto.at(pazienti->currentIndex()),donazione->isChecked(),orario,descrizione->text());
    close();
}

void NuovoEvento::PrimaDataDisponibile(const int index){

    if(donazione->isChecked() && static_cast<unsigned int>(index) < supporto.size() && index > -1){
        shared_ptr<Donatore> x =std::dynamic_pointer_cast<Donatore>
                (supporto.at(index));
        QDate ultimaDonazione;
        int durata = Donazione(*x.get(),QDateTime(),QString()).Durata();

        for(auto i = dati.get()->GetAgenda().begin(); i != dati.get()->GetAgenda().end()
            ;++i){
            shared_ptr<Donazione> d = std::dynamic_pointer_cast<Donazione>(*i);
            if(d && d.get()->GetDonatore() == *x.get() && d.get()->GetData().date() > ultimaDonazione )
                ultimaDonazione = d.get()->GetData().date();
            d.reset();
        }
        if ( QDate::currentDate().addMonths(-durata) < ultimaDonazione){
            ultimaDonazione = ultimaDonazione.addMonths(durata);
            ultimaDonazione = ultimaDonazione.addDays(1);
        }
        else {
            ultimaDonazione = QDate::currentDate();
        }
        data->setMinimumDate(ultimaDonazione);
        data->setDate(ultimaDonazione);
        x.reset();
    }
    else {
        data->setMinimumDate(QDate::currentDate());
        data->setDate(data->minimumDate());
    }
}
