#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	//오프닝 초기화
	_video = MCIWndCreate(_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, "image/opening.avi");
	MoveWindow(_video, 0, 0, WINSIZEX, WINSIZEY, NULL);
	MCIWndPlay(_video);

	SCENEMANAGER->addScene("ragnaRuinCore", new ragnaRuinCore);
	SCENEMANAGER->addScene("RagnaRuin", new RagnaRuin);	
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("battleScene", new battleScene);
	SCENEMANAGER->addScene("gameover", new gameoverScene);
	SCENEMANAGER->changeScene("title");

	return S_OK;

}

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();
}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}


//여기다 그려줘라!!!
void playGround::render()
{
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video) || KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		MCIWndDestroy(_video);

		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

		//==============위에는 제발 건드리지 마라 ============

		SCENEMANAGER->render();

		TIMEMANAGER->render(getMemDC());

		//=============== 밑에도 건들지마라 ================
		_backBuffer->render(getHDC(), 0, 0);
	}
}

