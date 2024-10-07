#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QLine>
#include <QColor>
#include <QRect>
#include <QVariant>
#include <QBrush>
#include <QPainterPath>

QT_BEGIN_NAMESPACE
namespace Ui {
class DrawWindow;
}
QT_END_NAMESPACE

class ShapeItem
{
public:

    int style;
    QVariant data;
    QColor color;
    int thickness;

    ShapeItem(int style, QVariant data, QColor color, int thickness) //shape and data are separated to differentiate rect and ellipse
    {
        this->style = style;
        this->data = data;
        this->color = color;
        this->thickness = thickness;
    }
};

class DrawWindow : public QWidget
{
    Q_OBJECT

public:
    DrawWindow(QWidget *parent = nullptr);
    ~DrawWindow();


    QColor currentColor = Qt::black;
    ShapeItem currentShape = ShapeItem(3, QVariant::fromValue(QPainterPath()), Qt::black, 1);
    int currentThickness = 1;
    int currentStyle = 4;
    bool anySelected = false;
    bool justSelected = false;

    QVector<ShapeItem> shapes;

    int colorToIndex(QColor color);

private:
    Ui::DrawWindow *ui;

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // DRAWWINDOW_H
