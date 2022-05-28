#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStack>
#include <QPainterPath>

class Scene : public QGraphicsScene
{

    Q_OBJECT

public:
    int size,type;
    QColor color;
    QBrush brush;
    QPen pen;
    QStack<QGraphicsItem*> undo_items, redo_items;
    explicit Scene(QObject *parent = 0);
    ~Scene();

private:
    bool changed;
    QPainterPath    path;
    QPointF         prev;


private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


signals:
    void clear_emit();
    void redo_emit();
};

#endif // SCENE_H
