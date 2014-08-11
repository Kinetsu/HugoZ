#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <unordered_map>

using namespace std;

class Item {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	int intId;
	DWORD dwdEndereco;
	string strNome;
	int intDistancia;

	Item();
	Item(int p_id);
};