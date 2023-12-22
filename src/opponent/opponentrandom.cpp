#include "opponent/opponentrandom.h"

OpponentRandom::OpponentRandom(QString name, TileButton::TileSymbol turn): Opponent(name, turn){


}

TileButton::TilePosition OpponentRandom::makeTurn(TileButton::TileSymbol** currentState){

	QList<TileButton::TilePosition> openPositions;

	for(int row = 0; row < NUM_OF_ROWS; row++){
		for(int col = 0; col < NUM_OF_COLS; col++){
			if(currentState[row][col] == TileButton::TileSymbol::Clear){
				openPositions.append(TileButton::intToTilePosition((row * NUM_OF_COLS) + col));
			}
		}
	}

	if(openPositions.empty()){
		throw std::invalid_argument("Requested to make a turn after game is over.");
	}

	int selectIndex = rand() % openPositions.count();

	return openPositions.at(selectIndex);
}
