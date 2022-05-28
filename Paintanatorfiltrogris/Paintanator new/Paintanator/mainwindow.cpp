#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsview.h"
#include "api.h"
#include <QFileDialog>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QMenuBar>
#include <QtMath>
#include <QTransform>
#include <QPainter>
#include <QBuffer>
#include <QGraphicsEffect>
#include <QColor>



MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
  //Ventana principal donde se encuentra nuestro programa de dibujo
{
    ui->setupUi(this);

    scene = new Scene();
    changed=false;
    ui->graphicsView->setScene(scene);
    view = ui->graphicsView;
    QBrush bg= QColor(Qt::white);
    scene->setBackgroundBrush(bg);
    int baseSize = 1000;
    view->setSceneRect(0,0,baseSize,baseSize);
    baseViewSize = view->sceneRect().width();
    view->setScene(scene);
    timer = new QTimer();
    timer->start(100);
    connect(scene, SIGNAL(clear_emit()),this, SLOT(clear_enable()));
    connect(scene, SIGNAL(redo_emit()),this, SLOT(redo_unable()));
    paint.begin(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)//Con un slider se puede elegir el tamaño del "pincel" también se puede elegir con el spinbox a la par
{
    scene->size = value;
    ui->spinBox->setValue(value);
}

void MainWindow::on_spinBox_valueChanged(int value)//Spinbox para cambiar el tamaño al "pincel"
{
    scene->size = value;
    ui->horizontalSlider->setValue(value);
}

void MainWindow::on_typeLine_currentIndexChanged(int index)//Selector de pincel sea recto curvo rectangular o elipsis
{
    scene->type = index;
}

void MainWindow::on_clear_clicked()//Limpia la escena de nuestro dibujo para comenzar desde 0
{
    scene->clear();
    scene->undo_items.clear();
    scene->redo_items.clear();
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);
    ui->clear->setEnabled(false);
    scene->update();
}

void MainWindow::clear_enable()//Indica que se dibujo en la escena donde clear esta dispoible a ser utilizado
{
    ui->clear->setEnabled(true);
    ui->undo->setEnabled(true);
}

void MainWindow::redo_unable()//Indica que se ha dibujado en la escena y borrado algun elemento para poder re hacer el trazo
{
    ui->redo->setEnabled(false);
    scene->redo_items.clear();
}

void MainWindow::on_undo_clicked()//Indica que se ha dibujado en la escena para poder deshacer la escena y se manda señal de deshaer el trazo
{
    if (!scene->undo_items.isEmpty())
    {
        scene->redo_items.push(scene->undo_items.top());
        scene->removeItem(scene->undo_items.top());
        scene->undo_items.pop();
        ui->redo->setEnabled(true);
    }

    if (scene->undo_items.isEmpty())
        ui->undo->setEnabled(false);
    scene->update();
}

void MainWindow::on_redo_clicked()//Señal que se ha querido hacer un redo
{
    if (!scene->redo_items.isEmpty())
    {
        scene->addItem(scene->redo_items.top());
        scene->undo_items.push(scene->redo_items.top());
        scene->redo_items.pop();
        ui->undo->setEnabled(true);
    }

    if (scene->redo_items.isEmpty())
        ui->redo->setEnabled(false);
    scene->update();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)//Zoom de la escena
{
    const qreal factor = 1.01;
    viewScaleValue = qPow(factor, -position);
    QTransform matrix;
    matrix.scale(((baseViewSize/6) / position), ((baseViewSize/6) / position));
    view->setTransform(matrix);
    update();
}

void MainWindow::on_pushButton_clicked()//Rota la imagen 90º
{
    QTransform matrix;
    matrix.rotate(90);
    view->setTransform(matrix);
    update();
}

bool MainWindow::saveImage(const QString &filename, const char *format)//Salva la imagen dibujada sea esta vacia o con algun tazo encima
{
    QTransform matrix;
    view->setTransform(matrix);
    QImage s_image(view->size(), QImage::Format_ARGB32);
    QPainter paint=QPainter(&s_image);
    paint.save();
    scene->render(&paint);
    paint.end();

    QImage image_fin=s_image;
    if (image_fin.save(filename, format)) {
        changed = false;
        return true;
    }
    else
        return false;
}

void MainWindow::resizeImage(QImage *image, const QSize &newSize)//No funciona para cambiar de tamaño de la imagen solo sirve para indicar el tamaño minimo que debe de tener la imagen si se abre algun file
{;
    if (image->size() == newSize)
        return;
    else  {
        QImage resizedImage(newSize, QImage::Format_ARGB32);
        QPainter painter(&resizedImage);
        painter.drawImage(QPoint(0, 0), *image);
        *image = resizedImage;
    }
}

bool MainWindow::loadImage(const QString &filename)//Abre file de la compu estos tienen que ser .bmp
{
    QTransform matrix;
    view->setTransform(matrix);
    QImage currentImage;
    currentImage.load(filename);
    if (!currentImage.load(filename))
        return false;
    image = currentImage;
    changed = false;
    ui->graphicsView->setBackgroundBrush(currentImage);
    update();
    return true;
}

bool MainWindow::saveDrawing(const QByteArray &fileFormat)//Guarda la imagen dentro de la computadora
{
    QString currentPath = QDir::currentPath() + "/painter." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), currentPath,
              tr("%1 Files (*.%2;;All Files (*)").arg(QString::fromLatin1(fileFormat.toUpper()))
                                                  .arg(QString::fromLatin1(fileFormat)));

    if (fileName.isEmpty()) {
        return false;
    } else {
        return saveImage(fileName, fileFormat.constData());
    }
}

void MainWindow::open()//Abre el .bmp facilita llamado con el boton
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
       loadImage(fileName);

}

void MainWindow::on_saveButton_clicked()//Manda señal de guardar la imagen
{
    saveDrawing("bmp");
}

void MainWindow::on_openButton_clicked()//Manda señal de abrir la imagen
{
    open();
}

void MainWindow::on_pushButton_2_clicked()//Filtro de greyscale **solo torna la imagen negra
{
    /*
    ui->graphicsView->setForegroundBrush(QColor(255,255,255,127));
    update();

    //Filtro gris

    QTransform matrix;
    QImage currentImage;
    QColor graylayout;
    currentImage.convertToFormat(QImage::Format_Grayscale8);
    ui->graphicsView->setForegroundBrush(currentImage);
    paint.begin(view);
    update();
    */

    update();

}

void MainWindow::on_fltrpstl_clicked()//Filtro para suavizar los colores
{
    ui->graphicsView->setForegroundBrush(QColor(255,255,255,127));
    update();
}

