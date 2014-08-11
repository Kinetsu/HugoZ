#pragma once

#include "hItem.h"
#include "hGlobais.h"

Item::Item() {
}

Item::Item(int p_id) {
	if (p_id == 0) {
		this->intId = 0;
		this->strNome = "";
		return;
	}

	this->intId = p_id;
	this->strNome = Global::getInstance()->objItemList[p_id];
}