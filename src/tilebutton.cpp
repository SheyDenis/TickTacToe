#include "tilebutton.h"
#include "moc_tilebutton.cpp"

namespace ticktactoe {

TileButton::TileButton(TilePosition position, QWidget* parent)
    : QPushButton(parent) {
  tilePos = position;
  tileSymbol = TileSymbol::Clear;
}

void TileButton::mouseReleaseEvent(QMouseEvent* event) {
  TilePosition pos = tilePos;
  QPushButton::mouseReleaseEvent(event);

  emit clicked(pos);
}

void TileButton::resizeSymbol() {

  QFont font = QPushButton::font();

  QSize thisSize = size();
  int minSize = (thisSize.height() < thisSize.width()) ? (int)(thisSize.height() / 2) : (int)(thisSize.width() / 2);
  font.setPointSize(minSize);
  QPushButton::setFont(font);
}

bool TileButton::setSymbol(TileButton::TileSymbol symbol) {
  if (tileSymbol != TileSymbol::Clear) {
    return false;
  } else if (tileSymbol == symbol) {
    return true;
  }

  switch (symbol) {
    case TileSymbol::X:
      setText("X");
      break;
    case TileSymbol::O:
      setText("O");
      break;
    case TileSymbol::Clear:
      setText("");
      break;
    default:
      return false;
      break;
  }
  tileSymbol = symbol;
  return true;
}

TileButton::TileSymbol TileButton::getSymbol() {
  return tileSymbol;
}

bool TileButton::resetTile() {
  tileSymbol = TileButton::TileSymbol::Clear;
  setText("");
  return true;
}

TileButton::TilePosition TileButton::intToTilePosition(int n) {
  TileButton::TilePosition tmpPos;
  switch (n) {
    case 0:
      tmpPos = TileButton::TilePosition::TopLeft;
      break;
    case 1:
      tmpPos = TileButton::TilePosition::TopMiddle;
      break;
    case 2:
      tmpPos = TileButton::TilePosition::TopRight;
      break;
    case 3:
      tmpPos = TileButton::TilePosition::MiddleLeft;
      break;
    case 4:
      tmpPos = TileButton::TilePosition::MiddleMiddle;
      break;
    case 5:
      tmpPos = TileButton::TilePosition::MiddleRight;
      break;
    case 6:
      tmpPos = TileButton::TilePosition::BottomLeft;
      break;
    case 7:
      tmpPos = TileButton::TilePosition::BottomMiddle;
      break;
    case 8:
      tmpPos = TileButton::TilePosition::BottomRight;
      break;
    default:
#if DEBUG_FLAG
      qDebug() << "Requested conversion from invalid number to TilePosition";
#endif
      throw std::invalid_argument("Requested conversion from invalid number to TilePosition");
  }

  return tmpPos;
}
} // namespace ticktactoe
