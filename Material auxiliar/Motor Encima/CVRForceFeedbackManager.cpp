/**
* @author Bruno Oliveira de Alcântara.
* @version 1.0                                                                     
* Arquivo: CVRForceFeedbackManager.cpp                                    
* Descrição: Implementação da classe responsável pelo reconhecimento   
*            do ForceFeedBack do joystick.                             
*                                                                      
* Data de Criação: 24/01/2008                                          
* Data da última modificação: 15/05/2008                                 
* Local: LNCC                                                           
* Programador: Bruno Oliveira de Alcântara                                                                                                   
*/

#include "CVRForceFeedbackManager.h"

CVRForceFeedbackManager::CVRForceFeedbackManager()
{ 
	eixoX = 0;
	eixoY = 0;
	eixoZ = 0;
    joystickEffect = NULL;
	numEixos       = 0;
	CVRJoystick::GetSingleton()->setEnumObjectParamTwo( numEixos );
	setNumEixos( CVRJoystick::GetSingleton()->getEnumObjectParamTwo() ); 
}

CVRForceFeedbackManager::CVRForceFeedbackManager( HWND hDlg )
{
	eixoX = 0;
	eixoY = 0;
	eixoZ = 0;
	joystickEffect = NULL;
	numEixos       = 0;   
	CVRJoystick::GetSingleton()->setEnumObjectParamTwo( numEixos );
    initFFManager( hDlg );
	setNumEixos( CVRJoystick::GetSingleton()->getEnumObjectParamTwo() );
}

bool CVRForceFeedbackManager::initFFManager( HWND hDlg )
{
	if( FAILED( CVRJoystick::GetSingleton()->Init( hDlg )))
	{
		return false;
	}	
	setNumEixos( CVRJoystick::GetSingleton()->getEnumObjectParamTwo() );
	return true;
}

bool CVRForceFeedbackManager::release()
{
	//descarega efeito antigo
	unloadEffect();

    //limpa objetos do DirectInput.
	if( joystickEffect )
	{
		joystickEffect->Release();
		joystickEffect = NULL;
	}	
	return true;
}

bool CVRForceFeedbackManager::createEffect( CVRStructEffect eff, GUID refGuid )
{	
	//descarrega efeito antigo
	unloadEffect();

	//seta o npumero de eixos no joystick para a estrutura eff
	eff.setNumAxesEffect( getNumEixos() ); 
	
    //Cria o efeito preparado
    if(FAILED( CVRJoystick::GetSingleton()->getJoystick()->CreateEffect(
				refGuid,&eff.getEffect(), &joystickEffect, NULL)))
	{
        return false;
	}
    if( joystickEffect == NULL )
	{
        return false;
	}
	return true;
}

