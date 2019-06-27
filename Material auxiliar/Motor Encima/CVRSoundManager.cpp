/***********************************************************************
*Nome: CVRSoundManager.cpp
*Descrição: Implementação da classe responsável pelo gerenciamento dos sons
*Data: 28/09/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRSoundManager.h"

/***********************************************************
*Name: CVRSoundManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSoundManager::CVRSoundManager()
{
	bIsMusicLoad = false; 
} 

/***********************************************************
*Name: ~CVRSoundManager()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSoundManager::~CVRSoundManager()
{
	 
} 

/***********************************************************
*Name: Initialize()
*Description: chama o método que inicializa a interface da
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSoundManager::Init()
{	 
	CVRSound::Init();
	listener.soundManager = this;
	return true;
}

/***********************************************************
*Name: Initialize()
*Description: Limpa as interfaces da classe CVRSound e fecha a COM
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSoundManager::Release()
{
	if (CVRSound::DSperformance)
	{
		CVRSound::DSperformance->Stop(NULL,NULL,0,0);
	}

	if(bIsMusicLoad == true)
	     music.Release();
	
	
	if (listener.GetListener())
	{
		listener.GetListener()->Release();
		listener.SetNULL();
	}

	for(int iIndex = (int)sounds.size()-1; iIndex>=0; iIndex--)
	{
		sounds[iIndex]->Release();
		sounds[iIndex]->SetNULL();
	}

	if(CVRSound::DSloader != NULL)
	{
	    CVRSound::DSloader->Release();
    	CVRSound::DSloader= NULL;
	}
	else
		return;

	if(CVRSound::DSperformance != NULL)
	{
      	CVRSound::DSperformance->CloseDown();
	    CVRSound::DSperformance->Release();
    	CVRSound::DSperformance = NULL;
	}
	else
		return;
	
	//fecha a COM
	CoUninitialize();
}

/***********************************************************
*Name: Remove()
*Description: remove um som do vetor de sons
*Params: Sound*
*Return: bool
************************************************************/
bool CVRSoundManager::Remove(CVRSound* p)
{
	for(int iIndex = (int)sounds.size()-1; iIndex >=0; iIndex--)
	{
		if(sounds[iIndex] == p)
		{
			    p->StopSound();
			    sounds[iIndex]->Release();
				sounds[iIndex]->SetNULL();
				delete sounds[iIndex];
				p= NULL;
				sounds.erase(sounds.begin()+iIndex);
				return true;
		}
	}
	//objeto de som não encontrado
	return false;
}

/***********************************************************
*Name: LoadSound()
*Description: carrega um som 3D para o vetor de sons da classe
manager
*Params: char*
*Return: CVRSound*
************************************************************/
CVRSound* CVRSoundManager::LoadSound(char * arq)
{
          
	    CVRSound *p_Sound = new CVRSound();
		sounds.push_back(p_Sound);
        p_Sound->InitInterface();
		p_Sound->LoadSound(arq);
		listener.LinkSoundListener(p_Sound);
				
		return p_Sound;
}

/***********************************************************
*Name: LoadMusic()
*Description: chama a função LoadMusic da classe CVRMusic
manager
*Params: char*
*Return: bool
************************************************************/
bool CVRSoundManager::LoadMusic(char* arquivo)
{
	if( music.LoadMusic(arquivo))
	{
		bIsMusicLoad = true;
		return true;
	}//fim do if
	else
		return false;
}

/***********************************************************
*Name: GetListener()
*Description: retorna um ponteiro para o ouvinte
manager
*Params: Nenhum
*Return: CVRListener*
************************************************************/
CVRListener* CVRSoundManager::GetListener()
{
	return &listener;
}

/***********************************************************
*Name: StopAll()
*Description: para de tocar todos os sons e musica
manager
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSoundManager::StopALL()
{
	bool test = false;

	CVRSound::DSperformance->Stop(NULL,NULL,0,0);
	//seta o estado de música para FALSE, indica que a música não está tocando
	
	music.SetIsPlaying(false);

	for(int iIndex = (int)sounds.size()-1;iIndex>=0; iIndex++)
	{
		if(CVRSound::DSperformance->IsPlaying((sounds[iIndex])->GetSegment(),NULL) == S_OK)
		{
		    return false;
		}
	}//fim do for
    
	return true;
}//fim da função stopALL

/***********************************************************
*Name: GetMusic()
*Description: retorna o objeto da classe CVRMusic
manager
*Params: Nenhum
*Return: bool
************************************************************/
CVRMusic CVRSoundManager::GetMusic()
{
		  return music;
}