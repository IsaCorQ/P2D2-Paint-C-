#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QColorDialog>
#include <QDebug>

void MainWindow::on_black_clicked()//Indica que se eligio el color negro
{
    scene->color = ui->black->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void MainWindow::on_l_grey_clicked()//Indica que se eligio el color gris claro
{
    scene->color = ui->l_grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(191, 191, 191)");
}

void MainWindow::on_blue_clicked()//Indica que se eligio el color azul
{
    scene->color = ui->blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 5, 129)");
}

void MainWindow::on_sea_clicked()//Indica que se eligio el color turquesa
{
    scene->color = ui->sea->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 127, 131)");
}

void MainWindow::on_green_clicked()//Indica que se eligio el color verde
{
    scene->color = ui->green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 124, 0)");
}

void MainWindow::on_d_green_clicked()//Indica que se eligio el color verde oscuro
{
    scene->color = ui->d_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 127, 0)");
}

void MainWindow::on_d_red_clicked()//Indica que se eligio el color rojo oscuro
{
    scene->color = ui->d_red->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 4, 0)");
}

void MainWindow::on_violet_clicked()//Indica que se eligio el color violeta
{
    scene->color = ui->violet->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(126, 10, 125)");
}

void MainWindow::on_grey_clicked()//Indica que se eligio el color gris
{
    scene->color = ui->grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 128, 128)");
}

void MainWindow::on_white_clicked()//Indica que se eligio el color blanco
{
    scene->color = ui->white->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(255, 255, 255)");
}

void MainWindow::on_l_blue_clicked()//Indica que se eligio el color celeste
{
    scene->color = ui->l_blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 7, 243)");
}

void MainWindow::on_cyan_clicked()//Indica que se eligio el color cyan
{
    scene->color = ui->cyan->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(5, 226, 248)");
}

void MainWindow::on_l_green_clicked()//Indica que se eligio el color verde claro
{
    scene->color = ui->l_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 210, 0)");
}

void MainWindow::on_yellow_clicked()//Indica que se eligio el color amarillo
{
    scene->color = ui->yellow->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(249, 236, 9)");
}

void MainWindow::on_red_clicked()//Devuelve el valor en escala de grises del color seleccionado
{
    QColor invert = QColorDialog::getColor();
        QColor trafic;
        trafic.setHsv(0,0,invert.hsvHue());
        scene->color = trafic;
        ui->currentColor->setStyleSheet("background-color: rgb(239, 11, 0)");
}

void MainWindow::on_pink_clicked()//Deja que uno elija un color
{
    QPen pen;
    QColor newColor = QColorDialog::getColor();
    QString ColorString = newColor.name();
    scene->color = newColor;
    ui->currentColor->setStyleSheet("background-color:" + ColorString);
}
