#ifndef OPPONENTRANDOM_H_
#define OPPONENTRANDOM_H_

#if DEBUG_FLAG
#include <QDebug>
#endif

#include "opponent/opponent.h"
#include "tileboard.h"
#include <QList>

namespace ticktactoe {

class OpponentRandom : public Opponent {
public:
  explicit OpponentRandom(QString name, TileButton::TileSymbol turn = TileButton::TileSymbol::O);

  TileButton::TilePosition makeTurn(TileButton::TileSymbol** currentState) override;
};

} // namespace ticktactoe

#endif
