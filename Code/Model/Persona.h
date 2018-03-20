#ifndef PERSONA
#define PERSONA
#include <QDateTime>
#include <QString>

class Persona {
private:
    QString nome;
    QString cognome;
    QDate nascita;
    QString codiceFiscale;
    char sesso;
public:
    Persona(const QString ,const QString ,const QDate,const QString , char);
    QString Nome() const;
    QString Cognome() const;
    QDate DataNascita() const;
    QString CodiceFiscale() const;
    char Sesso() const;
    virtual bool operator == ( const Persona&) const;
    virtual ~Persona() = default;
};

#endif // PERSONA

