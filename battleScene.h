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

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	void cameraSetting();
	void gameover();
	void collision();
	void valkyrieCollision();
	void kyleMoveLimit();
};

