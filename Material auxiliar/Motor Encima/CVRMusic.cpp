/***********************************************************************
*Nome: CVRMusic.cpp
*Descri��o: Implementa��o da classe respons�vel pelo carregamento de imagens
*Data: 18/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRMusic.h"
#include "CVRSound.h"


/***********************************************************
*Name: CVRMusic()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRMusic::CVRMusic()
{
	DSsegmentMusic = NULL; 
	DSaudiopathMusic = NULL;
	bIsPlaying = false;
}

/***********************************************************
*Name: ~CVRMusic()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRMusic::~CVRMusic()
{
		  
}

/***********************************************************
*Name: InitInterface()
*Description: Inicia o direct music
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRMusic::InitInterface()
{
    // Cria o audiopathMusic STEREO
	if (this->GetIsPlaying())
		return true;

	if (FAILED(CVRSound::DSperformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_STEREO,64, TRUE, &DSaudiopathMusic)))
	   return false;		

	return true;
}

/***********************************************************
*Name: LoadMusic()
*Description: carrega uma musica
*Params: char*
*Return: bool
************************************************************/
bool CVRMusic::LoadMusic(char *arquivo)
{
	//inicia o DSaudiopathMusic
	InitInterface();

	WCHAR music[MAX_PATH];

    //converte char para WCHAR
    MultiByteToWideChar(CP_ACP, 0, arquivo, -1, music, MAX_PATH);

    //carrega o arquivo a ser tocado
	if(FAILED(CVRSound::DSloader->LoadObjectFromFile(CLSID_DirectMusicSegment,IID_IDirectMusicSegment8,
						music, (void**)&DSsegmentMusic )))
		    return false;

    //converte o segmento para tipo WAV
    DSsegmentMusic->Download( DSaudiopathMusic ); 
     	
	return true;
}

/***********************************************************
*Name: PlayMusic()
*Description: toca a musica
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRMusic::PlayMusic()
{
	if (bIsPlaying == true)
	{
		return false;
	}
	else
	{
		//d� play no segmento de m�sica 
		CVRSound::DSperformance->PlaySegmentEx(DSsegmentMusic, NULL, NULL, DMUS_SEGF_SECONDARY, 0, NULL, NULL, DSaudiopathMusic);
		bIsPlaying = true;
		return true;
	}
}

/***********************************************************
*Name: StopMusic()
*Description: p�ra a musica
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRMusic::StopMusic()
{
	if (CVRSound::DSperformance->IsPlaying(DSsegmentMusic,NULL) == S_OK)
	{
		//d� stop no segmento de m�sica
		CVRSound::DSperformance->StopEx(DSsegmentMusic,0,0);
		bIsPlaying = false;
		return true;
	}
	else
		return false;
}

/***********************************************************
*Name: SetRepeat()
*Description: configura o numero de vezes que a musica ir� repetir (-1 = infinito)
*Params: int
*Return: bool
************************************************************/
bool CVRMusic::SetRepeat(int iNumRepeat)
{

	if(iNumRepeat < 0)
	{
		DSsegmentMusic->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
	}
	else
	{
		DSsegmentMusic->SetRepeats(iNumRepeat);			
	}

	return true;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: bool
************************************************************/
void CVRMusic::Release()
{
	if(DSaudiopathMusic)
	{
		DSaudiopathMusic->Release();
		DSaudiopathMusic = NULL;
	}
	else
		return;

	if(DSsegmentMusic)
	{
		DSsegmentMusic->Release();
		DSsegmentMusic = NULL;
	}
	else 
		return;

}

/***********************************************************
*Name: SetVolume()
*Description: configura o volume da m�sica -9600 = m�nimo  0 = m�ximo
*Params: long
*Return: Nenhum
*************************	***********************************/
void CVRMusic::SetVolume(long vol)
{
	//coloca o volume e a dura��o do volume 
	DSaudiopathMusic->SetVolume(vol,0); 
}

/***********************************************************
*Name: GetIsPlaying()
*Description: retorna verdadeiro se a musica esta tocando, senao retorna falso
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRMusic::GetIsPlaying()
{ 
	return bIsPlaying;
}

/***********************************************************
*Name: SetIsPlaying()
*Description: configura a musica para tocar ou nao
*Params: bool
*Return: Nenhum
************************************************************/
void CVRMusic::SetIsPlaying(bool estate)
{
	bIsPlaying = estate;
}
