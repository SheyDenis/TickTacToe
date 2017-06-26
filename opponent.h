#ifndef OPPONENT_H
#define OPPONENT_H

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QString>
#include "tilebutton.h"
#include "tileboard.h"

class Opponent{

public:
	Opponent(QString name, TileButton::TileSymbol turn = TileButton::TileSymbol::O);
	virtual QString getName();
	virtual TileButton::TileSymbol getTurn();
	virtual TileButton::TilePosition makeTurn(TileButton::TileSymbol** currentState) = 0;

protected:
	QString opponentName;
	TileButton::TileSymbol turn;

};

#endif // OPPONENT_H
