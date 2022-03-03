#include "pch.h"
#include "title.h"

title::title()
{
}

title::~title()
{
}

HRESULT title::init()
{
	IMAGEMANAGER->addImage("title", "image/Title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newGame", "image/newGame.bmp", 400, 84, true, RGB(255, 0, 255));

	return S_OK;
}

void title::release()
{
}

void title::update()
{

	_newGameRc = RectMake(WINSIZEX / 2 - 200, WINSIZEY / 2 + 100,
		IMAGEMANAGER->findImage("newGame")->getWidth(), IMAGEMANAGER->findImage("newGame")->getHeight());


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _ptMouse.x <= _newGameRc.right && _ptMouse.x >= _newGameRc.left &&
		_ptMouse.y <= _newGameRc.bottom && _ptMouse.y >= _newGameRc.top)

	{
		SCENEMANAGER->changeScene("RagnaRuin");
	}

}

void title::render()
{
	IMAGEMANAGER->findImage("title")->render(getMemDC());

	IMAGEMANAGER->findImage("newGame")->render(getMemDC(), _newGameRc.left, _newGameRc.top);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _newGameRc);
	}
}
