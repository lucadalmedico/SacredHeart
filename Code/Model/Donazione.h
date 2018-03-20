#ifndef DONAZIONE
#define DONAZIONE
#include "Donatore.h"
#include "Evento.h"
class Donazione : public Evento{
private:
    Donatore persona;
public:
    Donazione(const Donatore&, const QDateTime, const QString);
    Donatore GetDonatore() const;
    int Durata() const; //Gli uomini possono donare ogni 3 mesi, le donne ogni 4
    ~Donazione() = default;
    bool operator== (const Evento &) const;
};

#endif // DONAZIONE

