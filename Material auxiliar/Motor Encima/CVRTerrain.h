/***********************************************************************
*Nome: CVRTerrain.h
*Descrição: Cabeçalho da classe responsável pela criação de terrenos
*Data: 18/04/07
*Local: LNCC
************************************************************************/
#ifndef _CVRTERRAIN_
#define _CVRTERRAIN_

#include "CVRObject3D.h"

class CVRTerrain: public CVRObject3D
{
private:
	float fScale;
	int iWidth;
	int iDepth;
	unsigned int uiListId;

public:
	CVRTerrain();
	~CVRTerrain();
	void Render();
	void CreateBitmapTerrain(char *, char *, float);
	void CreateRandomTerrain(char *,int, float);
	void LoadTexture(char *);
	void Release();
	void SetTerrainScale(float);
	int GetSize();
	float GetScale();
	void ReleaseTerrain();
	float GetHeight(float, float);
	bool Init();
	void Update();

public:
	float** terrainData;
};
#endif