#include "pch.h"
#include "player.h"


player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{

	joom = 4;
	_playerX = 100;
	_playerY = 2000;
	_backgroundX = 2688 * 1.3;
	_backgroundY = 1951 * 1.3;

	_cameraPosX = WINSIZEX / 2;
	_cameraPosY = WINSIZEY / 2;

	_count = _index = 0;

	IMAGEMANAGER->addFrameImage("playerIdle", "image/kyle/kyle_idle.bmp",2300, 360, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerWalk", "image/kyle/kyle_walk.bmp", 1840,360, 8, 2, true, RGB(255, 0, 255));

	_playerImg = IMAGEMANAGER->findImage("playerIdle");

	_cameraScreen = RectMake(_playerX - _cameraPosX, +_playerY - _cameraPosY, WINSIZEX, WINSIZEY);

	_playerState = plRightIdle;

	return S_OK;
}

void player::release()
{
}

void player::update()
{	
	_cameraScreen = RectMake(_playerX - _cameraPosX, +_playerY - _cameraPosY, WINSIZEX, WINSIZEY);
	playerMove();
	playerAnimation();
}			

void player::render()
{
	char str[25];
	sprintf_s(str, "%d", _playerX);
	TextOut(getMemDC(), 20, 70, str, strlen(str));

	sprintf_s(str, "%d", _playerY);
	TextOut(getMemDC(), 20, 80, str, strlen(str));

	_playerImg->frameRender(getMemDC(),_playerX - _cameraScreen.left, _playerY - _cameraScreen.top);
}

void player::playerMove()
{

	//A 버튼 누르면

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerWalk");
		_playerImg->setFrameY(1);
		_playerState = plLeftWalk;
	}


	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerIdle");
		_playerImg->setFrameY(1);
		_playerState = plLeftIdle;
	}

	//D를 누르면
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerWalk");
		_playerImg->setFrameY(0);
		_playerState = plRightWalk;

	}


	if (KEYMANAGER->isOnceKeyUp('D'))
	{

		_playerImg = IMAGEMANAGER->findImage("playerIdle");
		_playerImg->setFrameY(0);
		_playerState = plRightIdle;

	}

	//W를 누르면
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerWalk");
	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerIdle");


	}
	//S를 누르면
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerWalk");

	}

	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_playerImg = IMAGEMANAGER->findImage("playerIdle");

	};

}

void player::playerAnimation()
{
	_count++;

	_playerImg->setFrameX(_index);

	if (_count % 10 == 0)
	{
		switch (_playerState)
		{
			case plLeftIdle:
			{
				_playerImg->setFrameY(1);

				_index--;
				
				if (_index < 0) _index = _playerImg->getMaxFrameX();

				break;
			}
			case plRightIdle:
			{	
				_playerImg->setFrameY(0);

				_index++;

				if (_index > _playerImg->getMaxFrameX()) _index = 0;

				break;
			}

			case plRightWalk:
			{
				_playerImg->setFrameY(0);

				_index++;

				if (_index > _playerImg->getMaxFrameX()) _index = 0;

				break;
			}

			case plLeftWalk:

			{	_playerImg->setFrameY(1);

				_index--;

				if (_index < 0) _index = _playerImg->getMaxFrameX();
				break;
			}
		}
	}
}


