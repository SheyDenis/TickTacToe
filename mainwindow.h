#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QMainWindow>
#include "tileboard.h"
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>
#include <QDockWidget>
#include "scoreboard.h"
#include "opponent.h"
#include "opponentrandom.h"

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:

private:
	TileButton::TileSymbol changeTurn();
	TileBoard *board;
	TileButton::TileSymbol turn;
	ScoreBoard *scoreBoard;
	bool opponentHuman;
	QMenu *opponentMenu;
	Opponent *opponent;
	bool opponentWorking;


public slots:
	bool newGame();

private slots:
//	void gameTie();
	void gameOver(TileButton::TileSymbol winner);
	void resetScore();
	TileButton::TileSymbol newTurn();
	bool setOpponentHuman();
	bool setOpponentRandom();
	bool nextTurn();
};

#endif // MAINWINDOW_H
