#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QGraphicsRectItem>

class BoardItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public:
	int color;

	enum { Type = UserType + 1 };

	int type() const override
	{
		// Enable the use of qgraphicsitem_cast with this item.
		return Type;
	}

signals:
	void clicked(int color);

};

#endif // BOARDITEM_H
