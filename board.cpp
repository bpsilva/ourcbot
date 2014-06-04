#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

using namespace std;


typedef struct bitboard
{
long long my_pawns, my_rooks, my_bishops, his_pawns, his_rooks, his_bishops;
}BOARD;

typedef struct mov
{
BOARD *b;
mov *prox;
}MOVEMENTS;

BOARD translation(char sboard[64], int who_moves, BOARD board)
{

board.my_pawns = 0;
board.my_rooks = 0;
board.my_bishops = 0;
board.his_pawns = 0;
board.his_rooks = 0;
board.his_bishops = 0;
unsigned long long um = 1;

for(int i = 0; i<64; i++)
{
switch(sboard[i])
	{
	case '.':
		break;

	case 'p':
		if(who_moves == 1)
			board.his_pawns = board.his_pawns | (um<<(63-i));
		else
			board.my_pawns = board.my_pawns | (um<<(63-i));
	case 'r':
		if(who_moves == 1)
			board.his_rooks = board.his_rooks | (um<<(63-i));
		else
			board.my_rooks = board.my_rooks | (um<<(63-i));
	case 'b':
		if(who_moves == 1)
			board.his_bishops = board.his_bishops | (um<<(63-i));
		else
			board.my_bishops = board.my_bishops | (um<<(63-i));
	case 'P':
		if(who_moves == -1)
			board.his_pawns = board.his_pawns | (um<<(63-i));
		else
			board.my_pawns = board.my_pawns | (um<<(63-i));
	case 'R':
		if(who_moves == -1)
			board.his_rooks = board.his_rooks | (um<<(63-i));
		else
			board.my_rooks = board.my_rooks | (um<<(63-i));
	case 'B':
		if(who_moves == -1)
			board.his_bishops = board.his_bishops | (um<<(63-i));
		else
			board.my_bishops = board.my_bishops | (um<<(63-i));
	
	}
}

return board;
}


void print2(unsigned long long board, int it)
{	
	if (it>0){
	print2(board/2, it-1);
	printf("%lli ", board%2);
	if(it%8 == 0)
		printf("\n");
	}
}
void print(unsigned long long board)
{
	print2(board, 64);
}
//zerar coluna 0 (esquerda) do tabuleiro : board &= 9187201950435737471ll
//zerar coluna 7 (direita) do tabuleiro : board &= -72340172838076674ll

unsigned long long movements()
{
	BOARD b;
	BOARD mov[100];
	int mcounter = 0;

	b.my_pawns = pow(2,10)-1;
	b.my_rooks = 9879889;
	b.my_bishops = 0;

	long long my_pieces = b.my_pawns | b.my_bishops;
	my_pieces = my_pieces | b.my_rooks;
	my_pieces = -my_pieces;
	my_pieces--;

	long long aux = 0;
	long long zerar = 9187201950435737471;

	aux = b.my_pawns&zerar;
	

	aux <<= 9;
	aux &=my_pieces;
	long long pawn = 1;

	BOARD newboard = {b.my_pawns, b.my_rooks, b.my_bishops, b.his_pawns, b.his_rooks, b.his_bishops};	
	
	print(b.my_pawns);
	printf("\n");
	while(pawn!=0)
	{
		pawn = aux&-aux;
		newboard.my_pawns&=pawn;
		newboard.my_pawns&=(pawn>>9);
		pawn = -pawn;
		pawn--;
		aux&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;
		print(newboard.my_pawns);
	printf("\n");
		
	}
	

// my pawns' movements



	


}


int main()

{
movements();
return 0;
}
