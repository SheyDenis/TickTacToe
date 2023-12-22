#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

#if DEBUG_FLAG
#include <QDebug>
#endif

#include "opponent/opponent.h"
#include "opponent/opponentrandom.h"
#include "scoreboard.h"
#include "tileboard.h"
#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

namespace ticktactoe {

class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  TileBoard* board;
  TileButton::TileSymbol turn;
  ScoreBoard* scoreBoard;
  bool opponentHuman;
  QMenu* opponentMenu;
  Opponent* opponent;
  bool opponentWorking;

private slots:
  void gameOver(TileButton::TileSymbol winner);
  void resetScore();
  TileButton::TileSymbol newTurn();
  bool setOpponentHuman();
  bool setOpponentRandom();
  bool nextTurn();
  TileButton::TileSymbol changeTurn();

public slots:
  bool newGame();

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override = default;
};

} // namespace ticktactoe

#endif
