/***********************************************************************
*Nome: CVRView.h
*Descri��o: Cabe�alho da classe respons�vel pela movimenta��o da camera
*Data: 08/02/07
*Local: LNCC
************************************************************************/
#ifndef _CVRVIEW_
#define _CVRVIEW_

//Bibliotecas
#include "CVRVector.h"
#include "CVRObject.h"

//Declara uma referencia para o Manager
class CVRManager;


class CVRView: public CVRObject
{
private:
	//Vetores responsaveis pelo posicionamento da camera
	CVRVector vPosition;
	CVRVector vLookAt;
	CVRVector vUp;
	CVRVector vDirection;

	//Variaveis que guardam os angulos e a velocidade da camera
	float fAngleY;
	float fAngleX;
	float fAngleZ;
	float fSpeed;
public:
	//Cria uma refer�ncia para o Manager
	CVRManager* pManager;
	
	//M�todos da c�mera
	CVRView();
	~CVRView();
	void SetView(float, float, float, float, float, float, float, float, float);
	void SetPosition(float, float, float);
	void SetPositionX(float);
	void SetPositionY(float);
	void SetPositionZ(float);
	void SetSpeed(float);
	void UpdateView();
	void RotY(float);
	void RotX(float);
	void RotZ(float);
	float GetAngleY();
	float GetAngleX();
	float GetAngleZ();
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	CVRVector GetPosition();
	float GetSpeed();
	void Move(float);//para mover a camera
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveTo(float);
	void Release();
	CVRVector GetDirection();
};

#endif;
