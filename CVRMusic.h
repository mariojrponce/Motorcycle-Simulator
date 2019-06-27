/***********************************************************************
*Nome: CVRMusic.h
*Descri��o: Cabe�alho da classe respons�vel pelo carregamento de m�sicas
*Data: 26/09/07
*Local: LNCC
************************************************************************/

#ifndef _CVRMUSIC_
#define _CVRMUSIC_

#include "CVRObject.h"

class CVRMusic: public CVRObject
{ 
   private:
	  //interface de segmento de m�sica
      IDirectMusicSegment8 * DSsegmentMusic;

	  //interface de caminho de m�sica
      IDirectMusicAudioPath * DSaudiopathMusic;

	  //atributo de estado da m�sica
	  bool bIsPlaying;
	      
   public:

	   //construtora
	   CVRMusic();
	
	   //destrutora
	   ~CVRMusic(); 

	  //carrega um arquivo de m�sica .wav, ou .mid
	  bool LoadMusic(char*);

	  //toca o segmento de m�sica
	  bool PlayMusic();

	  //p�ra o segmento de m�sica
	  bool StopMusic();

	  //repete a m�sica num vezes, passando num como -1 repete infinitamente
	  bool SetRepeat(int num = 0);

	  //seta o volume da m�sica
	  void SetVolume(long vol);
  
	  //inicia a interface DSaudiopathMusic
	  bool InitInterface();

	  //finaliza a m�sica
	  void Release();

	  //retorna o atributo de estado da m�sica, se TRUE(est� tocando), se FALSE(n�o est� tocando)
      bool GetIsPlaying();
	
	  //seta o estado da m�sica para TRUE ou para FALSE
	  void SetIsPlaying(bool estado);
	 	
};//fim da classe Music
#endif