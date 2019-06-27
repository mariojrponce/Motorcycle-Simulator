/***********************************************************************
*Nome: SceneGame
*Descrição: Classe criada para implementar o mundo virtual da simulação
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#ifndef _SCENEGAME_
#define _SCENEGAME_

#include "CVRScene.h"
#include "CVRObjLoader.h"




class SceneGame: public CVRScene
{
public:
	SceneGame();
	~SceneGame();
	void Release();
	void Execute();
	bool Init();
	void Render();
	void SetMotoModel(int);
	void MovimentaSprite(CVRSprite*);
	void MovimentaMoto();
	void DrawBoundingSphere(CVRVector vPos, CVRVector vScale, float fRadius);
	bool TestCollision();
	void MudaLedTest();
	void PainelMarchas();

	//Essa desgraça vai resolver nosso maldito problema
	int motoSelecao;
	
	
	
private:
	float fAngle;
	CVRObjLoader* spr_Motorcycle;
	CVRObjLoader* spr_Cidade;
	CVRFont* posicao;
	CVRFont* posicaoMoto;
	CVRLoadingBar* barraCarregamento;
	CVRSprite* spriteMarchas;
	CVRSprite* spriteVelocimetro;
	CVRSprite* spriteAgulhaVelo;
	CVRSprite* spriteGiros;
	CVRSprite* spriteAgulhaGiros;
	CVRSprite* spriteLedsVermelhoOn;
	CVRSprite* spriteLedsVermelho;
	CVRSprite* spriteCombustivel;
	CVRSprite* spriteAgulhaCombu;
	CVRSprite* spriteIconeCombu;
	CVRSprite* spriteSetaEsq;
	CVRSprite* spriteSetaDir;
	CVRSprite* spriteFarolAlto;
	CVRSprite* spriteFarolBaixo;
	CVRSprite* spriteIconeBateria;
	CVRSprite* spritePainelDigital;
	CVRListener* listener;
	CVRSound* sound;
};
#endif