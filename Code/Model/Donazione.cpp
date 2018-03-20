#include "Donazione.h"

Donazione::Donazione(const Donatore & dn, const QDateTime tm, const QString desc)
    :Evento(tm,"Centro trasfusionale",desc), persona(dn) {}

Donatore Donazione::GetDonatore() const {
    return persona;
}

int Donazione::Durata() const {
    int rit = 0;
    if(persona.Sesso() == 'M')
        rit = 3;
    else
        rit = 4;
    return rit;
}

bool Donazione::operator ==(const Evento& y) const{
    const Donazione* x =  dynamic_cast<const Donazione*>(&y);
    return x && x->GetData() >= GetData() && x->GetData() < GetData().addMonths(Durata()) &&
            persona == x->GetDonatore();
}
