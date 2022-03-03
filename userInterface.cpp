#include "pch.h"
#include "userInterface.h"

userInterface::userInterface()
{
}

userInterface::~userInterface()
{
}

HRESULT userInterface::init()
{
	_kyle = new kyle;
	_kyle->init();


	//IMAGEMANAGER->addImage("liara_profile","image/liara_profile1.bmp", 94, 144, true, RGB(255, 0, 255));

	return S_OK;
}

void userInterface::release()
{
	
}

void userInterface::update()

{
	_kyle->update();

	//if (KEYMANAGER->isOnceKeyDown('L')) setKyleHP(300);




}

void userInterface::render()
{
	_kyle->render();


}
