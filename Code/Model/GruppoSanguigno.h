#ifndef GRUPPOSANGUIGNO
#define GRUPPOSANGUIGNO

#include <QString>

class GruppoSanguigno{
private:
    QString gruppo_sanguigno;
    bool fattore;
public:
    GruppoSanguigno(const QString, const bool);//Nel caso qualcosa vada storto: gruppo_sanguigno = '?'
    ~GruppoSanguigno() = default;
    QString Gruppo() const;
    bool Fattore() const;
    QString GruppoCompleto() const; //Ritorna una stringa che descrive il gruppo e il fattore insieme

};

#endif // GRUPPOSANGUINEO

