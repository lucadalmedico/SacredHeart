#ifndef AZIONIEVENTO_H
#define AZIONIEVENTO_H

#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>

#include "Window.h"
#include "../Model/Database.h"

class AzioniEvento : public Window {
    Q_OBJECT
protected:
    shared_ptr<Database> dati;
    vector<shared_ptr<Personale>> mediciList; //Lista dei medici
    vector<shared_ptr<Persona>> supporto; //Contiene o tutti i pazienti o solo i donatori
    QPushButton* invia;
    QPushButton* annulla;
    QCheckBox* donazione;
    QComboBox* medici;//per scegliere tra i medici (se necessario)
    QComboBox* pazienti;//per scegliere tra i pazienti/donatori
    QLabel* medico;
    QLabel* paziente;
    QLabel* dona;
    QLabel* desc;
    QLabel* datal;
    QLabel* timel;

    QDateEdit* data;
    QTimeEdit* time;
    QLineEdit* descrizione;

    AzioniEvento(const shared_ptr<Database>&);
    virtual ~AzioniEvento();
    void TuttiPazienti(); //Inserisce in supporto tutti i pazienti
    void SoloDonatori(); //Inserisce in supporto solo i donatori
    void Carica(bool = false); //Carica in supporto: true = solo donatori | false = tutti i pazienti
    void SoloMedici(); //Carica in medici solo il personale con tipo Medico
protected slots:
    void CambioTipoPaziente(bool);
};

#endif // AZIONIEVENTO_H
