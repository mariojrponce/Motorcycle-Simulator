/***********************************************************************
*Nome: CVRSTDInput
*Descrição: Cabeçalho da classe responsável pela gerenciamento dos dispo-
sitivos padrao
*Data: 24/08/07
*Local: LNCC
************************************************************************/
#ifndef _CVRSTDINPUT_
#define _CVRSTDINPUT_

//Bibliotecas
#include "CVRObject.h"
#include "CVRVector.h"

class CVRManager;

//Numero de teclas a serem tratadas
#define NUMKEYS 256

class CVRSTDInput: public CVRObject
{
	private:
	
	LPDIRECTINPUT			p_DInput;
	LPDIRECTINPUTDEVICE		p_DevKeyboard;
	LPDIRECTINPUTDEVICE		p_DevMouse;
	unsigned char KeyboardState[NUMKEYS];
	unsigned char LastKeyboardState[NUMKEYS];
	DIMOUSESTATE MouseState;
	DIMOUSESTATE LastMouseState;
	CVRVector MousePos;
	CVRVector MouseWindowsPos;

public:
	CVRManager* pManager;

public:
	CVRSTDInput();
	~CVRSTDInput();
	void Release();
	bool Init();
	void Update();
	CVRVector GetMousePosition();
	bool KeyDown(unsigned char);
	bool KeyPressed(unsigned char);
	bool KeyReleased(unsigned char);
	bool MouBtnDown(unsigned char);
	bool MouBtnPressed(unsigned char);
	bool MouBtnReleased(unsigned char);	
	void SetWindowsMousePos(CVRVector &);

private:
	void UpdateMouse();
	void UpdateKeyboard();
	void InitMouse();
	void InitKeyboard();
};
#endif;