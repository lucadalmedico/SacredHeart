#include "LoginController.h"

LoginController::LoginController(const shared_ptr<Database> &x): dati(x){
    login = unique_ptr<LoginWindow>(new LoginWindow());
    login->show();
    connect(login.get(),SIGNAL(Inoltro(QString,QString)),this,SLOT(Controllo(QString,QString)));
}

LoginController::~LoginController(){
    window.reset();
    dati.reset();
    login.reset();
}

void LoginController::Controllo(const QString username, const QString password){
    if(dati.get()->GetPersonale().empty()){
        login->Error("Ci sono problemi nella lettura dei file, controlla i file nella cartella /Data");
    }
    else if(username == "" || password ==""){login->Error("I campi non possono essere vuoti");}
    else{
        const shared_ptr<Personale> persona = dati.get()->Login(username,password);
        if(persona != nullptr){
            dati.get()->CaricaDati();//Carico tutti i pazienti e gli appuntamenti
            if(window)
                window.reset();
            //Apro la finestra per l'utente
            const shared_ptr<Medico> medico = std::dynamic_pointer_cast<Medico>(persona);
            if(medico){
                const shared_ptr<Primario> primario = std::dynamic_pointer_cast<Primario>(medico);
                if(primario){
                    window = unique_ptr<PrimarioController>(new PrimarioController(primario,dati));
                }else {
                    window = unique_ptr<MedicoController>(new MedicoController(medico,dati));
                }
            }else{
                const shared_ptr<Segreteria> segreteria = std::dynamic_pointer_cast<Segreteria>(persona);
                if(segreteria){
                   window = unique_ptr<SegreteriaController>(new SegreteriaController(segreteria,dati));
                }
            }
            connect(window.get(),SIGNAL(log()),this,SLOT(Logout()));
            login->close();
        }else {
            login->Error("Dati inseriti non sono corretti");
        }
    }
}

void LoginController::Logout(){
    login.get()->Pulisci();
    login->show();
}
