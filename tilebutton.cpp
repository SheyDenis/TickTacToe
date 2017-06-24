#include "tilebutton.h"

TileButton::TileButton(TilePosition position, QWidget *parent) : QPushButton(parent){
	this->tilePos = position;
	this->tileSymbol = TileSymbol::Clear;
}

void TileButton::mouseReleaseEvent(QMouseEvent *event){
	TilePosition pos = this->tilePos;
	QPushButton::mouseReleaseEvent(event);

	emit clicked(pos);
}

void TileButton::resizeSymbol(){

	QFont font = QPushButton::font();

	QSize thisSize = size();
	int minSize = (thisSize.height() < thisSize.width()) ? (int)(thisSize.height() / 2) : (int)(thisSize.width() / 2);
	font.setPointSize(minSize);
	QPushButton::setFont(font);
}

bool TileButton::setSymbol(TileButton::TileSymbol symbol){
	if(this->tileSymbol != TileSymbol::Clear){
		return false;
	}else if(this->tileSymbol == symbol){
		return true;
	}

	switch (symbol) {
		case TileSymbol::X:
			this->setText("X");
			break;
		case TileSymbol::O:
			this->setText("O");
			break;
		case TileSymbol::Clear:
			this->setText("");
			break;
		default:
			return false;
			break;
	}
	this->tileSymbol = symbol;
	return true;
}

TileButton::TileSymbol TileButton::getSymbol(){
	return this->tileSymbol;
}

bool TileButton::resetTile(){
	this->tileSymbol = TileButton::TileSymbol::Clear;
	this->setText("");
	return true;
}
