# SacredHeart

L’idea alla base del progetto è quella di realizzare un’applicazione in C++/Qt per la gestione minimale dei dati all’interno di un ospedale. Viene fornita l’interfaccia da cui i dipendenti possono fare il login con le proprie credenziali e consultare i dati a cui hanno accesso. I tre tipi di utente presenti nel progetto sono:

1. **Primario**: ricopre il ruolo di amministratore, può esaminare tutte le visite attuali, consultare i pazienti o i dipendenti e modificarli,aggiungerli o eliminarli. Esso è l’unico utente che può aggiungere dati da file o esportarli in una cartella;
2. **Segreteria**: tipologia d’utente che gestisce gli appuntamenti e i pazienti: può aggiungere, cancellare o modificare i campi solo di questi due tipi;
3. **Medico**: utente base, può conoscere solo i propri appuntamenti e le informazioni dei pazienti delle sue visite.

## Specifica Progetto
### Scopo
Lo scopo del progetto è lo sviluppo in C++/Qt di un sistema di gestione ed accesso di un contenitore C di oggetti a libera scelta che soddisfi
alcuni vincoli obbligatori e che richieda approssimativamente 50-60 ore di lavoro complessivo.

### Vincoli Obbligatori
Il progetto consiste in un modulo di amministrazione ed in un modulo utente. I vincoli obbligatori sono i seguenti:
1. Il modulo di amministrazione deve permettere:
  - Lettura da file a memoria e scrittura da memoria su file del contenitore C. Non vi sono vincoli sulla tipologia del contenitore C
e sul formato di memorizzazione di C su file.
  - Inserimenti, rimozioni e modifiche degli oggetti di C in memoria. Non vi sono vincoli sulla natura degli oggetti memorizzati,
possibilmente anche di diversa natura.
  - Gestione degli utenti del sistema: registrazione, rimozione e modifiche di utenti.
  - Si devono prevedere più tipi di registrazione per gli utenti, in cui ogni tipo di registrazione garantisce all’utente diversi servizi di
accesso al contenitore C, ad esempio fornisce diverse capacità di interrogazione e ricerca.
2. Il modulo utente deve permettere ad un utente registrato U di accedere al contenitore C secondo i servizi di accesso garantiti ad U dal
suo tipo di registrazione.
3. Sia il modulo di amministrazione che il modulo utente devono essere dotati di una GUI sviluppata nel framework Qt.
