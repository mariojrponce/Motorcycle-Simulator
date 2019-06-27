/***********************************************************************
*Nome: CVRObject.h
*Descrição: Cabeçalho da classe responsável pela definicao da classe base da engine
*Data: 20/07/07
*Local: LNCC
************************************************************************/
#ifndef _CVROBJECT_
#define _CVROBJECT_

//Bibliotecas
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glaux.h>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <io.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <dinput.h>
#include <cguid.h>
#include <d3d8types.h>
#include <winsock.h>
#include <stdlib.h>


//define GUIDs do directX
#define INITGUID

#define MSG_NOSIGNAL 0 

//Tamanho das strings no engine
#define STRINGSIZE 100

//Namespace da biblioteca padrão
using namespace std;

class CVRObject
{
public:
	CVRObject();
	virtual ~CVRObject();
	virtual void Release() = 0;
};
#endif;
