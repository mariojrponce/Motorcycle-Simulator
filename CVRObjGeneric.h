/***********************************************************************
*Nome: CVRObjGeneric.h
*Descri��o: Cabe�alho da classe que implementa um objeto gen�rico
*Data: 18/06/08
*Local: LNCC
************************************************************************/

#ifndef _CVROBJGENERIC_
#define _CVROBJGENERIC_

#include "CVRObject3D.h"

class CVRObjGeneric:public CVRObject3D
{
public:
	CVRObjGeneric();
	~CVRObjGeneric();	
	virtual bool Init()=0;
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void Release()=0;
};
#endif