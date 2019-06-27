/***********************************************************************
*Nome: CVRSound.h
*Descri��o: Cabe�alho da classe respons�vel pelo carregamento de sons
*Data: 26/09/07
*Local: LNCC
************************************************************************/

#ifndef _CVRSOUND_
#define _CVRSOUND_

#include "CVRObject.h"
#include "CVRVector.h"

class CVRSound: public CVRObject
{    
   private:

	  //interface de atributos de som 3d
	  IDirectSound3DBuffer8  * DSbuffer;

	  //interface de segmento de som
      IDirectMusicSegment8 *DSsegment;
	  
	  //interface de caminho de som
      IDirectMusicAudioPath * DSaudiopath;

	  //estrutura para os par�metros de som
      DS3DBUFFER DSbufferparam;

	  //Armazena o numero de repeti��es
	  int iNumRepeat;

	  //valores para os �gulos interno e externo do ConeAngle
	  DWORD coneAngleInside;
	  DWORD coneAngleOutside;

   public:

	  //construtora
	  CVRSound();

	  //detrutora
	  ~CVRSound();

	  //interfaces est�ticas de performance e load
	  static IDirectMusicPerformance8* DSperformance;
      static IDirectMusicLoader8* DSloader;

	  //inicializa a COM e as interfaces DSperformance e DSloader 
	  static bool Init();

	  //retorna a interface DSbuffer
	  IDirectSound3DBuffer* GetBuffer();
	 
	  //retorna a interface DSsegment
	  IDirectMusicSegment8* GetSegment();
	  
	  //retorna a interface DSaudiopath
	  IDirectMusicAudioPath* GetAudiopath();
	  
	  //retorna a estrutura DSbufferparam(DS3DBUFFER)
	  DS3DBUFFER GetBufferparam();
	  
	  //carrega um som
	  bool LoadSound(char* );

	  //toca um som
	  bool PlaySound();

	  //p�ra um som
	  bool StopSound();

	  //repete um som num vezes, passando num como -1 repete infinitamente
	  //OBS: 1- Sempre utilizar a fun��o setRepeat antes da fun��o play, pois 
	  //        chamando-a depois do play ela perde sua funcionalidade.
	  //     2- Setar para zero a fun��o setRepeat para ela parar de repetir,
      //        pois quando a setRepeat � chamada ela marca quantas repeti��es 
	  //        devem ser feitas conforme � passado pelos seus par�metros.
	  //        EXEMPLO:
	  //              se um som � setado para repetir infinitamente passando -1
	  //        como par�metro, e depois � parado com a fun��o stop, e ap�s isso
	  //        � tocado novamente, ele vai repetir infinitamente, pois a fun��o 
	  //        setRepeat funciona como um bot�o de aparelho de som que est� apertado
	  //        e s� para de repetir quando for desapertado.
	  //              Para isso deve-se chamar a setRepeat novamente passando zero
	  //        como par�metro da fun��o.
	  bool SetRepeat(int num = 0);

	  //inicia as interfaces DSbuffer e DSaudiopath
	  bool InitInterface();

	  //seta as interfaces DSbuffer,DSsegment e DSaudiopath para NULL 
	  void SetNULL();

	  //seta as posi��es x,y e z do som
	  void SetPosition(float x,float y,float z);
	
	  //seta a posi��o x do som
	  void SetX(float x);
     
	  //seta a posi��o y do som
	  void SetY(float y);
	 
	  //seta a posi��o z do som
	  void SetZ(float z);

	  //seta a velocidade do som nos 3 eixos(x,y,z)
	  void SetVelocity(float x, float y, float z);

	  //seta a velocidade do som no eixo x
	  void SetVelocityAxe_x(float x);

	  //seta a velocidade do som no eixo y
	  void SetVelocityAxe_y(float y);

	  //seta a velocidade do som no eixo z
	  void SetVelocityAxe_z(float z);

	  //seta o �ngulo interno no Cone Angle do som
	  void SetConeAngle_Inside(DWORD insideAngle); 
	
	  //seta o �ngulo externo no Cone Angle do som
	  void SetConeAngle_Outside(DWORD outsideAngle);

	  //volume -9600=volume m�nimo, 0=volume m�ximo( valor para volume entre -9600 e 0 )
	  void SetVolume(long vol);
		   
	  //seta o m�ximo e m�nimo de dist�ncia para o som
	  bool SetMaxMin(float max, float min);
	
	  //retorna o valo do do �ngulo interno do cone do som
	  DWORD GetConeAngle_Inside();

	  //retorna o valo do do �ngulo externo do cone do som
	  DWORD GetConeAngle_Outside();

	  //retorna a dist�ncia m�xima para o som
	  float GetMax();
	
	  //retorna a dist�ncia m�nima para o som
	  float GetMin();
	
	  //retorna as posi��es x,y e z do som
	  CVRVector GetPosition();
	
	  //retorna a posi��o X do som
	  float GetX();
	  
	  //retorna a posi��o Y do som
	  float GetY();
	 
	  //retorna a posi��o Z do som
	  float GetZ();
	
	  //retorna o atributo de estado do som, se TRUE(est� tocando), se FALSE(n�o est� tocando)
	  bool GetIsPlaying();
	 
	  //seta o som para mudo, ou n�o
	  void MuteSound(bool mute);

	  //Libera o som
	  void Release();
	
};//fim da classe Sound
#endif