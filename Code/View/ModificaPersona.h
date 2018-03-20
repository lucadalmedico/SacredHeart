#ifndef MODIFICAPERSONA_H
#define MODIFICAPERSONA_H

#include "AzioniPersona.h"
#include "../Model/Donatore.h"
#include "../Model/Primario.h"
#include "../Model/Segreteria.h"

class ModificaPersona : public AzioniPersona{
    Q_OBJECT
private:
    shared_ptr<Persona> persona;

public:
   ModificaPersona(const shared_ptr<Persona>& );
    ~ModificaPersona();
private slots:
   void Invio();

signals:
   //segnale per paziente/donatore
   void invioS(shared_ptr<Persona>&,const QString, const QString, const QString, const QDate,
               const char, const QString, const bool);
   //segnale per dipendente
   void invioS(shared_ptr<Personale>&,const QString, const QString, const QString, const QDate,
               const char, const QString, const QString, const double);
};

#endif // MODIFICAPERSONA_H
