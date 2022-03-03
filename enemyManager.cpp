#include "pch.h"
#include "enemyManager.h"
#include "kyle.h"


enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	IMAGEMANAGER->addFrameImage("valkyrieIdle", "image/enemy/Valkyrie_idle.bmp", 219, 122, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("valkyrieWalk", "image/enemy/Valkyrie_walk.bmp", 305, 118, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("valkyrieAttack1", "image/enemy/valkyrie_attack1.bmp", 515, 148, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("valkyrieAttack2", "image/enemy/valkyrie_attack2.bmp", 558, 122, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("valkyrieAttack3", "image/enemy/valkyrie_attack3.bmp", 784, 132, 7, 2, true, RGB(255, 0, 255));

	animInit();

	animStart();

	setValkyrie();

	return S_OK;
}

void enemyManager::update()
{
	valkyrieFrameUpdate();
	valkyrieRectUpdate();
	valkyrieTracking();
	valkyrieAttackSetting();
}

void enemyManager::render()
{
	char str[25];
	sprintf_s(str, "_rndSummonCount : %d", _rndSummonCount);
	TextOut(getMemDC(), 10, 300, str, strlen(str));

	sprintf_s(str, "klcamx : %d", _kl->getCameraX());
	TextOut(getMemDC(), 10, 320, str, strlen(str));

	sprintf_s(str, "getkyleX : %d", _kl->getKyleX());
	TextOut(getMemDC(), 100, 40, str, strlen(str));


	for (int i = 0; i < _vValkyrie.size(); i++)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _vValkyrie[i].rc);

			Rectangle(getMemDC(), _vValkyrie[i].attackRc);
		}

		sprintf_s(str, "state : %d", _vValkyrie[i].state);
		TextOut(getMemDC(), 10, 330 + 10 * i, str, strlen(str));

		sprintf_s(str, "isAttack : %d", _vValkyrie[i].isAttack);
		TextOut(getMemDC(), 100, 50 + 10 * i, str, strlen(str));
	}

}

void enemyManager::release()
{

}

void enemyManager::animInit()
{
	int arrValkyrieIdle[] = { 0, 1, 2 };
	_valkyrieIdleAnim = new animation;
	_valkyrieIdleAnim->init(IMAGEMANAGER->findImage("valkyrieIdle")->getWidth(), IMAGEMANAGER->findImage("valkyrieIdle")->getHeight(), 73, 61);
	_valkyrieIdleAnim->setPlayFrame(arrValkyrieIdle, 3, true);
	_valkyrieIdleAnim->setFPS(1);

	int arrValkyrieAttack1[] = { 0, 1, 2, 3, 4};
	_valkyrieAttack1 = new animation;
	_valkyrieAttack1->init(IMAGEMANAGER->findImage("valkyrieAttack1")->getWidth(), IMAGEMANAGER->findImage("valkyrieAttack1")->getHeight(), 103, 74);
	_valkyrieAttack1->setPlayFrame(arrValkyrieAttack1, 5, true);
	_valkyrieAttack1->setFPS(1);


	int arrValkyrieAttack2[] = { 0, 1, 2,3,4,5 };
	_valkyrieAttack2 = new animation;
	_valkyrieAttack2->init(IMAGEMANAGER->findImage("valkyrieAttack2")->getWidth(), IMAGEMANAGER->findImage("valkyrieAttack2")->getHeight(), 93, 61);
	_valkyrieAttack2->setPlayFrame(arrValkyrieAttack2, 6, true);
	_valkyrieAttack2->setFPS(1);


	int arrValkyrieAttack3[] = { 0, 1, 2, 3, 4, 5, 6 };
	_valkyrieAttack3 = new animation;
	_valkyrieAttack3->init(IMAGEMANAGER->findImage("valkyrieAttack3")->getWidth(), IMAGEMANAGER->findImage("valkyrieAttack3")->getHeight(), 112, 66);
	_valkyrieAttack3->setPlayFrame(arrValkyrieAttack3, 7, true);
	_valkyrieAttack3->setFPS(1);


	int arrValkyrieWalk[] = { 0, 1, 2, 3, 4 };
	_valkyrieWalkAnim = new animation;
	_valkyrieWalkAnim->init(IMAGEMANAGER->findImage("valkyrieWalk")->getWidth(), IMAGEMANAGER->findImage("valkyrieWalk")->getHeight(), 61, 59);
	_valkyrieWalkAnim->setPlayFrame(arrValkyrieWalk, 5, true);
	_valkyrieWalkAnim->setFPS(1);
}

void enemyManager::animStart()
{
	_valkyrieIdleAnim -> start();
	_valkyrieWalkAnim->start();

}

void enemyManager::setValkyrie()
{

	_rndSummonCount = RND->getFromIntTo(2,5);

	for (int i = 1; i <= _rndSummonCount; i++)
	{
		tagValkyrie *valkyrie;
		valkyrie = new tagValkyrie;
		ZeroMemory(valkyrie, sizeof(tagValkyrie));
		//memset(&valkyrie, 0 , sizeof(tagValkyrie));

		valkyrie->Img = IMAGEMANAGER->findImage("valkyrieIdle");
		valkyrie->anim = _valkyrieIdleAnim;
		valkyrie->x = 1500+ 100 * i;
		valkyrie->y = 1580;
		valkyrie->rc = RectMake(valkyrie->x - _kl->getCameraX(), valkyrie->y - _kl->getCameraY(), 80, 80);
		valkyrie->isAttack1 = valkyrie->isAttack2 = valkyrie->isAttack1 = false;
		valkyrie->state = valkyrieIdle;
		valkyrie->HP = 100;
		valkyrie->isAttack = false;
		_vValkyrie.push_back(valkyrie);

	}
}

