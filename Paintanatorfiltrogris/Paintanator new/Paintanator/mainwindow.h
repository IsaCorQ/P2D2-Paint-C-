#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMatrix>
#include <QTimer>
#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QImage>
#include <QColor>
#include "scene.h"




namespace Ui { class MainWindow; }


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeImage(QImage *image, const QSize &newSize);
    bool loadImage(const QString &filename);
    bool saveImage(const QString &filename, const char *fileformat);
    //QImage img;
    //QImage m_imgCopy;
private:
    Ui::MainWindow *ui;
    static QImage grayfilter(const QImage &img);
    QImage m_img{nullptr};
    QImage m_imgCopy{nullptr};

    QTimer *timer;      //timer for scene resize
    Scene *scene;
    QGraphicsScene *gameScene;
    QGraphicsView *view;
    float baseViewSize;
    float heightViewSize;
    int viewScaleValue;
    QImage image;
    QImage image_fin;
    QPainter paint;
    bool changed;
    bool saveDrawing(const QByteArray &fileFormat);
    static QImage GrayScaleImage(const QImage &img);



private slots:
    void on_typeLine_currentIndexChanged(int index);
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int value);
    void on_clear_clicked();
    void on_undo_clicked();
    void on_redo_clicked();
    void clear_enable();
    void redo_unable();
    void on_black_clicked();
    void on_l_grey_clicked();
    void on_blue_clicked();
    void on_sea_clicked();
    void on_green_clicked();
    void on_d_green_clicked();
    void on_d_red_clicked();
    void on_violet_clicked();
    void on_grey_clicked();
    void on_white_clicked();
    void on_l_blue_clicked();
    void on_cyan_clicked();
    void on_l_green_clicked();
    void on_yellow_clicked();
    void on_red_clicked();
    void on_pink_clicked();
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_pushButton_clicked();
    void on_saveButton_clicked();
    void on_openButton_clicked();
    void open();
    void on_pushButton_2_clicked();
    void on_fltrpstl_clicked();
};
#endif // MAINWINDOW_H
