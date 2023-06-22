#include "Queen.h"

Queen::Queen(Player* pl, int row, int col, Board* board) : Piece(pl, 'q', row, col, board)
{

}

bool Queen::isLegalMove(int dstRow, int dstCol) const
{

	// check if its diagonal
	int rowSteps = abs(dstRow - this->_row);
	int colSteps = abs(dstCol - this->_col);
	bool isDiagonal = rowSteps == colSteps;
	bool isNotStraight = rowSteps != 0 && colSteps != 0;

	if (!isDiagonal && isNotStraight)
	{
		return false;
	}



	// check if the way is free
	bool res = Piece::isWayFree(dstRow, dstCol);
	return res;
}