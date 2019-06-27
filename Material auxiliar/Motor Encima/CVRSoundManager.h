/***********************************************************************
*Nome: CVRSoundManager.h
*Descri��o: Cabe�alho da classe respons�vel pelo gerenciamento dos sons
*Data: 28/09/07
*Local: LNCC
************************************************************************/

#ifndef _CVRSOUNDMANAGER_
#define _CVRSOUNDMANAGER_

#include "CVRObject.h"
#include "CVRListener.h"
#include "CVRMusic.h"
#include "CVRSound.h"

class CVRSoundManager: public CVRObject
{ 
   private:
	  //ouvinte
	  CVRListener listener;

	  //objeto music
	  CVRMusic music;

	  //atributo da m�sica para verificar se h� m�sica carregada
	  bool bIsMusicLoad;

   public:

	  //construtora
	  CVRSoundManager();
	   
	  //destrutora
	  ~CVRSoundManager(); 

	  //vetor de sons
	  vector<CVRSound*> sounds;

	  //carrega um som para o vetor(sounds) de sons 
	  CVRSound* LoadSound(char *);

	  //carrega uma m�sica
	  bool LoadMusic(char*);

	  //inicializa som
	  bool Init();

	  //finaliza som
	  void Release();

	  //remove um som do vetor
	  bool Remove(CVRSound*);

	  //retorna o atributo avatar
	  CVRListener* GetListener();

	  //p�ra todos os sons do vetor
	  bool StopALL();

	  //retorna o objeto music
	  CVRMusic GetMusic();
	    
      //atualiza a posi��o do ouvinte 
	  void UpdatePosListener(float x, float y, float z);	  
      		
};//fim da classe Manager
#endif