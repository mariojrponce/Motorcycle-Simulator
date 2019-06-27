/**
* @author Bruno Oliveira de Alcântara.
* @version 1.0   
* Arquivo: CVRStructEffect.cpp
* Descrição: implementação das funções da classe responsável pela estrutura
* dos efeitos de Force Feedback do joystick.
* Data de Criação: 24/01/2008                                                                     
* Data da última modificação: 15/07/2008  
* Local: LNCC                                                                                      
*/

#include "CVRStructEffect.h"

CVRStructEffect::CVRStructEffect()
{
	//Libera as estruturas do efeito
	ZeroMemory( &customForce, sizeof( customForce ) );
	ZeroMemory( &envelope, sizeof( envelope ) );
	ZeroMemory( &periodic, sizeof( periodic ) );
	ZeroMemory( &constantForce, sizeof( constantForce) );
    ZeroMemory( &effect, sizeof( effect) );
	ZeroMemory( &conditForce, sizeof( conditForce ) );

	//tamanho das estruturas DIEFFECT e DIENVELOPE
	effect.dwSize             = sizeof(DIEFFECT); 
	envelope.dwSize           = sizeof(DIENVELOPE);

	//seta o valor default de lMagnitude para DI_FFNOMINALMAX(10000)
	constantForce.lMagnitude = DI_FFNOMINALMAX;

	//initiacializa os eixos X, Y, e Z do joystick na posição 0(zero)
	axesDirection[0] = 0;
	axesDirection[1] = 0;
	axesDirection[2] = 0;
}

CVRStructEffect::~CVRStructEffect()
{
}

//**************Funções da estrutura DIEFFECT**************************

void CVRStructEffect::setDIEFFECT( DIEFFECT diEffect )
{
	effect.cAxes                   = diEffect.cAxes;
	effect.cbTypeSpecificParams    = diEffect.cbTypeSpecificParams;
	effect.dwDuration              = diEffect.dwDuration;
	effect.dwFlags                 = diEffect.dwFlags;
	effect.dwGain                  = diEffect.dwGain;
	effect.dwSamplePeriod          = diEffect.dwSamplePeriod;
	effect.dwSize                  = diEffect.dwSize;
	effect.dwStartDelay            = diEffect.dwStartDelay;
	effect.dwTriggerButton         = diEffect.dwTriggerButton;
	effect.dwTriggerRepeatInterval = diEffect.dwTriggerRepeatInterval;
	effect.lpEnvelope              = diEffect.lpEnvelope;
	effect.lpvTypeSpecificParams   = diEffect.lpvTypeSpecificParams;
	effect.rgdwAxes                = diEffect.rgdwAxes;
	effect.rglDirection            = diEffect.rglDirection;
}

void CVRStructEffect::Release()
{
	//Libera as estruturas do efeito
	ZeroMemory( &customForce, sizeof( customForce ) );
	ZeroMemory( &envelope, sizeof( envelope ) );
	ZeroMemory( &periodic, sizeof( periodic ) );
	ZeroMemory( &constantForce, sizeof( constantForce) );
    ZeroMemory( &effect, sizeof( effect) );
	ZeroMemory( &conditForce, sizeof( conditForce ) );
}

void CVRStructEffect::setFlagsEffect( DWORD flag )
{
	effect.dwFlags = flag;
}

void CVRStructEffect::setDurationEffect( DWORD duration )
{
	effect.dwDuration = duration;
}

void CVRStructEffect::setPeriodEffect( DWORD period )
{
	effect.dwSamplePeriod = period;
}

void CVRStructEffect::setGainEffect( DWORD gain )
{
	effect.dwGain = gain;
}

void CVRStructEffect::setButtonEffect( DWORD button, DWORD rInterval )
{
	effect.dwTriggerButton          = button;
	effect.dwTriggerRepeatInterval  = rInterval;
}

void CVRStructEffect::setAxesEffect( LPDWORD vectorAxes, DWORD countAxes )
{
	effect.rgdwAxes = vectorAxes;
	effect.cAxes    = countAxes;
}

void CVRStructEffect::setNumAxesEffect( DWORD countAxes )
{
	effect.cAxes    = countAxes;
}

void CVRStructEffect::setDirectionEffect( int directionX, int directionY = 0 )
{
	axesDirection[0] = directionX;
	axesDirection[1] = directionY;
	axesDirection[2] = 0; // valor do eixo Z NULO
	effect.rglDirection = axesDirection;
}

void CVRStructEffect::setDirectionEffect( int directionX, int directionY = 0, 
										  int directionZ = 0 )
{
	axesDirection[0] = directionX;
	axesDirection[1] = directionY;
	axesDirection[2] = directionZ;
	effect.rglDirection = axesDirection;
}

void CVRStructEffect::setEnvelopeEffect( LPDIENVELOPE envelope )
{
	effect.lpEnvelope = envelope;
}

void CVRStructEffect::setTypeSpecificParamsEffect( LPVOID lType ,DWORD cType )
{
	effect.lpvTypeSpecificParams = lType;
	effect.cbTypeSpecificParams  = cType;
}

