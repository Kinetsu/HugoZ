#pragma once

#include <string>
#include <Windows.h>

using namespace std;

class Config {
public:
	const static string strMyWindowName;
	const static UINT intMyWindowWidth;
	const static UINT intMyWindowHeight;

	const static string strTargetWindowName;
	const static string strTargetProcessName;

	const static UINT intMaxDistancePlayer;
	const static UINT intMaxDistanceItem;

	bool blnShowMenu;
	bool blnShowItens;
	bool blnShowPlayers;
};