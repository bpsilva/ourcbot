#include<vector>
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
typedef struct bitboard
{
long long white_pawns, white_rooks, white_bishops, black_pawns, black_rooks, black_bishops, enpassant;
}BOARD;
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
BOARD transtobitboard(string sboard, BOARD board)
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
		board.black_pawns = board.black_pawns | (um<<(63-i));
		break;
	case 'r':
		board.black_rooks = board.black_rooks | (um<<(63-i));
		break;
	case 'b':
		board.black_bishops = board.black_bishops | (um<<(63-i));
		break;
	case 'P':
		board.white_pawns = board.white_pawns | (um<<(63-i));
		break;
	case 'R':
		board.white_rooks = board.white_rooks | (um<<(63-i));
		break;
	case 'B':
		board.white_bishops = board.white_bishops | (um<<(63-i));
		break;	
	}
}
return board;
}


class Board{

public:
	
BOARD getBoard(){return b;}
BOARD setBoard(BOARD board){b = board;}

Board(BOARD board, int wm)
{
	b.black_pawns = board.black_pawns;
	b.black_rooks = board.black_rooks;
	b.black_bishops = board.black_bishops;
	b.white_pawns = board.white_pawns;
	b.white_rooks = board.white_rooks;
	b.white_bishops = board.white_bishops;
	b.enpassant = board.enpassant;
	mcounter = 0;
	who_moves = wm;
}

	
	int mcounter;
//	BOARD mov[150];
	vector<BOARD> mov;	

	BOARD b;
	int who_moves;

		

void movements()
{
	

	long long swap;
	BOARD newboard = {b.white_pawns, b.white_rooks, b.white_bishops, b.black_pawns, b.black_rooks, b.black_bishops, b.enpassant};	

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
	unsigned  long long pawn = 0;
	unsigned long long rook = 0;
	unsigned long long bishop = 0;
	long long superior = 72057594037927935;
	long long inferior = -256;
	long long direita = -72340172838076674;
	long long esquerda = 9187201950435737471;
	int white = 1, black = -1;

if(who_moves == white)
{
// MOVIMENTOS DOS PEÕES
	
//---------------------------------------------PARA FRENTE

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
		mov.push_back(newboard);;
		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
	}
	pawn = aux2&-aux2;
//	cout<<(long long)(pow(2,32)-1)<<endl;
	while(pawn!=0 && (pawn & (long long)4294967295))
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
		mov.push_back(newboard);;
		newboard.white_pawns = b.white_pawns;
		newboard.enpassant = b.enpassant;
		//pawn = menos signigicativo de aux
		pawn = aux2&-aux2;
	}
	
	
	
	black_pieces = -black_pieces;
	black_pieces--;

//-------------------------------------------CAPTURA PARA A ESQUERDA
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
		mov.push_back(newboard);;

		newboard.black_pawns = b.black_pawns;
		newboard.black_rooks = b.black_rooks;
		newboard.black_bishops = b.black_bishops;
		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

//--------------------------------------CAPTURA PARA A DIREITA
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
		mov.push_back(newboard);;
		newboard.black_pawns = b.black_pawns;
		newboard.black_rooks = b.black_rooks;
		newboard.black_bishops = b.black_bishops;
		newboard.white_pawns = b.white_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

//--------------------------------------------EN PASSANT
	//cout<<((long long)(pow(2, 8)-1)<< 32)<<endl;
	//print((long long)1095216660480);
	if((b.enpassant) && ((long long)1095216660480 & b.white_pawns))
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
			mov.push_back(newboard);;			
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
			mov.push_back(newboard);;			
		}
	}


//MOVIMENTOS DAS TORRES

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;


