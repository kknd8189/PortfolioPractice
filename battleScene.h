#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "kyle.h"
#include "progressBar.h"
#include "gameData.h"


class battleScene : public gameNode,gameData
{
private:
	enemyManager* _em;
	kyle* _kyle;

	int _delay,_sceneDelay;

	int _bgY;

	progressBar* _hpBar;
	progressBar* _mpBar;
	progressBar* _spBar;

	

public:
	battleScene();
	~battleScene();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	void cameraSetting();
	void gameover();
	void collision();
	void valkyrieCollision();
	void kyleMoveLimit();
};

