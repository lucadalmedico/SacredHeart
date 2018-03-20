#ifndef MEDICO
#define MEDICO

#include "Personale.h"

class Medico : public Personale {
private:
    QString studio;
public:
    Medico(const QString, const QString, const QDate , const QString, const char,
           const double, const QString, const QString = "", const QString = "");

    QString Studio() const;
    virtual ~Medico() = default;
    //Cerca gli eventi personali
    virtual list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>> &) const;
    //Cerca eventi di un paziente
    virtual list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>>&, const shared_ptr<Persona>&) const;
};

#endif // MEDICO

