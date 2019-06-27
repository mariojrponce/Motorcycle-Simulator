//Arquivos de cabeçalho
#include "CVRManager.h"
#include "SceneLogo.h"
#include "SceneMenu.h" 
#include "SceneAjuda.h"
#include "SceneConfig.h" 
#include "SceneSobre.h"
#include "SceneGame.h"
#include <wiiuse.h>

//Função principal do programa
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Cria um objeto do gerenciador
	CVRManager manager;

	//Cria um objeto da cena
	SceneLogo sceneLogo;
	SceneMenu sceneMenu;
	SceneGame sceneGame;
	SceneConfig sceneConfig;
	SceneAjuda sceneAjuda;
	SceneSobre sceneSobre;

	//Ponteiro
	sceneConfig.vrMotoSelecao = &sceneGame.motoSelecao;
	

	//Configurando a janela
	manager.cMainWindow.SetTitle("MOTORCYCLE");
	manager.cMainWindow.SetResolution(1024,768,32); 
	manager.cMainWindow.SetFullScreen(true);
	manager.cMainWindow.SetBackground(0,0,0);
	manager.cMainWindow.SetPosition(150,80);
	manager.cMainWindow.Show();

	//Adiciona uma cena a lista de cenas
	manager.AddNewScene(&sceneLogo);
	manager.AddNewScene(&sceneMenu);
	manager.AddNewScene(&sceneGame);
	manager.AddNewScene(&sceneConfig);
	manager.AddNewScene(&sceneAjuda);
	manager.AddNewScene(&sceneSobre);
	

	//Iniciando o programa
	manager.Loop();
	
	return 1;
}