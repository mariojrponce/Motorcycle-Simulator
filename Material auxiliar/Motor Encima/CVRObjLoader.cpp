/***********************************************************************
*Nome: CVRObjLoader.cpp
*Descrição: Implementação da classe responsável pela importação do OBJ
*Data: 24/10/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRObjLoader.h"
#include "CVRLog.h"
#include "CVRImage.h"

int contfaces=0;

/***********************************************************
*Name: CVRObjLoader()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObjLoader::CVRObjLoader()
{
	uiListId = 0;
	bGeometry = false;
	image = NULL;
	sprintf(sWorkDirectory,"");
}

/***********************************************************
*Name: ~CVRObjLoader()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObjLoader::~CVRObjLoader()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRObjLoader::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name: Load()
*Description: carrega o objeto
*Params: char*
*Return: bool
************************************************************/
bool CVRObjLoader::Load(char* fileName, bool bGetGeometry)
{
	char* extName=NULL;

	char fName[STRINGSIZE];
	sprintf(fName,"%s%s",sWorkDirectory,fileName);
	
	extName = strchr(fileName, '.');
	extName++;

	bGeometry = bGetGeometry;

	//Verifica se é um arquivo obj
	if (!(strcmp(extName, "obj") == 0) && (strcmp(extName, "OBJ") == 0))
	{
		return false;
	}

	//Le o arquivo
	if (!ReadFile(fName))
	{
		return false;
	}

	//Cria a lista de visualização
	CreateViewList();

	// Obtem os vértices do objeto
	CVRVector* vVertexObj = new CVRVector[vVertex.size()];
	for(int i = 0; i < (long int)vVertex.size(); i++)
	{
		vVertexObj[i].SetX(vVertex[i].x);
		vVertexObj[i].SetY(vVertex[i].y);
		vVertexObj[i].SetZ(vVertex[i].z);
	}

	
	// Calcula os boundings
	CalculateBoundings(vVertexObj, (long int)vVertex.size());

	//Limpa o vetor de vértices
	if (!bGetGeometry)
	{
		if (vVertex.size())
		{
			vVertex.clear();
		}
	}

	return true;
}

/***********************************************************
*Name: GetGeometry()
*Description: devolve a geometria do objeto
*Params: Nenhum
*Return: vector<stVertex>
************************************************************/
vector<stVertex> CVRObjLoader::GetGeometry()
{
	return vVertex;
}

/***********************************************************
*Name: GetGroup
*Description: devolve os grupos que compoe o objeto
*Params: Nenhum
*Return: vector<stGroup>
************************************************************/
vector<stGroup> CVRObjLoader::GetGroups()
{
	return vGroup;
}

/***********************************************************
*Name: ReadFile()
*Description: faz a leitura do arquivo
*Params: char*
*Return: bool
************************************************************/
bool CVRObjLoader::ReadFile(char* fileName)
{
	FILE* file = NULL;
	char sLine[STRINGSIZE];

	file = fopen(fileName,"rt");

	//Verifica se o arquivo existe
	if (!file)
	{
		return false;
	}

	//Enquanto nao for final de arquivo
	while(!feof(file))
	{
		//Le uma linha do arquivo
		fgets(sLine,STRINGSIZE,file);

		//Carrega os materiais
		if (strlen(sLine)>1 && strstr(sLine,"mtllib"))
		{
			char* matName = strtok(sLine," \n");
			matName = strtok(NULL," \n");
			LoadMaterial(matName);
		}
		//Adiciona um novo grupo de faces
		else if (strlen(sLine)>1 && strstr(sLine,"usemtl"))
		{
			char* matName = strtok(sLine," \n");
			matName = strtok(NULL," \n");
			AddGroup(matName);
		}
		//Trata as linhas que começam com v
		else if (strlen(sLine)>1 && sLine[0] == 'v')
		{
			//Adiciona um vértice
			if (sLine[1] == ' ' || sLine[1] == '\t')
			{
				AddVertex(sLine);
			}
			//Adiciona uma normal
			else if (sLine[1] == 'n')
			{
				AddNormal(sLine);
			}
			//Adiciona um a coordenada de textura
			else if (sLine[1] == 't')
			{
				AddTexture(sLine);
			}
		}
		//Trata as linhas que começam com f
		else if (strlen(sLine)>1 && sLine[0] == 'f')
		{
			AddFace(sLine);
		} 
	}
	fclose(file);
	return true;
}

