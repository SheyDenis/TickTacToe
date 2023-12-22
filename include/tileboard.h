#ifndef TILEBOARD_H_
#define TILEBOARD_H_

#if DEBUG_FLAG
#include <QDebug>
#endif

#include "tilebutton.h"
#include <QGridLayout>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QWidget>

#define NUM_OF_ROWS 3
#define NUM_OF_COLS 3

namespace ticktactoe {
class TileBoard : public QWidget {
  Q_OBJECT

private:
  TileButton::TileSymbol turn;
  bool isGameOver;
  bool OClicks;

protected:
  TileButton* tiles[3][3]{};

private:
  bool checkGameOver();
  bool checkBoardFull();
  bool selectTile(TileButton::TilePosition position);

protected:
  void resizeEvent(QResizeEvent* event) override;

public:
  explicit TileBoard(QWidget* parent = nullptr);

  [[nodiscard]] bool getIsGameOver() const;
  bool resetBoard(TileButton::TileSymbol beginner);
  TileButton::TileSymbol getCurrentTurn();
  bool toggleOClicks(bool toggle);
  bool getOClicks();
  TileButton::TileSymbol** getCurrentState();

public slots:
  bool tileClicked(TileButton::TilePosition position);
  bool tileSelected(TileButton::TilePosition position);

signals:
  void resized(const QSize* newSize);
  void gameOver(TileButton::TileSymbol winner);
  void gameTie();
  void nextTurn();
};
} // namespace ticktactoe

#endif
