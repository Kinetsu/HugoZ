#pragma once

#include "hESP.h"
#include "hGlobais.h"
#include "hPlayer.h"
#include "hPlayerSkeleton.h"
#include <string>

using namespace std;
//--------------------------------------------------
//	Variáveis
//--------------------------------------------------
Player objPlayerList[GameData::intMaxPlayers];
int intQtdPlayers;

int objItemIdList[500];
int intQtdItens;

int objZombieIdList[500];
int intQtdZombies;

int objCarIdList[100];
int intQtdCars;
//--------------------------------------------------
//	Métodos
//--------------------------------------------------
int ESP::Renderizar(Janela p_objJanela) {
	Global::getInstance()->objDirectX.objDispositivo->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	Global::getInstance()->objDirectX.objDispositivo->BeginScene();

	if (p_objJanela.hwndReferencia == GetForegroundWindow()) {
		Global::getInstance()->RefreshRenderizador();
		Global::getInstance()->RefreshMe();

		if (Global::getInstance()->objConfig.blnShowMenu) {
			this->DesenharMenu();
		}

		if (Global::getInstance()->objConfig.blnShowPlayers) {
			this->LoadPlayerList();
			this->DesenharPlayers();
			this->DesenharCrosshair();
			this->DesenharHora();
			this->DesenharMeuHP();
		}

		if (Global::getInstance()->objConfig.blnShowItens) {
			this->LoadObjectLists();
			this->DesenharItens(); //Causa flicker.
		}
	}

	Global::getInstance()->objDirectX.objDispositivo->EndScene();
	Global::getInstance()->objDirectX.objDispositivo->PresentEx(0, 0, 0, 0, 0);

	return 0;
}

void ESP::LoadPlayerList() {
	int contador;
	Player objPlayer;

	Global::getInstance()->RefreshGameClient(); //Atualiza as informações de jogadores (Todas as informações de Players)
	Global::getInstance()->objMe.intPlayersAround = 0; //Reinicia o contador. Ele é incrementado pelo contrutor Player.

	contador = 0;

	for (int i = 0; i < GameData::intMaxPlayers; i++) {
		objPlayer = Player(i);

		if (objPlayer.blnValido && objPlayer.blnVivo && objPlayer.dwdAddress != Global::getInstance()->objMe.dwdAddress) {
			objPlayerList[contador] = objPlayer;
			contador++;
		}

		//Verifica se o player iterado é o player local.
		if (Global::getInstance()->objMe.dwdAddress == objPlayer.dwdAddress) {
			Global::getInstance()->objMe.intHP = objPlayer.intHP;
		}
	}

	intQtdPlayers = contador;
}

void ESP::LoadObjectLists() {
	DWORD dwdEnderecoItem;
	int intAuxTipo;

	int contadorItens = 0;
	int contadorZombies = 0;
	int contadorCars = 0;

	Global::getInstance()->RefreshGameWorld(); //Atualiza as informações de objetos (Itens, zumbis, carros)

	//for (int i = 0; i < Global::getInstance()->objGameWorld.GetMaxObjetos(); i++) {
	for (int i = 0; i < 2000; i++) {
		dwdEnderecoItem = Global::getInstance()->objMemoria.LerMemoria<int>(Global::getInstance()->objGameWorld.GetObjeto(i));
		intAuxTipo = Global::getInstance()->objMemoria.LerMemoria<int>(dwdEnderecoItem + GameData::ObjectManagerID);

		if (intAuxTipo == GameData::ItemDropado) {
			objItemIdList[contadorItens] = i;
			contadorItens++;
		} else if (intAuxTipo == GameData::Zombie) {
			objZombieIdList[contadorZombies] = i;
			contadorZombies++;
		} else if (intAuxTipo == GameData::Veiculo) {
			objCarIdList[contadorCars] = i;
			contadorCars++;
		}
	}

	intQtdItens = contadorItens;
	intQtdZombies = contadorZombies;
	intQtdCars = contadorCars;
}

