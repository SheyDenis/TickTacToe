#include "tileboard.h"
#include "moc_tileboard.cpp"

TileBoard::TileBoard(QWidget *parent) : QWidget(parent){
	QGridLayout *l = new QGridLayout;
	this->setLayout(l);

	for(int row = 0; row < NUM_OF_ROWS; row++){
		for(int col = 0; col < NUM_OF_COLS; col++){
			TileButton::TilePosition currentPosition = (TileButton::TilePosition)((row * NUM_OF_COLS) + col);
			TileButton *tmpTile = new TileButton(currentPosition, this);

			tmpTile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

			connect(tmpTile, SIGNAL(clicked(TileButton::TilePosition)), this, SLOT(tileClicked(TileButton::TilePosition)));
			connect(this,SIGNAL(resized(const QSize*)),tmpTile,SLOT(resizeSymbol()));
			tmpTile->setSymbol(TileButton::TileSymbol::Clear);

			tiles[row][col] = tmpTile;
			l->addWidget(tmpTile, row, col, 1, 1);
		}
	}

	this->turn = TileButton::TileSymbol::X;
	this->isGameOver = false;
	this->OClicks = false;

}

bool TileBoard::resetBoard(TileButton::TileSymbol beginner){

	bool fail = false;
	for(int row = 0; row < NUM_OF_ROWS; row++){
		for(int col = 0; col < NUM_OF_COLS; col++){
			fail = !this->tiles[row][col]->resetTile();
			if(fail){
#if DEBUG_FLAG
				qDebug() << "Failed to reset tile: " << row << "," << col;
#endif
				return false;
			}
		}
	}

	this->turn = beginner;
	this->isGameOver = false;
	return true;

}

TileButton::TileSymbol TileBoard::getCurrentTurn(){
	return this->turn;
}

void TileBoard::resizeEvent(QResizeEvent *event){

	QSize newSize = event->size();
	QGridLayout *l = (QGridLayout*)this->layout();
	for(int i = 0; i < NUM_OF_ROWS; i++){
		l->setColumnMinimumWidth(i, (int)(newSize.width() / 3));
		l->setRowMinimumHeight(i, (int)(newSize.height() / 3));
	}
	QWidget::resizeEvent(event);
	emit resized(&newSize);

}

bool TileBoard::checkGameOver(){

	if(this->tiles[0][0]->getSymbol() != TileButton::TileSymbol::Clear){
		if(this->tiles[0][0]->getSymbol() == this->tiles[0][1]->getSymbol() && this->tiles[0][0]->getSymbol() == this->tiles[0][2]->getSymbol()){ // Top row
			return true;
		}else if(this->tiles[0][0]->getSymbol() == this->tiles[1][0]->getSymbol() && this->tiles[0][0]->getSymbol() == this->tiles[2][0]->getSymbol()){ // Left col
			return true;
		}else if(this->tiles[0][0]->getSymbol() == this->tiles[1][1]->getSymbol() && this->tiles[0][0]->getSymbol() == this->tiles[2][2]->getSymbol()){ // Top left to bottom right
			return true;
		}
	}

	if(this->tiles[1][0]->getSymbol() != TileButton::TileSymbol::Clear){
		if(this->tiles[1][0]->getSymbol() == this->tiles[1][1]->getSymbol() && this->tiles[1][0]->getSymbol() == this->tiles[1][2]->getSymbol()){ // Middle row
			return true;
		}
	}

	if(this->tiles[2][0]->getSymbol() != TileButton::TileSymbol::Clear){
		if(this->tiles[2][0]->getSymbol() == this->tiles[2][1]->getSymbol() && this->tiles[2][0]->getSymbol() == this->tiles[2][2]->getSymbol()){ // Bottom row
			return true;
		}else if(this->tiles[2][0]->getSymbol() == this->tiles[1][1]->getSymbol() && this->tiles[2][0]->getSymbol() == this->tiles[0][2]->getSymbol()){ // Top right to bottom left
			return true;
		}
	}

	if(this->tiles[0][1]->getSymbol() != TileButton::TileSymbol::Clear){
		if(this->tiles[0][1]->getSymbol() == this->tiles[1][1]->getSymbol() && this->tiles[0][1]->getSymbol() == this->tiles[2][1]->getSymbol()){ // Middle col
			return true;
		}
	}

	if(this->tiles[0][2]->getSymbol() != TileButton::TileSymbol::Clear){
		if(this->tiles[0][2]->getSymbol() == this->tiles[1][2]->getSymbol() && this->tiles[0][2]->getSymbol() == this->tiles[2][2]->getSymbol()){ // Right col
			return true;
		}
	}

	return false;
}

bool TileBoard::checkBoardFull(){

	for(int row = 0; row < NUM_OF_ROWS; row++){
		for(int col = 0; col < NUM_OF_COLS; col++){
			if(this->tiles[row][col]->getSymbol() == TileButton::TileSymbol::Clear){
				return false;
			}
		}
	}

	return true;

}

bool TileBoard::tileClicked(TileButton::TilePosition position){
	if(this->turn == TileButton::TileSymbol::O && !this->OClicks){
		return false;
	}

	bool success = this->selectTile(position);
	return success;
}

bool TileBoard::toggleOClicks(bool toggle){
	this->OClicks = toggle;
	return true;
}

bool TileBoard::getOClicks(){
	return this->OClicks;
}

bool TileBoard::selectTile(TileButton::TilePosition position){
	if(this->isGameOver){
		return false;
	}

	int row = (int)(position / NUM_OF_ROWS);
	int col = (int)(position % NUM_OF_ROWS);

	bool success = this->tiles[row][col]->setSymbol(this->turn);
	if(success){
		bool over = checkGameOver();

		if(over){
#if DEBUG_FLAG
			qDebug() << "Game over.";
#endif
			this->isGameOver = true;
			emit gameOver(this->turn);
		}else{
			bool full = checkBoardFull();
			if(full){
#if DEBUG_FLAG
				qDebug() << "Game tie.";
#endif
				this->isGameOver = true;
				emit gameTie();
			}else{
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
			}
		}

	}

	emit nextTurn();
	return true;
}

bool TileBoard::tileSelected(TileButton::TilePosition position){
	bool success = this->selectTile(position);
	return success;
}

TileButton::TileSymbol** TileBoard::getCurrentState(){

	TileButton::TileSymbol** currentState = new TileButton::TileSymbol*[NUM_OF_ROWS];
	for(int row = 0; row < NUM_OF_ROWS; row++){

		currentState[row] = new TileButton::TileSymbol[NUM_OF_COLS];
		for(int col = 0; col < NUM_OF_COLS; col++){
			currentState[row][col] = this->tiles[row][col]->getSymbol();
		}
	}

	return currentState;

}

bool TileBoard::getIsGameOver(){
	return this->isGameOver;
}
