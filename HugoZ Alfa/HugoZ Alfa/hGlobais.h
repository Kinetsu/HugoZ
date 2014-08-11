#pragma once

#include "hDirectX.h"
#include "hESP.h"
#include "hGameClasses.h"
#include "hJanela.h"
#include "hMemoria.h"
#include "hPlayer.h"

#include <unordered_map>

//--------------------------------------------------
//Descrição: Esta classe que utiliza o padrão singleton, armazena todos os objetos de uso global.
//Atribuições:
//	Armazenar os objetos de uso global.
//	Inicializar os objetos de uso global.
//--------------------------------------------------
class Global {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	Janela objMyWindow;
	Janela objTargetWindow;

	Memoria objMemoria;
	DirectX objDirectX;
	Config objConfig;

	ESP objESP;
	Player objMe;
	unordered_map <int, string> objItemList;

	GameClient objGameClient;
	GameWorld objGameWorld;
	Renderizador objRenderizador;

	//--------------------------------------------------
	//	Métodos
	//--------------------------------------------------
	static Global* getInstance();

	void InicializarVariaveisGlobais();
	void RefreshGameWorld();
	void RefreshGameClient();
	void RefreshRenderizador();
	void RefreshMe();
	void RefreshConfig();
	void LoadItemList();

private:
	DWORD dwGameAddress;
	DWORD dwGameWorldAddress;

	Global();
	static Global* objGlobal;
};