#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>

#include "hJanela.h"

//--------------------------------------------------
//Descrição: Esta é a classe responsável por fornecer tudo que é necessário para realizar renderizações.
//--------------------------------------------------
class DirectX {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	IDirect3D9Ex* objDX;
	IDirect3DDevice9Ex* objDispositivo;
	D3DPRESENT_PARAMETERS objParametrosDX;

	ID3DXLine* objLinha;
	ID3DXFont* objFonteMini;
	ID3DXFont* objFontePequena;

	//--------------------------------------------------
	//	Métodos
	//--------------------------------------------------
	int Inicializar(Janela p_objJanela);
};