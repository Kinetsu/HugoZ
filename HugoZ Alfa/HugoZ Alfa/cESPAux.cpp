#pragma once

#include "hESP.h"
#include "hGlobais.h"

//--------------------------------------------------
//	Métodos
//--------------------------------------------------
void ESP::DesenharGradient(float x, float y, float w, float h, int r, int g, int b, int a) {
	int iColorr, iColorg, iColorb;

	for (int i = 1; i < h; i++) {
		iColorr = (int) (i / h*r);
		iColorg = (int) (i / h*g);
		iColorb = (int) (i / h*b);

		DesenharPreenchimento(x, (float)y + i, w, (float)1, r - iColorr, g - iColorg, b - iColorb, a);
	}
}

void ESP::DesenharLinha(float p1x, float p1y, float p2x, float p2y, int r, int g, int b, int a) {
	D3DXVECTOR2 dxvPontos[2];

	dxvPontos[0] = D3DXVECTOR2(p1x, p1y);
	dxvPontos[1] = D3DXVECTOR2(p2x, p2y);

	Global::getInstance()->objDirectX.objLinha->SetWidth(1);
	Global::getInstance()->objDirectX.objLinha->Draw(dxvPontos, 2, D3DCOLOR_ARGB(a, r, g, b));

}

void ESP::DesenharPreenchimento(float x, float y, float w, float h, int r, int g, int b, int a) {
	D3DXVECTOR2 dxvPontos[2];

	dxvPontos[0] = D3DXVECTOR2(x + w / 2, y);
	dxvPontos[1] = D3DXVECTOR2(x + w / 2, y + h);

	Global::getInstance()->objDirectX.objLinha->SetWidth(w);
	Global::getInstance()->objDirectX.objLinha->Draw(dxvPontos, 2, D3DCOLOR_ARGB(a, r, g, b));
}

void ESP::DesenharBox(float x, float y, float w, float h, int r, int g, int b, int a) {
	D3DXVECTOR2 dxvPontos[5];

	dxvPontos[0] = D3DXVECTOR2(x, y);
	dxvPontos[1] = D3DXVECTOR2(x + w, y);
	dxvPontos[2] = D3DXVECTOR2(x + w, y + h);
	dxvPontos[3] = D3DXVECTOR2(x, y + h);
	dxvPontos[4] = D3DXVECTOR2(x, y);

	Global::getInstance()->objDirectX.objLinha->SetWidth(1);
	Global::getInstance()->objDirectX.objLinha->Draw(dxvPontos, 5, D3DCOLOR_RGBA(r, g, b, a));
}

void ESP::DesenharTexto(string strTexto, int x, int y, int r, int g, int b, int a, ID3DXFont* p_objFonte) {
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;

	p_objFonte->DrawTextA(0, strTexto.c_str(), strlen(strTexto.c_str()), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));
}