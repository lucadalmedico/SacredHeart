#ifndef VISITA
#define VISITA
#include "Medico.h"
#include "Evento.h"

class Visita : public Evento{
private:
    Medico dottore;
    Persona paziente;
public:
    Visita(const QDateTime,const Medico &,const Persona&,const QString);
    ~Visita() = default;
    Medico GetMedico() const;
    Persona GetPaziente() const;
    int Durata() const; //30min
    bool operator== (const Evento &) const;

};

#endif // VISITA