/***********************************************************
*Name: AddVertex()
*Description: adiciona um vértice
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::AddVertex(char* line)
{
	sVertex temp;
	sscanf(line,"v %f %f %f",&temp.x,&temp.y, &temp.z);
	vVertex.push_back(temp);
}

/***********************************************************
*Name: AddNormal()
*Description: adiciona uma normal
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::AddNormal(char* line)
{
	sNormal temp;
	sscanf(line,"vn %f %f %f",&temp.x,&temp.y, &temp.z);
	vNormal.push_back(temp);
}

/***********************************************************
*Name: AddTexture()
*Description: adiciona uma coordenada de textura
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::AddTexture(char* line)
{
	sTexture temp;
	sscanf(line,"vt %f %f %f",&temp.s,&temp.t, &temp.u);
	vTexture.push_back(temp);
}

/***********************************************************
*Name: AddFace()
*Description: adiciona uma face
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::AddFace(char* line)
{
	int tokens=0;
	tokens = CountTokens(line);
	sFace temp;

	//Le a face conforme o seu formato
	if (tokens == 1)
	{
		temp.format = 1;
		char* matName = strtok(line," \n");
		matName = strtok(NULL," \n");
		while(matName)
		{
			long int vet[3];
			sscanf(matName,"%d/%d/%d",&vet[0],&vet[1],&vet[2]);
			temp.vIndex.push_back(vet[0]);
			temp.vTexture.push_back(vet[1]);
			temp.vNormal.push_back(vet[2]);
			matName = strtok(NULL," \n");
		}
	}
	else if (tokens == 2)
	{
		temp.format = 2;
		char* matName = strtok(line," \n");
		matName = strtok(NULL," \n");
		while(matName)
		{
			long int vet[2];
			sscanf(matName,"%d//%d",&vet[0],&vet[1]);
			temp.vIndex.push_back(vet[0]);
			temp.vNormal.push_back(vet[1]);
			matName = strtok(NULL," \n");
		}
	}
	else if (tokens == 0)
	{
		temp.format = 0;
		char* matName = strtok(line," \n");
		matName = strtok(NULL," \n");
		while(matName)
		{
			long int vet;
			sscanf(matName,"%d//%d",&vet);
			temp.vIndex.push_back(vet);
			matName = strtok(NULL," \n");
		}
	}

	//Certifica-se que tenha pelo menos um grupo
	if (!vGroup.size())
	{
		sGroup group;
		vGroup.push_back(group);
	}

	//Adiciona a face ao grupo
	vGroup[vGroup.size()-1].vFace.push_back(temp);
}

/***********************************************************
*Name: AddGroup()
*Description: adiciona um grupo
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::AddGroup(char* line)
{
	sGroup temp;
	temp.material = NULL;
	temp.material = GetMaterial(line);
	vGroup.push_back(temp);
}

/***********************************************************
*Name: CountTokens()
*Description: conta o total de barras na linha
*Params: char*
*Return: int
************************************************************/
int CVRObjLoader::CountTokens(char* line)
{
	if (strstr(line,"//"))
	{
		return 2;
	}
	else if (strstr(line,"/"))
	{
		return 1;
	}
	
	return 0;
}

/***********************************************************
*Name: GetMaterial()
*Description: método que retorna um material com base no nome
*Params: char*
*Return: sMaterial*
************************************************************/
sMaterial* CVRObjLoader::GetMaterial(char* material)
{
	for (int iIndex=0; iIndex<(int)vMaterial.size(); iIndex++)
	{
		if (strcmp(material,vMaterial[iIndex].name)==0)
		{
			return &vMaterial[iIndex];
		}
	}
	return NULL;
}

