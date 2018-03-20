#ifndef CAMBIOCHIAVI_H
#define CAMBIOCHIAVI_H


#include "Window.h"

class CambioChiavi:public Window{
    Q_OBJECT
private:
    QLabel* vecchioL;
    QLabel* nuovo2L;
    QLabel* nuovoL;
    QLineEdit* vecchio;
    QLineEdit* nuovo2;
    QLineEdit* nuovo;
    QPushButton* invio;
public:
    CambioChiavi(bool);//true = cambio username | false = cambio password
    ~CambioChiavi();
private slots:
    void invioId();//invia segnale per il cambio dell'username
    void invioPs();//invia segnale per il cambio password
signals:
    void Cambio(QString); //segnale cambio id
    void Cambio(QString,QString,QString); // segnale cambio password
};

#endif // CAMBIOCHIAVI_H
