#include "Database.h"

QString Database::Datapath() const{
    QDir p = QDir::current();
    return (p.path() + "/Data/");
}

list<shared_ptr<Evento> > &Database::GetAgenda(){
    return appuntamenti;
}

vector<shared_ptr<Personale> > &Database::GetPersonale(){
    return personale;
}

vector<shared_ptr<Persona> > &Database::GetPazienti() {
    return pazienti;
}

Database::Database(){LoadPersonale();}

Database::~Database(){Pulisci();}

void Database::Salva(){CloseAgenda(); ClosePersonale(); ClosePazienti(); Carica();}

void Database::Carica(){Pulisci(); LoadPersonale(); LoadPazienti(); LoadAgenda();}

void Database::CaricaDati(){LoadPazienti(); LoadAgenda();}

void Database::Pulisci(){appuntamenti.clear(); personale.clear(); pazienti.clear();}

shared_ptr<Personale> Database::Login(const QString username, const QString password) const{
    shared_ptr<Personale> ritorno = nullptr;
    bool trovato = false;
    for( auto i = personale.begin();!trovato && i != personale.end(); ++i) {
        if((*i)->Username() == username && (*i)->password == password){
            trovato = true;
            ritorno = *i;
        }
    }
    return ritorno;
}

void Database::Esporta(QString path) const{
    QFile* pazientiFile = new QFile(path + "/Pazienti.xml");
    QFile* personaleFile = new QFile(path + "/Personale.xml");
    QFile* eventiFile = new QFile(path + "/Appuntamenti.xml");
    ClosePazienti(pazientiFile);
    ClosePersonale(personaleFile);
    CloseAgenda(eventiFile);
}

void Database::AggiungiPazienti(QString path){
    QFile* file = new QFile(path);
    LoadPazienti(file);
}

void Database::AggiungiDipendenti(QString path){
    QFile* file = new QFile(path);
    LoadPersonale(file);
}

void Database::AggiungiEventi(QString path){
    QFile* file = new QFile(path);
    LoadAgenda(file);
}

void Database::LoadPersonale(){
    QFile* file = new QFile(Datapath() + "Personale.xml");
    LoadPersonale(file);
}


void Database::LoadPazienti() {
    QFile* file = new QFile(Datapath() + "Pazienti.xml");
    LoadPazienti(file);
}

void Database::LoadAgenda(){

    QFile* file = new QFile(Datapath() + "Appuntamenti.xml");
    LoadAgenda(file);
}
void Database::ClosePersonale() const{
    QFile* file = new QFile(Datapath() + "Personale.xml");
    ClosePersonale(file);
}

void Database::CloseAgenda() const{
    QFile* file = new QFile(Datapath() + "Appuntamenti.xml");
    CloseAgenda(file);
}

void Database::ClosePazienti() const{
    QFile* file = new QFile(Datapath() + "Pazienti.xml");
    ClosePazienti(file);
}

void Database::LoadPersonale(QFile* file){
    if(file->exists() && file->open(QIODevice::ReadOnly)) {

        QString Nome,Cognome,Codicefiscale,id,psw,Studio = "";
        QDate Data;
        char Sesso = '?';
        double Stipendio = 0;
        int type = -1;
        QXmlStreamReader Reader(file);
        while (!Reader.atEnd()){

            if(Reader.isStartElement()){
                if(Reader.name() == "Personale") Reader.readNext();
                else if(Reader.name() == "Medico" ) type = 0;
                else if(Reader.name() == "Primario" ) type = 1;
                else if(Reader.name() == "Segreteria" ) type = 2;

                foreach (const QXmlStreamAttribute &attr, Reader.attributes())
                { //Lettura attributi
                    if (attr.name().toString() == QLatin1String("username"))
                        id = attr.value().toString();
                    else if (attr.name().toString() == QLatin1String("password"))
                        psw = attr.value().toString();
                }
                if(Reader.name() == "nome" )Nome = Reader.readElementText();
                else if(Reader.name() == "cognome" )Cognome = Reader.readElementText();
                else if(Reader.name() == "nascita" )
                    Data  = QDate::fromString(Reader.readElementText(),"dd/MM/yyyy");
                else if(Reader.name() == "codiceFiscale" )Codicefiscale = Reader.readElementText();
                else if(Reader.name() == "sesso" )Sesso = Reader.readElementText().data()->toLatin1();
                else if(Reader.name() == "stipendio" )Stipendio = Reader.readElementText().toDouble();
                else if(type == 0 || type == 1)//Medico e primario hanno gli stessi parametri
                    if(Reader.name() == "studio" )
                        Studio = Reader.readElementText();
            }



            Reader.readNext();
            if(Reader.isEndElement() && Reader.name()!="Personale"){
                if(type == 0){//Medico
                    shared_ptr<Medico> x = std::make_shared<Medico>
                            (Medico(Nome,Cognome,Data,Codicefiscale,Sesso,Stipendio,Studio,id,psw));

                    if(!PersonalePresente(x))
                        personale.push_back(x);
                }
                else if(type == 1){//Primario
                    shared_ptr<Primario> x = std::make_shared<Primario>
                            (Primario(Nome,Cognome,Data,Codicefiscale,Sesso,Stipendio,Studio,id,psw));

                    if(!PersonalePresente(x))
                        personale.push_back(x);
                }
                else if(type == 2){//Segreteria
                    shared_ptr<Segreteria> x = std::make_shared<Segreteria>
                            (Segreteria(Nome,Cognome,Data,Codicefiscale,Sesso,Stipendio,id,psw));

                    if(!PersonalePresente(x))
                        personale.push_back(x);
                }
            }
        }//fine ciclo while
    }
    file->close();
    delete file;
    //Ordino i cognomi delle persone in ordine alfabetico
    std::sort(personale.begin(),personale.end(),OrdinaPersone);
}