void ESP::DesenharPlayers() {
	Player objEnemy;
	string strTexto;
	int intPadding = 5;
	int a;

	for (int i = 0; i < intQtdPlayers; i++) {
		objEnemy = objPlayerList[i];
		a = 255 - 255 * ((FLOAT)objEnemy.intDistancia / Config::intMaxDistancePlayer);  //Transparência

		this->DesenharSkeleton(objEnemy);
		this->DesenharHP(objEnemy);
		this->DesenharTexto(objEnemy.strNome + " - " + objEnemy.objMochila.strNome + " [" + to_string(objEnemy.intDistancia) + "]", objEnemy.dxvLocation.x - 37, objEnemy.dxvLocation.y + intPadding, 0, 255, 0, a, Global::getInstance()->objDirectX.objFontePequena);
		this->DesenharTexto(objEnemy.objArmaPrimaria.strNome + " - " + objEnemy.objArmaSecundaria.strNome, objEnemy.dxvLocation.x - 37, objEnemy.dxvLocation.y + intPadding * 4, 0, 0, 255, a, Global::getInstance()->objDirectX.objFontePequena);
		this->DesenharTexto(objEnemy.objCapacete.strNome + " - " + objEnemy.objColete.strNome, objEnemy.dxvLocation.x - 37, objEnemy.dxvLocation.y + intPadding * 7, 0, 0, 255, a, Global::getInstance()->objDirectX.objFontePequena);
	}

	if (Global::getInstance()->objMe.intPlayersAround > 0) {
		this->DesenharTexto("Warning! " + to_string(Global::getInstance()->objMe.intPlayersAround) + " Players around.", 600, 25, 255, 0, 0, 255, Global::getInstance()->objDirectX.objFontePequena);
	}
}

void ESP::DesenharCrosshair() {
	float x, y;

	x = (float)Global::getInstance()->objMyWindow.intLargura / 2;
	y = (float)Global::getInstance()->objMyWindow.intAltura / 2;

	this->DesenharLinha(x - 9, y, x + 9, y, 255, 255, 255, 255); //Traço horizontal - 9 pixels de largura
	this->DesenharLinha(x, y - 9, x, y + 9, 255, 255, 255, 255); //Traço vertical - 9 pixels de altura
}

void ESP::DesenharHP(Player p_objPlayer) {
	int intLarguraBarra = 75;
	int intAlturaBarra = 5;
	int x = p_objPlayer.dxvLocation.x - intLarguraBarra / 2; //Centraliza
	int y = p_objPlayer.dxvLocation.y;
	int a = 255 - 255 * ((FLOAT)p_objPlayer.intDistancia / Config::intMaxDistancePlayer); //Transparência

	this->DesenharBox(x - 1, y - 1, intLarguraBarra + 1, intAlturaBarra + 1, 255, 255, 255, a);
	this->DesenharPreenchimento(x, y, intLarguraBarra*(p_objPlayer.intHP / 100), intAlturaBarra, 0, 255, 0, a);
}

