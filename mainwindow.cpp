#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent){

//	this->menuBar()->addAction("New Game", this, SLOT(newGame()));
	this->menuBar()->addAction("New Turn", this, SLOT(newTurn()));
	this->menuBar()->addAction("Reset Score", this, SLOT(resetScore()));


	this->board = new TileBoard(this);
	this->turn = this->board->getCurrentTurn();
	setCentralWidget(board);

	this->setMinimumSize(300,300);

	QDockWidget *scoreWidget = new QDockWidget("Score:", this);
	scoreWidget->setAllowedAreas(Qt::TopDockWidgetArea);
	this->scoreBoard = new ScoreBoard(scoreWidget);
	scoreWidget->setWidget(scoreBoard);
	scoreWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	scoreWidget->setMaximumHeight(60);
	scoreWidget->setMaximumWidth(300);
	addDockWidget(Qt::TopDockWidgetArea, scoreWidget);

	connect(this->board, SIGNAL(gameOver(TileButton::TileSymbol)), this, SLOT(gameOver(TileButton::TileSymbol)));

}

MainWindow::~MainWindow(){

}

TileButton::TileSymbol MainWindow::changeTurn(){
	switch (this->turn) {
		case TileButton::TileSymbol::X:
			this->turn = TileButton::TileSymbol::O;
			break;
		case TileButton::TileSymbol::O:
			this->turn = TileButton::TileSymbol::X;
			break;
		default:
			qDebug() << "Current turn is set to neither X or O.";
			break;
	}

	return this->turn;
}

bool MainWindow::newGame(){
	bool fail = this->board == nullptr;

	if(!fail){
		this->changeTurn();
		this->resetScore();
		fail = !this->board->resetBoard(this->turn);
	}

	return !fail;
}

void MainWindow::gameOver(TileButton::TileSymbol winner){
	this->scoreBoard->incrementScore(winner);
	this->changeTurn();
	this->board->resetBoard(this->turn);
//	this->newGame();
}

void MainWindow::resetScore(){
	this->scoreBoard->resetScore();
}

TileButton::TileSymbol MainWindow::newTurn(){
	TileButton::TileSymbol newTurn = this->changeTurn();
	this->board->resetBoard(this->turn);
	return newTurn;
}
