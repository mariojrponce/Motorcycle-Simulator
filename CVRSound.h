/***********************************************************************
*Nome: CVRSound.h
*Descrição: Cabeçalho da classe responsável pelo carregamento de sons
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

	  //estrutura para os parâmetros de som
      DS3DBUFFER DSbufferparam;

	  //Armazena o numero de repetições
	  int iNumRepeat;

	  //valores para os âgulos interno e externo do ConeAngle
	  DWORD coneAngleInside;
	  DWORD coneAngleOutside;

   public:

	  //construtora
	  CVRSound();

	  //detrutora
	  ~CVRSound();

	  //interfaces estáticas de performance e load
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

	  //pára um som
	  bool StopSound();

	  //repete um som num vezes, passando num como -1 repete infinitamente
	  //OBS: 1- Sempre utilizar a função setRepeat antes da função play, pois 
	  //        chamando-a depois do play ela perde sua funcionalidade.
	  //     2- Setar para zero a função setRepeat para ela parar de repetir,
      //        pois quando a setRepeat é chamada ela marca quantas repetições 
	  //        devem ser feitas conforme é passado pelos seus parâmetros.
	  //        EXEMPLO:
	  //              se um som é setado para repetir infinitamente passando -1
	  //        como parâmetro, e depois é parado com a função stop, e após isso
	  //        é tocado novamente, ele vai repetir infinitamente, pois a função 
	  //        setRepeat funciona como um botão de aparelho de som que está apertado
	  //        e só para de repetir quando for desapertado.
	  //              Para isso deve-se chamar a setRepeat novamente passando zero
	  //        como parâmetro da função.
	  bool SetRepeat(int num = 0);

	  //inicia as interfaces DSbuffer e DSaudiopath
	  bool InitInterface();

	  //seta as interfaces DSbuffer,DSsegment e DSaudiopath para NULL 
	  void SetNULL();

	  //seta as posições x,y e z do som
	  void SetPosition(float x,float y,float z);
	
	  //seta a posição x do som
	  void SetX(float x);
     
	  //seta a posição y do som
	  void SetY(float y);
	 
	  //seta a posição z do som
	  void SetZ(float z);

	  //seta a velocidade do som nos 3 eixos(x,y,z)
	  void SetVelocity(float x, float y, float z);

	  //seta a velocidade do som no eixo x
	  void SetVelocityAxe_x(float x);

	  //seta a velocidade do som no eixo y
	  void SetVelocityAxe_y(float y);

	  //seta a velocidade do som no eixo z
	  void SetVelocityAxe_z(float z);

	  //seta o ângulo interno no Cone Angle do som
	  void SetConeAngle_Inside(DWORD insideAngle); 
	
	  //seta o ângulo externo no Cone Angle do som
	  void SetConeAngle_Outside(DWORD outsideAngle);

	  //volume -9600=volume mínimo, 0=volume máximo( valor para volume entre -9600 e 0 )
	  void SetVolume(long vol);
		   
	  //seta o máximo e mínimo de distância para o som
	  bool SetMaxMin(float max, float min);
	
	  //retorna o valo do do ângulo interno do cone do som
	  DWORD GetConeAngle_Inside();

	  //retorna o valo do do ângulo externo do cone do som
	  DWORD GetConeAngle_Outside();

	  //retorna a distância máxima para o som
	  float GetMax();
	
	  //retorna a distância mínima para o som
	  float GetMin();
	
	  //retorna as posições x,y e z do som
	  CVRVector GetPosition();
	
	  //retorna a posição X do som
	  float GetX();
	  
	  //retorna a posição Y do som
	  float GetY();
	 
	  //retorna a posição Z do som
	  float GetZ();
	
	  //retorna o atributo de estado do som, se TRUE(está tocando), se FALSE(não está tocando)
	  bool GetIsPlaying();
	 
	  //seta o som para mudo, ou não
	  void MuteSound(bool mute);

	  //Libera o som
	  void Release();
	
};//fim da classe Sound
#endif