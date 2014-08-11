#pragma once

#include <windows.h>

#include "hConfigs.h"
#include "hGameData.h"
#include "hDirectX.h"

//--------------------------------------------------
//	As classes abaixo utilizam um recurso chamado "padding", que na pr�tica significa causar espa�amento entre as vari�veis.
//	Isto � utilizado porque na fun��o de leitura de mem�ria, podemos ler um grande range e obter v�rias informa��es em apenas
//		uma leitura de mem�ria, o que economiza processamento.
//	As vari�veis precisam estar na "dist�ncia" correta pois o resultado que vier da leitura da mem�ria deve bater exatamente
//		com a posi��o das vari�veis da classe.
//--------------------------------------------------

//--------------------------------------------------
//Descri��o: Esta classe fornece informa��es sobre o GameWorld.
//--------------------------------------------------
class GameWorld {
public:
	char _0x0000[8];
	__int32 m_Counter;             //0x0008
	char _0x000C[32];
	DWORD m_MaxObjects;            //0x002C  XOR
	char _0x0030[20];
	DWORD m_ObjectList;            //0x0044  XOR

	DWORD GetMaxObjetos();
	DWORD GetObjeto(int p_intId);
};

//--------------------------------------------------
//Descri��o: Esta classe fornece informa��es sobre o GameClient.
//--------------------------------------------------
class  GameClient {
public:
	//Alterado - A classe ficou muito grande, � mais vantagem ler o endere�o espec�fico.
	//char _pad[0x920];
	DWORD dwListaJogadores[GameData::intMaxPlayers];

public:
	DWORD* GetPlayerByIndex(int p_intIndex);
};

//--------------------------------------------------
//Descri��o: Esta classe fornece informa��es sobre o Renderizador.
//--------------------------------------------------
class Renderizador {
public:
	char _pad0[24];
	int m_width;
	int m_height;
	char _pad1[48];
	IDirect3DDevice9* m_pDevice;
	char _pad2[332]; //0x0054
	D3DXMATRIX m_matrices[8];

public:
	IDirect3DDevice9* objDispositivo3D;

	void setDispositivo3D(IDirect3DDevice9* p_objDispositivo3D);
	int WorldToScreen(D3DXVECTOR3* pvPos, D3DXVECTOR3* pvOut);
};