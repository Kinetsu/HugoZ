#pragma once
#pragma comment(lib, "dwmapi.lib")

#include <dwmapi.h>
#include <TlHelp32.h>

#include "hMemoria.h"
#include "hGameClasses.h"
#include "hGameData.h"

//--------------------------------------------------
//Descrição: Localiza o processo informado.
//Atribuições:
//	Armazenar o endereço base do processo.
//	Armazenar o handle do processo.
//--------------------------------------------------
bool Memoria::Inicializar(string p_NomeProcesso) {
	HANDLE objCopiaProcessos = NULL;
	PROCESSENTRY32 objAuxProcesso;
	MODULEENTRY32 objAuxModulo;
	bool blnRetorno = false;

	objAuxProcesso.dwSize = sizeof(objAuxProcesso);
	objAuxModulo.dwSize = sizeof(objAuxModulo);

	objCopiaProcessos = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	while (Process32Next(objCopiaProcessos, &objAuxProcesso)) {
		if (p_NomeProcesso.compare(objAuxProcesso.szExeFile) == 0) {

			if (this->hndReferenciaProcesso) {
				CloseHandle(this->hndReferenciaProcesso);
			}

			this->hndReferenciaProcesso = OpenProcess(PROCESS_ALL_ACCESS, FALSE, objAuxProcesso.th32ProcessID);
			intIdProcesso = objAuxProcesso.th32ProcessID;
			CloseHandle(objCopiaProcessos);

			objCopiaProcessos = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, objAuxProcesso.th32ProcessID);
			Module32First(objCopiaProcessos, &objAuxModulo);
			this->intEnderecoBase = (unsigned int)objAuxModulo.modBaseAddr;

			this->strNomeProcesso = p_NomeProcesso;

			blnRetorno = true;
		}
	}

	CloseHandle(objCopiaProcessos);

	return blnRetorno;
}