void ESP::DesenharItens() {
	Item objItem;

	DWORD dwdEnderecoObjeto;
	D3DXVECTOR3 dxvWorld;
	D3DXVECTOR3 dxvScreen;
	float fltDistancia;

	//Itens
	for (int i = 0; i < intQtdItens; i++) {
		dwdEnderecoObjeto = Global::getInstance()->objMemoria.LerMemoria<int>(Global::getInstance()->objGameWorld.GetObjeto(objItemIdList[i]));

		dxvWorld = Global::getInstance()->objMemoria.LerMemoria<D3DXVECTOR3 >(dwdEnderecoObjeto + GameData::LocationAddress);
		fltDistancia = D3DXVec3Length(&(Global::getInstance()->objMe.dxvLocation - dxvWorld));

		if (fltDistancia > 0 && fltDistancia <= Config::intMaxDistanceItem) {
			if (Global::getInstance()->objRenderizador.WorldToScreen(&dxvWorld, &dxvScreen)) {
				int a = 255 - 255 * (fltDistancia / Config::intMaxDistanceItem);  //Transparência
				int objId = Global::getInstance()->objMemoria.LerMemoria<int>(dwdEnderecoObjeto + (DWORD)0x3b0);
				
				objItem = Item(objId);
				
				if (objItem.strNome.compare("") != 0) {
					string strTexto = objItem.strNome + string("[") + to_string((int)fltDistancia) + string("]");
					DesenharTexto(strTexto, dxvScreen.x, dxvScreen.y, 0, 0, 255, a, Global::getInstance()->objDirectX.objFontePequena); //Azul
				}
			}
		}
	}

	//Zumbis
	for (int i = 0; i < intQtdZombies; i++) {
		dwdEnderecoObjeto = Global::getInstance()->objMemoria.LerMemoria<int>(Global::getInstance()->objGameWorld.GetObjeto(objZombieIdList[i]));

		dxvWorld = Global::getInstance()->objMemoria.LerMemoria<D3DXVECTOR3 >(dwdEnderecoObjeto + GameData::LocationAddress);
		fltDistancia = D3DXVec3Length(&(Global::getInstance()->objMe.dxvLocation - dxvWorld));

		if (fltDistancia > 0 && fltDistancia <= Config::intMaxDistanceItem / 3) {
			if (Global::getInstance()->objRenderizador.WorldToScreen(&dxvWorld, &dxvScreen)) {
				int a = 255 - 255 * (fltDistancia / Config::intMaxDistanceItem / 3);  //Transparência

				string strTexto = string("[") + to_string((int)fltDistancia) + string("]");
				DesenharTexto(strTexto, dxvScreen.x, dxvScreen.y, 255, 255, 255, a, Global::getInstance()->objDirectX.objFontePequena); //Branco
			}
		}
	}

	//Veículo
	for (int i = 0; i < intQtdCars; i++) {
		dwdEnderecoObjeto = Global::getInstance()->objMemoria.LerMemoria<int>(Global::getInstance()->objGameWorld.GetObjeto(objCarIdList[i]));

		dxvWorld = Global::getInstance()->objMemoria.LerMemoria<D3DXVECTOR3 >(dwdEnderecoObjeto + GameData::LocationAddress);
		fltDistancia = D3DXVec3Length(&(Global::getInstance()->objMe.dxvLocation - dxvWorld));

		if (fltDistancia > 0 && fltDistancia <= Config::intMaxDistanceItem) {
			if (Global::getInstance()->objRenderizador.WorldToScreen(&dxvWorld, &dxvScreen)) {
				int a = 255 - 255 * (fltDistancia / Config::intMaxDistanceItem);  //Transparência

				string strTexto = string("Veículo - [") + to_string((int)fltDistancia) + string("]");
				DesenharTexto(strTexto, dxvScreen.x, dxvScreen.y, 255, 0, 255, a, Global::getInstance()->objDirectX.objFontePequena); //Roxo
			}
		}
	}
}

void ESP::DesenharSkeleton(Player p_objPlayer) {
	const int intTamanhoVetor = 12;
	int vetBones[intTamanhoVetor];

	vetBones[0] = Cabeca;
	vetBones[1] = BracoDireito;
	vetBones[2] = AntebracoDireito;
	vetBones[3] = MaoDireita;
	vetBones[4] = BracoEsquerdo;
	vetBones[5] = AntebracoEsquerdo;
	vetBones[6] = MaoEsquerda;
	vetBones[7] = Pelvis;
	vetBones[8] = JoelhoDireito;
	vetBones[9] = PeDireito;
	vetBones[10] = JoelhoEsquerdo;
	vetBones[11] = PeEsquerdo;

	D3DXVECTOR3 vetBonesWorld[intTamanhoVetor];
	D3DXVECTOR3 vetBonesScreen[intTamanhoVetor];

	GetSkeleton(p_objPlayer.dwdAddress, vetBones, vetBonesWorld);

	for (int i = 0; i < intTamanhoVetor; i++) {
		Global::getInstance()->objRenderizador.WorldToScreen(&vetBonesWorld[i], &vetBonesScreen[i]);
	}

	this->DesenharLinha(vetBonesScreen[0].x, vetBonesScreen[0].y, vetBonesScreen[1].x, vetBonesScreen[1].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[1].x, vetBonesScreen[1].y, vetBonesScreen[2].x, vetBonesScreen[2].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[2].x, vetBonesScreen[2].y, vetBonesScreen[3].x, vetBonesScreen[3].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[0].x, vetBonesScreen[0].y, vetBonesScreen[4].x, vetBonesScreen[4].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[4].x, vetBonesScreen[4].y, vetBonesScreen[5].x, vetBonesScreen[5].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[5].x, vetBonesScreen[5].y, vetBonesScreen[6].x, vetBonesScreen[6].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[0].x, vetBonesScreen[0].y, vetBonesScreen[7].x, vetBonesScreen[7].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[7].x, vetBonesScreen[7].y, vetBonesScreen[8].x, vetBonesScreen[8].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[8].x, vetBonesScreen[8].y, vetBonesScreen[9].x, vetBonesScreen[9].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[7].x, vetBonesScreen[7].y, vetBonesScreen[10].x, vetBonesScreen[10].y, 255, 0, 0, 255);
	this->DesenharLinha(vetBonesScreen[10].x, vetBonesScreen[10].y, vetBonesScreen[11].x, vetBonesScreen[11].y, 255, 0, 0, 255);
}

