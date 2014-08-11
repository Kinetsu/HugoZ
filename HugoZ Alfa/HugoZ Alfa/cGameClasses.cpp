	#pragma once

#include "hGameClasses.h"

//--------------------------------------------------
//	Classe GaameWorld - Métodos
//--------------------------------------------------
DWORD GameWorld::GetMaxObjetos() {
	return (this->m_MaxObjects ^ GameData::FimListaObjetosXOR);
}
DWORD GameWorld::GetObjeto(int p_intId) {
	return (this->m_ObjectList ^ GameData::InicioListaObjetosXOR) + (p_intId * 4);
}

//--------------------------------------------------
//	Classe GameClient - Métodos
//--------------------------------------------------
DWORD* GameClient::GetPlayerByIndex(int p_intIndex) {
	if (p_intIndex < 0 || p_intIndex > GameData::intMaxPlayers) {
		return NULL;
	} else {
		return (DWORD*)(this->dwListaJogadores[p_intIndex] ^ GameData::PlayerXOR);
	}
}

//--------------------------------------------------
//	Classe Renderizador - Métodos
//--------------------------------------------------
void Renderizador::setDispositivo3D(IDirect3DDevice9* p_objDispositivo3D) {
	this->objDispositivo3D = p_objDispositivo3D;
}

int Renderizador::WorldToScreen(D3DXVECTOR3* pvPos, D3DXVECTOR3* pvOut) {
	if (this->objDispositivo3D != NULL) {

		D3DVIEWPORT9 ViewPort;
		this->objDispositivo3D->GetViewport(&ViewPort);

		D3DXMATRIX mWorld;
		D3DXMatrixIdentity(&mWorld);

		D3DXVec3Project(pvOut, pvPos, &ViewPort, &(m_matrices[2]), &(m_matrices[0]), &mWorld);

		if (pvOut->z >= 1 || pvOut->z < 0 || pvOut->x < 0 || pvOut->y < 0 || m_matrices[2].m[3][3] == 1.f) {
			return false;
		}
	}
	return true;
}