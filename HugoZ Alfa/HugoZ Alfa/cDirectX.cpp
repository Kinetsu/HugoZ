#pragma once

#include "hGameData.h"
#include "hGlobais.h"

//--------------------------------------------------
//Descrição: Este método cria e configura um dispositivo DirectX onde serão realizadas as renderizações.
//Atribuições:
//	Criar e configurar o dispositivo DirectX.
//	Criar e configurar os objetos de fonte e linha utilizados pelo renderizador.
//Erros:
//	Finaliza a aplicação caso nao seja possivel criar o dispositivo.
//--------------------------------------------------
int DirectX::Inicializar(Janela p_objJanela) {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &this->objDX))) {
		MessageBox(0, "Erro ao referenciar o DirectX!", "Erro", MB_OK | MB_ICONERROR);
		exit(1);
	}

	ZeroMemory(&this->objParametrosDX, sizeof(this->objParametrosDX));
	this->objParametrosDX.Windowed = TRUE;
	this->objParametrosDX.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->objParametrosDX.hDeviceWindow = p_objJanela.hwndReferencia;
	this->objParametrosDX.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	this->objParametrosDX.BackBufferFormat = D3DFMT_A8R8G8B8;
	this->objParametrosDX.BackBufferWidth = p_objJanela.intLargura;
	this->objParametrosDX.BackBufferHeight = p_objJanela.intAltura;
	this->objParametrosDX.EnableAutoDepthStencil = TRUE;
	this->objParametrosDX.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(this->objDX->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, p_objJanela.hwndReferencia, D3DCREATE_HARDWARE_VERTEXPROCESSING, &this->objParametrosDX, 0, &this->objDispositivo))) {
		MessageBox(0, "Erro ao criar o dispositivo!", "Erro", MB_OK | MB_ICONERROR);
		exit(1);
	}

	D3DXCreateLine(this->objDispositivo, &this->objLinha);
	D3DXCreateFont(this->objDispositivo, 14, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &this->objFonteMini);
	D3DXCreateFont(this->objDispositivo, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri", &this->objFontePequena);

	return 0;
}