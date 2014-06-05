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
	///para teste--------
	BOARD b = {pow(2,8)-1, 0, 0, (pow(2,8)-1), 0, 0};
	b.his_pawns<<=8;
	///------------------


	BOARD newboard = {b.my_pawns, b.my_rooks, b.my_bishops, b.his_pawns, b.his_rooks, b.his_bishops};	
	BOARD mov[100];
	int mcounter = 0;

	long long my_pieces = b.my_pawns | b.my_bishops;
	my_pieces = my_pieces | b.my_rooks;
	my_pieces = -my_pieces;
	my_pieces--;

	long long his_pieces = b.his_pawns | b.his_bishops;
	his_pieces = his_pieces | b.his_rooks;
	his_pieces = -his_pieces;
	his_pieces--;

	long long aux = 0;
	long long pawn = 1;

// my pawns' movements
	
	//para frente
	aux = b.my_pawns;
	aux <<= 8;
	aux &=my_pieces;
	aux &=his_pieces;
	newboard.my_pawns = b.my_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.my_pawns|=pawn;
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
		newboard.my_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;

		newboard.my_pawns = b.my_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}
	
	his_pieces = -his_pieces;
	his_pieces--;

	//para diagonal esquerda
	aux = b.my_pawns;
	aux&=9187201950435737471;
	aux <<= 9;
	aux &=my_pieces;
	aux &=his_pieces;
	newboard.my_pawns = b.my_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;
	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.my_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.his_pawns&=pawn;		
		newboard.his_bishops&=pawn;
		newboard.his_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=9;
		pawn = -pawn;
		pawn--;
		newboard.my_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;

		newboard.my_pawns = b.my_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

	//para diagonal direita
	aux = b.my_pawns;
	aux&=-72340172838076674;
	aux <<= 7;
	aux &=my_pieces;
	aux &=his_pieces;
	newboard.my_pawns = b.my_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;
	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.my_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.his_pawns&=pawn;		
		newboard.his_bishops&=pawn;
		newboard.his_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=7;
		pawn = -pawn;
		pawn--;
		newboard.my_pawns&=pawn;
		pawn = -pawn;
		pawn--;
		mov[mcounter++] = newboard;

		newboard.my_pawns = b.my_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}


	for(int i =0;i<mcounter;i++)
	{
	print(mov[i].my_pawns);
	printf("\n");
	
	}


}


int main()

{
movements();
return 0;
}
