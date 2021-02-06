#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QSoundEffect>	// Sound not available in Qt6 < 6.2
#include <QLabel>

#include "view.h"
#include "boarditem.h"
#include "starfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void startNewGame();
	void onItemClicked(int color);

private:
	Ui::MainWindow *ui;
	View *view;
	QGraphicsScene *scene;
	QVector<QColor> colors;
	QList<BoardItem *> board_items;
	//QSoundEffect *snd_click;	// Sound not available in Qt6 < 6.2
	QLabel *label_moves;
	Starfield *starfield;
	static constexpr int board_size = 14;
	static constexpr int item_size = 35;
	static constexpr int max_moves = 25;
	int moves;
	bool game_over;
	bool win;
	bool loose;

	void populateScene();
	void floodFill(int i, int j, int old_color, int new_color);
	bool checkWinning();
	void updateStatusBar();
};

#endif // MAINWINDOW_H
