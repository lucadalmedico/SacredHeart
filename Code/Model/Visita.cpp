#include "Visita.h"

Visita::Visita (const QDateTime date, const Medico &dt, const Persona &p, const QString desc)
    : Evento(date,dt.Studio(),desc),dottore (dt), paziente(p) {}

Medico Visita::GetMedico() const {
    return dottore;
}

Persona Visita::GetPaziente() const {
    return paziente;
}

int Visita::Durata() const { // Una visita ha la durata di 30 minuti
    return 1800;
}
bool Visita::operator ==(const Evento& y) const {
    const Visita* x = dynamic_cast<const Visita*>(&y);
    return x && dottore == x->GetMedico() && paziente == x->GetPaziente() && x->GetData() >= GetData() && x->GetData() < GetData().addSecs(Durata());
}
