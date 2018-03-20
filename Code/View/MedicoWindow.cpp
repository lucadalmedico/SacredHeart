#include "MedicoWindow.h"

MedicoWindow::MedicoWindow(const shared_ptr<Medico> &x): persona(x){
    azioni->addAction(info);

    Costruisci();
    Disegna();

}

MedicoWindow::~MedicoWindow(){
    persona.reset();
}

void MedicoWindow::GetVisite(const list<shared_ptr<Evento>>& eventi){
    CostruisciTabella(eventi);
    tabella->removeColumn(3);
    connect(tabella,SIGNAL(clicked(QModelIndex)),this,SLOT(AttivaInfo(QModelIndex)));
    layout->addWidget(tabella,2,0,2,-1);
}

void MedicoWindow::AttivaInfo(const QModelIndex& x) const{
    if(x.column() == 2)
        info->setDisabled(false);
    else
        info->setDisabled(true);

}

void MedicoWindow::Info(){
    emit SegnaleInformazioni(tabella->currentRow());
}

void MedicoWindow::AskVisite() {
    emit askV(persona);
}
