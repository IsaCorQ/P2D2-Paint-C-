using namespace std;
#include "scene.h"
#include <iostream>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    size=4;
    color= Qt::black;
    type = 1;
    changed = false;
}

Scene::~Scene()
{}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)//Indica que hacer en caso de soltar mouse
{
    undo_items.push(items()[0]);
    redo_emit();
    if (items().size() > 0)
        emit clear_emit();
    path = QPainterPath();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)//Indica que hacer cuando se presioa mouse
{
    addEllipse(event->scenePos().x(),
               event->scenePos().y(),
               size,
               size,
               QPen(Qt::NoPen),
               QBrush(color));
    if (type == 5){
        addEllipse(event->scenePos().x(),
                   event->scenePos().y(),
                   100,
                   100,
                   QPen(Qt::NoPen),
                   QBrush(color));
    }
    prev = event->scenePos();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)//Indica como debe de seguir el rastro del mouse para dibujar las pinceladas cada tipo indica cual tipo de pincel los numeros correspoden al orden en type line
{
    if (type != 1)
        removeItem(items()[0]);

    if (type == 0)
    {
        addLine(prev.x(),
                prev.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
    else if  (type == 1)
    {
        path.moveTo(prev);
        path.lineTo(event->scenePos().x(),event->scenePos().y());
        removeItem(items()[0]);
        addPath(path, QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        prev = event->scenePos();
        update();
    }
    else if (type == 2)
    {
        addRect(prev.x(),prev.y(),
                event->scenePos().x()-prev.x(),
                event->scenePos().y()-prev.y(),
            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
    else if (type == 3)
    {
        addEllipse(prev.x(),prev.y(),
            event->scenePos().x()-prev.x(),
            event->scenePos().y()-prev.y(),
            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
    else if (type == 4)
    {
        addLine(prev.x(),
                prev.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(Qt::white,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
}
