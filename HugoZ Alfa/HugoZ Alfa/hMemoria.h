#pragma once

#include <string>
#include <windows.h>

using namespace std;

//--------------------------------------------------
//Descrição: Esta é a classe responsável por fornecer tudo que é necessário para realizar leituras de memória.
//--------------------------------------------------
class Memoria {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	UINT intEnderecoBase;
	UINT intIdProcesso;
	HANDLE hndReferenciaProcesso;
	string strNomeProcesso;

	//--------------------------------------------------
	//	Métodos
	//--------------------------------------------------
	bool Inicializar(string p_strNomeProcesso);

	//--------------------------------------------------
	//Descrição: Este método realiza a leitura na memória e retorna o tipo de dado especificado através do template.
	//Obs: O tamanho da dado passado como template determinará o range de memória que será lido.
	//Ex: Se for passado um inteiro como template o método realizará aleitura de 4 bytes de memória.
	//--------------------------------------------------
	template <class TemplateMemoriaRetorno>
	TemplateMemoriaRetorno LerMemoria(DWORD p_EnderecoDeMemoria) {
		TemplateMemoriaRetorno retorno;

		ReadProcessMemory(this->hndReferenciaProcesso, reinterpret_cast<LPCVOID>(p_EnderecoDeMemoria), &retorno, sizeof(TemplateMemoriaRetorno), NULL);

		return retorno;
	}
};