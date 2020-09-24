#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
	Q_OBJECT

public:
	View(QWidget *parent = nullptr);

protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // VIEW_H