bool CVRForceFeedbackManager::startEffect(DWORD time)
{
	CVRJoystick::GetSingleton()->getJoystick()->Acquire();

	if( joystickEffect ) 
	{
		joystickEffect->Start(time,0);
	}
	else 
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::stopEffect()
{
	if(joystickEffect)
	{
		joystickEffect->Stop();
	}
	else
	{
		return false;
	}
	return true;	
}

bool CVRForceFeedbackManager::setPosition( int x, int y, CVRStructEffect eff )
{
	eixoX = x;
	eixoY = y;
	eff.setNumAxesEffect( 2 ); 
	eff.setDirectionEffect(x,y);

	if( FAILED( joystickEffect->SetParameters( &eff.getEffect(),DIEP_DIRECTION 
 		                | DIEP_TYPESPECIFICPARAMS | DIEP_START )))
	{	
						return false;
	}	
	return true;
}

bool CVRForceFeedbackManager::setPosition( int x, int y, int z, CVRStructEffect eff )
{
	eixoX = x;
	eixoY = y;
	eixoZ = z;
   	eff.setNumAxesEffect( 3 ); 
	eff.setDirectionEffect(x,y,z);

	if( FAILED( joystickEffect->SetParameters( &eff.getEffect(),DIEP_DIRECTION 
		                | DIEP_TYPESPECIFICPARAMS | DIEP_START )))
	{
			return false;
	}
	return true;
}

bool CVRForceFeedbackManager::unloadEffect()
{ 
	if( joystickEffect )
	{
		joystickEffect->Unload();
	}
	else 
	{
		return false;
	}	
	return true; 
}

//===========================EFEITOS===================================

//NOT_OK
bool CVRForceFeedbackManager::metralhadora()
{	
	CVRStructEffect cCVRStructEffect;
	DIPERIODIC diPeriod;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	diPeriod.dwMagnitude = 10000;
	diPeriod.dwPeriod    = 100000;
	diPeriod.dwPhase     = 1;
	diPeriod.lOffset     = 1;

	//setNumEixos( 3 );
	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIPERIODIC( diPeriod );

	//DICONDITION    
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_POLAR | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( timeEffect );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getConditForce(), sizeof(DICONDITION));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect,GUID_Sine )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	if( FAILED (setPosition(360* DI_DEGREES, 270 * DI_DEGREES, cCVRStructEffect) ) )
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::condensado()
{
	CVRStructEffect cCVRStructEffect;
	DICONDITION diCond;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	//Estrutura - Força Condicional
	diCond.dwNegativeSaturation = 10000;
	diCond.dwPositiveSaturation = 0;
	diCond.lDeadBand            = 1;
	diCond.lNegativeCoefficient = 10000;
	diCond.lOffset              = 1;
	diCond.lPositiveCoefficient = 0;
	
	//seta a estrutura DICONDITION
    cCVRStructEffect.setDICONDITION(diCond);

	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( timeEffect );
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getConditForce(), sizeof(DICONDITION));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect, GUID_Inertia )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	if ( FAILED (setPosition( 1000,-1000, cCVRStructEffect ) ) )
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::atrito()
{
	CVRStructEffect cCVRStructEffect;
	DIPERIODIC diPeriod;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	diPeriod.dwMagnitude = 10000;
	diPeriod.dwPeriod    = 1;
	diPeriod.dwPhase     = 100000;
	diPeriod.lOffset     = 1;

	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIPERIODIC( diPeriod );

	//DIPERIODIC    
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_POLAR | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( timeEffect );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getPeriodic(), sizeof(DIPERIODIC));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect, GUID_Triangle )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	if( FAILED( setPosition( 1000,-1000, cCVRStructEffect ) ) )
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDirecao( direcao valor )
{
	CVRStructEffect cCVRStructEffect;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	//seta a estrutura DICONSTANTFORCE  
	cCVRStructEffect.setConstantForce( DI_FFNOMINALMAX );

	//DICONSTANTFORCE  
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( (DWORD)(5 * DI_SECONDS) );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getConstForce(), sizeof(DICONSTANTFORCE));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect, GUID_ConstantForce )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	switch(valor)
	{
		case ESQUERDA: setPosition( 1000, 0, cCVRStructEffect ); break;
		case DIREITA: setPosition( -1000, 0, cCVRStructEffect ); break;
		case FRENTE: setPosition( 0, 1000, cCVRStructEffect ); break;
		case TRAS: setPosition( 0, -1000, cCVRStructEffect ); break;
		case DIAGONAL_DIR_FRENTE: setPosition( -1000, 1000, cCVRStructEffect ); break;
		case DIAGONAL_DIR_TRAS: setPosition( -1000, -1000, cCVRStructEffect ); break;
		case DIAGONAL_ESQ_FRENTE: setPosition( 1000, 1000, cCVRStructEffect ); break;
		case DIAGONAL_ESQ_TRAS: setPosition( 1000, -1000, cCVRStructEffect ); break;
		default: break;
	}	
	return true;
}