/***********************************************************
*Name: LoadMaterial()
*Description: carrega o arquivo de materiais
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::LoadMaterial(char* line)
{
	FILE* file = NULL;
	char sLine[STRINGSIZE];
	char fileName[STRINGSIZE];
	char matAttrib[STRINGSIZE];

	//Configura o nome e diretorio do material
	sprintf(fileName,"%s%s",this->sWorkDirectory,line);

	//Abre o arquivo e certifica-se que foi aberto
	file = fopen(fileName,"rt");
	if (!file)
	{
		LOG->WriteToLog("Erro ","Material nao pode ser aberto");
		return;
	}

	//Enquanto nao for final de arquivo
	while(!feof(file))
	{
		//Le uma linha do arquivo
		fgets(sLine,STRINGSIZE,file);

		//Inicio de um novo material
		if(strstr(sLine,"newmtl"))
		{
			//Cria um novo material e configura o nome
			sMaterial temp;
			temp.texId = 0;
			sscanf(sLine,"newmtl %s",&temp.name);

			//Le a proxima linha do arquivo
			fgets(sLine,STRINGSIZE,file);

			//Carrega o resto do material
			while (sLine[0]=='\t')
			{
				//Le a linha atual
				sscanf(sLine,"\t %s",matAttrib);

				//Componente diffuso
				if (strcmp(matAttrib,"Kd")==0)
				{
					sscanf(sLine,"\t Kd %f %f %f", &temp.diffuse[0], &temp.diffuse[1], &temp.diffuse[2]);
				}
				//Componente especular
				else if (strcmp(matAttrib,"Ks")==0)
				{
					sscanf(sLine,"\t Ks %f %f %f", &temp.specular[0], &temp.specular[1], &temp.specular[2]);
				}
				//Componente ambiente
				else if (strcmp(matAttrib,"Ka")==0)
				{
					sscanf(sLine,"\t Ka %f %f %f", &temp.ambient[0], &temp.ambient[1], &temp.ambient[2]);
				}
				//Componente de textura
				else if (strcmp(matAttrib,"map_Kd")==0)
				{
					char imageName[STRINGSIZE];
					char fullName[STRINGSIZE];
					sscanf(sLine,"\t map_Kd %s",imageName);
					sprintf(fullName,"%s%s",this->sWorkDirectory,imageName);

					//Testa se o graphics manager está ativo
					if (!pGraphicsManager)
					{
						return;
					}

					//Obtem o Image Id
					temp.texId  = pGraphicsManager->GetBindImage(fullName);

					if (!temp.texId)
					{
						//Carrega a textura
						image = pGraphicsManager->LoadImage(fullName,false);

						//Testa se foi carregada
						if (image && image->GetImageData())
						{
							glGenTextures(1,&temp.texId);
							glBindTexture(GL_TEXTURE_2D, temp.texId);
							glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); 
							glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
							gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->GetImageWidth(), image->GetImageHeight(), GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
							pGraphicsManager->AddBindImage(fullName,temp.texId);
						}
					}
				}
				fgets(sLine,STRINGSIZE,file);
			}
			vMaterial.push_back(temp);
		}
	}
}

/***********************************************************
*Name: CreateViewList()
*Description: método que acria a lista de visualização
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRObjLoader::CreateViewList()
{
	//Obtem o identificador da lista e testa
	uiListId = glGenLists(1);
	if (!uiListId)
	{
		return false;
	}

	//Cria a Lista de visualização
	glNewList(uiListId,GL_COMPILE);

	//Passa por todos os grupos
	for (int iIndex=0; iIndex<(int)vGroup.size();iIndex++)
	{
		//Verifica se o grupo tem material e textura
		if (vGroup[iIndex].material)
		{
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vGroup[iIndex].material->diffuse);
			//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,vGroup[iIndex].material->ambient);
			//glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,vGroup[iIndex].material->specular);
			if (vGroup[iIndex].material->texId)
			{
				glBindTexture(GL_TEXTURE_2D,vGroup[iIndex].material->texId);
			}
		}


		//Passa por todas as faces do grupo
		for (int jIndex=0; jIndex<(int)vGroup[iIndex].vFace.size(); jIndex++)
		{
			//Verifica o formato da face
			if (vGroup[iIndex].vFace[jIndex].format == 1)
			{
				glBegin(GL_POLYGON);
				for (int vIndex=0; vIndex<(int)vGroup[iIndex].vFace[jIndex].vIndex.size();vIndex++)
				{
					glTexCoord2f(vTexture[vGroup[iIndex].vFace[jIndex].vTexture[vIndex]-1].s,vTexture[vGroup[iIndex].vFace[jIndex].vTexture[vIndex]-1].t);
					glNormal3f(vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].x, vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].y, vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].z);
					glVertex3f(vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].x, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].y, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].z);
				}
				glEnd();
			}
			else if (vGroup[iIndex].vFace[jIndex].format == 2)
			{
				//glDisable(GL_TEXTURE_2D);
				glBegin(GL_POLYGON);
				for (int vIndex=0; vIndex<(int)vGroup[iIndex].vFace[jIndex].vIndex.size();vIndex++)
				{
					glNormal3f(vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].x, vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].y, vNormal[vGroup[iIndex].vFace[jIndex].vNormal[vIndex]-1].z);
					glVertex3f(vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].x, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].y, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].z);
				}
				glEnd();
			}
			else if (vGroup[iIndex].vFace[jIndex].format == 0)
			{
				//glDisable(GL_TEXTURE_2D);
				glBegin(GL_POLYGON);
				for (int vIndex=0; vIndex<(int)vGroup[iIndex].vFace[jIndex].vIndex.size();vIndex++)
				{
					glVertex3f(vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].x, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].y, vVertex[vGroup[iIndex].vFace[jIndex].vIndex[vIndex]-1].z);
				}
				glEnd();
			}
		}
	}
	//Zera o id da textura
	glBindTexture(GL_TEXTURE_2D,0);
	glEndList();
	FreeResources();
	return true;
}

/***********************************************************
*Name: Render()
*Description: renderiza o objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjLoader::Render()
{
	//verifica se a lista existe e se é visível
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	if (uiListId && bVisible)
	{
		glPushMatrix();
			glTranslatef(vPos.x,vPos.y,vPos.z);
			glRotatef(vAngle.x,1.0f,0.0f,0.0f);
			glRotatef(vAngle.y,0.0f,1.0f,0.0f);
			glRotatef(vAngle.z,0.0f,0.0f,1.0f);
			glScalef(vScale.x,vScale.y,vScale.z);
			glCallList(uiListId);
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

/***********************************************************
*Name: SetWorkDirectory()
*Description: configura o diretorio de materiais
*Params: char*
*Return: Nenhum
************************************************************/
void CVRObjLoader::SetWorkDirectory(char* dir)
{
	sprintf(sWorkDirectory,"%s",dir);
}

