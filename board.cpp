#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

using namespace std;


typedef struct bitboard
{
long long white_pawns, white_rooks, white_bishops, black_pawns, black_rooks, black_bishops, enpassant;
}BOARD;

typedef struct mov
{
BOARD *b;
mov *prox;
}MOVEMENTS;

BOARD translation(char sboard[64], int who_moves, BOARD board)
{

board.white_pawns = 0;
board.white_rooks = 0;
board.white_bishops = 0;
board.black_pawns = 0;
board.black_rooks = 0;
board.black_bishops = 0;
unsigned long long um = 1;

for(int i = 0; i<64; i++)
{
switch(sboard[i])
	{
	case '.':
		break;

	case 'p':
		if(who_moves == 1)
			board.black_pawns = board.black_pawns | (um<<(63-i));
		else
			board.white_pawns = board.white_pawns | (um<<(63-i));
	case 'r':
		if(who_moves == 1)
			board.black_rooks = board.black_rooks | (um<<(63-i));
		else
			board.white_rooks = board.white_rooks | (um<<(63-i));
	case 'b':
		if(who_moves == 1)
			board.black_bishops = board.black_bishops | (um<<(63-i));
		else
			board.white_bishops = board.white_bishops | (um<<(63-i));
	case 'P':
		if(who_moves == -1)
			board.black_pawns = board.black_pawns | (um<<(63-i));
		else
			board.white_pawns = board.white_pawns | (um<<(63-i));
	case 'R':
		if(who_moves == -1)
			board.black_rooks = board.black_rooks | (um<<(63-i));
		else
			board.white_rooks = board.white_rooks | (um<<(63-i));
	case 'B':
		if(who_moves == -1)
			board.black_bishops = board.black_bishops | (um<<(63-i));
		else
			board.white_bishops = board.white_bishops | (um<<(63-i));
	
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
	///para teste--------
	BOARD b = {pow(2,8)-1, 0, 0, 0, 0, 0, 0};
	b.white_pawns<<=8;
	///------------------


	BOARD newboard = {b.white_pawns, b.white_rooks, b.white_bishops, b.black_pawns, b.black_rooks, b.black_bishops, b.enpassant};	
	BOARD mov[100];
	int mcounter = 0;

	long long white_pieces = b.white_pawns | b.white_bishops;
	white_pieces = white_pieces | b.white_rooks;
	white_pieces = -white_pieces;
	white_pieces--;

	long long black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;

	long long aux = 0;
	long long pawn = 0;

// white pawns' movements
	
	//para frente
	aux = b.white_pawns;
	aux <<= 8;
	aux &=white_pieces;
	aux &=black_pieces;
	newboard.white_pawns = b.white_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

		//movimentos para frente

	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.white_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;		
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=8;
		pawn = -pawn;
		pawn--;
		newboard.white_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;
		
		if(pawn<=pow(2,48)-1)
		{

			pawn <<= 16;
			black_pieces = -black_pieces;
			black_pieces--;
			white_pieces = -white_pieces;
			white_pieces--;
			
			if((pawn & black_pieces) == 0 && (pawn & white_pieces) == 0)
			{
				newboard.white_pawns|=pawn;
				pawn >>= 8;
				pawn = -pawn;
				pawn--;
				newboard.white_pawns&=pawn;
				pawn = -pawn;
				pawn--;

				if(pow(2,23)>=pawn && pawn >=pow(2,16))
				{

				pawn <<= 8;
				
					newboard.enpassant = pawn;
				}
				mov[mcounter++] = newboard;
				
			}		
			black_pieces = -black_pieces;
			black_pieces--;
			white_pieces = -white_pieces;
			white_pieces--;	
		}
		newboard.white_pawns = b.white_pawns;
		newboard.enpassant = b.enpassant;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
	}
	
	black_pieces = -black_pieces;
	black_pieces--;

	//para diagonal esquerda
	aux = b.white_pawns;
	aux&=9187201950435737471;
	aux <<= 9;
	aux &=white_pieces;
	aux &=black_pieces;
	newboard.white_pawns = b.white_pawns;

	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.white_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.black_pawns&=pawn;		
		newboard.black_bishops&=pawn;
		newboard.black_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=9;
		pawn = -pawn;
		pawn--;
		newboard.white_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;

		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

	//para diagonal direita
	aux = b.white_pawns;
	aux&=-72340172838076674;
	aux <<= 7;
	aux &=white_pieces;
	aux &=black_pieces;
	newboard.white_pawns = b.white_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;
	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.white_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.black_pawns&=pawn;		
		newboard.black_bishops&=pawn;
		newboard.black_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=7;
		pawn = -pawn;
		pawn--;
		newboard.white_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;

		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}


	for(int i =0;i<mcounter;i++)
	{
	print(mov[i].white_pawns);
	printf("\n");
	print(mov[i].enpassant);
	printf("\n");
	
	}


}


int main()

{
movements();

return 0;
}
