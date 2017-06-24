#ifndef TILEBOARD_H
#define TILEBOARD_H

#define NUM_OF_ROWS 3
#define NUM_OF_COLS 3

#include <QWidget>
#include "tilebutton.h"
#include <QResizeEvent>
#include <QGridLayout>
#include <QSizePolicy>
#include <QDebug>

class TileBoard : public QWidget{
	Q_OBJECT
public:
	explicit TileBoard(QWidget *parent = 0);

	bool getIsGameOver() const;
	void setIsGameOver(bool value);
	bool resetBoard(TileButton::TileSymbol beginner);
	TileButton::TileSymbol getCurrentTurn();

protected:
	TileButton *tiles[3][3];
	virtual void resizeEvent(QResizeEvent *event);

private:
	TileButton::TileSymbol turn;
	bool isGameOver;
	bool checkGameOver();
	bool checkBoardFull();

signals:
	void resized(const QSize *newSize);
	void gameOver(TileButton::TileSymbol winner);
	void gameTie();

public slots:
	bool tileClicked(TileButton::TilePosition position);

};

#endif // TILEBOARD_H
