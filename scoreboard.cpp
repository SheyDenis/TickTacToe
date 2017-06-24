#include "scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent) : QWidget(parent){
	this->xScoreLbl = new QLabel("", this);
	this->oScoreLbl = new QLabel("", this);
	this->resetScore();

	QBoxLayout *l = new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
	this->setLayout(l);

	QFont font = QWidget::font();
	font.setPointSize(15);
	this->xScoreLbl->setFont(font);
	this->oScoreLbl->setFont(font);
	this->xScoreLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->oScoreLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	l->addWidget(xScoreLbl, 0, Qt::AlignLeft);
	l->addWidget(oScoreLbl, 0, Qt::AlignLeft);
}

void ScoreBoard::resetScore(){
	this->xScore = 0;
	this->oScore = 0;
	this->redrawScores();
}

void ScoreBoard::redrawScores(){
	this->xScoreLbl->clear();
	this->oScoreLbl->clear();
	this->xScoreLbl->setText("X: " + QString::number(this->xScore, 10));
	this->oScoreLbl->setText("O: " + QString::number(this->oScore, 10));
}

int ScoreBoard::getScore(TileButton::TileSymbol symbol){

	switch(symbol){
		case TileButton::TileSymbol::X:
			return this->xScore;
		case TileButton::TileSymbol::O:
			return this->oScore;
		default:
#if DEBUG_FLAG
			qDebug() << "Requested score of neither X or O.";
#endif
			return -1;
	}
}

int ScoreBoard::incrementScore(TileButton::TileSymbol symbol){

	switch(symbol){
		case TileButton::TileSymbol::X:
			this->xScore++;
			this->redrawScores();
			return (this->xScore - 1);
		case TileButton::TileSymbol::O:
			this->oScore++;
			this->redrawScores();
			return (this->oScore - 1);
		default:
#if DEBUG_FLAG
			qDebug() << "Requested to increment score of neither X or O.";
#endif
			return -1;
	}
}
