#include "LoginWindow.h"

LoginWindow::LoginWindow(){
    setFont(QFont("Verdana",18));
    login = new QPushButton("Accedi");
    login->setFixedSize(120,50);

    username = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);

    form = new QFormLayout;
    form->addRow("Username: ",username);
    form->addRow("Password: ",password);
    form->addWidget(login);
    form->setAlignment(login,Qt::AlignRight);
    form->setContentsMargins(50,150,50,0);

    layout->addLayout(form,0,0,-1,-1);
    Disegna();
    connect(login,SIGNAL(clicked(bool)),this,SLOT(Invia()));
    connect(username,SIGNAL(returnPressed()),login,SLOT(click()));
    connect(password,SIGNAL(returnPressed()),login,SLOT(click()));
}

LoginWindow::~LoginWindow() {
    delete login;
    delete username;
    delete password;
    delete form;
}

void LoginWindow::Invia() {
    emit Inoltro(username->text(),password->text());
}

void LoginWindow::Pulisci(){
    username->clear();
    password->clear();
}
