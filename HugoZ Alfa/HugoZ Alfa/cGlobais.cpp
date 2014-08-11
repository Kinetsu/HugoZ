#pragma once

#include "hConfigs.h"
#include "hGlobais.h"

Global* Global::objGlobal = NULL;
bool blnTeclaSolta = true;

//--------------------------------------------------
//Construtores
//--------------------------------------------------

//Carrega algumas informações importantes na criação do objeto
Global::Global() {
	this->objTargetWindow.strNome = Config::strTargetWindowName;
	this->objMyWindow.strNome = Config::strMyWindowName;
	this->objMyWindow.intLargura = Config::intMyWindowWidth;
	this->objMyWindow.intAltura = Config::intMyWindowHeight;
	
	this->objConfig.blnShowMenu = false;
	this->objConfig.blnShowItens = false;
	this->objConfig.blnShowPlayers = true;
}

//--------------------------------------------------
//Métodos
//--------------------------------------------------

//Modo de acesso ao objeto (singleton)
Global* Global::getInstance() {
	if (objGlobal == NULL) {
		objGlobal = new Global();
	}

	return objGlobal;
}

void Global::InicializarVariaveisGlobais() {
	this->objMemoria.Inicializar(Config::strTargetProcessName);
	this->objDirectX.Inicializar(this->objMyWindow);
}

void Global::RefreshGameWorld() {
	DWORD GameWorldAddress;

	GameWorldAddress = this->objMemoria.LerMemoria<DWORD>(this->objMemoria.intEnderecoBase + GameData::GameWorldOffset);
	GameWorldAddress ^= GameData::GameWorldXOR;

	this->dwGameWorldAddress = GameWorldAddress;
	this->objGameWorld = this->objMemoria.LerMemoria<GameWorld>(GameWorldAddress);
}

void Global::RefreshGameClient() {
	DWORD GameAddress;

	GameAddress = this->objMemoria.LerMemoria<DWORD>(this->objMemoria.intEnderecoBase + GameData::GameOffset);
	GameAddress ^= GameData::GameXOR;

	this->dwGameAddress = GameAddress;
	//Alterado - A classe ficou muito grande, é mais vantagem ler o endereço específico.
	//this->objGameClient = this->objMemoria.LerMemoria<GameClient>(GameAddress);
	this->objGameClient = this->objMemoria.LerMemoria<GameClient>(GameAddress + 0x920);
}

void Global::RefreshRenderizador() {
	this->objRenderizador = this->objMemoria.LerMemoria<Renderizador>(this->objMemoria.LerMemoria<DWORD>(this->objMemoria.intEnderecoBase + GameData::Renderer));
	this->objRenderizador.setDispositivo3D(this->objDirectX.objDispositivo);
}

void Global::RefreshMe() {
	this->objMe.dwdAddress = Global::getInstance()->objMemoria.LerMemoria<DWORD>(this->dwGameAddress + GameData::LocalPlayerOffset);
	this->objMe.dwdAddress ^= GameData::LocalPlayerXOR;
	this->objMe.dxvLocation = Global::getInstance()->objMemoria.LerMemoria<D3DXVECTOR3 >(objMe.dwdAddress + GameData::LocationAddress);
}

void Global::RefreshConfig() {
	if (GetAsyncKeyState(VK_DELETE)) {
		if (blnTeclaSolta) {
			this->objConfig.blnShowMenu = !this->objConfig.blnShowMenu;
			blnTeclaSolta = false;
		}
	} else {
		blnTeclaSolta = true;
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		this->objConfig.blnShowItens = true;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		this->objConfig.blnShowItens = false;
	}

	if (GetAsyncKeyState(VK_UP)) {
		this->objConfig.blnShowPlayers = true;
	} else if (GetAsyncKeyState(VK_DOWN)) {
		this->objConfig.blnShowPlayers = false;
	}
}

