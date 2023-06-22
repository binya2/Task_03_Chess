#include "Knight.h"

Knight::Knight(Player* pl, int row, int col, Board* board) : Piece(pl, 'n', row, col, board)
{

}

bool Knight::isLegalMove(int dstRow, int dstCol) const
{
	// check if its diagonal
	int rowSteps = abs(dstRow - this->_row);
	int colSteps = abs(dstCol - this->_col);
	
	bool res = (rowSteps == 2 && colSteps == 1) || (rowSteps == 1 && colSteps == 2);
	
	return res;
}
