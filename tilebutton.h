#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#if DEBUG_FLAG
#include <QDebug>
#endif

#include <QObject>
#include <QPushButton>
#include <QFont>

class TileButton : public QPushButton{
	Q_OBJECT

public:
	enum TilePosition{
		TopLeft = 0,
		TopMiddle = 1,
		TopRight = 2,
		MiddleLeft = 3,
		MiddleMiddle = 4,
		MiddleRight = 5,
		BottomLeft = 6,
		BottmMiddle = 7,
		BottomRight = 8
	};

	enum TileSymbol{
		Clear = 0,
		X = 1,
		O = 2
	};

	explicit TileButton(TilePosition position, QWidget *parent = 0);

	bool setSymbol(TileSymbol symbol);
	TileButton::TileSymbol getSymbol();
	bool resetTile();

private:
	TilePosition tilePos;
	TileSymbol tileSymbol;

protected:
	virtual void mouseReleaseEvent(QMouseEvent* event);

signals:
	void clicked(TileButton::TilePosition tilePos);

public slots:
	void resizeSymbol();

};

#endif // TILEBUTTON_H