void Global::LoadItemList() {
		//Armor
		this->objItemList[20015] = "Custom Guerilla";
		this->objItemList[20054] = "IBA Sand";
		this->objItemList[20056] = "MTV Forest";
		this->objItemList[20059] = "Light Gear Forest";
	
		//ASR
		this->objItemList[101002] = "M16";
		this->objItemList[101005] = "G36";
		this->objItemList[101022] = "AK-74M";
		this->objItemList[101032] = "AKM";
		this->objItemList[101040] = "M4 Semi";
		this->objItemList[101055] = "M4";
		this->objItemList[101169] = "MASADA";
		this->objItemList[101172] = "SIG SAUER 556";
		this->objItemList[101173] = "IMI TAR-21";
		this->objItemList[101193] = "FN SCAR CQC";
		this->objItemList[101210] = "FN SCAR NIGHT STALKER";
		this->objItemList[101332] = "Kruger .22 Rifle";
		this->objItemList[101334] = "Kruger Mini-14";
	
		//Attachment
		this->objItemList[400000] = "Forward Grip";
		this->objItemList[400001] = "5.45 AK 30";
		this->objItemList[400003] = "ACOG";
		this->objItemList[400004] = "Rifle Laser";
		this->objItemList[400005] = "Holographic";
		this->objItemList[400006] = "SCAR IS";
		this->objItemList[400007] = "Kobra";
		this->objItemList[400008] = "Tactical Sniper Scope";
		this->objItemList[400009] = "SMG Grip";
		this->objItemList[400010] = "STANAG 60";
		this->objItemList[400012] = "Flash Hider";
		this->objItemList[400013] = "Silencer ";
		this->objItemList[400015] = "STANAG 45";
		this->objItemList[400016] = "STANAG 30";
		this->objItemList[400017] = "STANAG C-Mag";
		this->objItemList[400018] = "Rifle Flashlight";
		this->objItemList[400019] = "Compact Scope";
		this->objItemList[400020] = "Red Dot SP";
		this->objItemList[400021] = "Pistol laser";
		this->objItemList[400022] = "Pistol Flashlight";
		this->objItemList[400023] = "Reflex Sight";
		this->objItemList[400024] = "M4 IS";
		this->objItemList[400025] = "SIG 556 IS";
		this->objItemList[400026] = "MP7 IS";
		this->objItemList[400027] = "PSO-1";
		this->objItemList[400029] = "G36 ammo";
		this->objItemList[400030] = "VSS-20";
		this->objItemList[400031] = "VSS-10";
		this->objItemList[400032] = "MP7 40";
		this->objItemList[400033] = "MP7 30";
		this->objItemList[400034] = "9x19 Para Mag";
		this->objItemList[400035] = "M249 IS";
		this->objItemList[400036] = "KT IS";
		this->objItemList[400038] = "Blackwater Long Range";
		this->objItemList[400039] = "Swiss Arms Scope 8x";
		this->objItemList[400040] = "Iron AK74M";
		this->objItemList[400042] = "Iron G36";
		this->objItemList[400043] = "AWM .338 Magnum ammo";
		this->objItemList[400046] = "P90 50 rounds";
		this->objItemList[400047] = "Bizon 64 ammo";
		this->objItemList[400048] = "SVD ammo";
		this->objItemList[400049] = "CZ Scorpion EVO-3 ammo";
		this->objItemList[400050] = "AA-12 Drum";
		this->objItemList[400051] = "EVO-3 IS";
		this->objItemList[400052] = "Bizon IS";
		this->objItemList[400053] = "USS-12 IS";
		this->objItemList[400054] = "P90 IS";
		this->objItemList[400055] = "Pecheneg IS";
		this->objItemList[400056] = "PKM IS";
		this->objItemList[400058] = "SIG516 IS";
		this->objItemList[400059] = "TAR21 IS";
		this->objItemList[400060] = "RPK IS";
		this->objItemList[400061] = "RPO IS";
		this->objItemList[400062] = "AN94 IS";
		this->objItemList[400065] = "AT4 IS";
		this->objItemList[400066] = "M4 IS2";
		this->objItemList[400069] = "5.45 AK 45 ";
		this->objItemList[400070] = ".308 Winchester Sniper rifle amm";
		this->objItemList[400071] = "9mm Mag";
		this->objItemList[400073] = "Saiga 10 ammo";
		this->objItemList[400074] = "standard muzzle";
		this->objItemList[400079] = "MP5 10mm Mag";
		this->objItemList[400080] = "SAIGA IS";
		this->objItemList[400081] = "XA5 IS";
		this->objItemList[400082] = "M590 Is";
		this->objItemList[400083] = "Veresk IS";
		this->objItemList[400084] = "SMG-20 ammo";
		this->objItemList[400085] = "SMG-40 ammo";
		this->objItemList[400086] = "Desert Eagle ammo";
		this->objItemList[400087] = "5.7 FN M240 Mag";
		this->objItemList[400088] = "SMG Grip 1";
		this->objItemList[400099] = "G36 C-Mag";
		this->objItemList[400100] = "5.45 AK Drum";
		this->objItemList[400101] = "7.62 AKM clip";
		this->objItemList[400119] = "MASADA IS";
		this->objItemList[400121] = "USS-12 IS";
		this->objItemList[400127] = "M16 IS";
		this->objItemList[400128] = "AKM IS";
		this->objItemList[400129] = "AKS IS";
		this->objItemList[400133] = ".50 BMG";
		this->objItemList[400134] = "UZI IS";
		this->objItemList[400135] = ".45 ACP STI Eagle Elite ammo";
		this->objItemList[400136] = "12 Gauge Slug";
		this->objItemList[400137] = "2x 12gauge ";
		this->objItemList[400139] = "Arrow Explosive";
		this->objItemList[400140] = "Arrow";
		this->objItemList[400141] = "Shotgun shell 2x";
		this->objItemList[400142] = "Shotgun shell 8x";
		this->objItemList[400143] = "M249 Ammo Box";
		this->objItemList[400144] = ".22 Caliber Clip";
		this->objItemList[400145] = "Anaconda clip";
		this->objItemList[400146] = "Large Kruger Rifle Clip";
		this->objItemList[400147] = "Medium Kruger Rifle Clip";
		this->objItemList[400148] = "Stardard Kruger .22 Rifle Clip";
		this->objItemList[400149] = "Kruger Rifle IS";
		this->objItemList[400150] = "Kruger Mini-14 clip";
		this->objItemList[400151] = "Kruger Mini-14 IS";
	
		//Backpack
		this->objItemList[20175] = "Medium Backpack";
		this->objItemList[20176] = "Small Backpack";
		this->objItemList[20179] = "Large Backpack";
		this->objItemList[20180] = "Military Ruck";
		this->objItemList[20181] = "Teddy Bear backpack";
		this->objItemList[20185] = "ALICE Rucksack";
		this->objItemList[20196] = "GameSpot Backpack";
		this->objItemList[20200] = "Santa's Sack";
	
		//Consumable
		this->objItemList[101256] = "Antibiotics";
		this->objItemList[101261] = "Bandages ";
		this->objItemList[101262] = "Bandages DX";
		this->objItemList[101300] = "Pain killers";
		this->objItemList[101301] = "Zombie Repellent";
		this->objItemList[101302] = "C01-Vaccine";
		this->objItemList[101303] = "C04-Vaccine";
		this->objItemList[101304] = "Medkit";
		//this->objItemList[101305] = "Time Capsule";
		this->objItemList[101315] = "Binoculars";
		//this->objItemList[101316] = "Barb wire barricade";
		//this->objItemList[101317] = "Wood shield barricade";
		//this->objItemList[101318] = "Riot Shield";
		this->objItemList[101319] = "Range Finder";
		this->objItemList[101323] = "Air horn";
		//this->objItemList[101324] = "Sandbag barricade";
	
		//Food
		//this->objItemList[101283] = "Bag of Chips";
		this->objItemList[101284] = "Bag MRE";
		//this->objItemList[101285] = "Instant Oatmeal";
		//this->objItemList[101288] = "Chocolate Bar";
		//this->objItemList[101289] = "Granola Bar";
		this->objItemList[101290] = "Can of Pasta";
		this->objItemList[101291] = "Can of Soup";
		this->objItemList[101292] = "Can of Ham";
		this->objItemList[101293] = "Can of Tuna";
		//this->objItemList[101340] = "MiniSaints";
	
		//Grenade
		this->objItemList[101310] = "Frag Grenade";
		//this->objItemList[101311] = "Chemlight White";
		//this->objItemList[101312] = "Flare";
		//this->objItemList[101325] = "Chemlight blue";
		//this->objItemList[101326] = "Chemlight green";
		//this->objItemList[101327] = "Chemlight orange";
		//this->objItemList[101328] = "Chemlight red";
		//this->objItemList[101329] = "Chemlight yellow";
	
		//Helmet
		this->objItemList[20006] = "K. Style Helmet";
		//this->objItemList[20022] = "Beret Cover";
		//this->objItemList[20023] = "Boonie Cover";
		//this->objItemList[20025] = "Shadow";
		//this->objItemList[20032] = "Black Mask";
		//this->objItemList[20033] = "Clown Mask";
		//this->objItemList[20034] = "Jason Mask";
		//this->objItemList[20035] = "Skull Mask";
		//this->objItemList[20036] = "Slash Mask";
		//this->objItemList[20041] = "Boonie Desert";
		//this->objItemList[20042] = "Boonie Green";
		//this->objItemList[20043] = "M9 helmet black";
		//this->objItemList[20046] = "M9 Helmet with Goggles";
		//this->objItemList[20047] = "M9 Helmet Green";
		//this->objItemList[20048] = "M9 Helmet Urban";
		//this->objItemList[20049] = "M9 Helmet Forest 1";
		//this->objItemList[20050] = "M9 Helmet Goggles 1";
		this->objItemList[20067] = "NVG Goggles";
		//this->objItemList[20096] = "Boonie Hat Leather";
		//this->objItemList[20097] = "Fireman Helmet";
		//this->objItemList[20098] = "Hard Hat";
		//this->objItemList[20177] = "Gas Mask";
		//this->objItemList[20178] = "Gas Mask 2";
		this->objItemList[20187] = "Night vision military";
		this->objItemList[20188] = "Night vision civilian";
		//this->objItemList[20192] = "Helloween Special!";
		//this->objItemList[20197] = "Christmas Special";
		//this->objItemList[20198] = "Santa's Lil Helper";
		//this->objItemList[20199] = "Captain Jack Frost";
	
		//HG
		this->objItemList[101004] = "FN FiveSeven";
		this->objItemList[101111] = "B92";
		this->objItemList[101112] = "B93R ";
		this->objItemList[101115] = "Jericho 9mm";
		this->objItemList[101120] = "Sig Sauer P226";
		this->objItemList[101180] = "Desert Eagle";
		this->objItemList[101224] = "STI Eagle Elite .45 ACP";
		this->objItemList[101320] = "Flare Gun";
		this->objItemList[101330] = "Kruger .22";
		this->objItemList[101331] = "Colt Anaconda";
		this->objItemList[101342] = "1911";
	
		//Melee
		this->objItemList[101267] = "Tactical Knife";
		//this->objItemList[101278] = "Bat";
		//this->objItemList[101306] = "Flashlight";
		this->objItemList[101307] = "Hammer";
		this->objItemList[101308] = "Hatchet";
		this->objItemList[101309] = "Pickaxe";
		//this->objItemList[101313] = "Spiked Bat";
		//this->objItemList[101314] = "Metal Bat";
		//this->objItemList[101335] = "Kandy Kane";
		this->objItemList[101336] = "Katana";
		this->objItemList[101337] = "Jokoto Katana";
		this->objItemList[101338] = "Wakizashi";
		this->objItemList[101339] = "Machete";
	
		//MG
		this->objItemList[101060] = "PKM";
		this->objItemList[101093] = "RPK-74 ";
		this->objItemList[101095] = "FN M249 ";
		this->objItemList[101197] = "RA H23";
	
		//SG
		this->objItemList[101098] = "SAIGA";
		this->objItemList[101158] = "MOSSBERG 590";
		this->objItemList[101183] = "KT DECIDER";
		this->objItemList[101200] = "AA-12";
		this->objItemList[101321] = "Double Barrel";
	
		//SMG
		this->objItemList[101035] = "AKS-74U";
		this->objItemList[101063] = "MP7";
		this->objItemList[101064] = "UZI";
		this->objItemList[101103] = "MP5/10";
		this->objItemList[101106] = "Honey Badger";
		this->objItemList[101107] = "FN P90 ";
		this->objItemList[101108] = "EVO-3";
		this->objItemList[101109] = "BIZON";
		this->objItemList[101201] = "VERESK SR-2";
		this->objItemList[101246] = "FN P90 S";
	
		//Sniper
		this->objItemList[101068] = "SVD ";
		this->objItemList[101084] = "VSS VINTOREZ";
		this->objItemList[101085] = "MAUSER SP66";
		this->objItemList[101087] = "AW Magnum";
		this->objItemList[101088] = "M107";
		this->objItemList[101217] = "MAUSER SRG DESERT";
		this->objItemList[101247] = "BLASER R93";
		this->objItemList[101322] = "Compound Crossbow";
	
		//Water
		this->objItemList[101286] = "Coconut Water";
		this->objItemList[101294] = "Energy drink";
		this->objItemList[101295] = "Electro-AID";
		//this->objItemList[101296] = "Can of soda";
		this->objItemList[101297] = "Juice";
		this->objItemList[101298] = "Water 1L";
		this->objItemList[101299] = "Water 375ml";
	
		//Misc
		this->objItemList[1280266068] = "Loot Box";
		this->objItemList[1196379204] = "Money";
}