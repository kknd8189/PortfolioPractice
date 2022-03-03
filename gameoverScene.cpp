#include "pch.h"
#include "gameoverScene.h"

gameoverScene::gameoverScene()
{
}

gameoverScene::~gameoverScene()
{
	_alpha = 0;
}

HRESULT gameoverScene::init()
{
	IMAGEMANAGER->addImage("blackBackground", "image/blackBackground.bmp", 1200, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameover", "image/gameover.bmp", 1200, 800, true, RGB(255, 0, 255));

	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
	if (_alpha <= 255)
	{
		_alpha++;
	}
	else if (_alpha > 255)
	{
		SCENEMANAGER->changeScene("title");
	}
}

void gameoverScene::render()
{
	IMAGEMANAGER->findImage("blackBackground")->render(getMemDC(),0,0);
	IMAGEMANAGER->findImage("gameover")->alphaRender(getMemDC(), _alpha);
}
