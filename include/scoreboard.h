#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#if DEBUG_FLAG
#include <QDebug>
#endif

#include "tilebutton.h"
#include <QBoxLayout>
#include <QFont>
#include <QLabel>
#include <QString>
#include <QWidget>

namespace ticktactoe {

class ScoreBoard : public QWidget {
  Q_OBJECT

private:
  QLabel* xScoreLbl;
  QLabel* oScoreLbl;
  int xScore = 0;
  int oScore = 0;

protected:
  void redrawScores();

public:
  explicit ScoreBoard(QWidget* parent = nullptr);

  void resetScore();
  int getScore(TileButton::TileSymbol symbol);
  int incrementScore(TileButton::TileSymbol symbol);
};
} // namespace ticktactoe

#endif
