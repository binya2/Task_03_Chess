#include "Rook.h"

Rook::Rook(Player* pl, int row, int col, Board* board) : Piece(pl, 'r', row, col, board)
{

}

bool Rook::isLegalMove(int dstRow, int dstCol) const
{
	// check if its only row or only col
	int rowSteps = dstRow - this->_row;
	int colSteps = dstCol - this->_col;
	bool isNotStraight = rowSteps != 0 &&  colSteps != 0;

	if (isNotStraight)
	{
		return false;
	}

	// check if the way is free
	bool res = Piece::isWayFree(dstRow, dstCol);
	return res;
}