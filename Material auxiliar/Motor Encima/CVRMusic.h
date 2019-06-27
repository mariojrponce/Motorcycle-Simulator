/***********************************************************************
*Nome: CVRMusic.h
*Descrição: Cabeçalho da classe responsável pelo carregamento de músicas
*Data: 26/09/07
*Local: LNCC
************************************************************************/

#ifndef _CVRMUSIC_
#define _CVRMUSIC_

#include "CVRObject.h"

class CVRMusic: public CVRObject
{ 
   private:
	  //interface de segmento de música
      IDirectMusicSegment8 * DSsegmentMusic;

	  //interface de caminho de música
      IDirectMusicAudioPath * DSaudiopathMusic;

	  //atributo de estado da música
	  bool bIsPlaying;
	      
   public:

	   //construtora
	   CVRMusic();
	
	   //destrutora
	   ~CVRMusic(); 

	  //carrega um arquivo de música .wav, ou .mid
	  bool LoadMusic(char*);

	  //toca o segmento de música
	  bool PlayMusic();

	  //pára o segmento de música
	  bool StopMusic();

	  //repete a música num vezes, passando num como -1 repete infinitamente
	  bool SetRepeat(int num = 0);

	  //seta o volume da música
	  void SetVolume(long vol);
  
	  //inicia a interface DSaudiopathMusic
	  bool InitInterface();

	  //finaliza a música
	  void Release();

	  //retorna o atributo de estado da música, se TRUE(está tocando), se FALSE(não está tocando)
      bool GetIsPlaying();
	
	  //seta o estado da música para TRUE ou para FALSE
	  void SetIsPlaying(bool estado);
	 	
};//fim da classe Music
#endif