void enemyManager::valkyrieDamaged(int damage, int t)
{
	_vValkyrie[t].HP -= damage;
}

void enemyManager::setValkyrieback(int i)
{
	_vValkyrie[i].x += 5;
}

void enemyManager::removeValkyrie(int arrNum)
{
	_vValkyrie.erase(_vValkyrie.begin() + arrNum);
}

void enemyManager::valkyrieRender(int cx,int cy)
{
	for (_viValkyrie = _vValkyrie.begin(); _viValkyrie != _vValkyrie.end(); ++_viValkyrie)
	{
		_viValkyrie->Img->aniRender(getMemDC(), _viValkyrie->x- cx, _viValkyrie->y - cy, _viValkyrie->anim);
	}
}

void enemyManager::valkyrieFrameUpdate()
{
	_valkyrieIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);
	_valkyrieWalkAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_valkyrieAttack1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_valkyrieAttack2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_valkyrieAttack3->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void enemyManager::valkyrieRectUpdate()
{
	for (_viValkyrie = _vValkyrie.begin(); _viValkyrie != _vValkyrie.end(); ++_viValkyrie)
	{
		_viValkyrie->rc = RectMake(_viValkyrie->x - _kl->getCameraX(), _viValkyrie->y - _kl->getCameraY(), 60, 60);
	}

}

void enemyManager::valkyrieAttackSetting()
{

	for (_viValkyrie = _vValkyrie.begin(); _viValkyrie != _vValkyrie.end(); ++_viValkyrie)
	{
		if (_viValkyrie->isAttack)
		{
				_viValkyrie->attackRc = RectMake(_viValkyrie->x - _kl->getCameraX() - 50, _viValkyrie->y - _kl->getCameraY(), 70, 70);
		}

		else _viValkyrie->attackRc = RectMake(0,0,0,0);
	}
	

	RECT temp;

	for (_viValkyrie = _vValkyrie.begin(); _viValkyrie != _vValkyrie.end(); ++_viValkyrie)
	{


		if (IntersectRect(&temp, &_kl->getkyleRC(), &_viValkyrie->attackRc))
		{
			_viValkyrie->isAttack = false;
		}
	}

}






void enemyManager::valkyrieTracking()
{
	
	_attackCount++;
	_checkingCount++;


	for (_viValkyrie = _vValkyrie.begin(); _viValkyrie != _vValkyrie.end(); ++_viValkyrie)
	{
		if(_kl->getKyleX() + 152 > _viValkyrie->x)
		{

	

			 if (_viValkyrie->state == valkyrieAttack2 && _attackCount % 30 == 0)
			{
			_viValkyrie->isAttack = true;
			_viValkyrie->state = valkyrieAttack3;
			_viValkyrie->Img = IMAGEMANAGER->findImage("valkyrieAttack3");
			_viValkyrie->anim = _valkyrieAttack3;
			_valkyrieAttack3->start();
			_viValkyrie->y = 1570;
			_attackCount = 0;
			_checkingCount = 0;
			}

			else if (_viValkyrie->state == valkyrieAttack1 && !_viValkyrie->isAttack&& _attackCount % 30 == 0)
			{
				_viValkyrie->isAttack = true;
				_viValkyrie->state = valkyrieAttack2;
				_viValkyrie->Img = IMAGEMANAGER->findImage("valkyrieAttack2");
				_viValkyrie->anim = _valkyrieAttack2;
				_valkyrieAttack2->start();
				_viValkyrie->y = 1570;
				_attackCount = 0;
				_checkingCount = 0;
			}

			
			
		else if (_viValkyrie->state != valkyrieAttack1 && !_viValkyrie->isAttack && _attackCount % 40 == 0)
		{
			_viValkyrie->isAttack = true;
			_viValkyrie->state = valkyrieAttack1;
			_viValkyrie->Img = IMAGEMANAGER->findImage("valkyrieAttack1");
			_viValkyrie->anim = _valkyrieAttack1;
			_valkyrieAttack1->start();
			_viValkyrie->y = 1570;
			_attackCount = 0;
			_checkingCount = 0;
		}


		}













		else if (_kl->getKyleX() + 350 > _viValkyrie->x && _checkingCount > 50)
		{
			_viValkyrie->state = valkyrieWalk;
			_viValkyrie->Img = IMAGEMANAGER->findImage("valkyrieWalk");
			_viValkyrie->anim = _valkyrieWalkAnim;
			_viValkyrie->y = 1580;
			_viValkyrie->x -= 4;
		}


		else
		{
			_viValkyrie->state = valkyrieIdle;
			_viValkyrie->Img = IMAGEMANAGER->findImage("valkyrieIdle");
			_viValkyrie->anim = _valkyrieIdleAnim;
			_viValkyrie->y = 1580;
		}
	}
}
