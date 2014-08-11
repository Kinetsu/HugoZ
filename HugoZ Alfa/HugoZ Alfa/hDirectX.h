#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>

#include "hJanela.h"

//--------------------------------------------------
//Descri��o: Esta � a classe respons�vel por fornecer tudo que � necess�rio para realizar renderiza��es.
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
	//	M�todos
	//--------------------------------------------------
	int Inicializar(Janela p_objJanela);
};