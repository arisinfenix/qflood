#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, view(new View(this))
	, scene(new QGraphicsScene(this))
	, colors({Qt::red, Qt::blue, Qt::yellow, Qt::green, Qt::white, Qt::magenta})
	, snd_click(new QSoundEffect(this))
	, label_moves(new QLabel)
{
	ui->setupUi(this);
	this->setCentralWidget(view);

	// toolbar
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::startNewGame);

	ui->statusbar->addWidget(label_moves);

	snd_click->setSource(QUrl("qrc:/sounds/click.wav"));

	populateScene();

	view->setFrameStyle(QFrame::NoFrame);
	view->setScene(scene);
	view->show();

	startNewGame();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::populateScene()
{
	const int margin = 0;

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			BoardItem *item = new BoardItem;
			item->setRect(j * item_size + j * margin, i * item_size + i * margin, item_size, item_size);
			item->color = QRandomGenerator::global()->bounded(0, colors.count());
			item->setBrush(colors[item->color]);
			item->setPen(QPen(Qt::gray));
			//item->setPen(QPen(Qt::NoPen));
			scene->addItem((item));
			connect(item, &BoardItem::clicked, this, &MainWindow::onItemClicked);
			// store pointers for easy access
			board_items.append(item);
		}
	}
}

void MainWindow::floodFill(int i, int j, int old_color, int new_color)
{
	if (board_items[j * board_size + i]->color != old_color || new_color == old_color) {
		return;
	}

	board_items[j * board_size + i]->color = new_color;

	if (j + 1 < board_size) {
		floodFill(i, j + 1, old_color, new_color);
	}
	if (j - 1 >= 0) {
		floodFill(i, j - 1, old_color, new_color);
	}
	if (i - 1 >= 0) {
		floodFill(i - 1, j, old_color, new_color);
	}
	if (i + 1 < board_size) {
		floodFill(i + 1, j, old_color, new_color);
	}
}

bool MainWindow::checkWinning()
{
	for (int i = 0; i < board_items.count() - 1; i++) {
		if (board_items[i]->color != board_items[i + 1]->color) {
			return false;
		}
	}
	return true;
}

void MainWindow::updateStatusBar()
{
	label_moves->setText(QString::number(moves) + " / " + QString::number(max_moves));
}

// SLOTS

void MainWindow::startNewGame()
{
	moves = 0;
	game_over = false;
	win = false;
	loose = false;

	for (auto i : board_items) {
		i->color = QRandomGenerator::global()->bounded(0, colors.count());
		i->setBrush(colors[i->color]);
	}

	updateStatusBar();
}

void MainWindow::onItemClicked(int color)
{
	if (game_over) {
		return;
	}

	snd_click->play();

	moves++;

	floodFill(0, 0, board_items[0]->color, color);

	for (auto i : board_items) {
		i->setBrush(colors[i->color]);
	}

	if (checkWinning()) {
		game_over = true;
		win = true;
	}

	if (!win && moves == max_moves) {
		game_over = true;
		loose = true;
	}

	updateStatusBar();
}
