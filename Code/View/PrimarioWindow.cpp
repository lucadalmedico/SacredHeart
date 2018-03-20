
#include "PrimarioWindow.h"

PrimarioWindow::PrimarioWindow(const shared_ptr<Primario> &x) :persona(x) {

    AzioniFile = menuBar()->addMenu(tr("Importa/Esporta"));

    Apazienti = new QAction(QIcon(":apri"),"Aggiungi pazienti da file",this);
    Adipendenti = new QAction(QIcon(":apri"),"Aggiungi dipendenti da file",this);
    Aeventi = new QAction(QIcon(":apri"),"Aggiungi appuntamenti da file",this);
    backup = new QAction(QIcon(":backup"),"Esporta file di backup",this);

    AzioniFile->addAction(Apazienti);
    AzioniFile->addAction(Adipendenti);
    AzioniFile->addAction(Aeventi);
    AzioniFile->addAction(backup);

    connect(Apazienti,SIGNAL(triggered(bool)),this,SLOT(addP()));
    connect(Adipendenti,SIGNAL(triggered(bool)),this,SLOT(addD()));
    connect(Aeventi,SIGNAL(triggered(bool)),this,SLOT(addE()));
    connect(backup,SIGNAL(triggered(bool)),this,SLOT(doBackup()));

    elenchi->addAction(visite);
    elenchi->addAction(personale);
    elenchi->addAction(pazienti);

    azioni->addAction(aggiungi);
    azioni->addAction(modifica);
    azioni->addAction(elimina);
    azioni->addAction(info);
    azioni->addAction(salva);

    Costruisci();

    Disegna();

    connect(personale,SIGNAL(triggered()),this,SLOT(AskDipendenti()));

}

PrimarioWindow::~PrimarioWindow(){
    delete AzioniFile;
    delete Apazienti;
    delete Adipendenti;
    delete Aeventi;
    delete backup;

    persona.reset();
}


void PrimarioWindow::GetDipendenti(const vector<shared_ptr<Personale> > &dipendenti) {
    personale->setDisabled(true);
    visite->setDisabled(false);
    pazienti->setDisabled(false);
    info->setVisible(false);
    info->setDisabled(true);
    elimina->setDisabled(true);
    modifica->setDisabled(true);
    tabella = new QTableWidget;
    CostruisciTabella(dipendenti);
    layout->addWidget(tabella,2,0,2,-1);
    connect(tabella,SIGNAL(clicked(QModelIndex)),this,SLOT(AttivaInfo(QModelIndex)));
    connect(tabella->verticalHeader(), SIGNAL(sectionClicked(int)),this,SLOT(attivaEM(int)));
}

void PrimarioWindow::AskDipendenti(){
    emit askD();
}

void PrimarioWindow::CostruisciTabella(const vector<shared_ptr<Personale> > &dipendenti) {
    tabella->clear();
    delete tabella;
    tabella = new QTableWidget(dipendenti.size(),8);

    QStringList header;
    header<<"Cognome"<<"Nome"<<"Data di nascita"<<"Codice fiscale"<<"Sesso"<<"Stipendio"<<"Studio"<<"Professione";
    tabella->setHorizontalHeaderLabels(header);

    int riga = 0;
    for( auto i = dipendenti.begin();i != dipendenti.end(); ++i) {
        tabella->setCellWidget(riga,0,new QLabel((*i).get()->Cognome()));
        tabella->setCellWidget(riga,1,new QLabel((*i).get()->Nome()));
        tabella->setCellWidget(riga,2,new QLabel((*i).get()->DataNascita().toString("dd/MM/yyyy")));
        tabella->setCellWidget(riga,3,new QLabel((*i).get()->CodiceFiscale()));
        tabella->setCellWidget(riga,4,new QLabel(QString(QChar((*i).get()->Sesso()))));
        shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(*i);
        if(!medico){ //tipo segreteria
            tabella->setCellWidget(riga,5,new QLabel(
                                       QString::number((std::dynamic_pointer_cast<Segreteria>(*i)).get()->Stipendio())));
            tabella->setCellWidget(riga,7,new QLabel("Segreteria"));
        }
        else{
            tabella->setCellWidget(riga,5,new QLabel(QString::number(medico.get()->Stipendio())));
            tabella->setCellWidget(riga,6,new QLabel(medico.get()->Studio()));
            if(std::dynamic_pointer_cast<Primario>(medico))
                 tabella->setCellWidget(riga,7,new QLabel("Primario"));
            else
                 tabella->setCellWidget(riga,7,new QLabel("Medico"));

        }
        medico.reset();

        ++riga;
    }
    tabella->horizontalHeader()->setMinimumWidth(100);
    tabella->horizontalHeader()->setStretchLastSection(true);

}

void PrimarioWindow::AskVisite() {
    emit askV(persona);
}

void PrimarioWindow::Info(){
    emit SegnaleInformazioni(tabella->currentColumn(),tabella->currentRow(),persona);
}

void PrimarioWindow::addP(){
    emit addPazienti();
}

void PrimarioWindow::addD(){
    emit addDipendenti();
}
void PrimarioWindow::addE(){
    emit addEventi();
}

void PrimarioWindow::doBackup(){
    emit Backup();
}
QString PrimarioWindow::GetFile(){
    return QFileDialog::getOpenFileName(this,tr("Apri"), QDir::currentPath(), tr("xml files (*.xml)"));
}

QString PrimarioWindow::GetFolder(){
    return QFileDialog::getExistingDirectory(this,tr("Seleziona cartella"), QDir::currentPath());
}
