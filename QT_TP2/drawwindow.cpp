#include "drawwindow.h"
#include "ui_drawwindow.h"
#include "mainwindow.h"

#include <QCursor>
#include <QPainter>
#include <QMouseEvent>
#include <QVariant>
#include <QPainterPath>

int DrawWindow::colorToIndex(QColor color)
{
    if (color == Qt::black) return 0;
    if (color == Qt::red) return 1;
    if (color == Qt::green) return 2;
    if (color == Qt::blue) return 3;
    if (color == Qt::yellow) return 4;
    return 0;
}


void DrawWindow::mousePressEvent(QMouseEvent *event)
{
    if (this->anySelected) { // On enleve la selection
        QVariant updatedShapeData;
        switch (this->currentStyle) {
        case 1: {
            QLineF line = qvariant_cast<QLineF>(this->currentShape.data);
            updatedShapeData = QVariant::fromValue(line);
            break;
        }
        case 2:
        case 3: {
            QRectF rect = qvariant_cast<QRectF>(this->currentShape.data);
            updatedShapeData = QVariant::fromValue(rect);
            break;
        }
        case 4: updatedShapeData = this->currentShape.data; break;
        }

        this->shapes.append(ShapeItem(this->currentStyle, updatedShapeData, this->currentColor, this->currentThickness));
        this->anySelected = false;

        if (event->button() == Qt::RightButton) {
            this->update();
            return;
        }
    }

    //Si clic droit
    if (event->button() == Qt::RightButton) {
        QLineF mouseLine(event->pos(), event->pos());
        for (int i = this->shapes.size() - 1; i >= 0; --i) {
            ShapeItem& shape = this->shapes[i];

            if ((shape.style == 1 && qvariant_cast<QLineF>(shape.data).intersects(mouseLine)) ||
                (shape.style == 2 && qvariant_cast<QRectF>(shape.data).contains(event->pos())) ||
                (shape.style == 3 && qvariant_cast<QRectF>(shape.data).contains(event->pos())) ||
                (shape.style == 4 && qvariant_cast<QPainterPath>(shape.data).contains(event->pos()))) {
                qDebug() << shape.style << "shape selected.";
                this->anySelected = true;

                this->currentShape = shape;
                this->currentStyle = shape.style;
                this->currentColor = shape.color;
                this->currentThickness = shape.thickness;
                this->shapes.remove(i);

                // Update the UI elements in the MainWindow

                MainWindow *mainWindow = (MainWindow *)this->parent();
                mainWindow->styleComboBox->setCurrentIndex(this->currentStyle);
                mainWindow->thicknessLabel->setText(QString::number(this->currentThickness));
                mainWindow->thicknessSlider->setValue(this->currentThickness);
                mainWindow->colorComboBox->setCurrentIndex(this->colorToIndex(this->currentColor));

                this->update();
                return;
            }
        }
        return;
    }

    QVariant shapeData;
    switch (this->currentStyle) {
    case 1: shapeData = QVariant::fromValue(QLineF(event->pos(), event->pos())); break;
    case 2:
    case 3: shapeData = QVariant::fromValue(QRectF(event->pos(), event->pos())); break;
    case 4: {
        QPainterPath path;
        path.moveTo(event->pos());
        shapeData = QVariant::fromValue(path);
        break;
    }
    default: return;
    }

    this->currentShape = ShapeItem(this->currentStyle, shapeData, this->currentColor, this->currentThickness);
    this->update();
}

void DrawWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        if (!this->anySelected) {
            // Update current shape with the color and thickness
            this->currentShape.color = this->currentColor;
            this->currentShape.thickness = this->currentThickness;
            this->anySelected = false;
        }
        return;
    }

    QVariant updatedShapeData;
    switch (this->currentStyle) {
    case 1: {
        QLineF line = qvariant_cast<QLineF>(this->currentShape.data);
        line.setP2(event->pos());
        updatedShapeData = QVariant::fromValue(line);
        break;
    }
    case 2:
    case 3: {
        QRectF rect = qvariant_cast<QRectF>(this->currentShape.data);
        rect.setBottomRight(event->pos());
        updatedShapeData = QVariant::fromValue(rect);
        break;
    }
    case 4: updatedShapeData = this->currentShape.data; break;
    }

    this->shapes.append(ShapeItem(this->currentStyle, updatedShapeData, this->currentColor, this->currentThickness));
    qDebug() << "Mouse release event.";
    this->update();
}

void DrawWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons()==Qt::LeftButton) {
        QVariant updatedShapeData;
        switch (this->currentStyle) {
        case 1: {
            QLineF line = qvariant_cast<QLineF>(this->currentShape.data);
            line.setP2(event->pos());
            updatedShapeData = QVariant::fromValue(line);
            break;
        }
        case 2:
        case 3: {
            QRectF rect = qvariant_cast<QRectF>(this->currentShape.data);
            rect.setBottomRight(event->pos());
            updatedShapeData = QVariant::fromValue(rect);
            break;
        }
        case 4: {
            QPainterPath path = qvariant_cast<QPainterPath>(this->currentShape.data);
            path.lineTo(event->pos());
            updatedShapeData = QVariant::fromValue(path);
            break;
        }
        }
        this->currentShape.data = updatedShapeData;
        this->update();
    }
}

DrawWindow::DrawWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::DrawWindow)
{
    this->setMinimumSize(800, 600);
    this->setMouseTracking(true);
}

void DrawWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    auto drawShape = [&](const ShapeItem& shape) {
        switch (shape.style) {
        case 1: painter.drawLine(qvariant_cast<QLineF>(shape.data)); break;
        case 2: painter.drawRect(qvariant_cast<QRectF>(shape.data)); break;
        case 3: painter.drawEllipse(qvariant_cast<QRectF>(shape.data)); break;
        case 4: painter.drawPath(qvariant_cast<QPainterPath>(shape.data)); break;
        }
    };

    for (const ShapeItem& shape : this->shapes) {
        painter.setPen(QPen(shape.color, shape.thickness));
        drawShape(shape);
    }

    if (this->anySelected) { // Draw it dashed
        qDebug() << "Drawing dashed.";
        painter.setPen(QPen(this->currentColor, this->currentThickness, Qt::DashLine));
        drawShape(this->currentShape);
    }
    else {
        painter.setPen(QPen(this->currentColor, this->currentThickness));
        drawShape(this->currentShape);
    }
}

DrawWindow::~DrawWindow()
{
    delete ui;
}