//----------------------------------------TORRE 1: DIREITA

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

	while((rook & direita) && ((rook>>1)& white_pieces) && ((rook>>1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}
//----------------------------------------TORRE 2: DIREITA

	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	rook = aux;

	black_pieces = b.black_pawns | b.black_bishops;
	black_pieces = black_pieces | b.black_rooks;
	black_pieces = -black_pieces;
	black_pieces--;

	while((rook & direita) && ((rook>>1)& white_pieces) && ((rook>>1)& black_pieces))
	{
		cout<<"AQUI"<<endl;
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 1: ESQUERDA
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

	while((rook & esquerda) && ((rook<<1)& white_pieces) && ((rook<<1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: ESQUERDA
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

	while((rook & esquerda) && ((rook<<1)& white_pieces) && ((rook<<1)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}


//----------------------------------------TORRE 1: CIMA
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


while((rook & superior) && ((rook<<8)& white_pieces) && ((rook<<8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: CIMA
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

	while((rook &superior) && ((rook<<8)& white_pieces) && ((rook<<8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 1: BAIXO
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

	while((rook & inferior) && ((rook>>8)& white_pieces) && ((rook>>8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: BAIXO
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

	while((rook &inferior) && ((rook>>8)& white_pieces) && ((rook>>8)& black_pieces))
	{
		
		rook = -rook; rook--;
		newboard.white_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.white_rooks|=rook;
		mov.push_back(newboard);;
		
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
		mov.push_back(newboard);;		
	}


//MOVIMENTOS BISPOS
//----------------------------------------BISPO 1: CIMA-DIREITA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	aux = newboard.white_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & direita & superior) && ((bishop<<7)& white_pieces) && ((bishop<<7)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & direita & superior )&& !((bishop<<7)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 2: CIMA-DIREITA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & superior & direita) && ((bishop<<7)& white_pieces) && ((bishop<<7)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & superior & direita)&& !((bishop<<7)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 1: CIMA-ESQUERDA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	aux = newboard.white_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & esquerda & superior) && ((bishop<<9)& white_pieces) && ((bishop<<9)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & esquerda & superior )&& !((bishop<<9)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 2: CIMA-ESQUERDA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & superior & esquerda) && ((bishop<<9)& white_pieces) && ((bishop<<9)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & superior & esquerda)&& !((bishop<<9)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}

//--------------------------------------------BISPO 1: BAIXO-DIREITA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	aux = newboard.white_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;


	while((bishop & direita & inferior) && ((bishop>>9)& white_pieces) && ((bishop>>9)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & direita & inferior )&& !((bishop>>9)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//--------------------------------------------BISPO 2: BAIXO-DIREITA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & inferior & direita) && ((bishop>>9)& white_pieces) && ((bishop>>9)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & inferior & direita)&& !((bishop>>9)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}
//--------------------------------------------BISPO 1: BAIXO-ESQUERDA	
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	aux = newboard.white_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & esquerda & inferior) && ((bishop>>7)& white_pieces) && ((bishop>>7)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & esquerda & inferior )&& !((bishop>>7)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//--------------------------------------------BISPO 2: BAIXO-ESQUERDA
	newboard.white_pawns = b.white_pawns;
	newboard.black_pawns = b.black_pawns;
	newboard.white_rooks = b.white_rooks;
	newboard.black_rooks = b.black_rooks;
	newboard.white_bishops = b.white_bishops;
	newboard.black_bishops = b.black_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & inferior & esquerda) && ((bishop>>7)& white_pieces) && ((bishop>>7)& black_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.white_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & inferior & esquerda)&& !((bishop>>7)& black_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.white_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.white_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.black_pawns&=bishop;
		newboard.black_bishops&=bishop;
		newboard.black_bishops&=bishop;
		mov.push_back(newboard);;		
	}	
}else//----------------------------------------------------------------------------BLACK MOVES
{

// MOVIMENTOS DOS PEÕES
	
//---------------------------------------------PARA FRENTE

	aux = b.black_pawns;
	aux >>= 8;
	aux &=black_pieces;
	aux &=white_pieces;
	aux2 = aux;
	aux2>>=8;
	aux2 &=black_pieces;
	aux2 &=white_pieces;
	newboard.black_pawns = b.black_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

	while(pawn!=0)
	{

		//adiciona pawn em newboard.pawns
		newboard.black_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;		
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn<<=8;
		pawn = -pawn;
		pawn--;
		newboard.black_pawns&=pawn;

		newboard.enpassant = 0;
		mov.push_back(newboard);;
		newboard.black_pawns = b.black_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
	}

	pawn = aux2&-aux2;
	while(pawn!=0 )
	{
		
		if(pawn & (long long)1095216660480)
		{
		//adiciona pawn em newboard.pawns
		newboard.black_pawns|=pawn;
		newboard.enpassant = pawn;
		//apaga pawn de aux
		pawn = -pawn;
		pawn--;
		aux2 &=pawn;		
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn<<=16;
		pawn = -pawn;
		pawn--;
		newboard.black_pawns&=pawn;
		mov.push_back(newboard);;
		newboard.black_pawns = b.black_pawns;
		newboard.enpassant = b.enpassant;
		}
		else{
			//apaga pawn de aux
			pawn = -pawn;
			pawn--;
			aux2 &=pawn;		

			}
		//pawn = menos signigicativo de aux
		pawn = aux2&-aux2;
	}
	
	
	
	white_pieces = -white_pieces;
	white_pieces--;

//-------------------------------------------CAPTURA PARA A direita
	aux = b.black_pawns;
	aux&=direita;
	aux >>= 7;
	aux &=black_pieces;
	aux &=white_pieces;
	newboard.black_pawns = b.black_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

	while(pawn!=0)
	{
		//adiciona pawn em newboard.pawns
		newboard.black_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.white_pawns&=pawn;		
		newboard.white_bishops&=pawn;
		newboard.white_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn<<=7;
		pawn = -pawn;
		pawn--;
		newboard.black_pawns&=pawn;
		newboard.enpassant = 0;
		mov.push_back(newboard);;
		newboard.white_pawns = b.white_pawns;
		newboard.white_rooks = b.white_rooks;
		newboard.white_bishops = b.white_bishops;
		newboard.black_pawns = b.black_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

//--------------------------------------CAPTURA PARA A esquerda
	aux = b.black_pawns;
	aux&=esquerda;
	aux >>= 7;
	aux &=black_pieces;
	aux &=white_pieces;
	newboard.black_pawns = b.black_pawns;
	//pawn = menos signigicativo de aux
	pawn = aux&-aux;

	while(pawn!=0)
	{

		//adiciona pawn em newboard.pawns
		newboard.black_pawns|=pawn;
		//apaga pawn de aux e elimina peças do oponente
		pawn = -pawn;
		pawn--;
		aux &=pawn;
		newboard.white_pawns&=pawn;		
		newboard.white_bishops&=pawn;
		newboard.white_rooks&=pawn;
		pawn = -pawn;
		pawn--;
		//remover pawn da posição original em newboard.pawns
		pawn<<=7;
		pawn = -pawn;
		pawn--;
		newboard.black_pawns&=pawn;
		newboard.enpassant = 0;
		mov.push_back(newboard);;

		newboard.white_pawns = b.white_pawns;
		newboard.white_rooks = b.white_rooks;
		newboard.white_bishops = b.white_bishops;
		newboard.black_pawns = b.black_pawns;
		//pawn = menos signigicativo de aux
		pawn = aux&-aux;
		
	}

//--------------------------------------------EN PASSANT
	//print((long long)(pow(2, 8)-1)<< 24);
	//cout<<((long long)(pow(2, 8)-1))<< 24<<endl;

	if((b.enpassant) && ((long long)25524 & b.black_pawns))
	{
	newboard.black_pawns = b.black_pawns;
	aux = b.enpassant;
		
		if(((newboard.black_pawns & esquerda) << 1) & aux)
		{
			
			newboard.black_pawns |= (aux>>8);

			aux>>=1;
			aux = - aux;
			aux--;
			newboard.black_pawns &= aux;
			aux = - aux;
			aux--;			
			aux<<=1;
			aux = - aux;
			aux--;

			newboard.white_pawns &=aux;
			newboard.enpassant = 0;
			mov.push_back(newboard);;			
		}	

	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	aux = b.enpassant;

		if(((newboard.black_pawns & direita) >> 1) & aux)
		{
			
			newboard.black_pawns |= (aux>>8);
			aux<<=1;
			aux = - aux;
			aux--;
			newboard.black_pawns &= aux;
			aux = - aux;
			aux--;			
			aux>>=1;
			aux = - aux;
			aux--;
			newboard.white_pawns &=aux;
			newboard.enpassant = 0;
			mov.push_back(newboard);;			
		}
	}


//MOVIMENTOS DAS TORRES

	white_pieces = b.white_pawns | b.white_bishops;
	white_pieces = white_pieces | b.white_rooks;
	white_pieces = -white_pieces;
	white_pieces--;


//----------------------------------------TORRE 1: esquerda

	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;


	aux = newboard.black_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	while((rook & esquerda) && ((rook<<1)& black_pieces) && ((rook<<1)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}

	if((rook & esquerda)&& !((rook<<1)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}
//----------------------------------------TORRE 2: esquerda

	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	white_pieces = b.white_pawns | b.white_bishops;
	white_pieces = white_pieces | b.white_rooks;
	white_pieces = -white_pieces;
	white_pieces--;

	while((rook & esquerda) && ((rook<<1)& black_pieces) && ((rook<<1)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & esquerda)&& !((rook<<1)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=1;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 1: direita
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;


	aux = newboard.black_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	while((rook & direita) && ((rook>>1)& black_pieces) && ((rook>>1)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & direita)&& !((rook>>1)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: direita
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;




	while((rook&direita) && ((long long)(rook>>1)& black_pieces) && ((long long)(rook>>1)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}

	if((rook & direita)&& !((rook>>1)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=1;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}


//----------------------------------------TORRE 1: CIMA
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	aux = newboard.black_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;


while((rook & inferior) && ((rook>>8)& black_pieces) && ((rook>>8)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & inferior)&& !((rook>>8)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: CIMA
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	while((rook &inferior) && ((rook>>8)& black_pieces) && ((rook>>8)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & inferior)&& !((rook>>8)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook>>=8;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 1: BAIXO
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	aux = newboard.black_rooks;
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	while((rook & superior) && ((rook<<8)& black_pieces) && ((rook<<8)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & superior)&& !((rook<<8)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}

//----------------------------------------TORRE 2: BAIXO
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;
	
	rook = aux&-aux;
	rook = -rook; rook--;
	aux&=rook;
	rook = -rook; rook--;

	while((rook &superior) && ((rook<<8)& black_pieces) && ((rook<<8)& white_pieces))
	{
		
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.black_rooks|=rook;
		mov.push_back(newboard);;
		
	}
	if((rook & superior)&& !((rook<<8)& white_pieces))
	{
		rook = -rook; rook--;
		newboard.black_rooks &=rook;		
		rook = -rook; rook--;
		rook<<=8;
		newboard.black_rooks|=rook;
		rook = -rook; rook--;
		newboard.white_pawns&=rook;
		newboard.white_rooks&=rook;
		newboard.white_bishops&=rook;
		mov.push_back(newboard);;		
	}


//MOVIMENTOS BISPOS
//----------------------------------------BISPO 1: CIMA-esquerda
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	aux = newboard.black_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & esquerda & inferior) && ((bishop>>7)& black_pieces) && ((bishop>>7)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & esquerda & inferior )&& !((bishop>>7)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 2: CIMA-esquerda
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & inferior & esquerda) && ((bishop>>7)& black_pieces) && ((bishop>>7)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & inferior & esquerda)&& !((bishop>>7)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=7;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 1: CIMA-direita
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	aux = newboard.black_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & esquerda & inferior) && ((bishop>>9)& black_pieces) && ((bishop>>9)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & esquerda & inferior )&& !((bishop>>9)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//----------------------------------------BISPO 2: CIMA-direita
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;
	cout<<"AQUI"<<endl;
	while((bishop & inferior & direita) && ((bishop>>9)& black_pieces) && ((bishop>>9)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & inferior & direita)&& !((bishop>>9)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop>>=9;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}

//--------------------------------------------BISPO 1: BAIXO-esquerda
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	aux = newboard.black_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;


	while((bishop & esquerda & superior) && ((bishop<<9)& black_pieces) && ((bishop<<9)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & esquerda & superior )&& !((bishop<<9)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//--------------------------------------------BISPO 2: BAIXO-esquerda
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & superior & esquerda) && ((bishop<<9)& black_pieces) && ((bishop<<9)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & superior & esquerda)&& !((bishop<<9)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=9;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}
//--------------------------------------------BISPO 1: BAIXO-direita	
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	aux = newboard.black_bishops;
	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & direita & superior) && ((bishop<<7)& black_pieces) && ((bishop<<7)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & direita & superior )&& !((bishop<<7)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}


//--------------------------------------------BISPO 2: BAIXO-direita
	newboard.black_pawns = b.black_pawns;
	newboard.white_pawns = b.white_pawns;
	newboard.black_rooks = b.black_rooks;
	newboard.white_rooks = b.white_rooks;
	newboard.black_bishops = b.black_bishops;
	newboard.white_bishops = b.white_bishops;
	newboard.enpassant = 0;

	bishop = aux&-aux;
	bishop = -bishop; bishop--;
	aux&=bishop;
	bishop = -bishop; bishop--;

	while((bishop & superior & direita) && ((bishop<<7)& black_pieces) && ((bishop<<7)& white_pieces))
	{
		
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.black_bishops|=bishop;
		mov.push_back(newboard);;
		
	}
	if((bishop & superior & direita)&& !((bishop<<7)& white_pieces))
	{
		bishop = -bishop; bishop--;
		newboard.black_bishops &=bishop;		
		bishop = -bishop; bishop--;
		bishop<<=7;
		newboard.black_bishops|=bishop;
		bishop = -bishop; bishop--;
		newboard.white_pawns&=bishop;
		newboard.white_bishops&=bishop;
		newboard.white_bishops&=bishop;
		mov.push_back(newboard);;		
	}

}

}

};

int main()
{
string a ("r.b..b.rppp.pppp...p.............................PPPPPPPR.B..B.R");


BOARD b = transtobitboard(a, b);

Board *board = new Board(b, 1);

//print(board.getBoard().white_bishops);

(*board).movements();

for(int i = 0; i<(*board).mov.size();i++)
{
	cout<<"JOGADA "<<i<<endl;
	print((*board).mov[i].white_rooks);
	cout<<endl;
}

return 0;
}

