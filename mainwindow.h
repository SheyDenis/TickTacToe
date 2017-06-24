#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tileboard.h"
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>
#include <QDebug>
#include <QDockWidget>
#include "scoreboard.h"

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


public slots:
	bool newGame();

private slots:
//	void gameTie();
	void gameOver(TileButton::TileSymbol winner);
	void resetScore();
	TileButton::TileSymbol newTurn();
};

#endif // MAINWINDOW_H
