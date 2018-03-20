#include "Evento.h"

Evento::Evento(const QDateTime x, const QString s, const QString d):
    giorno(x),luogo(s),descrizione(d) {}

QDateTime Evento::GetData() const {
    return giorno;
}

QString Evento::Stanza() const {
    return luogo;
}

QString Evento::Descrizione() const {
    return descrizione;
}

