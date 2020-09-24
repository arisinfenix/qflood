#include "boarditem.h"

void BoardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	emit clicked(this->color);
}
