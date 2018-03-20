#ifndef PRIMARIOWINDOW
#define PRIMARIOWINDOW

#include "PersonaleWindow.h"
#include "../Model/Database.h"

class PrimarioWindow : public PersonaleWindow  {
    Q_OBJECT
private:
    shared_ptr<Primario> persona;

    QMenu* AzioniFile;
    QAction* Apazienti;
    QAction* Adipendenti;
    QAction* Aeventi;
    QAction* backup;

    void CostruisciTabella(const vector<shared_ptr<Personale>>&);//costruisce la tabella dei dipendenti
public:
    PrimarioWindow(const shared_ptr<Primario>&);
    ~PrimarioWindow();
    QString GetFile();//apre una finestra per selezionare un file
    QString GetFolder();//apre una finestra per selezionare una cartella
private slots:
    void AskDipendenti();//richiede dipendenti
    void GetDipendenti(const vector<shared_ptr<Personale>>&);//ottiene i dipendenti e ne costruisce la tabella
    void AskVisite();
    void Info();
    void addP();//emette segnale per aggiungere pazienti da file
    void addD();//emette segnale per aggiungere dipendenti da file
    void addE();//emette segnale per aggiungere eventi da file
    void doBackup();//emette segnale per salvare tutti i file su una cartella
signals:
    void askD();//richiedi i dipendenti
    void addPazienti();//aggiungi pazienti da file
    void addDipendenti();//aggiungi dipendenti da file
    void addEventi();//aggiungi eventi da file
    void Backup();//salva tutti i file in una cartella
};


#endif // PRIMARIOWINDOW

