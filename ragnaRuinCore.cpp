#include "pch.h"
#include "ragnaRuinCore.h"

ragnaRuinCore::ragnaRuinCore()
{
}

ragnaRuinCore::~ragnaRuinCore()
{
}

HRESULT ragnaRuinCore::init()
{
	_player = new player;

	_player->init();

	IMAGEMANAGER->addImage("ragnaRuinCore", "image/ragnaRuinCore.bmp", 2400, 1907, true, RGB(255, 0, 255));
	return S_OK;
}

void ragnaRuinCore::release()
{
}

void ragnaRuinCore::update()
{
	_player->update();
}

void ragnaRuinCore::render()
{
	_player->render();

	IMAGEMANAGER->findImage("ragnaRuinCore")->render(getMemDC());
}

void ragnaRuinCore::pixelCollision()
{
}

void ragnaRuinCore::cameraSetting()
{
}
