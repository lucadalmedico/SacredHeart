#ifndef PERSONALEWINDOW_H
#define PERSONALEWINDOW_H


#include <QTableWidget>
#include <QHeaderView>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QFileDialog>

#include "Window.h"
#include "../Model/Visita.h"
#include "../Model/Donazione.h"


class PersonaleWindow : public Window {
    Q_OBJECT
protected:
    QMenu* File;
    QAction* logout;
    QAction* esci;
    QMenu* Profilo;
    QAction* nuovoid;
    QAction* nuovapss;
    QAction* Pinfo;

    QTableWidget* tabella;
    QToolBar* elenchi;
    QToolBar* azioni;

    QAction* visite;
    QAction* personale;
    QAction* pazienti;

    QAction* aggiungi;
    QAction* aggiorna;
    QAction* modifica;
    QAction* elimina;
    QAction* info;
    QAction* salva;
public:
    PersonaleWindow();
    virtual ~PersonaleWindow();
protected:
    bool Conferma(const QString);//crea una finestra di avviso con messaggio da inserire bloccando l'azione dell'utente
    void Costruisci();//aggiunge a layout elenchi, azioni e tabella
    void CostruisciTabella(const list<shared_ptr<Evento>>&);//costruisce la tabella di appuntamenti contenuti nella lista
    void CostruisciTabella(const vector<shared_ptr<Persona>>&); //costruisce la tabella di pazienti contentuti nel vector
protected slots:
    void AttivaInfo(const QModelIndex&) const;//attiva/disattiva il pulsante info
    void attivaEM(const int) const;//attiva/disattiva pulsanti modifica ed elimina
    void modifiche(const bool) const;//attiva/disattiva il pulsante salva se sono state esaguite azioni
    virtual void Info() = 0;//Emette il segnale per le informazioni in una cella della tabella
    void Nuovo();//Emette il segnale per inserire una nuova riga nella tabella
    void AskPazienti();//Emette il segnale per richiedere il vettore dei pazienti
    virtual void AskVisite() = 0;//richiede le visite a seconda del metodo di ricerca del dipendente
    void GetPazienti(const vector<shared_ptr<Persona>>&);//ottiene i pazienti e costruisce la tabella
    void GetVisite(const list<shared_ptr<Evento>>&);//ottiene gli appuntamenti e costruisce la tabella
    void closeEvent(QCloseEvent*);//salva i dati quando viene chiusa la finestra
    void SendSalva();//emette il segnale per salvare i dati
    void ModificaAppuntamento();//emette il segnale per modificare una riga della tabella
    void Delete();//emette il segnale per eliminare una riga della tabella
    void Aggiorna();//Ricarica il database ed emette il segnale per aggiornare la tabella
    void AggiornaViste();//Richiede i dati per aggiornare la tabella
    void Logout();//emette il segnale per il logout
    void NewId();//emette il segnale per cambiare username
    void NewPw();//emette il segnale per cambiare password
    void InformazioniPersonali();//emette il segnale per conoscere i propri dati
signals:
    void SegnaleInformazioni(const int,const int,const shared_ptr<Personale>&);//richiede informazioni sulla tabella
    void NuovoPSignal();//nuovo paziente
    void NuovoDSignal();//nuovo dipendente
    void NuovoESignal();//nuovo evento
    void askP();//richiede pazienti
    void askV(const shared_ptr<Personale>&);//richiede le visite secondo i metodi di ricerca del
                                            //dipendente
    void askD();//richiede i dipendenti
    void save();//salva i dati
    void update();//aggiorna la tabella
    void modificaS(const int,const bool);//modifica persona(paziente o dipendente)
    void ModificaAppuntamento(const int);//modifica evento nella riga int
    void deletePaziente(const int);//elimina il paziente
    void deleteEvento(const int);//elimina l'evento
    void deleteDipendente(const int);//elimina il dipendente
    void log();//richiede logout
    void newId();//richiede nuovo id
    void newPw();//richiede nuova password
    void pInfo();//richiede le informazioni personali
};

#endif // PERSONALEWINDOW_H
