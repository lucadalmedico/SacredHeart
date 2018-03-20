#ifndef NUOVOEVENTO_H
#define NUOVOEVENTO_H

#include "AzioniEvento.h"

class NuovoEvento :public AzioniEvento{
      Q_OBJECT
public:
    NuovoEvento(const shared_ptr<Database>&);
    ~NuovoEvento() = default;
private slots:
    void invio();
    void PrimaDataDisponibile(const int);
signals:
    void invio(const shared_ptr<Medico>&,const shared_ptr<Persona>&,const bool,
               const QDateTime,const QString);
};

#endif // NUOVOEVENTO_H
