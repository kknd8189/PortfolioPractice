#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	//������ �ʱ�ȭ
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

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();
}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}


//����� �׷����!!!
void playGround::render()
{
	if (MCIWndGetLength(_video) <= MCIWndGetPosition(_video) || KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		MCIWndDestroy(_video);

		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

		//==============������ ���� �ǵ帮�� ���� ============

		SCENEMANAGER->render();

		TIMEMANAGER->render(getMemDC());

		//=============== �ؿ��� �ǵ������� ================
		_backBuffer->render(getHDC(), 0, 0);
	}
}