void Database::LoadPazienti(QFile* file) {
    if(file->exists() && file->open(QIODevice::ReadOnly)){
        QString Nome,Cognome,Codicefiscale,Gruppo = "";
        QDate Data;
        char Sesso = '?';
        bool Fattore = false;
        int type = -1;
        QXmlStreamReader Reader(file);
        while (!Reader.atEnd()){

            if(Reader.isStartElement()){
                if(Reader.name() == "Pazienti") Reader.readNext();
                else if(Reader.name() == "Paziente" ) type = 0;
                else if(Reader.name() == "Donatore" ) type = 1;

                else if(Reader.name() == "nome" )Nome = Reader.readElementText();
                else if(Reader.name() == "cognome" )Cognome = Reader.readElementText();
                else if(Reader.name() == "nascita" )
                    Data  = QDate::fromString(Reader.readElementText(),"dd/MM/yyyy");
                else if(Reader.name() == "codiceFiscale" )Codicefiscale = Reader.readElementText();
                else if(Reader.name() == "sesso" )Sesso = Reader.readElementText().data()->toLatin1();

                else if(type == 1){
                    if(Reader.name() == "gruppo" ) Gruppo = Reader.readElementText();
                    else if(Reader.name() == "fattore" )
                        Fattore = (Reader.readElementText().toUpper() == "TRUE")? true :false;
                }

            }


            Reader.readNext();
            if(Reader.isEndElement() && Reader.name()!="Pazienti"){
                if(type == 0){
                    shared_ptr<Persona> x = std::make_shared<Persona>
                            (Persona(Nome,Cognome,Data,Codicefiscale,Sesso));

                    if(!PersonaPresente(x))
                        pazienti.push_back(x);
                }
                else if(type == 1){
                    shared_ptr<Donatore> x = std::make_shared<Donatore>
                            (Donatore(Nome,Cognome,Data,Codicefiscale,Sesso,Gruppo,Fattore));

                    if(!PersonaPresente(x))
                        pazienti.push_back(x);
                }
            }

        }//fine ciclo while
    }
    file->close();
    delete file;
    //Ordino i cognomi delle persone in ordine alfabetico
    std::sort(pazienti.begin(),pazienti.end(),OrdinaPersone);
}



