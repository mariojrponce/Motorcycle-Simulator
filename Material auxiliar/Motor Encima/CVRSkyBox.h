/***********************************************************************
*Nome: CVRSkyBox.h
*Descrição: Cabeçalho da classe que implementa o sky box
*Data: 21/05/07
*Local: LNCC
************************************************************************/
#ifndef _CVRSKYBOX_
#define _CVRSKYBOX_

#include "CVRObject3D.h"

#define FRONT	 0
#define BACK	 1
#define LEFT	 2
#define RIGHT	 3
#define UP		 4
#define DOWN     5

#define GL_CLAMP_TO_EDGE	0x812F

class CVRSkyBox: public CVRObject3D
{
private:
	float fWidth, fHeight, fDepth;
	float fFloor;
	unsigned int texIds[6];
	bool bDrawGround;

public:
	
	CVRSkyBox();
	CVRSkyBox(float, float, float, float, float, float);
	~CVRSkyBox();

	void SetBoxSize(float, float, float);
	
	float GetCenterX();
	float GetCenterY();
	float GetCenterZ();
	
	void SetCenterBox(float, float, float);
	void SetCenterX(float);
	void SetCenterY(float);
	void SetCenterZ(float);
	
	void SetFrontTexture(char*);
	void SetBackTexture(char*);
	void SetUpTexture(char*);
	void SetLeftTexture(char*);
	void SetRightTexture(char*);
	void SetDownTexture(char*);
	void SetAllTextures(char*);
	void SetFloorHeight(float);
	void LoadTexture(char*, int);
	void SetDrawGround(bool);
	bool GetDrawGround();
	void Update();
	
	bool Init();
	void Render();
	void Release();
};
#endif