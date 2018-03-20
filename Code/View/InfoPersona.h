#ifndef INFOPERSONA_H
#define INFOPERSONA_H

#include "Window.h"
#include "../Model/Donatore.h"
#include "../Model/Primario.h"
#include "../Model/Segreteria.h"

class InfoPersona : public Window{
    Q_OBJECT
private:
    QLabel* cognome;
    QLabel* nome;
    QLabel* data;
    QLabel* cf;
    QLabel* sesso;
    QLabel* gruppo;
    QLabel* id;
    QLabel* stipendio;
    QLabel* studio;
    QLabel* prof;
public:
    InfoPersona(const shared_ptr<Persona>&, bool = false ,bool = false);
        //soggetto | possibilitá di vedere lo stipendio | possibilitá di vedere l'username
    ~InfoPersona();
    void AggiungiEvento(QWidget*); // Metodo per aggiungere eventualmente altri widget
};

#endif // INFOPERSONA_H
