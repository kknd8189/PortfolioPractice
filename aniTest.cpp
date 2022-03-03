#include "pch.h"
#include "aniTest.h"


aniTest::aniTest()
{
}


aniTest::~aniTest()
{
}

HRESULT aniTest::init()
{
	_camel = IMAGEMANAGER->addImage("camel", "camel.bmp", 300, 267, true, RGB(255, 0, 255));

	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani1->setDefPlayFrame(true, true);
	_ani1->setFPS(1);

	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani2->setPlayFrame(3, 9, false);
	_ani2->setFPS(1);

	int arrAni[] = { 5, 1, 3, 4, 7, 2, 6 };
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), 75, 89);
	_ani3->setPlayFrame(arrAni, 7, true);
	_ani3->setFPS(1);

	return S_OK;
}

void aniTest::release()
{
}

void aniTest::update()
{
	if(KEYMANAGER->isOnceKeyDown('Q')) _ani1->start();
	if(KEYMANAGER->isOnceKeyDown('W')) _ani1->stop();
	if(KEYMANAGER->isOnceKeyDown('E')) _ani1->pause();
	if(KEYMANAGER->isOnceKeyDown('R')) _ani1->resume();

	if (KEYMANAGER->isOnceKeyDown('A')) _ani2->start();
	if (KEYMANAGER->isOnceKeyDown('S')) _ani2->stop();
	if (KEYMANAGER->isOnceKeyDown('D')) _ani2->pause();
	if (KEYMANAGER->isOnceKeyDown('F')) _ani2->resume();

	if (KEYMANAGER->isOnceKeyDown('Z')) _ani3->start();
	if (KEYMANAGER->isOnceKeyDown('X')) _ani3->stop();
	if (KEYMANAGER->isOnceKeyDown('C')) _ani3->pause();
	if (KEYMANAGER->isOnceKeyDown('V')) _ani3->resume();

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("ÀÌÆåÆ®¾À");
}



void aniTest::render()
{
	_camel->aniRender(getMemDC(), 100, 200, _ani1);
	_camel->aniRender(getMemDC(), 100, 300, _ani2);
	_camel->aniRender(getMemDC(), 300, 300, _ani3);
}
