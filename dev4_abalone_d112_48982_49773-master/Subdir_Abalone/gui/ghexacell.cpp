#include "ghexacell.h"
#include <cmath>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include"point.hpp"
#include<QGraphicsPolygonItem>
#include<QGraphicsScene>
#include<QColor>




void GHexaCell::setColor(const QColor &color)
{
    m_color = color;
    update();
}


void GHexaCell::setSelected(bool value)
{
    selected = value;
    update();
}



void GHexaCell::setIsSelectable(bool value)
{
    isSelectable = value;
}

GHexaCell::GHexaCell(double rad,double x, double y,
                     std::string value,bool _isSelectable,QColor color,
                     QGraphicsItem * parent)
    : QGraphicsPolygonItem(parent),rad(rad), moved(false), selected(false),mouseover(false),isSelectable(_isSelectable),
      _x { x }, _y { y },
      _value { value }
{

    this->setAcceptHoverEvents(true);
    zval = zValue();
    m_color=color;
    static const double pi_over_6 = atan(1) * 4 / 6;
    QPolygonF polygon;
    auto&& corners = orbit({_x, _y},6, rad, pi_over_6);
    for(auto& p : corners)
        polygon << QPointF(p.first, p.second);
    setPolygon(polygon);
    setFlags(QGraphicsItem::ItemIsSelectable);
}


void GHexaCell::paint(QPainter * painter,
                      [[maybe_unused]] const QStyleOptionGraphicsItem * option,
[[maybe_unused]] QWidget * widget)
{


    QPen pen(Qt::red, 1);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(m_color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

    if(isSelectable){
        if (selected)
        {
            QPen pen(Qt::red, 3);
            painter->setPen(pen);

            QBrush brush;
            brush.setColor(Qt::yellow);
            brush.setStyle(Qt::SolidPattern);

            painter->setBrush(brush);
        }
    }
    painter->drawPolygon(polygon());
}


void GHexaCell::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    event->accept();
    emit sendValue(_value,m_color);
    moved = false;
    setSelected(!selected);
    update();
    QGraphicsItem::mousePressEvent(event);
}

