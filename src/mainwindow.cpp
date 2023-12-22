#include "mainwindow.h"
#include "moc_mainwindow.cpp"

namespace ticktactoe {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), opponentHuman(false), opponent(nullptr), opponentWorking(false) {

  menuBar()->addAction("New Turn", this, SLOT(newTurn()));

  opponentMenu = new QMenu("Opponent"); // TODO - Replace raw pointer usage all over.
  opponentMenu->addAction("Human", this, SLOT(setOpponentHuman()));
  opponentMenu->addAction("Random", this, SLOT(setOpponentRandom()));

  foreach (QAction* qa, opponentMenu->actions()) {
    qa->setCheckable(true);
  }

  menuBar()->addMenu(opponentMenu);

  menuBar()->addAction("Reset Score", this, SLOT(resetScore()));

  board = new TileBoard(this);
  turn = board->getCurrentTurn();
  setCentralWidget(board);

  setMinimumSize(300, 300);

  QDockWidget* scoreWidget = new QDockWidget("Score:", this);
  scoreWidget->setAllowedAreas(Qt::TopDockWidgetArea);
  scoreBoard = new ScoreBoard(scoreWidget);
  scoreWidget->setWidget(scoreBoard);
  scoreWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
  scoreWidget->setMaximumHeight(60);
  scoreWidget->setMaximumWidth(300);
  addDockWidget(Qt::TopDockWidgetArea, scoreWidget);

  connect(board, SIGNAL(gameOver(TileButton::TileSymbol)), this, SLOT(gameOver(TileButton::TileSymbol)));
  connect(board, SIGNAL(nextTurn()), this, SLOT(nextTurn()));
  setOpponentHuman();
  board->toggleOClicks(true);
}

TileButton::TileSymbol MainWindow::changeTurn() {
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

  return turn;
}

bool MainWindow::newGame() {
  bool fail = board == nullptr;

  if (!fail) {
    changeTurn();
    board->toggleOClicks(opponentHuman);
    resetScore();
    fail = !board->resetBoard(turn);
  }

  return !fail;
}

void MainWindow::gameOver(TileButton::TileSymbol winner) {
  scoreBoard->incrementScore(winner);
}

void MainWindow::resetScore() {
  scoreBoard->resetScore();
}

TileButton::TileSymbol MainWindow::newTurn() {
  TileButton::TileSymbol newTurn = changeTurn();
  board->resetBoard(turn);
  nextTurn();
  return newTurn;
}

bool MainWindow::setOpponentHuman() {
  opponentHuman = true;
  board->toggleOClicks(opponentHuman);
  opponentWorking = false;

  QObject* sendingObject = sender();
  foreach (QAction* qa, opponentMenu->actions()) {
    if (sendingObject == qa || qa->text().compare("Human") == 0) {
      qa->setChecked(true);
    } else {
      qa->setChecked(false);
    }
  }

#if DEBUG_FLAG
  qDebug() << "Opponent set Human.";
#endif
  return true;
}

bool MainWindow::setOpponentRandom() {
  opponentHuman = false;
  board->toggleOClicks(opponentHuman);
  opponentWorking = false;

  QObject* sendingObject = sender();
  foreach (QAction* qa, opponentMenu->actions()) {
    if (sendingObject == qa) {
      qa->setChecked(true);
    } else {
      qa->setChecked(false);
    }
  }

  opponent = new OpponentRandom("Random Opponent", TileButton::TileSymbol::O);

#if DEBUG_FLAG
  qDebug() << "Opponent set Random.";
#endif

  if (turn == TileButton::TileSymbol::O) {
    nextTurn();
  }
  return true;
}

bool MainWindow::nextTurn() {
#if DEBUG_FLAG
  qDebug() << "MainWindow nextTurn()";
#endif

  turn = board->getCurrentTurn();
  if (board->getIsGameOver() || opponentHuman || turn == TileButton::TileSymbol::X || opponentWorking) {
    return true;
  }

  opponentWorking = true;
  TileButton::TileSymbol** currentState = board->getCurrentState();
  TileButton::TilePosition selectedPosition = opponent->makeTurn(currentState);

  board->tileSelected(selectedPosition);
  for (int row = 0; row < NUM_OF_ROWS; ++row) {
    delete currentState[row];
  }
  delete currentState;

  opponentWorking = false;
  return false;
}
} // namespace ticktactoe
