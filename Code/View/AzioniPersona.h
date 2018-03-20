#ifndef AZIONIPERSONA_H
#define AZIONIPERSONA_H

#include <memory>
#include <QDateEdit>
#include <QCheckBox>
#include <QComboBox>

#include "../Model/Persona.h"
#include "Window.h"

using std::shared_ptr;

class AzioniPersona : public Window{
    Q_OBJECT
protected:
    AzioniPersona();
    virtual ~AzioniPersona();


    QPushButton* invia;
    QPushButton* annulla;

    QLineEdit* cognome;
    QLineEdit* nome;
    QLineEdit* codiceFiscale;
    QDateEdit* data;
    QCheckBox* sessoM;
    QCheckBox* sessoF;
    QComboBox* gruppo; //insieme di tutti i gruppi sanguinei
    QComboBox* fattore; //tipo del fattore del gruppo sanguigno(positivo/negativo)
    QComboBox* professione;//insieme di tutti i tipi di personale
    QLineEdit* stipendio;
    QLineEdit* studio;

    QLabel* cognomeL;
    QLabel* nomeL;
    QLabel* codiceFiscaleL;
    QLabel* dataL;
    QLabel* sessoL;
    QLabel* gruppoL;
    QLabel* fattoreL;
    QLabel* professioneL;

    QLabel* stipendioL;
    QLabel* studioL;

    QCheckBox* donatore;
    QLabel* donatoreL;
protected slots:
    void CambioPersonale(QString);//attiva il campo per l'inserimento dello studio solo se
                        //si tratta di un medico (quindi anche per il primario)

    void CambioDonatore();//se si vuole inserire un donatore abilita i campi
                            //per inserire il gruppo sanguigno

    //Metodi per deselezionare automaticamenti sessoM o sessoF
    void CambioSM(bool);
    void CambioSF(bool);
};

#endif // AZIONIPERSONA_H
