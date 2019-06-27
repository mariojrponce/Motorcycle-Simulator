/***********************************************************************
*Nome: CVRImage.h
*Descrição: Cabeçalho da classe responsável pelo carregamento de imagens
*Data: 18/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRIMAGE_
#define _CVRIMAGE_

//Bibliotecas
#include "CVRObject.h"

// Identificador universal do bmp
#define BITMAP_ID 0x4D42

//Estrutura que define o color key
typedef struct sColorKey
{
	short int R;
	short int G;
	short int B;
}COLORKEY;

//Estrutura de cabeçalho para o PCX
typedef struct
{
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} PCXHEADER;

//Estrutura de cabeçalho para TGA
typedef struct
{
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
	unsigned char *imageData;
}TGAFILE;

//Classe que faz o carregamento das imagens
class CVRImage: public CVRObject
{
//Atributos da imagem
private:
	unsigned char *imageData;
	char imageName[STRINGSIZE];
	int height;
	int width;
	COLORKEY colorKey;
//Metodos publicos da Imagem
public:
	CVRImage();
	~CVRImage();
	unsigned char* GetImageData();
	char* GetImageName();
	int GetImageWidth();
	int GetImageHeight();
	void Release();
	bool LoadImage(char *, bool);
	bool LoadImage(char *, char*);
	void SetColorKey(short int, short int, short int);
	int iReferences;
	bool bAlpha;

//Metodos privados da Imagem
private:
	bool LoadBmpFile(char *);
	bool LoadPcxFile(char *);
	bool LoadBmpAlphaFile(char *);
	bool LoadTGAFile(char *);
};
#endif