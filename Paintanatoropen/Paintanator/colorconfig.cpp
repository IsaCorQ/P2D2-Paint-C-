#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include <QColorDialog>
#include <QDebug>

void MainWindow::on_black_clicked()
{
    scene->color = ui->black->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void MainWindow::on_l_grey_clicked()
{
    scene->color = ui->l_grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(191, 191, 191)");
}

void MainWindow::on_blue_clicked()
{
    scene->color = ui->blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 5, 129)");
}

void MainWindow::on_sea_clicked()
{
    scene->color = ui->sea->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 127, 131)");
}

void MainWindow::on_green_clicked()
{
    scene->color = ui->green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 124, 0)");
}

void MainWindow::on_d_green_clicked()
{
    scene->color = ui->d_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 127, 0)");
}

void MainWindow::on_d_red_clicked()
{
    scene->color = ui->d_red->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 4, 0)");
}

void MainWindow::on_violet_clicked()
{
    scene->color = ui->violet->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(126, 10, 125)");
}

void MainWindow::on_grey_clicked()
{
    scene->color = ui->grey->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(128, 128, 128)");
}

void MainWindow::on_white_clicked()
{
    scene->color = ui->white->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(255, 255, 255)");
}

void MainWindow::on_l_blue_clicked()
{
    scene->color = ui->l_blue->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(0, 7, 243)");
}

void MainWindow::on_cyan_clicked()
{
    scene->color = ui->cyan->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(5, 226, 248)");
}

void MainWindow::on_l_green_clicked()
{
    scene->color = ui->l_green->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(1, 210, 200)");
}

void MainWindow::on_yellow_clicked()
{
    scene->color = ui->yellow->palette().background().color();
    ui->currentColor->setStyleSheet("background-color: rgb(249, 236, 9)");
}

void MainWindow::on_red_clicked()
{
    QColor invert = QColorDialog::getColor();
    invert.darker(400);
    scene->color = invert;
    ui->currentColor->setStyleSheet("background-color: rgb(239, 11, 0)");
}

void MainWindow::on_pink_clicked()
{
    QPen pen;
    QColor newColor = QColorDialog::getColor();
    QString ColorString = newColor.name();
    scene->color = newColor;
    ui->currentColor->setStyleSheet("background-color:" + ColorString);
}
