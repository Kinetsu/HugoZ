#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <Windows.h>

using namespace std;

//--------------------------------------------------
//	As classes abaixo utilizam um recurso chamado "padding", que na prática significa causar espaçamento entre as variáveis.
//	Isto é utilizado porque na função de leitura de memória, podemos ler um grande range e obter várias informações em apenas
//		uma leitura de memória, o que economiza processamento.
//	As variáveis precisam estar na "distância" correta pois o resultado que vier da leitura da memória deve bater exatamente
//		com a posição das variáveis da classe.
//--------------------------------------------------

class CBone {
public:
	char*       m_BoneName;     //0x00   
	char        pad_04[136];       //0x04 
	D3DXMATRIX  BoneMatrix;   //0x8C   
	D3DXMATRIX  SomeMatrix;  //0xCC   
};


class CBoneInfo {
public:
	char       pad_00[20];
	DWORD      oneNum;          //0x18  
	CBone*     pBones;            //0x1C  
};


class CSkeleton {
public:
	char       pad_00[40];
	CBoneInfo* BonePtr;         //0x28  
};

D3DXVECTOR3 GetBoneOrigin(DWORD pPlayer, int iBoneID);
void GetSkeleton(DWORD pPlayer, int vetEsqueleto[], D3DXVECTOR3 Retorno[]);

enum enmIdBones {
	Desconhecido = 0,
	Pelvis = 1,
	Coluna0 = 2,
	Coluna1 = 3,
	Coluna2 = 4,
	Pescoco = 5,
	Cabeca = 6,
	ClaviculaEsquerda = 7,
	BracoEsquerdo = 8,
	AntebracoEsquerdo = 9,
	MaoEsquerda = 10,
	DedoEsquerdo0 = 11,
	DedoEsquerdo01 = 12,
	DedoEsquerdo02 = 13,
	DedoEsquerdo1 = 14,
	DedoEsquerdo11 = 15,
	DedoEsquerdo12 = 16,
	DedoEsquerdo2 = 17,
	DedoEsquerdo21 = 18,
	DedoEsquerdo22 = 19,
	DedoEsquerdo3 = 20,
	DedoEsquerdo31 = 21,
	DedoEsquerdo32 = 22,
	DedoEsquerdo4 = 23,
	DedoEsquerdo41 = 24,
	DedoEsquerdo42 = 25,
	Bip01_L_ForeTwist = 26,
	Bip01_L_ForeTwist1 = 27,
	ClaviculaDireita = 28,
	BracoDireito = 29,
	AntebracoDireito = 30,
	MaoDireita = 31,
	DedoDireito0 = 32,
	DedoDireito01 = 33,
	DedoDireito02 = 34,
	DedoDireito1 = 35,
	DedoDireito11 = 36,
	DedoDireito12 = 37,
	DedoDireito2 = 38,
	DedoDireito21 = 39,
	DedoDireito22 = 40,
	DedoDireito3 = 41,
	DedoDireito31 = 42,
	DedoDireito32 = 43,
	DedoDireito4 = 44,
	DedoDireito41 = 45,
	DedoDireito42 = 46,
	PrimaryWeaponBone = 47,
	Bip01_R_ForeTwist = 48,
	Bip01_R_ForeTwist1 = 49,
	Weapon_BackLeft = 50,
	Weapon_BackRPG = 51,
	Weapon_BackRight = 52,
	PernaEsquerda = 53,
	JoelhoEsquerdo = 54,
	PeEsquerdo = 55,
	DedaoEsquerdo = 56,
	Weapon_Side = 57,
	PernaDireita = 58,
	JoelhoDireito = 59,
	PeDireito = 60,
	DedaoDireito = 61
};