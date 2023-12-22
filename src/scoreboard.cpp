#include "scoreboard.h"
#include "moc_scoreboard.cpp"

namespace ticktactoe {

ScoreBoard::ScoreBoard(QWidget* parent)
    : QWidget(parent), xScoreLbl(new QLabel("", this)), oScoreLbl(new QLabel("", this)) {
  resetScore();

  QBoxLayout* l = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
  setLayout(l);

  QFont font = QWidget::font();
  font.setPointSize(15);
  xScoreLbl->setFont(font);
  oScoreLbl->setFont(font);
  xScoreLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  oScoreLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  l->addWidget(xScoreLbl, 0, Qt::AlignLeft);
  l->addWidget(oScoreLbl, 0, Qt::AlignLeft);
}

void ScoreBoard::resetScore() {
  xScore = 0;
  oScore = 0;
  redrawScores();
}

void ScoreBoard::redrawScores() {
  xScoreLbl->clear();
  oScoreLbl->clear();
  xScoreLbl->setText("X: " + QString::number(xScore, 10));
  oScoreLbl->setText("O: " + QString::number(oScore, 10));
}

int ScoreBoard::getScore(TileButton::TileSymbol symbol) {

  switch (symbol) {
    case TileButton::TileSymbol::X:
      return xScore;
    case TileButton::TileSymbol::O:
      return oScore;
    default:
#if DEBUG_FLAG
      qDebug() << "Requested score of neither X or O.";
#endif
      return -1;
  }
}

int ScoreBoard::incrementScore(TileButton::TileSymbol symbol) {

  switch (symbol) {
    case TileButton::TileSymbol::X:
      ++xScore;
      redrawScores();
      return (xScore - 1);
    case TileButton::TileSymbol::O:
      ++oScore;
      redrawScores();
      return (oScore - 1);
    default:
#if DEBUG_FLAG
      qDebug() << "Requested to increment score of neither X or O.";
#endif
      return -1;
  }
}
} // namespace ticktactoe
