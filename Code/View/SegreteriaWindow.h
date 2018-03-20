#ifndef SEGRETERIAWINDOW_H
#define SEGRETERIAWINDOW_H

#include "PersonaleWindow.h"
#include "../Model/Segreteria.h"

class SegreteriaWindow : public PersonaleWindow{
    Q_OBJECT
private:
    shared_ptr<Segreteria> persona;
public:
    SegreteriaWindow(const shared_ptr<Segreteria>&);
    ~SegreteriaWindow();
private slots:
    void AskVisite();
    void Info();
};

#endif // SEGRETERIAWINDOW_H
