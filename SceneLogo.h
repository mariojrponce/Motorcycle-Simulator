/***********************************************************************
*Nome: SceneLogo
*Descrição: Classe criada para apresentar o LOGO da Unitins
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
//EVITA QUE ESTA CLASSE SEJA IMPORTADA DUAS VEZES NO MESMO PROJETO
#ifndef _SCENELOGO_
#define _SCENELOGO_

//PACOTES UTILIZADOS (IMPORT DO JAVA)
#include "CVRScene.h"

//CLASSE SCENELOGO QUE ESTENDE DE CVRSCENE(CLASSE PAI)
class SceneLogo: public CVRScene
{
//METODOS E ATRIBUTOS PUBLICOS
public:
	
	SceneLogo();
	~SceneLogo();
	void Release();
	void Execute();
	bool Init();

//METODOS E ATRIBUTOS PRIVADOS
private:
	CVRSprite* sprCatolicaLogo;
	int iFadeState;
};
#endif