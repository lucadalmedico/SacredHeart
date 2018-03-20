#include "Persona.h"

Persona::Persona(const QString nm, const QString cgn, const QDate ns, const QString cf, const char ss)
    : nome(nm), cognome(cgn),nascita (ns), codiceFiscale(cf), sesso ((toupper(ss) == 'M' ||
                                                                      toupper(ss) == 'F')? toupper(ss): '?'  ){
}

QString Persona::Nome() const{
    return nome;
}

QString Persona::Cognome() const{
    return cognome;
}

QDate Persona::DataNascita() const {
    return nascita;
}

QString Persona::CodiceFiscale() const {
    return codiceFiscale;
}

char Persona::Sesso() const {
    return sesso;
}

bool Persona::operator ==(const Persona& x) const{
    return CodiceFiscale() == x.CodiceFiscale();
}
