#include "view.h"

View::View(QWidget *parent)
	: QGraphicsView(parent)
{

}

void View::resizeEvent(QResizeEvent *event)
{
	qreal f = 1.2; // margin

	fitInView(0, 0, this->scene()->width() * f, this->scene()->height() * f, Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(event);
}
