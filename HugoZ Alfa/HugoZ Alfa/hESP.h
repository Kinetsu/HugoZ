#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "hPlayer.h"
#include "hJanela.h"

using namespace std;

class ESP {
private:
	//Métodos - Aux
	void DesenharGradient(float x, float y, float w, float h, int r, int g, int b, int a);
	void DesenharLinha(float p1x, float p1y, float p2x, float p2y, int r, int g, int b, int a);
	void DesenharPreenchimento(float x, float y, float w, float h, int r, int g, int b, int a);
	void DesenharBox(float x, float y, float w, float h, int r, int g, int b, int a);
	void DesenharTexto(string strTexto, int x, int y, int r, int g, int b, int a, ID3DXFont* p_objFonte);

	//Métodos
	void LoadPlayerList();
	void LoadObjectLists();

	void DesenharItens();
	void DesenharPlayers();
	void DesenharCrosshair();
	void DesenharHP(Player p_objPlayer);
	void DesenharSkeleton(Player p_objPlayer);
	void DesenharMenu();
	void DesenharHora();
	void DesenharMeuHP();

public:
	int Renderizar(Janela p_objJanela);
};