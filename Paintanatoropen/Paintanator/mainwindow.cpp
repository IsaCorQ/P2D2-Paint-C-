#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsview.h"
#include <QFileDialog>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QPushButton>
#include <QMenuBar>
#include <QtMath>
#include <QTransform>
#include <QPainter>
#include <QBuffer>
#include <QGraphicsEffect>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
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
    connect(timer, &QTimer::timeout, this, &MainWindow::Timer);
    timer->start(100);
    connect(scene, SIGNAL(clear_emit()),this, SLOT(clear_enable()));
    connect(scene, SIGNAL(redo_emit()),this, SLOT(redo_unable()));
    paint.begin(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Timer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    scene->size = value;
    ui->spinBox->setValue(value);
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    scene->size = value;
    ui->horizontalSlider->setValue(value);
}

void MainWindow::on_typeLine_currentIndexChanged(int index)
{
    scene->type = index;
}

void MainWindow::on_clear_clicked()
{
    scene->clear();
    scene->undo_items.clear();
    scene->redo_items.clear();
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);
    ui->clear->setEnabled(false);
    scene->update();
}

void MainWindow::clear_enable()
{
    ui->clear->setEnabled(true);
    ui->undo->setEnabled(true);
}

void MainWindow::redo_unable()
{
    ui->redo->setEnabled(false);
    scene->redo_items.clear();
}

void MainWindow::on_undo_clicked()
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

void MainWindow::on_redo_clicked()
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

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    const qreal factor = 1.0;
    viewScaleValue = qPow(factor, -position);
    QTransform matrix;
    matrix.scale((baseViewSize / position), (baseViewSize / position));
    view->setTransform(matrix);
    update();
}

void MainWindow::on_pushButton_clicked()
{
    QTransform matrix;
    matrix.rotate(90);
    view->setTransform(matrix);
    matrix.reset();
    update();
}

bool MainWindow::saveImage(const QString &filename, const char *format)
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

void MainWindow::resizeImage(QImage *image, const QSize &newSize)
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

bool MainWindow::loadImage(const QString &filename)
{


    QTransform matrix;
    view->setTransform(matrix);
    QImage currentImage;

    currentImage.load(filename);
    QLabel uwu;
    if (!currentImage.load(filename))
        return false;
    image = currentImage;

    changed = false;

    ui->graphicsView->setBackgroundBrush(currentImage);
    update();

    return true;

}

bool MainWindow::saveDrawing(const QByteArray &fileFormat) {
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
void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
       loadImage(fileName);

}

void MainWindow::on_saveButton_clicked()
{
    saveDrawing("bmp");
}


void MainWindow::on_openButton_clicked()
{
    open();
}


void MainWindow::on_pushButton_2_clicked()
{

}

