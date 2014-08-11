#pragma once

#include <windows.h>

class GameData {
public:
	//--------------------------------------------------
	//	Atributos
	//--------------------------------------------------
	const static DWORD GameOffset = 0x8BCA58;
	const static DWORD GameWorldOffset = 0x8BD260;
	const static DWORD GameXOR = 0x1735146A;
	const static DWORD GameWorldXOR = 0xFC5AD98D;
	const static DWORD LocationAddress = 0x24;
	const static DWORD PlayerXOR = 0x4AC38963;
	const static DWORD LocalPlayerOffset = 0xCE92C;
	const static DWORD LocalPlayerXOR = 0x8347816F;
	const static DWORD Renderer = 0xE1E6EC;

	const static DWORD ObjectManagerID = 0x210;
	const static DWORD InicioListaObjetosXOR = 0x304CFD16;
	const static DWORD FimListaObjetosXOR = 0x13E1855C;

	const static DWORD Player = 0x21;
	const static DWORD Zombie = 0x20001;
	const static DWORD ItemDropado = 0x240005;
	const static DWORD Veiculo = 0x250005;

	const static DWORD PlayerName = 0x03D8;
	const static DWORD PlayerNameLength = 0x0418;
	const static DWORD PlayerHP = 0x04B4;
	const static DWORD PlayerBag = 0x4A0;
	const static DWORD PlayerIsDead = 0x12F8; //1 - Dead || 0 - Alive
	//Slots do inimigo. Iniciando da posição 610, a cada adição de 20 pega o próximo item.
	const static DWORD PlayerPrimaryWeapon = 0x610;
	const static DWORD PlayerSecondaryWeapon = 0x630;
	//Pula os slots 3,4,5 e 6 - (0x650, 0x670, 0x690 e 0x6B0)
	const static DWORD PlayerChest = 0x6D0;
	const static DWORD PlayerHelmet = 0x6F0;
	//Apartir daqui, inicia os slots do inventário a partir do 0x710

	const static DWORD PlayerSkeletonAddress = 0x11F8;
	const static DWORD PlayerBoneCoeffAddress = 0x1428;


	const static UINT intMaxPlayers = 200;
};