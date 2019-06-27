/**
* @author Victor de Almeida Thomaz
* @change Bruno Oliveira de Alcântara.
* @changelog pequenas alterações para adaptação ao joystick de force feedback
* @version 1.0   
* Arquivo: CVRJoystick.h  
* Descrição: Cabeçalho da classe responsável pelo reconhecimanto 
*            dos joysticks .
* Data de Criação: 24/01/2008                                                                     
* Data da última modificação: 15/07/2008  
* Local: LNCC                                                                                      
*/

#ifndef _CVRJOYSTICK_
#define _CVRJOYSTICK_

// Set the maxmimum range to which we'll gauge the swing
#define JOYMAX 10000
#define JOYMIN -10000
// Dead zone is the amount of sway the joystick can have before we start registering movement, in this case 20%
#define JOYDEAD 2000
// The Saturation Point is Where the Joystick is deemed to be at Full Swing, in this case 95%
#define JOYSAT  9500

#include <windows.h>
#include <basetsd.h>
#include <assert.h>
#include <dinput.h>

class CVRJoystick
{ 
   //Métodos joystick
   public:
      CVRJoystick();
	  ~CVRJoystick();
	  bool Init(HWND);
	  bool Init();
	  bool Update();
	  void Release();
	  bool IsButtonDown(int iButton);
	  bool IsButtonUp(int iButton);
	  bool IsXAxisFront();
	  bool IsXAxisBack();
	  bool IsYAxisUp();
	  bool IsYAxisDown();
	  bool IsZAxisFront();
	  bool IsZAxisBack();
	  bool IsZRotUp();
	  bool IsZRotDown();
      int  GetXAxis();
	  int  GetYAxis();
	  int  GetZAxis();
	  int  GetXRot();
	  int  GetYRot();
      int  GetZRot();
      bool HasJoystick();
	  LPDIRECTINPUTDEVICE8 getJoystick(){ return joystick; }

	  //gets
	  DWORD getEnumObjectParamTwo(){ return enumObjectParamTwo; }
	
	  //sets
	  void setEnumObjectParamTwo( DWORD p ){ enumObjectParamTwo = p; }

	  LPDIRECTINPUT8 GetInput(void);
	  static CVRJoystick * GetSingleton(void);

	  static BOOL CALLBACK enumJoysticksCallback(const DIDEVICEINSTANCE*, VOID* );
      static BOOL CALLBACK enumObjectsCallback(const DIDEVICEOBJECTINSTANCE*, VOID* );

	  void setJoystick(LPDIRECTINPUTDEVICE8 device){ joystick = device; }

   //Atributos Joystick
   private:
      LPDIRECTINPUT8          diObject;
      LPDIRECTINPUTDEVICE8    joystick;
	  DIJOYSTATE2 JoyData;

	  DWORD     enumObjectParamTwo;
	
	  /** ponteiro para a classe forceFeedbackManager
		* usado para acessar as funões da própria classe 
	  */
      static CVRJoystick * ptrSingleton;

};//fim CVRJoystick
#endif

