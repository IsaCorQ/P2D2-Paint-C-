#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QPainter>


class GraphicsView: public QObject {
    Q_OBJECT

public:
  GraphicsView(QGraphicsView* view);
  void gentle_zoom(double factor);
  void set_modifiers(Qt::KeyboardModifiers modifiers);
  void set_zoom_factor_base(double value);
  QImage getBackUpImage();
  QImage getImage();
  void resizeImage(QImage *image, const QSize &newSize);
  void setBackUpImage(QImage& image);
  void setImage(QImage& image);
  bool loadImage(const QString &filename);
  bool saveImage(const QString &filename, const char *fileformat);

private:
  QGraphicsView* _view;
  Qt::KeyboardModifiers _modifiers;
  double _zoom_factor_base;
  QPointF target_scene_pos, target_viewport_pos;
  bool eventFilter(QObject* object, QEvent* event);
  bool changed;
  QImage image;
  QImage backupImage;

signals:
  void zoomed();
};

#endif // GRAPHICSVIEW_H
