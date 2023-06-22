#include "Bishop.h"

Bishop::Bishop(Player* pl, int row, int col ,Board* board) : Piece(pl, 'b', row, col, board)
{

}

bool Bishop::isLegalMove(int dstRow, int dstCol) const
{
	// check if its diagonal
	int rowSteps = abs(dstRow - this->_row);
	int colSteps = abs(dstCol - this->_col);
	bool isDiagonal = rowSteps == colSteps;

	if (!isDiagonal)
	{
		return false;
	}

	// check if the way is free
	bool res = Piece::isWayFree(dstRow, dstCol);
	return res;
}