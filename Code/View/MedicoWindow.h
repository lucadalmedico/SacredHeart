#ifndef MEDICOWINDOW_H
#define MEDICOWINDOW_H

#include "PersonaleWindow.h"
#include "../Model/Medico.h"

class MedicoWindow : public PersonaleWindow {
    Q_OBJECT
protected:
    shared_ptr<Medico> persona;
public:
    MedicoWindow(const shared_ptr<Medico>&);
    ~MedicoWindow();
private slots:
    void AttivaInfo(const QModelIndex & ) const; //ridefinito perché si attivi solo sulla 2 colonna

    void GetVisite(const list<shared_ptr<Evento>>&);//ridefinito per togliere le terza colonna cioé
                                                    //il medico(é ovviamente sempre l'utente)
    void Info();
    void AskVisite();
signals:
    void SegnaleInformazioni(const int);
};

#endif // MEDICOWINDOW_H
