#include "Donatore.h"

Donatore::Donatore(const QString nm, const QString cgn, const QDate ns, const QString cf,
                   const char ss, const QString gruppoS, const bool fattoreS)
    : Persona(nm,cgn,ns,cf,ss),gruppo(GruppoSanguigno(gruppoS,fattoreS)){}

GruppoSanguigno& Donatore::GetGruppoSanguigno() {
    return gruppo;
}

bool Donatore::operator == ( const Persona& x) const{
    return dynamic_cast<const Donatore*>(&x) && this->CodiceFiscale() == x.CodiceFiscale();
}
