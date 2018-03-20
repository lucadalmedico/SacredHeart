#ifndef MODIFICAEVENTO_H
#define MODIFICAEVENTO_H

#include "AzioniEvento.h"

class ModificaEvento :public AzioniEvento{
    Q_OBJECT
private:
    shared_ptr<Evento> evento;
public:
    ModificaEvento(const shared_ptr<Database>&, const shared_ptr<Evento>);
    ~ModificaEvento();
private slots:
    void Invio();
signals:
    void invio(shared_ptr<Evento>&,const shared_ptr<Medico>&,const shared_ptr<Persona>&,
               const QDateTime,const QString);
};

#endif // MODIFICAEVENTO_H
