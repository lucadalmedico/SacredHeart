#ifndef EVENTO
#define EVENTO
#include <QDateTime>
#include <QString>

class Evento {
private:
    QDateTime giorno;
    QString luogo;
    QString descrizione;
public:
    Evento(const QDateTime,const QString, const QString ="");
    QDateTime GetData() const;
    QString Stanza() const;
    QString Descrizione() const;
    virtual int Durata() const = 0; //Durata standard di un evento
    virtual bool operator==(const Evento&) const = 0;
    virtual ~Evento() = default;
};

#endif // EVENTO

