#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "hItem.h"

using namespace std;

class Player {
private:
	int getDistancia(D3DXVECTOR3 Referencia);
	string getNome();

public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	int intId;
	string strNome;
	Item objArmaPrimaria;
	Item objArmaSecundaria;
	Item objColete;
	Item objCapacete;
	Item objMochila;
	int intDistancia;
	float intHP;
	bool blnValido;
	bool blnVivo;

	int intPlayersAround;

	DWORD dwdAddress;
	D3DXVECTOR3 dxvLocation;

	Player();
	Player(int p_id);
};