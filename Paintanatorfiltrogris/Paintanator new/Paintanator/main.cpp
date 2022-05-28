#include "mainwindow.h"

#include <QApplication>
/*Instituto Tecnlogico Costarricense
 * Proyecto 2 para la clase de algortmos y estructuras de datos 2
 * Profesor Isaac Ramirez
 * Autores: Isa Córdoba Quesada, Ian Hu Pacheco
 * Carné: 2021067015, 2021062270
 * Version:5 del proyecto
 * Fecha de revisión de codigo: 28 de marzo 2021 8:30pm*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
