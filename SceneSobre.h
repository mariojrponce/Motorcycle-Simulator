/***********************************************************************
*Nome: SceneSobre
*Descrição: Classe criada para apresentar a cena Sobre
*Data: 12/02/19
*Local: FACTO
************************************************************************/
//EVITA QUE ESTA CLASSE SEJA IMPORTADA DUAS VEZES NO MESMO PROJETO
#ifndef _SCENESOBRE_
#define _SCENESOBRE_

//PACOTES UTILIZADOS (IMPORT DO JAVA)
#include "CVRScene.h"
#include "CVRObjLoader.h"

//CLASSE SCENESOBRE QUE ESTENDE DE CVRSCENE(CLASSE PAI)
class SceneSobre: public CVRScene
{
//METODOS E ATRIBUTOS PUBLICOS
public:
	
	SceneSobre();
	~SceneSobre();

	void Release();
	void Execute();
	bool Init();
	void UpdateMouse();

//METODOS E ATRIBUTOS PRIVADOS
private:
	CVRSprite* spr_backgroundSobre;
	CVRSprite* spr_mouse[2];
	float fAngle;
};
#endif
