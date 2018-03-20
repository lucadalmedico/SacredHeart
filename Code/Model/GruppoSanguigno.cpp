#include "GruppoSanguigno.h"


GruppoSanguigno::GruppoSanguigno(const QString gruppoS, const bool fattoreS): fattore(fattoreS){
    gruppo_sanguigno = (gruppoS.toUpper() == "AB" || gruppoS.toUpper() == "A" ||
                        gruppoS.toUpper() == "B" || gruppoS.toUpper() == "O")? gruppoS.toUpper() : "?";
}

QString GruppoSanguigno::Gruppo() const {
    return gruppo_sanguigno;
}

bool GruppoSanguigno::Fattore() const {
    return fattore;
}

QString GruppoSanguigno::GruppoCompleto() const {
    QString help = (fattore)? "Positivo" : "Negativo";
    return gruppo_sanguigno + " " + help;
}
