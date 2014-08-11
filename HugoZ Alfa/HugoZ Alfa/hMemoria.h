#pragma once

#include <string>
#include <windows.h>

using namespace std;

//--------------------------------------------------
//Descri��o: Esta � a classe respons�vel por fornecer tudo que � necess�rio para realizar leituras de mem�ria.
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
	//	M�todos
	//--------------------------------------------------
	bool Inicializar(string p_strNomeProcesso);

	//--------------------------------------------------
	//Descri��o: Este m�todo realiza a leitura na mem�ria e retorna o tipo de dado especificado atrav�s do template.
	//Obs: O tamanho da dado passado como template determinar� o range de mem�ria que ser� lido.
	//Ex: Se for passado um inteiro como template o m�todo realizar� aleitura de 4 bytes de mem�ria.
	//--------------------------------------------------
	template <class TemplateMemoriaRetorno>
	TemplateMemoriaRetorno LerMemoria(DWORD p_EnderecoDeMemoria) {
		TemplateMemoriaRetorno retorno;

		ReadProcessMemory(this->hndReferenciaProcesso, reinterpret_cast<LPCVOID>(p_EnderecoDeMemoria), &retorno, sizeof(TemplateMemoriaRetorno), NULL);

		return retorno;
	}
};