/***********************************************************
*Name: GetWorkDirectory()
*Description: retorna o diretorio de materiais
*Params: Nenhum
*Return: char*
************************************************************/
char* CVRObjLoader::GetWorkDirectory()
{
	return sWorkDirectory;
}

/***********************************************************
*Name: Update()
*Description: atualiza o obj
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjLoader::Update()
{
	//Chama o update do pai
	CVRObject3D::Update();
}

/***********************************************************
*Name: Release()
*Description: método que libera todos os recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjLoader::Release()
{
	//Limpa o vetor de vértices
	if (vVertex.size())
	{
		vVertex.clear();
	}

	//Limpa o vetor de normais
	if (vNormal.size())
	{
		vNormal.clear();
	}

	//Limpa o vetor de coord. texturas
	if (vTexture.size())
	{
		vTexture.clear();
	}

	//Limpa os grupos com suas faces
	if (vGroup.size())
	{
		for (int iIndex = 0; iIndex<(int)vGroup.size();iIndex++)
		{
			vGroup[iIndex].material = NULL;
			for (int jIndex = 0; jIndex < (int)vGroup[iIndex].vFace.size(); jIndex++)
			{
				vGroup[iIndex].vFace[jIndex].vIndex.clear();
				vGroup[iIndex].vFace[jIndex].vNormal.clear();
				vGroup[iIndex].vFace[jIndex].vTexture.clear();
			}
			vGroup[iIndex].vFace.clear();
		}
		vGroup.clear();
	}

	//Limpa o vetor de materiais
	if (vMaterial.size())
	{
		for (int iIndex=0; iIndex<(int)vMaterial.size(); iIndex++)
		{
			pGraphicsManager->ReleaseBindImage(vMaterial[iIndex].texId);
		}
		vMaterial.clear();
	}

	//Libera a lista de visualização
	if (uiListId != 0)
	{
		glDeleteLists(uiListId,1);
	}

	//Libera a imagem
	if (image)
	{
		pGraphicsManager->DeleteImage(&image);
		image = NULL;
	}
}

/***********************************************************
*Name: FreeResources()
*Description: método que libera os vectors
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjLoader::FreeResources()
{
	//Limpa o vetor de normais
	if (vNormal.size())
	{
		vNormal.clear();
	}

	//Limpa o vetor de coord. texturas
	if (vTexture.size())
	{
		vTexture.clear();
	}

	//Limpa os grupos com suas faces
	if (vGroup.size() && !bGeometry)
	{
		for (int iIndex = 0; iIndex<(int)vGroup.size();iIndex++)
		{
			vGroup[iIndex].material = NULL;
			vGroup[iIndex].vFace.clear();
		}
		vGroup.clear();
	}
}

/***********************************************************
*Name: GetListId()
*Description: retorna o identificador da lista
*Params: Nenhum
*Return: unsigned int
************************************************************/
unsigned int CVRObjLoader::GetListId()
{
	return uiListId;
}

