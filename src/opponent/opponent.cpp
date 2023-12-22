#include "opponent/opponent.h"

#include <utility>

namespace ticktactoe {

Opponent::Opponent(QString name, TileButton::TileSymbol turn)
    : opponentName(std::move(name)), turn(turn) {}

QString const& Opponent::getName() const {
  return opponentName;
}

TileButton::TileSymbol Opponent::getTurn() const {
  return turn;
}

} // namespace ticktactoe