void CVRStructEffect::setDelayEffect( DWORD delay )
{
	effect.dwStartDelay = delay;
}

//***************Funções da estrutura DICONDITION**********************

void CVRStructEffect::setDICONDITION( DICONDITION diCONDITION )
{
	conditForce.dwNegativeSaturation = diCONDITION.dwNegativeSaturation;
	conditForce.dwPositiveSaturation = diCONDITION.dwNegativeSaturation;
	conditForce.lDeadBand            = diCONDITION.dwNegativeSaturation;
	conditForce.lNegativeCoefficient = diCONDITION.dwNegativeSaturation;
	conditForce.lOffset              = diCONDITION.dwNegativeSaturation;
	conditForce.lPositiveCoefficient = diCONDITION.dwNegativeSaturation;
		
}  

void CVRStructEffect::setIoffset( LONG ioffset )
{
	conditForce.lOffset = ioffset;
}

void CVRStructEffect::setLpositiveCoefficient( LONG pCoefficient )
{
	conditForce.lPositiveCoefficient = pCoefficient;
}

void CVRStructEffect::setLnegativeCoefficient( LONG nCoefficient )
{
	conditForce.lNegativeCoefficient = nCoefficient;
}

void CVRStructEffect::setDwPositiveSaturation( DWORD pSaturation )
{
	conditForce.dwPositiveSaturation = pSaturation;
}

void CVRStructEffect::setDwNegativeSaturation( DWORD nSaturation )
{
	conditForce.dwNegativeSaturation = nSaturation;
}

void CVRStructEffect::setLdeadBand( LONG dBand )
{
	conditForce.lDeadBand = dBand;
}

//*****************Funções da estrutura DICUSTOMFORCE******************

void CVRStructEffect::setDICUSTOMFORCE( DICUSTOMFORCE diCUSTOMFORCE )
{
	customForce.cChannels      = diCUSTOMFORCE.cChannels;
	customForce.cSamples       = diCUSTOMFORCE.cSamples;
	customForce.dwSamplePeriod = diCUSTOMFORCE.dwSamplePeriod;
	customForce.rglForceData   = diCUSTOMFORCE.rglForceData;
}

void CVRStructEffect::setCchannels( DWORD channels )
{
	customForce.cChannels = channels;
}

void CVRStructEffect::setDwSamplePeriod( DWORD dSamplePeriod )
{
	customForce.dwSamplePeriod = dSamplePeriod;
}

void CVRStructEffect::setCsamples( DWORD samples )
{
	customForce.cSamples = samples;
}

void CVRStructEffect::setRglForceData( LPLONG rForceData )
{
	customForce.rglForceData = rForceData;
}

//****************Funções da estrutura DIENVELOPE**********************

void CVRStructEffect::setDIENVELOPE( DIENVELOPE diENVELOPE )
{
	envelope.dwAttackLevel = diENVELOPE.dwAttackLevel;
	envelope.dwAttackTime  = diENVELOPE.dwAttackTime;
	envelope.dwFadeLevel   = diENVELOPE.dwFadeLevel;
	envelope.dwFadeTime    = diENVELOPE.dwFadeTime;
	envelope.dwSize        = diENVELOPE.dwSize;
}
        
void CVRStructEffect::setDwAttackLevel( DWORD dAttackLevel )
{
	envelope.dwAttackLevel = dAttackLevel;
}

void CVRStructEffect::setDwAttackTime( DWORD dAttackTime )
{
	envelope.dwAttackTime = dAttackTime;
}

void CVRStructEffect::setDwFadeLevel( DWORD dFadeLevel )
{
	envelope.dwFadeLevel = dFadeLevel;
}

void CVRStructEffect::setDwFadeTime( DWORD dFadeTime )
{
	envelope.dwFadeTime = dFadeTime;
}

//**************Funções da estrutura DIPERIODIC************************

void CVRStructEffect::setDIPERIODIC( DIPERIODIC  diPERIODIC )
{
	periodic.dwMagnitude = diPERIODIC.dwMagnitude;
	periodic.dwPeriod    = diPERIODIC.dwPeriod;
	periodic.dwPhase     = diPERIODIC.dwPhase;
	periodic.lOffset     = diPERIODIC.lOffset;	
}
        
void CVRStructEffect::setDwMagnitude( DWORD dMagnitude )
{
	periodic.dwMagnitude = dMagnitude;
}

void CVRStructEffect::setLoffset( LONG loffset )
{
	periodic.lOffset = loffset;
}

void CVRStructEffect::setDwPhase( DWORD dPhase )
{
	periodic.dwPhase = dPhase;
}

void CVRStructEffect::setDwPeriod( DWORD dPeriod )
{
	periodic.dwPeriod = dPeriod;
}

//***************Função da estrutura DICONSTANTFORCE*******************

void CVRStructEffect::setConstantForce( LONG cForce )
{
	constantForce.lMagnitude = cForce; 
}
