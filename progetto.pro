QT += core gui
QT += widgets
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SacredHeart
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

RESOURCES	= Immagini.qrc

SOURCES += Code/Main.cpp \
        Code/Model/Database.cpp \
        Code/Model/Donatore.cpp \
        Code/Model/Donazione.cpp \
        Code/Model/Evento.cpp \
        Code/Model/GruppoSanguigno.cpp \
        Code/Model/Medico.cpp \
        Code/Model/Persona.cpp \
        Code/Model/Personale.cpp \
        Code/Model/Primario.cpp \
        Code/Model/Segreteria.cpp \
        Code/Model/Visita.cpp \
        Code/View/AzioniPersona.cpp \
        Code/View/AzioniEvento.cpp  \
        Code/View/InfoPersona.cpp \
        Code/View/LoginWindow.cpp \
        Code/View/Window.cpp \
        Code/View/NuovaPersona.cpp \
        Code/View/NuovoEvento.cpp \
        Code/View/ModificaEvento.cpp \
        Code/View/ModificaPersona.cpp \
        Code/View/PersonaleWindow.cpp \
        Code/View/MedicoWindow.cpp \
        Code/View/PrimarioWindow.cpp \
        Code/View/SegreteriaWindow.cpp \
        Code/View/CambioChiavi.cpp \
        Code/Controller/LoginController.cpp \
        Code/Controller/MedicoController.cpp \
        Code/Controller/SegreteriaController.cpp \
        Code/Controller/PrimarioController.cpp \
        Code/Controller/PersonaleController.cpp \

HEADERS  += Code/Model/Database.h \
        Code/Model/Donatore.h \
        Code/Model/Donazione.h \
        Code/Model/Evento.h \
        Code/Model/GruppoSanguigno.h \
        Code/Model/Medico.h \
        Code/Model/Persona.h \
        Code/Model/Personale.h \
        Code/Model/Primario.h \
        Code/Model/Segreteria.h \
        Code/Model/Visita.h \
        Code/View/AzioniPersona.h \
        Code/View/AzioniEvento.h \
        Code/View/InfoPersona.h \
        Code/View/LoginWindow.h \
        Code/View/Window.h \
        Code/View/NuovaPersona.h \
        Code/View/NuovoEvento.h \
        Code/View/ModificaEvento.h \
        Code/View/ModificaPersona.h \
        Code/View/PersonaleWindow.h \
        Code/View/MedicoWindow.h \
        Code/View/PrimarioWindow.h \
        Code/View/SegreteriaWindow.h \
        Code/View/CambioChiavi.h \
        Code/Controller/LoginController.h \
        Code/Controller/PrimarioController.h \
        Code/Controller/MedicoController.h \
        Code/Controller/SegreteriaController.h \
        Code/Controller/PersonaleController.h \