void Database::LoadAgenda(QFile* file){
    if(file->exists() && file->open(QIODevice::ReadOnly)){
        QDateTime Data;
        QString MedicoCF,PazienteCF;
        int type = -1;
        QString desc;
        QXmlStreamReader Reader(file);
        while (!Reader.atEnd()){

            if(Reader.isStartElement()){
                if(Reader.name() == "Appuntamenti") Reader.readNext();
                else if(Reader.name() == "Visita" ) type = 0;
                else if(Reader.name() == "Donazione" ) type = 1;

                else if(Reader.name() == "data" )
                    Data  = QDateTime::fromString(Reader.readElementText(),"hh:mm:ss dd/MM/yyyy");
                else if(Reader.name() == "paziente" ) PazienteCF = Reader.readElementText();
                else if(Reader.name() == "descrizione" ) desc = Reader.readElementText();

                if(type == 0)
                    if(Reader.name() == "Medico" ) MedicoCF = Reader.readElementText();

            }
            Reader.readNext();

            if(Reader.isEndElement() && Reader.name()!="Appuntamenti"){
                bool trovatoP = false;
                if(type == 0){ //Visita
                    bool trovatoM = false;
                    shared_ptr<Medico> MedicoIndex;
                    //Cerco il medico dal codice fiscale
                    for( auto i = personale.begin(); !trovatoM && i != personale.end(); ++i){
                        if( (*i)->CodiceFiscale() == MedicoCF){
                            trovatoM = true;
                            MedicoIndex = std::dynamic_pointer_cast<Medico>(*i);
                        }
                    }
                    if(trovatoM && MedicoIndex){
                        //Cerco il paziente dal codice fiscale
                        for( auto i = pazienti.begin();!trovatoP && i != pazienti.end(); ++i){
                            if((*i)->CodiceFiscale() == PazienteCF){
                                trovatoP = true;
                                shared_ptr<Visita> x = std::make_shared<Visita>
                                        (Visita(Data,*MedicoIndex,**i,desc));

                                if(!EventoPresente(x))
                                    appuntamenti.push_back(x);  
                            }
                        }
                    }
                }
                else if(type == 1){ //Donazione
                    shared_ptr<Donatore> PazienteIndex;
                    //cerco donatore dal codice fiscale
                    for( auto i = pazienti.begin();!trovatoP && i != pazienti.end(); ++i){
                        if( (*i)->CodiceFiscale() == PazienteCF){
                            trovatoP = true;
                            PazienteIndex = std::dynamic_pointer_cast<Donatore>(*i);
                        }
                    }
                    if(trovatoP && PazienteIndex){
                        shared_ptr<Donazione> x = std::make_shared<Donazione>
                                (Donazione(*PazienteIndex,Data,desc));

                        if(!EventoPresente(x))
                            appuntamenti.push_back(x);
                    }
                }
            }
        }//fine ciclo while
    }
    file->close();
    delete file;
    //ordino gli appuntamenti in ordine cronologico
    appuntamenti.sort(OrdinaEventi);
}

void Database::ClosePersonale(QFile* file) const{
    if(file->open(QIODevice::WriteOnly)){
        QXmlStreamWriter Writer(file);
        Writer.setAutoFormatting(true);
        Writer.writeStartDocument("1.0");
        Writer.writeStartElement("Personale");
        if(!personale.empty()){
            for( auto i = personale.begin(); i != personale.end() ;++i) {
                int type = -1;
                shared_ptr<Medico> nuovoMedico = std::dynamic_pointer_cast<Medico>(*i);
                if(nuovoMedico){
                    if(std::dynamic_pointer_cast<Primario>(*i))
                        type = 0;
                    else
                        type = 1;
                }
                else if(std::dynamic_pointer_cast<Segreteria>(*i))
                    type = 2;


                switch(type){
                case 0:
                    Writer.writeStartElement("Primario");
                    break;
                case 1:
                    Writer.writeStartElement("Medico");
                    break;
                case 2:
                    Writer.writeStartElement("Segreteria");
                    break;
                }
                if( type != -1)
                    Writer.writeAttribute("username",(*i).get()->Username());
                    Writer.writeAttribute("password",(*i).get()->password);
                    Writer.writeTextElement("nome",(*i).get()->Nome());
                    Writer.writeTextElement("cognome",(*i).get()->Cognome());
                    Writer.writeTextElement("nascita",(*i).get()->DataNascita().toString("dd/MM/yyyy"));
                    Writer.writeTextElement("codiceFiscale",(*i).get()->CodiceFiscale());
                    Writer.writeTextElement("sesso",QString(QChar((*i).get()->Sesso())));
                    Writer.writeTextElement("stipendio",QString::number(((*i).get()->Stipendio())));
                    if(nuovoMedico)
                        Writer.writeTextElement("studio",nuovoMedico->Studio());
                    Writer.writeEndElement();
            }
            Writer.writeEndElement();
        }
    }
    file->close();
    delete file;
}

