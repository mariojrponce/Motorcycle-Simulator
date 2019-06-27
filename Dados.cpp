#include "Dados.h"

int Dados::motoSelecao;

Dados::Dados()
{
	motoSelecao = 0;
}
void Dados::SetMoto(int selecao) 
{
	motoSelecao = selecao;
}
int Dados::GetMoto() 
{
	return motoSelecao;
}