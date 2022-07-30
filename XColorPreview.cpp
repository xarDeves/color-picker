#include "XColorPreview.hpp"
#include <QStylePainter>
#include <QStyleOptionFrame>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

XColorPreview::XColorPreview(QWidget *parent) :
    QWidget(parent), col(Qt::red), back( Qt::darkGray, Qt::DiagCrossPattern ),
    alpha_mode(NoAlpha)
{
    back.setTexture(QPixmap(QString(":/images/alphaback.png")));
}

QSize XColorPreview::sizeHint() const
{
    return QSize(12,12);
}

void XColorPreview::setColor(QColor c)
{
    col = c;
    update();
    emit colorChanged(c);
}

void XColorPreview::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setPen(QPen(Qt::black, 1));
    QSize rectSize(40,40);
    painter.setBrush(back);
    painter.drawRect(1,1,rectSize.width(),rectSize.height());

    int h = rectSize.height();
    painter.setPen(Qt::NoPen);
    painter.setBrush(col);
    painter.drawRect(1,1,rectSize.width(),h);
}


