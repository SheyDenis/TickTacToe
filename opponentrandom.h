#ifndef OPPONENTRANDOM_H
#define OPPONENTRANDOM_H

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QList>
#include "opponent.h"
#include "tileboard.h"

class OpponentRandom : public Opponent{

public:
	OpponentRandom(QString name, TileButton::TileSymbol turn = TileButton::TileSymbol::O);
	virtual TileButton::TilePosition makeTurn(TileButton::TileSymbol** currentState);

};

#endif // OPPONENTRANDOM_H
