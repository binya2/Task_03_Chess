#include "Board.h"
#include "Pawn.h"
#include "NullPiece.h"
#include "Player.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#include <iostream>

Board::Board(Player* pl1, Player* pl2) : _lastPiece(NULL)
{
	int i, j;

	// Rooks
	_brd[0][0] = new Rook(pl1, 0, 0, this);
	_brd[0][BOARD_SIZE - 1] = new Rook(pl1, 0, BOARD_SIZE - 1, this);

	_brd[BOARD_SIZE - 1][0] = new Rook(pl2, BOARD_SIZE - 1, 0, this);
	_brd[BOARD_SIZE - 1][BOARD_SIZE - 1] = new Rook(pl2, BOARD_SIZE - 1, BOARD_SIZE - 1, this);

	// Knights
	_brd[0][1] = new Knight(pl1, 0, 1, this);
	_brd[0][BOARD_SIZE - 2] = new Knight(pl1, 0, BOARD_SIZE - 2, this);

	_brd[BOARD_SIZE - 1][1] = new Knight(pl2, BOARD_SIZE - 1, 1, this);
	_brd[BOARD_SIZE - 1][BOARD_SIZE - 2] = new Knight(pl2, BOARD_SIZE - 1, BOARD_SIZE - 2, this);

	// Bishops
	_brd[0][2] = new Bishop(pl1, 0, 2, this);
	_brd[0][BOARD_SIZE - 3] = new Bishop(pl1, 0, BOARD_SIZE - 3, this);

	_brd[BOARD_SIZE - 1][2] = new Bishop(pl2, BOARD_SIZE - 1, 2, this);
	_brd[BOARD_SIZE - 1][BOARD_SIZE - 3] = new Bishop(pl2, BOARD_SIZE - 1, BOARD_SIZE - 3, this);

	// Kings
	_brd[0][3] = new King(pl1, 0, 3, this);

	_brd[BOARD_SIZE - 1][3] = new King(pl2, BOARD_SIZE - 1, 3, this);

	// Queens
	_brd[0][4] = new Queen(pl1, 0, 4, this);

	_brd[BOARD_SIZE - 1][4] = new Queen(pl2, BOARD_SIZE - 1, 4, this);

	// Pawns
	for (j = 0; j < BOARD_SIZE; j++)
	{
		_brd[1][j] = new Pawn(pl1, 1, j, this);
		_brd[BOARD_SIZE - 2][j] = new Pawn(pl2, BOARD_SIZE - 2, j, this);
	}

	// Null pieces
	for (i = 2; i < BOARD_SIZE - 2; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			_brd[i][j] = new NullPiece(i, j);
		}
	}
	
}

Board::~Board()
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			delete _brd[i][j];
		}
	}
}

void Board::print() const
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			cout << _brd[i][j]->getSign() << " ";
		}

		cout << endl;
	}
}

void Board::getString(char res[]) const
{
	int i, j, z=0;
	
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			res[z++] = _brd[i][j]->getSign();
		}
	}
	res[z] = 0;
}

bool Board::isPieceOfPlayer(int row, int col, Player* pl) const
{
	
	return _brd[row][col]->getPlayer() == pl;
}

bool Board::tryMove(int srcRow, int srcCol, int dstRow, int dstCol) const
{
	return _brd[srcRow][srcCol]->isLegalMove(dstRow, dstCol);
}

void Board::Move(int srcRow, int srcCol, int dstRow, int dstCol) 
{
	if (_lastPiece != NULL)
	{
		delete _lastPiece;
	}
	_lastPiece = _brd[dstRow][dstCol];
	_lastSrcRow = srcRow;
	_lastSrcCol = srcCol;
	_lastDstRow = dstRow;
	_lastDstCol = dstCol;


	_brd[dstRow][dstCol] = _brd[srcRow][srcCol];
	_brd[dstRow][dstCol]->setPosition(dstRow, dstCol);

	_brd[srcRow][srcCol] = new NullPiece(srcRow, srcCol);
}

void Board::undoLastMove()
{
	// unable to do undo
	if (_lastPiece == NULL)
	{
		return;
	}
	delete _brd[_lastSrcRow][_lastSrcCol];
	_brd[_lastSrcRow][_lastSrcCol] = _brd[_lastDstRow][_lastDstCol];
	_brd[_lastSrcRow][_lastSrcCol]->setPosition(_lastSrcRow, _lastSrcCol);
	_brd[_lastDstRow][_lastDstCol] = _lastPiece;
	_lastPiece = NULL;
}

Piece** Board::getBoard() const
{
	return (Piece**)_brd;
}