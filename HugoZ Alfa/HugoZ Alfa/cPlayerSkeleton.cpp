#pragma once

#include "hPlayerSkeleton.h";
#include "hGlobais.h"

//Foi criada uma função que recebe o array de bones e faz tudo em uma só leitura.
void GetSkeleton(DWORD pPlayer, int vetEsqueleto[], D3DXVECTOR3 Retorno[]) {
	D3DXMATRIX v6;
	D3DXMATRIX v7;
	D3DXMATRIX BoneMatrix;
	int intArraySize;

	D3DXMatrixRotationYawPitchRoll(&v6, 0.0, 1.5707963, 0.0);

	DWORD CSkeletonAddress = Global::getInstance()->objMemoria.LerMemoria<DWORD>(pPlayer + GameData::PlayerSkeletonAddress);

	CSkeleton _pSkeleton = Global::getInstance()->objMemoria.LerMemoria<CSkeleton>(CSkeletonAddress);
	CBoneInfo _pBoneInfo = Global::getInstance()->objMemoria.LerMemoria<CBoneInfo>((DWORD)_pSkeleton.BonePtr);

	DWORD CBoneArrayAddress = (DWORD)_pBoneInfo.pBones;

	for (int i = 0; i < 12; i++) {
		CBone Bone = Global::getInstance()->objMemoria.LerMemoria<CBone>((DWORD)CBoneArrayAddress + (vetEsqueleto[i] * sizeof(CBone)));

		BoneMatrix = Bone.BoneMatrix;

		D3DXMATRIX BoneCoeff = Global::getInstance()->objMemoria.LerMemoria<D3DXMATRIX>(pPlayer + GameData::PlayerBoneCoeffAddress);

		D3DXMatrixMultiply(&BoneMatrix, &BoneMatrix, &BoneCoeff);
		D3DXMatrixMultiply(&v7, &v6, &BoneMatrix);

		Retorno[i].x = v7._41;
		Retorno[i].y = v7._42;
		Retorno[i].z = v7._43;
	}
}