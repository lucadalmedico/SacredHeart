#include "CambioChiavi.h"

CambioChiavi::CambioChiavi(bool tipo){
    setMinimumSize(400,200);
    setGeometry(0,0,400,200);
    Centra();

    invio = new QPushButton("Invio");
    if(tipo){
        vecchio = nullptr;
        nuovo2 = nullptr;
        vecchioL = nullptr;
        nuovo2L = nullptr;

        nuovoL = new QLabel("Nuovo username: ");
        nuovo = new QLineEdit;

        connect(invio,SIGNAL(clicked()),this,SLOT(invioId()));
        connect(nuovo,SIGNAL(returnPressed()),invio,SLOT(click()));

        layout->addWidget(nuovoL,0,0);
        layout->addWidget(nuovo,0,1);
        layout->addWidget(invio,1,0,Qt::AlignBottom);
    }
    else{
        vecchio = new QLineEdit;
        vecchio->setEchoMode(QLineEdit::Password);
        nuovo2 = new QLineEdit;
        nuovo2->setEchoMode(QLineEdit::Password);
        nuovo = new QLineEdit;
        nuovo->setEchoMode(QLineEdit::Password);
        vecchioL = new QLabel("Vecchia password: ");
        nuovo2L = new QLabel("Nuova password: ");
        nuovoL = new QLabel("Ripeti nuova password: ");

        connect(invio,SIGNAL(clicked()),this,SLOT(invioPs()));

        connect(vecchio,SIGNAL(returnPressed()),invio,SLOT(click()));
        connect(nuovo2,SIGNAL(returnPressed()),invio,SLOT(click()));
        connect(nuovo,SIGNAL(returnPressed()),invio,SLOT(click()));

        layout->addWidget(vecchioL,0,0);
        layout->addWidget(vecchio,0,1);
        layout->addWidget(nuovo2L,1,0);
        layout->addWidget(nuovo2,1,1);
        layout->addWidget(nuovoL,2,0);
        layout->addWidget(nuovo,2,1);
        layout->addWidget(invio,3,0,Qt::AlignBottom);
    }
    Disegna();

}

CambioChiavi::~CambioChiavi(){
    delete vecchioL;
    delete nuovo2L;
    delete nuovoL;
    delete vecchio;
    delete nuovo2;
    delete nuovo;
    delete invio;
}

void CambioChiavi::invioId(){
    if(nuovo->text().isEmpty())
        Error("Campo usename vuoto");
    else{
        emit Cambio(nuovo->text());
        close();
    }
}

void CambioChiavi::invioPs(){
    if(nuovo->text().isEmpty() || vecchio->text().isEmpty() || nuovo2->text().isEmpty())
        Error("Compilare tutti i campi");
    else if(nuovo->text() != nuovo2->text())
        Error("Le password non coincidono");
    else {
        emit Cambio(vecchio->text(),nuovo2->text(),nuovo->text());
        close();
    }
}

