#ifndef TILEBUTTON_H_
#define TILEBUTTON_H_

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QFont>
#include <QObject>
#include <QPushButton>

namespace ticktactoe {

class TileButton : public QPushButton {
  Q_OBJECT

public:
  enum class TilePosition : std::uint8_t {
    TopLeft = 0,
    TopMiddle = 1,
    TopRight = 2,
    MiddleLeft = 3,
    MiddleMiddle = 4,
    MiddleRight = 5,
    BottomLeft = 6,
    BottomMiddle = 7,
    BottomRight = 8,
  };

  enum class TileSymbol : std::uint8_t {
    Clear = 0,
    X = 1,
    O = 2,
  };

private:
  TilePosition tilePos;
  TileSymbol tileSymbol;

protected:
  void mouseReleaseEvent(QMouseEvent* event) override;

public:
  explicit TileButton(TilePosition position, QWidget* parent = nullptr);

  bool setSymbol(TileSymbol symbol);
  TileButton::TileSymbol getSymbol();
  bool resetTile();
  static TileButton::TilePosition intToTilePosition(int n);

signals:
  void clicked(TileButton::TilePosition tilePos);
public slots:
  void resizeSymbol();
};
} // namespace ticktactoe

#endif
