#pragma once
#pragma comment (lib, "Vfw32.lib")

#include "gameNode.h"
#include "RagnaRuin.h"
#include "ragnaRuinCore.h"
#include "battleScene.h"
#include "gameoverScene.h"
#include "title.h"


#include <Vfw.h>


class playGround : public gameNode
{
private:
	HWND _video;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	
};

