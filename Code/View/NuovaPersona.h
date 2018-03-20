#ifndef NUOVAPERSONA_H
#define NUOVAPERSONA_H

#include "AzioniPersona.h"

class NuovaPersona : public AzioniPersona {
     Q_OBJECT
private:
    bool personale;

    QLineEdit* username;
    QLineEdit* password1;
    QLineEdit* password2;

    QLabel* idL;
    QLabel* ps1;
    QLabel* ps2;



public:
    NuovaPersona(bool = false);//true = dipendente | false = paziente
    ~NuovaPersona();
private slots:
    void Invio();
signals:
    //invio paziente/donatore
    void invioS(const QString, const QString, const QString, const QDate, const char, const QString, const bool);
    //invio dipendente
    void invioS(const QString, const QString, const QString, const QDate, const char,QString, QString,
                QString, const QString, const double);

};

#endif // NUOVAPERSONA_H
