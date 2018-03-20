#ifndef PERSONALE
#define PERSONALE

#include <list>
#include <vector>
#include <memory>


#include "Persona.h"
#include "Donazione.h"
/*#include "Visita.h" nel file sorgente (è incluso perchè serve nella definizione dei metodi di
Functor, se viene messo in questo file header crea un errore perchè la classe Visita include il file Medico.h,
viene fatta questa scelta anche se non elegante per mantenere la classe Functor diponibile solo ai alle classe derivate
de Personale)
*/

using std::shared_ptr;
using std::unique_ptr;
using std::list;
using std::vector;

class Personale : public Persona {
friend class Database;
private:
    double stipendio;
    QString id;
    QString password;
protected:
    class Functor {
    public:
        int tipo;
        Functor(int = -1);
        bool operator () (const shared_ptr<Evento>&, const shared_ptr<Persona>&) const;//Ricerca con dipendente/paziente
    };

public:
    Personale(const QString, const QString, const QDate , const QString, const char,
              const double, const QString ="", const QString ="");
    double Stipendio() const;
    QString Username() const;
    void CambioPassword(const QString,const QString,const QString);
    void CambioUsername(const QString);
    void CopiaCredenziali(shared_ptr<Personale>&) const;//permette di copiare le credenziali senza
                                                        //rendere pubblica la password
    bool ControlloUsername(const QString,const vector<shared_ptr<Personale>>&) const;//controllo se l'username é giá in uso
    virtual ~Personale() = default;

    virtual list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>>&, const shared_ptr<Persona>&) const = 0;
    virtual list<shared_ptr<Evento>> Ricerca(const list<shared_ptr<Evento>>&) const = 0;

};

#endif // PERSONALE

