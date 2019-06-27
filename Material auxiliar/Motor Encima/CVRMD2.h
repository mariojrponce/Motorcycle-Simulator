/***********************************************************************
*Nome: CVRMd2.h
*Descrição: Cabeçalho da classe que implementa o modelo MD2
*Data: 25/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRMD2_
#define _CVRMD2_

#include "CVRObject3D.h"
#include "CVRTimer.h"

//Estrutura para o cabeçalho do MD2
struct SMD2HEADER
{
	int iMd2Id;
	int iVersion;
	int iWidth;
	int iHeight;
	int iFrameSize;
	int iNumSkins;
	int iNumVertices;
	int iNumTexCoods;
	int iNumTriangles;
	int iNumGlCommands;
	int iNumFrames;
	int iOffsetSkins;
	int iOffsetTexCoords;
	int iOffsetTriangles;
	int iOffsetFrames;
	int iOffsetGlCommands;
	int iFileSize;
};

//Estrutura de vértices para o MD2
struct SMD2VERTEX
{
	float fVertex[3];
	unsigned char ucReserved;
};

//Estrutura do Frame do MD2
struct SMD2FRAME
{
	float fScale[3];
	float fTranslation[3];
	char cFrameName[16];
	SMD2VERTEX *vertexList;

	//Construtor e destrutor
	SMD2FRAME()
	{
		vertexList = NULL;
	}

	~SMD2FRAME()
	{
		if(vertexList)
		{
			delete[] vertexList;
		}
	}
};

//Estrutura que representa um triangulo
struct SMD2TRIANGLE
{
	unsigned short vertex[3];
	unsigned short texture[3];
};

//Estrutura que representa as coordenadas de textura
struct SMD2TEXCOORD
{
	float texCoord[2];
};

class CVRMd2: public CVRObject3D
{
public:
	CVRMd2();
	CVRMd2(char *);
	~CVRMd2();
	bool Load(char*);
	void Render();
	void RenderFrame(int);
	void Release();
	void SetAnimSpeed(float);
	bool Init();
	void SetAnimFrames(unsigned int, unsigned int);
	bool LoadTexture(char *);
	unsigned int uiMSPerFrame;	
	float fLastInterp;
	CVRTimer timer;
	void Update();
	bool AnimationEnded();
	void SetRepeat(bool);

private:
	SMD2HEADER header;

	SMD2FRAME *frames;

	SMD2TRIANGLE *triangles;

	SMD2TEXCOORD *texCoordinates;

	SMD2VERTEX *verts;

	float fSpeed;

	unsigned int uiStartFrame;

	unsigned int uiEndFrame;

	unsigned int uiCurrentFrame;

	bool bRepeat;
};
#endif