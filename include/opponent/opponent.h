#ifndef OPPONENT_H_
#define OPPONENT_H_

#if DEBUG_FLAG
#include <QDebug>
#endif

#include "tileboard.h"
#include "tilebutton.h"
#include <QString>

namespace ticktactoe {

class Opponent {
protected:
  QString const opponentName;
  TileButton::TileSymbol turn;

public:
  explicit Opponent(QString name, TileButton::TileSymbol turn = TileButton::TileSymbol::O);

  [[nodiscard]] virtual QString const& getName() const;
  [[nodiscard]] virtual TileButton::TileSymbol getTurn() const;
  virtual TileButton::TilePosition makeTurn(TileButton::TileSymbol** currentState) = 0;
};

} // namespace ticktactoe

#endif
