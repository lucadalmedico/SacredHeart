#ifndef DONATORE
#define DONATORE

#include "GruppoSanguigno.h"
#include "Persona.h"

class Donatore : public Persona {
private:
    GruppoSanguigno gruppo;
public:
    Donatore(const QString,const QString,const QDate,const QString,const char,const QString,const bool);
    GruppoSanguigno &GetGruppoSanguigno();
    ~Donatore() = default;
    bool operator == ( const Persona&) const;
};

#endif // DONATOREMODEL

