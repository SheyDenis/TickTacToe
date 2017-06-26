#ifndef TILEBOARD_H
#define TILEBOARD_H

#define NUM_OF_ROWS 3
#define NUM_OF_COLS 3

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QWidget>
#include "tilebutton.h"
#include <QResizeEvent>
#include <QGridLayout>
#include <QSizePolicy>

class TileBoard : public QWidget{
	Q_OBJECT
public:
	explicit TileBoard(QWidget *parent = 0);

	bool getIsGameOver();
//	void setIsGameOver(bool value);
	bool resetBoard(TileButton::TileSymbol beginner);
	TileButton::TileSymbol getCurrentTurn();
	bool toggleOClicks(bool toggle);
	bool getOClicks();
	TileButton::TileSymbol** getCurrentState();

protected:
	TileButton *tiles[3][3];
	virtual void resizeEvent(QResizeEvent *event);

private:
	TileButton::TileSymbol turn;
	bool isGameOver;
	bool checkGameOver();
	bool checkBoardFull();
	bool OClicks;
	bool selectTile(TileButton::TilePosition position);

signals:
	void resized(const QSize *newSize);
	void gameOver(TileButton::TileSymbol winner);
	void gameTie();
	void nextTurn();

public slots:
	bool tileClicked(TileButton::TilePosition position);
	bool tileSelected(TileButton::TilePosition position);


};

#endif // TILEBOARD_H
