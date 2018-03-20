#include "SegreteriaWindow.h"
SegreteriaWindow::SegreteriaWindow(const shared_ptr<Segreteria> &x) : persona(x) {

    elenchi->addAction(visite);
    elenchi->addAction(pazienti);

    azioni->addAction(aggiungi);
    azioni->addAction(modifica);
    azioni->addAction(elimina);
    azioni->addAction(info);
    azioni->addAction(salva);


    Costruisci();

    Disegna();
}


SegreteriaWindow::~SegreteriaWindow(){
    persona.reset();
}


void SegreteriaWindow::AskVisite() {
    emit askV(persona);
}

void SegreteriaWindow::Info(){
    emit SegnaleInformazioni(tabella->currentColumn(),tabella->currentRow(),persona);
}
