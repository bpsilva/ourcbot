#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

using namespace std;


typedef struct bitboard
{
long long white_pawns, white_rooks, white_bishops, black_pawns, black_rooks, black_bishops, enpassant;
}BOARD;

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
	BOARD b = {1, 0, 0, 1, 0, 0, 0};
	long long um = 1;
	b.white_pawns<<=36;
	b.white_pawns|= um <<15;		
	b.white_pawns|= um <<38;
	b.white_pawns|= um <<41;
	b.white_pawns|= um <<42;
	
	b.black_pawns<<=37;
	//b.black_pawns|= um <<49;
	b.black_pawns|= um <<50;
	b.black_pawns|= um <<51;
	b.black_pawns|= um <<52;
	b.black_pawns|= um <<54;
	b.black_pawns|= um <<55;
	b.enpassant|= um <<37;
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
	long long aux2 = 0;	
	long long pawn = 0;

// white pawns' movements
	
	//para frente
	aux = b.white_pawns;
	aux <<= 8;
	aux &=white_pieces;
	aux &=black_pieces;
	aux2 = aux;
	aux2<<=8;
	aux2 &=white_pieces;
	aux2 &=black_pieces;
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

		newboard.enpassant = 0;
		mov[mcounter++] = newboard;
		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
	}
	pawn = aux2&-aux2;
	while(pawn!=0 && pawn <= pow(2,31))
	{
		//adiciona pawn em newboard.pawns
		newboard.white_pawns|=pawn;
		newboard.enpassant = pawn;
		//apaga pawn de aux
		pawn = -pawn;
		pawn--;
		aux2 &=pawn;		
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn>>=16;
		pawn = -pawn;
		pawn--;
		newboard.white_pawns&=pawn;
		mov[mcounter++] = newboard;
		newboard.white_pawns = b.white_pawns;
		newboard.enpassant = b.enpassant;
		//pawn = menos signigicativo de aux
		pawn = aux2&-aux2;
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
	newboard.black_pawns = b.black_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.black_bishops = b.black_bishops;

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

		newboard.enpassant = 0;
		mov[mcounter++] = newboard;

		newboard.black_pawns = b.black_pawns;
		newboard.black_rooks = b.black_rooks;
		newboard.black_bishops = b.black_bishops;
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
		newboard.enpassant = 0;
		mov[mcounter++] = newboard;

		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}


	if((b.enpassant) && ((long long)(pow(2, 8)-1)<< 32) & b.white_pawns)
	{
	newboard.white_pawns = b.white_pawns;
	aux = b.enpassant;
		
		if(((newboard.white_pawns & -72340172838076674) >> 1) & aux)
		{
			
			newboard.white_pawns |= (aux<<8);

			aux<<=1;
			aux = - aux;
			aux--;
			newboard.white_pawns &= aux;
			aux = - aux;
			aux--;			
			aux>>=1;
			aux = - aux;
			aux--;

			newboard.black_pawns &=aux;
			newboard.enpassant = 0;
			mov[mcounter++] = newboard;			
		}	

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	aux = b.enpassant;

		if(((newboard.white_pawns & 9187201950435737471) << 1) & aux)
		{
			
			newboard.white_pawns |= (aux<<8);
			aux>>=1;
			aux = - aux;
			aux--;
			newboard.white_pawns &= aux;
			aux = - aux;
			aux--;			
			aux<<=1;
			aux = - aux;
			aux--;
			newboard.black_pawns &=aux;
			newboard.enpassant = 0;
			mov[mcounter++] = newboard;			
		}
	}
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;


	cout<<"ESTADO INICIAL:"<<endl;
	cout<<"WHITE PAWNS"<<endl;
	print(b.white_pawns);
	cout<<"BLACK PAWNS"<<endl;
	print(b.white_pawns);
	for(int i =0;i<mcounter;i++)
	{
	cout<<"MOVIMENTO "<<i<<":"<<endl;
	cout<<"WHITE PAWNS"<<endl;
	print(mov[i].white_pawns);
	printf("\n");
	cout<<"BLACK PAWNS"<<endl;
	print(mov[i].black_pawns);
	cout<<"ENPASSANT"<<endl;
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
