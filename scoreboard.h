#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include "tilebutton.h"
#include <QDebug>
#include <QString>
#include <QFont>

class ScoreBoard : public QWidget{
	Q_OBJECT
public:
	explicit ScoreBoard(QWidget *parent = nullptr);
	void resetScore();
	int getScore(TileButton::TileSymbol symbol);
	int incrementScore(TileButton::TileSymbol symbol);

protected:
	void redrawScores();

private:
	QLabel *xScoreLbl;
	QLabel *oScoreLbl;
	int xScore = 0;
	int oScore = 0;

signals:

public slots:

};

#endif // SCOREBOARD_H
