#include "tileboard.h"
#include "moc_tileboard.cpp"

namespace ticktactoe {

TileBoard::TileBoard(QWidget* parent)
    : QWidget(parent),
      turn(TileButton::TileSymbol::X),
      isGameOver(false),
      OClicks(false)

{
  QGridLayout* l = new QGridLayout;
  setLayout(l);

  for (int row = 0; row < NUM_OF_ROWS; ++row) {
    for (int col = 0; col < NUM_OF_COLS; ++col) {
      TileButton::TilePosition currentPosition = (TileButton::TilePosition)((row * NUM_OF_COLS) + col);
      TileButton* tmpTile = new TileButton(currentPosition, this);

      tmpTile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

      connect(tmpTile, SIGNAL(clicked(TileButton::TilePosition)), this, SLOT(tileClicked(TileButton::TilePosition)));
      connect(this, SIGNAL(resized(const QSize*)), tmpTile, SLOT(resizeSymbol()));
      tmpTile->setSymbol(TileButton::TileSymbol::Clear);

      tiles[row][col] = tmpTile;
      l->addWidget(tmpTile, row, col, 1, 1);
    }
  }
}

bool TileBoard::resetBoard(TileButton::TileSymbol beginner) {

  bool fail;
  for (int row = 0; row < NUM_OF_ROWS; ++row) {
    for (int col = 0; col < NUM_OF_COLS; ++col) {
      fail = !tiles[row][col]->resetTile();
      if (fail) {
#if DEBUG_FLAG
        qDebug() << "Failed to reset tile: " << row << "," << col;
#endif
        return false;
      }
    }
  }

  turn = beginner;
  isGameOver = false;
  return true;
}

TileButton::TileSymbol TileBoard::getCurrentTurn() {
  return turn;
}

void TileBoard::resizeEvent(QResizeEvent* event) {

  QSize newSize = event->size();
  QGridLayout* l = (QGridLayout*)layout();
  for (int i = 0; i < NUM_OF_ROWS; ++i) {
    l->setColumnMinimumWidth(i, (int)(newSize.width() / 3));
    l->setRowMinimumHeight(i, (int)(newSize.height() / 3));
  }
  QWidget::resizeEvent(event);
  emit resized(&newSize);
}

bool TileBoard::checkGameOver() {

  if (tiles[0][0]->getSymbol() != TileButton::TileSymbol::Clear) {
    if (tiles[0][0]->getSymbol() == tiles[0][1]->getSymbol() && tiles[0][0]->getSymbol() == tiles[0][2]->getSymbol()) { // Top row
      return true;
    } else if (tiles[0][0]->getSymbol() == tiles[1][0]->getSymbol() && tiles[0][0]->getSymbol() == tiles[2][0]->getSymbol()) { // Left col
      return true;
    } else if (tiles[0][0]->getSymbol() == tiles[1][1]->getSymbol() &&
               tiles[0][0]->getSymbol() == tiles[2][2]->getSymbol()) { // Top left to bottom right
      return true;
    }
  }

  if (tiles[1][0]->getSymbol() != TileButton::TileSymbol::Clear) {
    if (tiles[1][0]->getSymbol() == tiles[1][1]->getSymbol() && tiles[1][0]->getSymbol() == tiles[1][2]->getSymbol()) { // Middle row
      return true;
    }
  }

  if (tiles[2][0]->getSymbol() != TileButton::TileSymbol::Clear) {
    if (tiles[2][0]->getSymbol() == tiles[2][1]->getSymbol() && tiles[2][0]->getSymbol() == tiles[2][2]->getSymbol()) { // Bottom row
      return true;
    } else if (tiles[2][0]->getSymbol() == tiles[1][1]->getSymbol() &&
               tiles[2][0]->getSymbol() == tiles[0][2]->getSymbol()) { // Top right to bottom left
      return true;
    }
  }

  if (tiles[0][1]->getSymbol() != TileButton::TileSymbol::Clear) {
    if (tiles[0][1]->getSymbol() == tiles[1][1]->getSymbol() && tiles[0][1]->getSymbol() == tiles[2][1]->getSymbol()) { // Middle col
      return true;
    }
  }

  if (tiles[0][2]->getSymbol() != TileButton::TileSymbol::Clear) {
    if (tiles[0][2]->getSymbol() == tiles[1][2]->getSymbol() && tiles[0][2]->getSymbol() == tiles[2][2]->getSymbol()) { // Right col
      return true;
    }
  }

  return false;
}

bool TileBoard::checkBoardFull() {

  for (int row = 0; row < NUM_OF_ROWS; ++row) {
    for (int col = 0; col < NUM_OF_COLS; ++col) {
      if (tiles[row][col]->getSymbol() == TileButton::TileSymbol::Clear) {
        return false;
      }
    }
  }

  return true;
}

bool TileBoard::tileClicked(TileButton::TilePosition position) {
  if (turn == TileButton::TileSymbol::O && !OClicks) {
    return false;
  }

  bool success = selectTile(position);
  return success;
}

bool TileBoard::toggleOClicks(bool toggle) {
  OClicks = toggle;
  return true;
}

bool TileBoard::getOClicks() {
  return OClicks;
}

bool TileBoard::selectTile(TileButton::TilePosition position) {
  if (isGameOver) {
    return false;
  }

  int row = static_cast<int>(static_cast<std::uint8_t>(position) / NUM_OF_ROWS);
  int col = static_cast<int>(static_cast<std::uint8_t>(position) % NUM_OF_ROWS);

  bool success = tiles[row][col]->setSymbol(turn);
  if (success) {
    bool over = checkGameOver();

    if (over) {
#if DEBUG_FLAG
      qDebug() << "Game over.";
#endif
      isGameOver = true;
      emit gameOver(turn);
    } else {
      bool full = checkBoardFull();
      if (full) {
#if DEBUG_FLAG
        qDebug() << "Game tie.";
#endif
        isGameOver = true;
        emit gameTie();
      } else {
        switch (turn) {
          case TileButton::TileSymbol::X:
            turn = TileButton::TileSymbol::O;
            break;
          case TileButton::TileSymbol::O:
            turn = TileButton::TileSymbol::X;
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

bool TileBoard::tileSelected(TileButton::TilePosition position) {
  bool success = selectTile(position);
  return success;
}

TileButton::TileSymbol** TileBoard::getCurrentState() {

  TileButton::TileSymbol** currentState = new TileButton::TileSymbol*[NUM_OF_ROWS];
  for (int row = 0; row < NUM_OF_ROWS; ++row) {

    currentState[row] = new TileButton::TileSymbol[NUM_OF_COLS];
    for (int col = 0; col < NUM_OF_COLS; ++col) {
      currentState[row][col] = tiles[row][col]->getSymbol();
    }
  }

  return currentState;
}

bool TileBoard::getIsGameOver() const {
  return isGameOver;
}
} // namespace ticktactoe
