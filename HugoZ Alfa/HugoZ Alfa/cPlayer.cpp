#pragma once

#include "hPlayer.h"
#include "hGlobais.h"

Player::Player() {
}

//--------------------------------------------------
// Construtor da classe.
// Recebe o id por parâmetro e instancia um objeto Player com todas as informações.
//--------------------------------------------------
Player::Player(int p_id) {
	D3DXVECTOR3 dxvWorldLocation;
	int intItemId;

	this->intId = p_id;
	this->blnValido = false;
	this->dwdAddress = (DWORD)Global::getInstance()->objGameClient.GetPlayerByIndex(this->intId);

	//Verifica se o objeto localizado é do tipo Player
	if (Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::ObjectManagerID) == GameData::Player) {
		dxvWorldLocation = Global::getInstance()->objMemoria.LerMemoria<D3DXVECTOR3>(this->dwdAddress + GameData::LocationAddress);
		
		this->intDistancia = D3DXVec3Length(&(Global::getInstance()->objMe.dxvLocation - dxvWorldLocation));

		//Verifica se o Player está dentro da distância limite e incrementa o contador.
		if (this->intDistancia > Config::intMaxDistancePlayer) {
			return;
		} else if(this->dwdAddress != Global::getInstance()->objMe.dwdAddress) {
			Global::getInstance()->objMe.intPlayersAround++;
		}

		//Verifica se o Player está na direção da câmera
		if (Global::getInstance()->objRenderizador.WorldToScreen(&dxvWorldLocation, &this->dxvLocation)) {

			if (Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerIsDead) == 0) {
				this->blnVivo = true;
				this->intHP = Global::getInstance()->objMemoria.LerMemoria<float>(this->dwdAddress + GameData::PlayerHP);
			} else {
				this->blnVivo = false;
				return;
			}

			this->strNome = getNome();

			this->objArmaPrimaria = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerPrimaryWeapon);
			this->objArmaSecundaria = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerSecondaryWeapon);
			this->objColete = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerChest);
			this->objCapacete = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerHelmet);
			this->objMochila = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerBag);

			if (this->objArmaPrimaria.strNome.compare("") == 0) {
				this->objArmaPrimaria.strNome = "Empty";
			}
			if (this->objArmaSecundaria.strNome.compare("") == 0) {
				this->objArmaSecundaria.strNome = "Empty";
			}
			if (this->objCapacete.strNome.compare("") == 0) {
				this->objCapacete.strNome = "Empty";
			}
			if (this->objColete.strNome.compare("") == 0) {
				this->objColete.strNome = "Empty";
			}

			this->blnValido = true;
		}
	}
}

//--------------------------------------------------
// Obtem o nome do Player.
//--------------------------------------------------
string Player::getNome() {
	string strNomePlayer;
	int intTamanhoNome;

	intTamanhoNome = Global::getInstance()->objMemoria.LerMemoria<int>(this->dwdAddress + GameData::PlayerNameLength);

	for (int i = 0; i < intTamanhoNome; i++) {
		strNomePlayer += Global::getInstance()->objMemoria.LerMemoria<unsigned char>(this->dwdAddress + GameData::PlayerName + i) ^ i - 87;
	}

	return strNomePlayer;
}