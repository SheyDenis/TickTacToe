#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent){

//	this->menuBar()->addAction("New Game", this, SLOT(newGame()));
	this->menuBar()->addAction("New Turn", this, SLOT(newTurn()));

	this->opponentMenu = new QMenu("Opponent");
	opponentMenu->addAction("Human", this, SLOT(setOpponentHuman()));
	opponentMenu->addAction("Random", this, SLOT(setOpponentRandom()));

	foreach(QAction *qa, this->opponentMenu->actions()){
		qa->setCheckable(true);
	}

	this->menuBar()->addMenu(opponentMenu);

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
	connect(this->board, SIGNAL(nextTurn()), this, SLOT(nextTurn()));
	this->setOpponentHuman();
	this->board->toggleOClicks(true);

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
#if DEBUG_FLAG
			qDebug() << "Current turn is set to neither X or O.";
#endif
			break;
	}

	return this->turn;
}

bool MainWindow::newGame(){
	bool fail = this->board == nullptr;

	if(!fail){
		this->changeTurn();
		this->board->toggleOClicks(this->opponentHuman);
		this->resetScore();
		fail = !this->board->resetBoard(this->turn);
	}

	return !fail;
}

void MainWindow::gameOver(TileButton::TileSymbol winner){
	this->scoreBoard->incrementScore(winner);
}

void MainWindow::resetScore(){
	this->scoreBoard->resetScore();
}

TileButton::TileSymbol MainWindow::newTurn(){
	TileButton::TileSymbol newTurn = this->changeTurn();
	this->board->resetBoard(this->turn);
	this->nextTurn();
	return newTurn;
}

bool MainWindow::setOpponentHuman(){
	this->opponentHuman = true;
	this->board->toggleOClicks(opponentHuman);
	this->opponentWorking = false;

	QObject *sendingObject = sender();
	foreach(QAction *qa, this->opponentMenu->actions()){
		if(sendingObject == qa || qa->text().compare("Human") == 0){
			qa->setChecked(true);
		}else{
			qa->setChecked(false);
		}
	}

#if DEBUG_FLAG
	qDebug() << "Opponent set Human.";
#endif
	return true;
}

bool MainWindow::setOpponentRandom(){
	this->opponentHuman = false;
	this->board->toggleOClicks(opponentHuman);
	this->opponentWorking = false;

	QObject *sendingObject = sender();
	foreach(QAction *qa, this->opponentMenu->actions()){
		if(sendingObject == qa){
			qa->setChecked(true);
		}else{
			qa->setChecked(false);
		}
	}

	this->opponent = new OpponentRandom("Random Opponenet", TileButton::TileSymbol::O);

#if DEBUG_FLAG
	qDebug() << "Opponent set Random.";
#endif

	if(this->turn == TileButton::TileSymbol::O){
		nextTurn();
	}
	return true;
}

bool MainWindow::nextTurn(){
#if DEBUG_FLAG
	qDebug() << "MainWindow nextTurn()";
#endif

	this->turn = this->board->getCurrentTurn();
	if( this->board->getIsGameOver() || this->opponentHuman || this->turn == TileButton::TileSymbol::X || this->opponentWorking == true){
		return true;
	}

	this->opponentWorking = true;
	TileButton::TileSymbol** currentState = this->board->getCurrentState();
	TileButton::TilePosition selectedPosition = this->opponent->makeTurn(currentState);

	this->board->tileSelected(selectedPosition);
	for(int row = 0; row < NUM_OF_ROWS; row++){
		delete currentState[row];
	}
	delete currentState;

	this->opponentWorking = false;
	return false;
}
