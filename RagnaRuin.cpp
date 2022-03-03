#include "pch.h"
#include "RagnaRuin.h"



RagnaRuin::RagnaRuin()
{
}

RagnaRuin::~RagnaRuin()
{
}

HRESULT RagnaRuin::init()
{
	_player = new player;

	_probeY = _player->getPlayerY();
	_probeX = _player->getPlayerX();

	_randProb = 0;
	_randCount = 0;

	_player->init();

	IMAGEMANAGER->addImage("ragnaRuin", "image/ragnaRuin.bmp", 2688 * 1.3, 1951 * 1.3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ragnaRuinPixel", "image/ragnaRuinPixel.bmp", 2688 * 1.3, 1951 * 1.3, false, RGB(255, 0, 255));

	_player->setPlayerX(getPlayerCurrentX());
	_player->setPlayerY(getPlayerCurrentY());


	return S_OK;
}

void RagnaRuin::release()
{
}

void RagnaRuin::update()
{

	_player->update();
	
	cameraSetting();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) { SCENEMANAGER->changeScene("battleScene"); }
	
	pixelCollision();
}

void RagnaRuin::render()
{
	IMAGEMANAGER->findImage("ragnaRuin")->render(getMemDC(), 0, 0, _player->getCameraX(), _player->getCameraY(), WINSIZEX, WINSIZEY);


	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("ragnaRuinPixel")->render(getMemDC(), 0, 0, _player->getCameraX(), _player->getCameraY(), WINSIZEX, WINSIZEY);

	}


	_player->render();

	char str[25];
	sprintf_s(str, "randCount : %d", _randCount);
	TextOut(getMemDC(), 0, 100, str, strlen(str));

	sprintf_s(str, "randProb : %d", _randProb);
	TextOut(getMemDC(), 0, 110, str, strlen(str));

	//RectangleMake(gameNode::getMemDC(), _probeX+ 158- _player->getCameraX(), _player->getPlayerY() + 100 - _player->getCameraY(), 10, 10);


}

void RagnaRuin::pixelCollision()
{
	_probeX = _player->getPlayerX();
	_probeY = _player->getPlayerY();

	for (int i = _probeY - 3; i < _probeY +1; ++i)
	{
		

		COLORREF color = GetPixel(IMAGEMANAGER->findImage("ragnaRuinPixel")->getMemDC(), _player->getPlayerX()+100, i);

		 int r = GetRValue(color);
		 int g = GetGValue(color);
		 int b = GetBValue(color);
		 
		if (!(r == 255 && g == 0 && b == 255) && KEYMANAGER->isStayKeyDown('W'))
		{
			_player->setPlayerY(_player->getPlayerY() - 5);
			randomEncounter();
			break;
		}

		if (r ==0 && g == 0 && b == 0) 
		{
			SCENEMANAGER->changeScene("ragnaRuinCore");
		}
	}

	for (int i = _probeY + 183; i < _probeY + 186; ++i)
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("ragnaRuinPixel")->getMemDC(), _player->getPlayerX() + 100, i);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);



	if (!(r == 255 && g == 0 && b == 255) && KEYMANAGER->isStayKeyDown('S'))
	{
		_player->setPlayerY(_player->getPlayerY() + 5);
		randomEncounter();
		break;
	}
}

	for ( int i = _probeX - 5; i < _probeX + 5; ++i)
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("ragnaRuinPixel")->getMemDC(), i, _player->getPlayerY() + 100);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (!(r == 255 && g == 0 && b == 255) && KEYMANAGER->isStayKeyDown('A'))
	{
		_player->setPlayerX(_player->getPlayerX() - 5);
		randomEncounter();
		break;
	}
}

	for ( int i = _probeX +155; i < _probeX + 160; ++i)
{

	COLORREF color = GetPixel(IMAGEMANAGER->findImage("ragnaRuinPixel")->getMemDC(), i, _player->getPlayerY()  + 100 );

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	if (KEYMANAGER->isStayKeyDown('D')  && (!(r == 255 && g == 0 && b == 255)))
	{
		_player->setPlayerX(_player->getPlayerX() + 5);
		randomEncounter();
		break;
	}
}

}

void RagnaRuin::cameraSetting()
{
	if (_player->getCameraX() <= 0)
	{
		_player->setCameraLeft(0);
	}
	if (_player->getCameraY() <= 0)
	{
		_player->setCameraTop(0);
	}
	if (_player->getCameraX() + WINSIZEX >= 2688 * 1.3)
	{
		_player->setCameraLeft(2688 * 1.3 - WINSIZEX);
	}
	if (_player->getCameraY() + WINSIZEY >= 1951 * 1.3)
	{
		_player->setCameraTop(1951 * 1.3 - WINSIZEY);
	}
}

void RagnaRuin::randomEncounter()
{
	_randCount++;

	if (_randCount % 20 == 0)
	{
		_randProb = RND->getInt(15);

		if (_randProb == 0)
		{
			setPlayerCurrentX(_player->getPlayerX());
			setPlayerCurrentY(_player->getPlayerY());

			SCENEMANAGER->changeScene("battleScene");
		}
	}

}