bool CVRForceFeedbackManager::forceFrente()
{
	if( FAILED( forceDirecao( FRENTE ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceTras()
{
	if( FAILED( forceDirecao( TRAS ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDireita()
{
	if( FAILED( forceDirecao( DIREITA ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceEsquerda()
{
	if( FAILED( forceDirecao( ESQUERDA ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDiagDirFrente()
{
	if( FAILED( forceDirecao( DIAGONAL_DIR_FRENTE ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDiagDirTras()
{
	if( FAILED( forceDirecao( DIAGONAL_DIR_TRAS ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDiagEsqFrente()
{
	if( FAILED( forceDirecao( DIAGONAL_ESQ_FRENTE) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::forceDiagEsqTras()
{
	if( FAILED( forceDirecao( DIAGONAL_ESQ_TRAS ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDirecao( direcao valor )
{
	CVRStructEffect cCVRStructEffect;
	DIPERIODIC diPeriod;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	diPeriod.dwMagnitude = 10000;
	diPeriod.dwPeriod    = 100000;
	diPeriod.dwPhase     = 100;
	diPeriod.lOffset     = 10;
	
	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIPERIODIC( diPeriod );

	//DIPERIODIC    
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( timeEffect );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER, 0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getPeriodic(), sizeof(DIPERIODIC));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect, GUID_SawtoothUp )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	switch(valor)
	{
		case ESQUERDA: setPosition( 1000, 0, cCVRStructEffect ); break;
		case DIREITA: setPosition( -1000, 0, cCVRStructEffect ); break;
		case FRENTE: setPosition( 0, 1000, cCVRStructEffect ); break;
		case TRAS: setPosition( 0, -1000, cCVRStructEffect ); break;
		default: break;
	}	
	return true;
}

bool CVRForceFeedbackManager::vibrarFrente()
{
	if( FAILED( vibrarDirecao( FRENTE ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarTras()
{
	if( FAILED( vibrarDirecao( TRAS ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDireita()
{
	if( FAILED( vibrarDirecao( DIREITA ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarEsquerda()
{
	if( FAILED( vibrarDirecao( ESQUERDA ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDiagDirFrente()
{
	if( FAILED( vibrarDirecao( DIAGONAL_DIR_FRENTE ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDiagDirTras()
{
	if( FAILED( vibrarDirecao( DIAGONAL_DIR_TRAS ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDiagEsqFrente()
{
	if( FAILED( vibrarDirecao( DIAGONAL_ESQ_FRENTE ) ))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::vibrarDiagEsqTras()
{
	if( FAILED( vibrarDirecao( DIAGONAL_ESQ_TRAS ) ))
	{
		return false;
	}
	return true;
}

int CVRForceFeedbackManager::coordToForce( int nCoord )
{
    int nForce = MulDiv( nCoord, 2 * DI_FFNOMINALMAX, FEEDBACK_WINDOW_WIDTH )
                 - DI_FFNOMINALMAX;

    //mantém  a força com limites
    if( nForce < -DI_FFNOMINALMAX ) 
        nForce = -DI_FFNOMINALMAX;

    if( nForce > +DI_FFNOMINALMAX ) 
        nForce = +DI_FFNOMINALMAX;

    return nForce;
}

bool CVRForceFeedbackManager::controle(int x, int y )
{
	int coordX = - coordToForce(x);
	int coordY = - coordToForce(y);

	CVRStructEffect cCVRStructEffect;
	DWORD      rgdwAxes[2] = { DIJOFS_X, DIJOFS_Y };

	//seta a estrutura DICONSTANTFORCE  
	cCVRStructEffect.setConstantForce( DI_FFNOMINALMAX );

	//DICONSTANTFORCE  
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( (DWORD)(5 * DI_SECONDS) );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getConstForce(), sizeof(DICONSTANTFORCE));
	cCVRStructEffect.setDelayEffect( 0 );

	if( FAILED(createEffect( cCVRStructEffect, GUID_ConstantForce )))
	{
		return false;
	}
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	
	if( FAILED( setPosition( coordX, coordY , cCVRStructEffect )))
	{
		return false;
	}
	return true;
}

bool CVRForceFeedbackManager::test()
{
	/*
	//Forcefeedback: efeito explosivo
	CVRStructEffect cCVRStructEffect;
	DWORD rgdwAxes[1] = {DIJOFS_X};
	LONG lDirection[1] = {0};

	DIENVELOPE diEnvelope;
    diEnvelope.dwAttackLevel = 0;
	diEnvelope.dwAttackTime = 0;
	diEnvelope.dwFadeLevel = 0;
	diEnvelope.dwFadeTime = 1.0 * DI_SECONDS;

	DIPERIODIC diPeriod;
	diPeriod.dwMagnitude = DI_FFNOMINALMAX;
	diPeriod.lOffset = 0;
	diPeriod.dwPhase = 0;
	diPeriod.dwPeriod = 0.1 * DI_SECONDS;

	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIPERIODIC( diPeriod );

	//DIPERIODIC    
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_OBJECTOFFSETS | DIEFF_CARTESIAN );
	cCVRStructEffect.setDurationEffect( timeEffect );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( 0 );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getPeriodic(), sizeof(DIPERIODIC));
	cCVRStructEffect.setDelayEffect( 0 );
	*/

	CVRStructEffect cCVRStructEffect;
	DWORD      rgdwAxes[1] = { DIJOFS_X };
	setNumEixos(1);

	DIENVELOPE diEnvelope;
    diEnvelope.dwAttackLevel = 0;
	diEnvelope.dwAttackTime = 0;
	diEnvelope.dwFadeLevel = 0;
	diEnvelope.dwFadeTime = (DWORD)1.0 * DI_SECONDS;

	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIENVELOPE( diEnvelope );

	DIPERIODIC diPeriod;
	diPeriod.dwMagnitude = 10000;
	diPeriod.dwPeriod    = 1;
	diPeriod.dwPhase     = 1;
	diPeriod.lOffset     = 10000;

	//seta a estrutura DIPERIODIC
	cCVRStructEffect.setDIPERIODIC( diPeriod );
	
	//DIPERIODIC    
	cCVRStructEffect.setAxesEffect( rgdwAxes, getNumEixos() ); 
	cCVRStructEffect.setDirectionEffect(0,0);
	cCVRStructEffect.setFlagsEffect( DIEFF_SPHERICAL | DIEFF_OBJECTOFFSETS );
	cCVRStructEffect.setDurationEffect( timeEffect );   
	cCVRStructEffect.setPeriodEffect( 0 );          
	cCVRStructEffect.setGainEffect( DI_FFNOMINALMAX );
	cCVRStructEffect.setButtonEffect( DIEB_NOTRIGGER,0 );
	cCVRStructEffect.setEnvelopeEffect( &diEnvelope );
	cCVRStructEffect.setTypeSpecificParamsEffect( &cCVRStructEffect.getPeriodic(), sizeof(DIPERIODIC));
	cCVRStructEffect.setDelayEffect( 0 );

	createEffect( cCVRStructEffect, GUID_Sine );
	if( FAILED(startEffect(1)))
	{
		return false;
	}
	setPosition( 0,0, cCVRStructEffect );	
	return true;
}