void ESP::DesenharMenu() {
	int x = 8;
	int y = 8;

	//Container
	this->DesenharPreenchimento(x, y, 300, 375, 0, 0, 0, 200);

	//Título
	y += 5;
	this->DesenharPreenchimento(x + 5, y, 290, 20, 255, 255, 255, 50);
	this->DesenharTexto("Configurações", x + 110, y + 2, 0, 0, 255, 255, Global::getInstance()->objDirectX.objFonteMini);

	//Opções
	y += 25;
	this->DesenharPreenchimento(x + 5, y, 290, 340, 255, 255, 255, 50);

	y += 5;
	this->DesenharTexto("Draw Players", x + 10, y, 0, 0, 255, 255, Global::getInstance()->objDirectX.objFonteMini);
	if (Global::getInstance()->objConfig.blnShowPlayers) {
		this->DesenharTexto("ON", x + 90, y, 0, 255, 0, 255, Global::getInstance()->objDirectX.objFonteMini);

		y += 15;
		this->DesenharTexto("Distance", x + 10, y, 0, 0, 255, 255, Global::getInstance()->objDirectX.objFonteMini);
		this->DesenharTexto(to_string(Global::getInstance()->objConfig.intMaxDistancePlayer), x + 90, y, 0, 255, 0, 255, Global::getInstance()->objDirectX.objFonteMini);
	} else {
		this->DesenharTexto("OFF", x + 90, y, 255, 0, 0, 255, Global::getInstance()->objDirectX.objFonteMini);
	}

	y += 15;
	this->DesenharTexto("Draw Itens", x + 10, y, 0, 0, 255, 255, Global::getInstance()->objDirectX.objFonteMini);
	if (Global::getInstance()->objConfig.blnShowItens) {
		this->DesenharTexto("ON", x + 90, y, 0, 255, 0, 255, Global::getInstance()->objDirectX.objFonteMini);

		y += 15;
		this->DesenharTexto("Distance", x + 10, y, 0, 0, 255, 255, Global::getInstance()->objDirectX.objFonteMini);
		this->DesenharTexto(to_string(Global::getInstance()->objConfig.intMaxDistanceItem), x + 90, y, 0, 255, 0, 255, Global::getInstance()->objDirectX.objFonteMini);
	} else {
		this->DesenharTexto("OFF", x + 90, y, 255, 0, 0, 255, Global::getInstance()->objDirectX.objFonteMini);
	}
}

void ESP::DesenharHora() {
	int systemHour;
	int systemMinute;
	int systemSecond;
	double hours;
	int gameHour;
	int gameMinute;

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	systemHour = systemTime.wHour;
	systemMinute = systemTime.wMinute;
	systemSecond = systemTime.wSecond;

	hours = ((systemHour * 60) + systemMinute) * 12 + 720;
	hours += systemSecond * 12 / 60;
	hours /= 60;

	while (hours > 24) {
		hours -= 24;
	}

	gameHour = (int)hours;
	gameMinute = (hours - gameHour) * 60;

	this->DesenharTexto("Hora: " + to_string(gameHour) + ":" + to_string(gameMinute), 150, 720, 255, 255, 255, 255, Global::getInstance()->objDirectX.objFontePequena);
}

void ESP::DesenharMeuHP() {
	this->DesenharTexto("HP: " + to_string((int)Global::getInstance()->objMe.intHP) + "%", 150, 705, 255, 255, 255, 255, Global::getInstance()->objDirectX.objFontePequena);
}