void Database::CloseAgenda(QFile* file) const{

    if(file->open(QIODevice::WriteOnly)){
        QXmlStreamWriter Writer(file);
        Writer.setAutoFormatting(true);
        Writer.writeStartDocument("1.0");
        Writer.writeStartElement("Appuntamenti");

        if(!appuntamenti.empty()){
            for( auto i = appuntamenti.begin(); i != appuntamenti.end() ;++i){
                //Caso in cui l'appuntamento sia una visita
                shared_ptr<Visita> nuovaVisita = std::dynamic_pointer_cast<Visita>(*i);
                if(nuovaVisita) {
                    Writer.writeStartElement("Visita");
                    Writer.writeTextElement("data",nuovaVisita->GetData().toString("hh:mm:ss dd/MM/yyyy"));
                    Writer.writeTextElement("paziente",nuovaVisita->GetPaziente().CodiceFiscale());
                    Writer.writeTextElement("descrizione",nuovaVisita->Descrizione());
                    Writer.writeTextElement("Medico",nuovaVisita->GetMedico().CodiceFiscale());
                    Writer.writeEndElement();
                }
                else{
                //Caso in cui sia una donazione
                    shared_ptr<Donazione> nuovaDonazione = std::dynamic_pointer_cast<Donazione>(*i);
                    if(nuovaDonazione){
                        Writer.writeStartElement("Donazione");
                        Writer.writeTextElement("data",nuovaDonazione->GetData().toString("hh:mm:ss dd/MM/yyyy"));
                        Writer.writeTextElement("paziente",nuovaDonazione->GetDonatore().CodiceFiscale());
                        Writer.writeTextElement("descrizione",nuovaDonazione->Descrizione());
                        Writer.writeEndElement();
                    }
                }

            }
        }
        Writer.writeEndElement();
    }
    file->close();
    delete file;
}

void Database::ClosePazienti(QFile* file) const{
    if(file->open(QIODevice::WriteOnly) ){
        QXmlStreamWriter Writer(file);
        Writer.setAutoFormatting(true);
        Writer.writeStartDocument("1.0");
        Writer.writeStartElement("Pazienti");
        if(!pazienti.empty()){
            for( auto i = pazienti.begin(); i != pazienti.end() ;++i) {
                //Caso in cui sia un Donatore
                shared_ptr<Donatore> nuovoDonatore = std::dynamic_pointer_cast<Donatore>(*i);
                if(nuovoDonatore)
                    Writer.writeStartElement("Donatore");
                else
                    Writer.writeStartElement("Paziente");

                Writer.writeTextElement("nome",(*i).get()->Nome());
                Writer.writeTextElement("cognome",(*i).get()->Cognome());
                Writer.writeTextElement("nascita",(*i).get()->DataNascita().toString("dd/MM/yyyy"));
                Writer.writeTextElement("codiceFiscale",(*i).get()->CodiceFiscale());
                Writer.writeTextElement("sesso",QString(QChar((*i).get()->Sesso())));
                if(nuovoDonatore){
                    Writer.writeTextElement("gruppo",nuovoDonatore->GetGruppoSanguigno().Gruppo());
                    Writer.writeTextElement("fattore",(nuovoDonatore->GetGruppoSanguigno().Fattore())? "true" : "false");
                }
                Writer.writeEndElement();
            }
        }
        Writer.writeEndElement();
    }
    file->close();
    delete file;
}

bool Database::OrdinaPersone(const shared_ptr<Persona> & prima, const shared_ptr<Persona> & seconda){
    return (prima.get()->Cognome() < seconda.get()->Cognome());
}
bool Database::OrdinaEventi(const shared_ptr<Evento> & primo, const shared_ptr<Evento> & secondo){
    return (primo.get()->GetData() < secondo.get()->GetData());
}
bool Database::PersonalePresente(const shared_ptr<Personale> & dip) const{
    bool risultato = false;
    for(auto i = personale.begin();!risultato && i != personale.end();++i){
        if( *(*i).get() == *dip.get() )
            risultato = true;
    }
    return risultato;
}

bool Database::PersonaPresente(const shared_ptr<Persona> & p) const{
    bool risultato = false;
    for(auto i = pazienti.begin();!risultato && i != pazienti.end();++i){
        if( *(*i).get() == *p.get() )
            risultato = true;
    }
    return risultato;
}

bool Database::EventoPresente(const shared_ptr<Evento> &e) const{
    bool risultato = false;
    for(auto i = appuntamenti.begin();!risultato && i != appuntamenti.end();++i){
        if( *(*i).get() == *e.get() )
            risultato = true;
    }
    return risultato;
}
