#include "pch.h"
#include "battleScene.h"

battleScene::battleScene()
{
}

battleScene::~battleScene()
{
}


HRESULT battleScene::init()
{


	IMAGEMANAGER->addImage("battleBackground", "image/battleBackground.bmp", 2643, 2004,true,RGB(255,0,255));

	_bgY = 300;

	_kyle = new kyle;
	
	_em = new enemyManager;

	_sceneDelay = 0;

	_em->setKyleMemoryAddressLink(_kyle);
	_kyle->setEmMemoryAddressLink(_em);

	_kyle->init();
	_em->init();

	_delay = 100;

	_hpBar = new progressBar;
	_hpBar->init(300, WINSIZEY - 100, 80, 20, "hpBarTop", "image/hpBarTop.bmp");
	_hpBar->setGauge(_kyle->getKyleHP(), KYLEMAXHP);

	_mpBar = new progressBar;
	_mpBar->init(300, WINSIZEY - 40, 80, 20, "mpBarTop", "image/mpBarTop.bmp");
	_mpBar->setGauge(_kyle->getKyleMP(), KYLEMAXMP);

	_spBar = new progressBar;
	_spBar->init(300, WINSIZEY - 70, 80, 20, "spBarTop", "image/spBarTop.bmp");
	_spBar->setGauge(_kyle->getKyleSP(), 500);


	_kyle->setKyleHP(getDataKyleHP());
	_kyle->setKyleMP(getDataKyleMP());
	_kyle->setKyleBlast(getDataKyleBlast());

	IMAGEMANAGER->addImage("kyle_profile", "image/kyle_profile1.bmp", 94, 144, true, RGB(255, 0, 255));

	return S_OK;
}

void battleScene::release()
{

}

void battleScene::update()
{

	if (_delay > 0)
	{
		_delay--;
		_bgY++;
	}

	else if (_delay <= 0)
	{

		_kyle->update();
		cameraSetting();

		_em->update();

		gameover();

		if (KEYMANAGER->isOnceKeyDown(VK_F1)) { SCENEMANAGER->changeScene("RagnaRuin"); }

		_spBar->setGauge(_kyle->getKyleSP(), 500);
		_spBar->update();
		_hpBar->setGauge(_kyle->getKyleHP(), KYLEMAXHP);
		_hpBar->update();
		_mpBar->setGauge(_kyle->getKyleMP(), KYLEMAXMP);
		_mpBar->update();

		collision();
		valkyrieCollision();
		kyleMoveLimit();
	
		for (int i = 0; i < _em->getVValkyrie().size(); i++)
		{
			if (_em->getVValkyrie()[i].HP <= 0)
			{
				_em->removeValkyrie(i);
				_em->setRndCount();
			}
		}

		if (_em->getRndCount() <= 0)
		{
			setKyleDataHP(_kyle->getKyleHP());
			setKyleDataMP(_kyle->getKyleMP());
			setKyleBlast(_kyle->getKyleBlast());

		
			_sceneDelay++;

			if (_sceneDelay > 120) SCENEMANAGER->changeScene("RagnaRuin");
		}
	}
}
	
void battleScene::render()
{
	if (_delay >0)
	{ 
		IMAGEMANAGER->findImage("battleBackground")->render(gameNode::getMemDC(), 0, 0, 700, _bgY, WINSIZEX, WINSIZEY);
	}


	else if (_delay <= 0)
	{
		IMAGEMANAGER->findImage("battleBackground")->render(gameNode::getMemDC(), 0, 0, _kyle->getCameraX(), _kyle->getCameraY(), WINSIZEX, WINSIZEY);


		_em->render();

		_kyle->render();

		
		_em->valkyrieRender(_kyle->getCameraX(), _kyle->getCameraY());
		

		_hpBar->render("hpBarTop");
		_mpBar->render("mpBarTop");
		_spBar->render("spBarTop");

		IMAGEMANAGER->findImage("kyle_profile")->render(getMemDC(), 200, WINSIZEY - 150);



	}
}

void battleScene::cameraSetting()
{
	if (_kyle->getCameraX() <= 0)
	{
		_kyle->setCameraX(0);
	}
	if (_kyle->getCameraY() <= 0)
	{
		_kyle->setCameraY(0);
	}
	if (_kyle->getCameraX() + WINSIZEX >= 2643)
	{
		_kyle->setCameraX(2643 - WINSIZEX);
	}
	if (_kyle->getCameraY() + WINSIZEY >= 2004)
	{
		_kyle->setCameraY(2004 - WINSIZEY);
	}
}

void battleScene::gameover()
{
	if (_kyle->getKyleHP() <= 0)
	{
	SCENEMANAGER->changeScene("gameover");
	}
}

void battleScene::collision()
{
	RECT temp;
	for (int i = 0; i < _em->getVValkyrie().size(); i++)
	{
		if (IntersectRect(&temp, &_kyle->getkyleAttack1(), &_em->getVValkyrie()[i].rc))
		{
			_em->valkyrieDamaged(1, i);
			_em->setValkyrieback(i);
		}
		if (IntersectRect(&temp, &_kyle->getkyleAttack2(), &_em->getVValkyrie()[i].rc))
		{

			_em->valkyrieDamaged(1, i);
			_em->setValkyrieback(i);
		}
		if (IntersectRect(&temp, &_kyle->getkyleAttack3(), &_em->getVValkyrie()[i].rc))
		{

			_em->valkyrieDamaged(2, i);
			_em->setValkyrieback(i);
		}

		if (IntersectRect(&temp, &_kyle->getkyleWasa1(), &_em->getVValkyrie()[i].rc))
		{

			_em->valkyrieDamaged(3, i);
			_em->setValkyrieback(i);
		}
		if (IntersectRect(&temp, &_kyle->getkyleWasa2(), &_em->getVValkyrie()[i].rc))
		{

			_em->valkyrieDamaged(3, i);
			_em->setValkyrieback(i);
		}

		if (IntersectRect(&temp, &_kyle->getkyleBioeRC(), &_em->getVValkyrie()[i].rc))
		{
			_em->valkyrieDamaged(1, i);
			_em->setValkyrieback(i);
		}
	}
}

void battleScene::valkyrieCollision()
{
	RECT temp;

	for (int i = 0; i < _em->getVValkyrie().size(); i++)
	{
		if (IntersectRect(&temp, &_em->getVValkyrie()[i].attackRc, &_kyle->getkyleRC() ))
		{
			_kyle->kyleHitted(40);
		}
	}
}

void battleScene::kyleMoveLimit()
{
	for (int i = 0; i < _em->getVValkyrie().size(); i++)
	{
		if(_em->getVValkyrie()[i].rc.left < _kyle->getkyleRC().right)
		{
			_kyle->setKyleX(_em->getVValkyrie()[i].x - 150);

			_kyle->setKyleCurrentSpeed(0);
			_kyle->setKyleFriction(0);

			break;
		}
	}
}