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
//zerar coluna 0 (esquerda) do tabuleiro : board &= esquerdall
//zerar coluna 7 (direita) do tabuleiro : board &= -72340172838076674

unsigned long long movements()
{
	///para teste--------
	BOARD b = {0, pow(2,15)+pow(2,11), 0, 0, pow(2,9), 0, 0};
	
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
	long long rook = 0;
	long long bishop = 0;
	long long superior = 72057594037927935;
	long long inferior = -256;
	long long direita = -72340172838076674;
	long long esquerda = 9187201950435737471;

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
	aux&=esquerda;
	aux <<= 9;
	aux &=white_pieces;//+
	aux &=black_pieces;//+
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
	aux&=direita;
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

	//en passant
	if((b.enpassant) && ((long long)(pow(2, 8)-1)<< 32) & b.white_pawns)
	{
	newboard.white_pawns = b.white_pawns;
	aux = b.enpassant;
		
		if(((newboard.white_pawns & direita) >> 1) & aux)
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

		if(((newboard.white_pawns & esquerda) << 1) & aux)
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
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;


	aux = newboard.white_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;
	
	//torre 1 move direita
	while((rook & direita) && ((rook>>1)& white_pieces) && ((rook>>1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & direita)&& !((rook>>1)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;
	


	//torre 2 move direita
	while((rook & direita) && ((rook>>1)& white_pieces) && ((rook>>1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & direita)&& !((rook>>1)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;


	aux = newboard.white_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;
	
	//torre 1 move esquerda
	while((rook & esquerda) && ((rook<<1)& white_pieces) && ((rook<<1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & esquerda)&& !((rook<<1)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;
	


	//torre 2 move direita
	while((rook & esquerda) && ((rook<<1)& white_pieces) && ((rook<<1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & esquerda)&& !((rook<<1)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	aux = newboard.white_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

		//torre 1 move cima

while((rook & superior) && ((rook<<8)& white_pieces) && ((rook<<8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & superior)&& !((rook<<8)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;


	


	//torre 2 move cima
	while((rook &superior) && ((rook<<8)& white_pieces) && ((rook<<8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & superior)&& !((rook<<8)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	aux = newboard.white_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	//torre 1 move baixo

	while((rook & inferior) && ((rook>>8)& white_pieces) && ((rook>>8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & inferior)&& !((rook>>8)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;


	


	//torre 2 move baixo
	while((rook &inferior) && ((rook>>8)& white_pieces) && ((rook>>8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		mov[mcounter++] = newboard;
		
	}
	if((rook & inferior)&& !((rook>>8)& black_pieces))
	{
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		rook = -rook; rook--;
		newboard.black_pawns&=rook;
		newboard.black_rooks&=rook;
		newboard.black_bishops&=rook;
		mov[mcounter++] = newboard;		
	}
	
		

	cout<<"ESTADO INICIAL:"<<endl;
	cout<<"WHITE rooks"<<endl;
	print(b.white_rooks);

	for(int i =0;i<mcounter;i++)
	{
	cout<<"MOVIMENTO "<<i<<":"<<endl;
	cout<<"WHITE rooks"<<endl;
	print(mov[i].white_rooks);
	cout<<"BLACK rooks"<<endl;
	print(mov[i].black_rooks);
	printf("\n");
	}


}


int main()

{
movements();

return 0;
}
