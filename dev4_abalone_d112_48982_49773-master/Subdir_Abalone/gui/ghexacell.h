#ifndef GHEXACELL_H
#define GHEXACELL_H

#include <QGraphicsPolygonItem>
#include <QObject>

/*
 * forward declaration.
 * put include in cpp file not in .h file
 */
class QPainter;
class QPointF;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneMouseEvent;

/**
 * @brief The GHexaCell class.
 * represent an hexagon at position x,y and with a "value". this
 * value is emited on click.
 *
 * inherit from QObject to have capability of sending signal.
 */
class GHexaCell : public QObject, public QGraphicsPolygonItem
{

    Q_OBJECT


   static const double zValMax; //z-val of selected items
   double zval; //z-val at instanciation


  protected:
    double _x, _y; // coordinates of center
    std::string _value; // some value to emit (e.g. abapro position)
    double rad;
    public:
    bool moved,selected,mouseover,isSelectable;//mouse interaction booleans
   private:
    QColor m_color;
    int dx,dy,dz;

  public:
    explicit GHexaCell(double rad,double x, double y,
                       std::string value,bool isSelectable,QColor color=Qt::cyan,
                       QGraphicsItem * parent = nullptr);
    inline double x() const;
    inline double y() const ;
    inline std::string value() const;
    inline QColor color() const;
    inline bool getSelected() const;
    inline bool getIsSelectable() const;


    /*
     * how can I what method rewrite ?
     * first because is in abs poc… and in doc
     * see https://doc.qt.io/qt-5/qgraphicspolygonitem.html#paint
     */
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);


    void setColor(const QColor &color);

    void setSelected(bool value);

    void setIsSelectable(bool value);

protected:
    /*
     * Capture mouse press event. ghexacell is now clickable.
     * see https://www.learnqt.guide/events/working-with-events/
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /*
     * #1 add signal to emit when hexagon is clicked.
     * this method must return void and is implemented by Qt.
     * To do this, class must inherit from QObject.
     */
  signals:
    void sendValue(std::string value,QColor color);
};

//
// inline methods
//
double GHexaCell::x() const
{
    return _x;
}

double GHexaCell::y() const
{
    return _y;
}

std::string GHexaCell::value() const
{
    return _value;
}

QColor GHexaCell::color() const
{
    return m_color;
}
bool GHexaCell::getSelected() const
{
    return selected;
}
bool GHexaCell::getIsSelectable() const
{
    return isSelectable;
}






#endif // GHEXACELL_H
