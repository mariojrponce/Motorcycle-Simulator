/***********************************************************************
*Nome: SceneAjuda
*Descrição: Classe criada para apresentar a cena Ajuda
*Data: 06/03/19
*Local: PALMAS-TO
************************************************************************/
//EVITA QUE ESTA CLASSE SEJA IMPORTADA DUAS VEZES NO MESMO PROJETO
#ifndef _SCENEAJUDA_
#define _SCENEAJUDA_

//PACOTES UTILIZADOS (IMPORT DO JAVA)
#include "CVRScene.h"

#define QTDBUTTONS 1

//CLASSE SCENESOBRE QUE ESTENDE DE CVRSCENE(CLASSE PAI)
class SceneAjuda: public CVRScene
{
//METODOS E ATRIBUTOS PUBLICOS
public:
	SceneAjuda();
	~SceneAjuda();
	void Release();
	void Execute();
	bool Init();
	void UpdateMouse();

//METODOS E ATRIBUTOS PRIVADOS
private:
	CVRSprite* spr_backgroundAjuda;
	CVRSprite* spr_menuVoltar;
	CVRSprite* spr_mouse[2];
	float fAngle;

};
#endif