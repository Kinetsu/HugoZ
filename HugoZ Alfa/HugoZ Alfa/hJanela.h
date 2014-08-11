#pragma once

#include <string>
#include <windows.h>

using namespace std;

class Janela {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	int intLargura;
	int intAltura;
	string strNome;
	HWND hwndReferencia;
	RECT rectDimensao;
};