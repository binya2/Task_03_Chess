#include "King.h"

King::King(Player* pl, int row, int col, Board* board) : Piece(pl, 'k', row, col, board)
{
	pl->setKing(this);
}

bool King::isLegalMove(int dstRow, int dstCol) const
{
	// check if its diagonal
	int rowSteps = abs(dstRow - this->_row);
	int colSteps = abs(dstCol - this->_col);
	bool res = rowSteps <=1 && colSteps <= 1;

	return res;

}

bool King::isChess()
{
	// should be able to undo the movement that will make for check the chess
	
	Piece** matBoard = _brd->getBoard();
	Piece* currPiece;
	
	Player* pl;

	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			currPiece = matBoard[i * BOARD_SIZE + j];
			pl = currPiece->getPlayer();

			if (pl != NULL && pl != _player)
			{
				// if the piece of the oponnent can reach the King
				if (currPiece->isLegalMove(_row, _col))
				{
					return true;
				}
			}
		}
	}
	
	return false;
}