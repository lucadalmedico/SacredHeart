#include "PersonaleWindow.h"

PersonaleWindow::PersonaleWindow(){

    File = menuBar()->addMenu(tr("File"));
    Profilo = menuBar()->addMenu(tr("Profilo"));

    logout = new QAction(QIcon(":logout"),"Logout",this);
    esci = new QAction(QIcon(":esci"),"Chiudi",this);
    connect(esci,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(logout,SIGNAL(triggered(bool)),this,SLOT(Logout()));

    File->addAction(logout);
    File->addAction(esci);

    nuovoid = new QAction(QIcon(":chiave"),"Cambia username",this);
    nuovapss = new QAction(QIcon(":chiave"),"Cambia password",this);
    Pinfo = new QAction(QIcon(":info"),"Informazioni personali",this);

    connect(nuovoid,SIGNAL(triggered(bool)),this,SLOT(NewId()));
    connect(nuovapss,SIGNAL(triggered(bool)),this,SLOT(NewPw()));
    connect(Pinfo,SIGNAL(triggered(bool)),this,SLOT(InformazioniPersonali()));

    Profilo->addAction(nuovoid);
    Profilo->addAction(nuovapss);
    Profilo->addAction(Pinfo);

    elenchi = new QToolBar(this);
    azioni = new QToolBar(this);
    tabella = new QTableWidget(this);
    elenchi->setIconSize(QSize(50,30));
    azioni->setIconSize(QSize(30,30));

    visite = new QAction(QIcon(":appuntamenti"),"Elenco appuntamenti",this);
    personale = new QAction(QIcon(":dipendenti"),"Elenco dipendenti",this);
    pazienti = new QAction(QIcon(":pazienti"),"Elenco pazienti",this);

    aggiungi = new QAction(QIcon(":aggiungi"),"Aggiungi",this);
    modifica =  new QAction(QIcon(":modifica"),"Modifica",this);
    elimina =   new QAction(QIcon(":cancella"),"Elimina",this);
    info =   new QAction(QIcon(":info"),"Informazioni",this);
    salva = new QAction(QIcon(":salva"),"Salva",this);
    aggiorna = new QAction(QIcon(":aggiorna"),"Ricarica",this);

    aggiorna->setShortcut(QKeySequence::Refresh);
    aggiungi->setShortcuts(QKeySequence::New);
    elimina->setShortcuts(QKeySequence::Delete);
    salva->setShortcut(QKeySequence::Save);

    modifica->setDisabled(true);
    elimina->setDisabled(true);
    info->setDisabled(true);
    salva->setDisabled(true);

    azioni->addAction(aggiorna);

    connect(salva,SIGNAL(triggered(bool)),this,SLOT(SendSalva()));
    connect(info,SIGNAL(triggered()),this,SLOT(Info()));
    connect(pazienti,SIGNAL(triggered()),this,SLOT(AskPazienti()));
    connect(visite,SIGNAL(triggered()),this,SLOT(AskVisite()));
    connect(modifica,SIGNAL(triggered(bool)),this,SLOT(ModificaAppuntamento()));
    connect(aggiungi,SIGNAL(triggered(bool)),this,SLOT(Nuovo()));
    connect(elimina,SIGNAL(triggered(bool)),this,SLOT(Delete()));
    connect(aggiorna,SIGNAL(triggered(bool)),this,SLOT(Aggiorna()));
}

PersonaleWindow::~PersonaleWindow(){
    delete logout;
    delete esci;
    delete File;
    delete nuovoid;
    delete nuovapss;
    delete Pinfo;
    delete Profilo;

    delete visite;
    delete personale;
    delete pazienti;

    delete aggiungi;
    delete modifica;
    delete elimina;
    delete info;
    delete salva;

    elenchi->clear();
    delete elenchi;
    azioni->clear();
    delete azioni;
    tabella->clear();
    delete tabella;
}

void PersonaleWindow::CostruisciTabella(const list<shared_ptr<Evento> >& eventi) {
    tabella->clear();
    delete tabella;
    tabella = new QTableWidget(eventi.size(),5);
    QStringList header;
    header<<"Data"<<"Ora"<<"Paziente"<<"Medico"<<"Descrizione";
    tabella->setHorizontalHeaderLabels(header);

    int riga = 0;
    for( auto i = eventi.begin(); i != eventi.end(); ++i) {

        tabella->setCellWidget(riga,0,new QLabel((*i).get()->GetData().toString("dd/MM/yyyy")));
        tabella->setCellWidget(riga,1,new QLabel( (*i).get()->GetData().toString("hh:mm") ));
        shared_ptr<Visita> visita = std::dynamic_pointer_cast<Visita>(*i);
        if(visita) {
            tabella->setCellWidget(riga,2,new QLabel( visita.get()->GetPaziente().Cognome() + " " +
                                                      visita->GetPaziente().Nome() ));
            tabella->setCellWidget(riga,3,new QLabel( visita.get()->GetMedico().Cognome() + " " +
                                                      visita->GetMedico().Nome() ));
        }
        visita.reset();
        shared_ptr<Donazione> donazione = std::dynamic_pointer_cast<Donazione>(*i);
        if(donazione){
            tabella->setCellWidget(riga,2,new QLabel( donazione.get()->GetDonatore().Cognome() + " " +
                                                      donazione->GetDonatore().Nome() ));
            tabella->setCellWidget(riga,3,new QLabel);
        }

        tabella->setCellWidget(riga,4,new QLabel( (*i).get()->Descrizione() ));
        donazione.reset();
        if((*i).get()->GetData().date() == QDate::currentDate()){ //Colora la riga se l'appuntamento é oggi
            for(int i = 0; i < 5; ++i){
                tabella->setItem(riga, i, new QTableWidgetItem());
                tabella->item(riga,i)->setBackgroundColor(QColor::fromRgb(200, 230, 201));;
            }
        }
        ++riga;
    }
    tabella->horizontalHeader()->setMinimumWidth(100);
    tabella->horizontalHeader()->setStretchLastSection(true);
}

void PersonaleWindow::CostruisciTabella(const vector<shared_ptr<Persona>> &pazienti) {
    tabella->clear();
    delete tabella;
    tabella = new QTableWidget(pazienti.size(),6);

    QStringList header;
    header<<"Cognome"<<"Nome"<<"Data di nascita"<<"Codice fiscale"<<"Sesso"<<"Gruppo sanguigno";
    tabella->setHorizontalHeaderLabels(header);

    int riga = 0;
    for( auto i = pazienti.begin(); i != pazienti.end(); ++i) {  
        tabella->setCellWidget(riga,0,new QLabel((*i).get()->Cognome()));
        tabella->setCellWidget(riga,1,new QLabel((*i).get()->Nome()));
        tabella->setCellWidget(riga,2,new QLabel((*i).get()->DataNascita().toString("dd/MM/yyyy")));
        tabella->setCellWidget(riga,3,new QLabel((*i).get()->CodiceFiscale()));
        tabella->setCellWidget(riga,4,new QLabel(QString(QChar((*i).get()->Sesso()))));
        shared_ptr<Donatore> donatore = std::dynamic_pointer_cast<Donatore>(*i);
        if(donatore)
            tabella->setCellWidget(riga,5,new QLabel(donatore.get()->GetGruppoSanguigno().GruppoCompleto()));
        ++riga;
        donatore.reset();
    }
    tabella->horizontalHeader()->setMinimumWidth(100);
    tabella->horizontalHeader()->setStretchLastSection(true);

}


void PersonaleWindow::AttivaInfo(const QModelIndex& x) const {
    if(x.column() == 2 || x.column() == 3)
        info->setDisabled(false);
    else{
        info->setDisabled(true);
    }
    elimina->setDisabled(true);
    modifica->setDisabled(true);

}

void PersonaleWindow::attivaEM(const int) const{
    elimina->setDisabled(false);
    modifica->setDisabled(false);
    info->setDisabled(true);
}

void PersonaleWindow::modifiche(const bool x) const{
    if(x)
        salva->setDisabled(false);
    else
        salva->setDisabled(true);
}

void PersonaleWindow::AskPazienti(){
    emit askP();
}

void PersonaleWindow::Nuovo() {
    if(!pazienti->isEnabled())
        emit NuovoPSignal();
    if(!personale->isEnabled())
        emit NuovoDSignal();
    if(!visite->isEnabled())
        emit NuovoESignal();
}

void PersonaleWindow::GetPazienti(const vector<shared_ptr<Persona>>& elencoPazienti){
    personale->setDisabled(false);
    visite->setDisabled(false);
    pazienti->setDisabled(true);
    info->setVisible(false);
    info->setDisabled(true);
    elimina->setDisabled(true);
    modifica->setDisabled(true);
    PersonaleWindow::CostruisciTabella(elencoPazienti);
    layout->addWidget(tabella,2,0,2,-1);
    connect(tabella,SIGNAL(clicked(QModelIndex)),this,SLOT(AttivaInfo(QModelIndex)));
    connect(tabella->verticalHeader(), SIGNAL(sectionClicked(int)),this,SLOT(attivaEM(int)));
}


void PersonaleWindow::GetVisite(const list<shared_ptr<Evento> > &eventi){
    personale->setDisabled(false);
    visite->setDisabled(true);
    pazienti->setDisabled(false);
    info->setVisible(true);
    info->setDisabled(true);
    elimina->setDisabled(true);
    modifica->setDisabled(true);
    PersonaleWindow::CostruisciTabella(eventi);
    layout->addWidget(tabella,2,0,2,-1);
    connect(tabella,SIGNAL(clicked(QModelIndex)),this,SLOT(AttivaInfo(QModelIndex)));
    connect(tabella->verticalHeader(), SIGNAL(sectionClicked(int)),this,SLOT(attivaEM(int)));
}
void PersonaleWindow::closeEvent(QCloseEvent*){
    if(Conferma("Alcune modifiche non sono state salvate, salvarle ora?"))
        emit save();
}

void PersonaleWindow::SendSalva(){
    salva->setDisabled(true);
    emit save();
}

void PersonaleWindow::ModificaAppuntamento(){
    if(visite->isEnabled()){
        bool persona = !(pazienti->isEnabled());
        emit modificaS(tabella->currentRow(),persona);
    }else
        emit ModificaAppuntamento(tabella->currentRow());
}

void PersonaleWindow::Delete(){
    if(!pazienti->isEnabled())
        emit deletePaziente(tabella->currentRow());
    if(!personale->isEnabled())
        emit deleteDipendente(tabella->currentRow());
    if(!visite->isEnabled())
        emit deleteEvento(tabella->currentRow());
}

void PersonaleWindow::Aggiorna(){
    if( Conferma("Modifiche non salvate, continuare?") ){
        salva->setDisabled(true);
        emit update();
    }
}

void PersonaleWindow::AggiornaViste(){
    if(!visite->isEnabled())
        AskVisite();
    else if(!pazienti->isEnabled())
        emit askP();
    else if(!personale->isEnabled())
        emit askD();
}

void PersonaleWindow::Logout(){
    if(Conferma("Modifiche non salvate, continuare?"))
        emit log();
}

bool PersonaleWindow::Conferma(const QString avviso){
    bool conferma = true;
    if(salva->isEnabled()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Attenzione", avviso, QMessageBox::Yes|QMessageBox::No);
        if (reply != QMessageBox::Yes) {
            conferma = false;
        }
    }
    return conferma;
}

void PersonaleWindow::NewId(){
    emit newId();
}
void PersonaleWindow::NewPw(){
    emit newPw();
}
void PersonaleWindow::InformazioniPersonali(){
    emit pInfo();
}
void PersonaleWindow::Costruisci(){
    layout->addWidget(elenchi,0,1,Qt::AlignRight);
    layout->addWidget(azioni,0,0,Qt::AlignLeft);
    layout->addWidget(tabella,1,0,1,-1);
}
