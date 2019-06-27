/***********************************************************************
*Nome: CVRObjLoader.h
*Descrição: Cabeçalho da classe que o loader OBJ
*Data: 24/10/07
*Local: LNCC
************************************************************************/

#ifndef _CVROBJLOADER_
#define _CVROBJLOADER_

#include "CVRObject3D.h"


//Estrutura responsável por guardar informações sobre os vértices
typedef struct stVertex
{
	float x;
	float y;
	float z;
}sVertex;

//Estrutura responsável por guardar informações das normais
typedef struct stNormal
{
	float x;
	float y;
	float z;
}sNormal;

//Estrutura responsável por guardar as informações para cada textura
typedef struct stTexture
{
	float s;
	float t;
	float u;
}sTexture;

//Estrutura responsável por guardar informações sobre o material
typedef struct stMaterial
{
	char name[STRINGSIZE];
	float diffuse[3];
	float specular[3];
	float ambient[3];
	unsigned int texId;
}sMaterial;

//Estrutura responsável por guardar informações de cada face
typedef struct stFace
{
	vector<long int> vIndex;
	vector<long int> vNormal;
	vector<long int> vTexture;
	unsigned int format;
}sFace;

//Estrutura responsável por guardar um grupo de faces
typedef struct stGroup
{
	vector<stFace> vFace;
	sMaterial* material;
}sGroup;

class CVRObjLoader:public CVRObject3D
{
private:
	unsigned int uiListId;
	vector<sVertex> vVertex;
	vector<sNormal> vNormal;
	vector<sTexture> vTexture;
	vector<sMaterial> vMaterial;
	vector<sGroup> vGroup;
	char sWorkDirectory[STRINGSIZE];
	CVRImage* image;
	bool bGeometry;

public:
	CVRObjLoader();
	~CVRObjLoader();
	bool Load(char* fileName = NULL, bool bGetGeomety=false);
	bool ReadFile(char*);
	void AddVertex(char*);
	void AddNormal(char*);
	void AddFace(char*);
	void AddTexture(char*);
	void AddGroup(char*);
	int CountTokens(char*);
	sMaterial* GetMaterial(char*);
	void Release();
	char* GetWorkDirectory();
	void SetWorkDirectory(char*);
	void LoadMaterial(char*);
	void FreeResources();
	bool CreateViewList();
	void Render();
	bool Init();
	void Update();
	unsigned int GetListId();
	vector<stVertex> GetGeometry();
	vector<stGroup> GetGroups();
};
#endif