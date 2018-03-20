#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>

#include <QFont>
#include <QIcon>
#include <QPushButton>
#include <QLineEdit>

#include <QDesktopWidget>
#include <QGridLayout>
#include <QMessageBox>


class Window :public QMainWindow{
     Q_OBJECT
protected:
    QGridLayout* layout;
    QWidget* central;

    void Centra(); //Centra la finestra sullo schermo
    void Disegna(); //Rende visibile la finestra
public:
    Window();
    virtual ~Window();
    void Error(const QString = "") const; //Crea un messaggio di errore con una stringa da dare
};

#endif // WINDOW_H
