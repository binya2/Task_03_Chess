#include "Pawn.h"


Pawn::Pawn(Player* pl, int row, int col, Board* board) : Piece(pl, 'p', row, col, board)
{

}

 bool Pawn::isLegalMove(int dstRow, int dstCol) const
{
	bool res;
	int num = 1;

	// check if want to eat
	Piece* destPiece = _brd->getBoard()[dstRow * BOARD_SIZE + dstCol];
	Player* pl = destPiece->getPlayer();

	// the oponnent piece
	if (pl != NULL  && pl != this->_player)
	{
		if (this->_player->isGoingUp())
		{
			res = (_row - dstRow) == 1;
		}
		else
		{
			res = (_row - dstRow) == -1;

		}
		
		res = res && abs(_col - dstCol) == 1;
		return res;
	}
	
	// if the place is not free
	if (pl != NULL)
	{
		return false;
	}
	// check if didnt move yet
	if (_row == _startRow && _col == _startCol)
	{
		num = 2;
	}


	if (this->_player->isGoingUp())
	{
		res = _col == dstCol && (dstRow - _row) < 0 && (dstRow - _row) >= num * -1;
	}
	else
	{
		res = _col == dstCol && (dstRow - _row) > 0 && (dstRow - _row) <= num;
	}

	if (res && num == 2)
	{
		res = this->isWayFree(dstRow, dstCol);

	}
	
	return res;
}