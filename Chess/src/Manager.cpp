#include "Manager.h"
#include "King.h"
#include <iostream>
#include <exception>

using namespace std;

#define VALID_MOVE 42
#define INVALID_EMPTY_POSIRION 11

#define VALID_CHESS_MOVE 41
#define INVALID_NOT_YOUR_PLAYER 12
#define INVALID_DEST_NOT_FREE 13

#define INVALID_CHESS_WILL_OCCURE 31

#define INVALID_OUT_OF_BOUNDS 21
#define INVALID_ILLEGAL_MOVE 21
#define INVALID_SRC_AND_DEST_EQUAL 21

//#define CHECK_MATE 8

Manager::Manager()
{
	_player1 = new Player(true);
	_player2 = new Player(false);

	_currPlayer = _player1;
	_otherPlayer = _player2;

	_brd = new Board(_player1, _player2);

}



void Manager::changeTurn()
{
	Player* temp = _currPlayer;
	_currPlayer = _otherPlayer;
	_otherPlayer = temp;
}


int Manager::playMove(string move)
{
	int srcCol = BOARD_SIZE - (move[1] - '0');
	int srcRow = move[0] - 'a';

	int dstCol = BOARD_SIZE -  (move[3] - '0');
	int dstRow = move[2] - 'a';
	cout << "Move from: " << srcRow << ", " << srcCol << "To " << dstRow << ", " << dstCol << endl;
	
	if (srcRow < 0 || srcRow >= BOARD_SIZE ||
		srcCol < 0 || srcCol >= BOARD_SIZE ||
		dstRow < 0 || dstRow >= BOARD_SIZE ||
		dstCol < 0 || dstCol >= BOARD_SIZE)
	{
		return INVALID_OUT_OF_BOUNDS;
	}

	if (_brd->isPieceOfPlayer(srcRow, srcCol, NULL))
	{
		return INVALID_EMPTY_POSIRION;
	}

	if (!_brd->isPieceOfPlayer(srcRow, srcCol, _currPlayer))
	{
		return INVALID_NOT_YOUR_PLAYER;
	}

	if (_brd->isPieceOfPlayer(dstRow, dstCol, _currPlayer))
	{
		return INVALID_DEST_NOT_FREE;
	}

	if (srcRow == dstRow && srcCol == dstCol)
	{
		return INVALID_SRC_AND_DEST_EQUAL;
	}

	if (!_brd->tryMove(srcRow, srcCol, dstRow, dstCol))
	{
		return INVALID_ILLEGAL_MOVE;
	}

	// Make the move!
	_brd->Move(srcRow, srcCol, dstRow, dstCol);

	// check for chess
	if (_currPlayer->getKing()->isChess())
	{
		// if chess undo the last move
		_brd->undoLastMove();
		return INVALID_CHESS_WILL_OCCURE;
	}

	int res;
	// after move check if it is chess
	if (_otherPlayer->getKing()->isChess())
	{
		res =  VALID_CHESS_MOVE;
	}
	else
	{
		res = VALID_MOVE;
	}
	
	this->changeTurn();
	return res;

} 


Manager::~Manager()
{
	delete _player1;
	delete _player2;
	delete _brd;
}
