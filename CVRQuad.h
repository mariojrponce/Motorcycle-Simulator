/***********************************************************************
*Nome: CVRQuad.h
*Descrição: Cabeçalho da classe responsável pela representação de um frame na animação
*Data: 11/01/08
*Local: LNCC
************************************************************************/
#ifndef _CVRQUAD_
#define _CVRQUAD_

//Bibliotecas
#include "CVRObject.h"

class CVRQuad: public CVRObject
{
//Variaveis publicas
public:
	float fLeft, fRight, fTop, fBottom;

//Metodos publicos
	public:
	CVRQuad();
	CVRQuad(float, float, float, float);
	~CVRQuad();
	void Release();
	bool IsValid();
	float GetHeight();
	float GetWidth();
	bool Collide(CVRQuad&);
};
#endif