#include "opponent.h"

Opponent::Opponent(QString name, TileButton::TileSymbol turn){
	this->opponentName = name;
	this->turn = turn;
}

QString Opponent::getName(){
	return this->opponentName;
}

TileButton::TileSymbol Opponent::getTurn(){
	return this->turn;
}
