#include "pch.h"
#include "kyle.h"
#include "enemyManager.h"


kyle::kyle()
{
}

kyle::~kyle()
{

}

HRESULT kyle::init()
{


	joom = 4;

	_kyle.speed = 0;
	_kyle.currentSpeed = 0;
	_kyle.jumpPower = 0;
	_kyle.gravity = 0;
	_kyle.friction = 0;
	_kyle.isJump = false;

	_kyle.x = 200;
	_kyle.y = 1500;
	_index = 0;
	_count = 0;
	_camera.PosX = 400;
	_camera.PosY = WINSIZEY - 500;

	_kyle.SP = 500;


	_maxY = 1500;

	_kyle.isBlast = false;
	_kyle.blastCount = 0;


	_kyle.kyleImg = IMAGEMANAGER->addFrameImage("kyleIdle", "image/kyle/kyle_idle.bmp", 2300, 360, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleRun", "image/kyle/kyle_run.bmp", 1380, 360, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleAttack1", "image/kyle/kyle_attack1.bmp", 1380, 360, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleAttack2", "image/kyle/kyle_attack2.bmp", 1840, 360, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleAttack3", "image/kyle/kyle_attack3.bmp", 1380, 360, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleWasa1", "image/kyle/kyle_wasa1.bmp", 1380, 180, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleWasa2", "image/kyle/kyle_wasa2.bmp", 1840, 180, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleJump", "image/kyle/kyle_jump.bmp", 230, 360, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleFall", "image/kyle/kyle_fall.bmp", 230, 360, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleStop", "image/kyle/kyle_stop.bmp", 230, 360, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleDie", "image/kyle/kyle_die.bmp", 48 * joom, 46 * joom, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleGuard", "image/kyle/kyle_guard.bmp", 230, 180, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleHit", "image/kyle/kyle_hit.bmp", 230, 180, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("kyleBioe", "image/kyle/kyle_bioe.bmp", 7820, 180, 34, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("blastEffect", "image/blastEffect.bmp", 5130, 191, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("blastEffect", "image/blastEffect.bmp", 5130, 191, 190, 191, 1, 0.1f, 1000);


	////////////////////////////////////////////////////////////////////////

	animInit();

	_kyle.kyleAnim = _kyle.kyleRightIdleAnim;

	animStart();

	return S_OK;
}

void kyle::release()
{
}

void kyle::update()
{


	if (!_kyle.isBioe)
	{

		if (_kyle.SP <= 500)
		{
			if (_kyleState != attack1 && _kyleState != attack2 && _kyleState != attack3 && _kyleState != wasa1 && _kyleState != wasa2)
				_kyle.SP++;
		}


		_kyle.rc = RectMake(_kyle.x - _camera.Screen.left + 50, _kyle.y - _camera.Screen.top+50, 100, 100);

		//카메라 스크린
		_camera.Screen = RectMake(_kyle.x - _camera.PosX, +_kyle.y - _camera.PosY, WINSIZEX, WINSIZEY);

		if (_kyle.x <= -80) _kyle.x = -80;
		if (_kyle.x >= 2500)_kyle.x = 2500;

		if ((_kyleState == rightFall || _kyleState == rightJump) && _kyle.currentSpeed <= 0)
		{
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
		}
		else if ((_kyleState == leftFall || _kyleState == leftJump) && _kyle.currentSpeed >= 0)
		{
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
		}

		if (_kyleState == wasa2)
		{
			_kyle.y -= 5;
		}

		if (_kyleState == rightFall)
		{
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleFall");
			_kyle.kyleAnim = _kyle.kyleRightFallAnim;
		}

		kyleGuard();

		kyleJump();
		kyleMove();
		kyleState();
		frameUpdate();
		kyleAttack();
		kyleSkill();
		kyleBlast();


		if(_kyle.isBlast) _kyle.blast = 0;
	}

	kyleBieo();


	EFFECTMANAGER->update();
	//////////////////////////////////////////////////////////////////////


}

void kyle::render()
{
	// 디버깅
	char str[25];

	sprintf_s(str, "x: %d", _kyle.x);
	TextOut(getMemDC(), 20, 80, str, strlen(str));

	sprintf_s(str, "y : %d", _kyle.y);
	TextOut(getMemDC(), 20, 90, str, strlen(str));

	sprintf_s(str, "jumpPower :  %f", _kyle.jumpPower);
	TextOut(getMemDC(), 20, 100, str, strlen(str));

	sprintf_s(str, "gravity:%f", _kyle.gravity);
	TextOut(getMemDC(), 20, 110, str, strlen(str));

	sprintf_s(str, "isJump:%d", _kyle.isJump);
	TextOut(getMemDC(), 20, 120, str, strlen(str));


	sprintf_s(str, "fliction:%f", _kyle.friction);
	TextOut(getMemDC(), 20, 130, str, strlen(str));

	sprintf_s(str, "currentSpeed:%f", _kyle.currentSpeed);
	TextOut(getMemDC(), 20, 140, str, strlen(str));


	kyleStateDebug();

	sprintf_s(str, "isBlast:%d", _kyle.isBlast);
	TextOut(getMemDC(), 20, 170, str, strlen(str));


	sprintf_s(str, "Blast:%d", _kyle.blast);
	TextOut(getMemDC(), 20, 180, str, strlen(str));


	sprintf_s(str, "Blastcount:%d", _kyle.blastCount);
	TextOut(getMemDC(), 20, 190, str, strlen(str));


	sprintf_s(str, "MP:%d", _kyle.MP);
	TextOut(getMemDC(), 20, 200, str, strlen(str));

	sprintf_s(str, "isBioe : %d", _kyle.isBioe);
	TextOut(getMemDC(), 20, 210, str, strlen(str));


	sprintf_s(str, "count : %d", _frameCount);
	TextOut(getMemDC(), 20, 220, str, strlen(str));


	sprintf_s(str, "index : %d", _index);
	TextOut(getMemDC(), 20, 230, str, strlen(str));

	if (!_kyle.isBioe)
	{
		_kyle.kyleImg->aniRender(getMemDC(), _kyle.x - _camera.Screen.left, _kyle.y - _camera.Screen.top, _kyle.kyleAnim);
	}
	else
	{
		IMAGEMANAGER->addImage("image/blackBackground", 1200, 800)->render(getMemDC(),0,0);
		_kyle.kyleImg->frameRender(getMemDC(), _kyle.x - _camera.Screen.left, _kyle.y - _camera.Screen.top);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _kyle.rc);
		Rectangle(getMemDC(), _kyle.attack1);
		Rectangle(getMemDC(), _kyle.attack2);
		Rectangle(getMemDC(), _kyle.attack3);
		Rectangle(getMemDC(), _kyle.wasa1);
		Rectangle(getMemDC(), _kyle.wasa2);
		Rectangle(getMemDC(), _kyle.bioeRc);


	}
	EFFECTMANAGER->render();

}

void kyle::kyleState()
{

	if (_kyle.currentSpeed > 0 && _kyle.isJump == false)
	{
		_kyleState = rightRun;
	}
	else if (_kyle.currentSpeed < 0 && _kyle.isJump == false)
	{
		_kyleState = leftRun;
	}
	/////////////////////////////////////////////////

	if (_kyleState == rightRun && _kyle.currentSpeed <= 1)
	{
		_kyle.currentSpeed = 0;
		_kyle.friction = 0;
		_kyleState = rightIdle;
	}
	else if (_kyleState == leftRun && _kyle.currentSpeed >= -1)
	{
		_kyle.currentSpeed = 0;
		_kyle.friction = 0;
		_kyleState = leftIdle;
	}

	/////////////////////////////////////////////////


	else if (_kyle.friction != 0 && _kyleState == rightRun)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleStop");
		_kyle.kyleAnim = _kyle.kyleRightStopAnim;
	}

	else if (_kyle.friction != 0 && _kyleState == leftRun)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleStop");
		_kyle.kyleAnim = _kyle.kyleLeftStopAnim;
	}

	/////////////////////////////////////////////////
	else if (_kyleState == rightIdle)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleIdle");
		_kyle.kyleAnim = _kyle.kyleRightIdleAnim;
	}
	else if (_kyleState == leftIdle)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleIdle");
		_kyle.kyleAnim = _kyle.kyleLeftIdleAnim;
	}
	/////////////////////////////////////////////////
	else if (_kyleState == rightRun)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleRun");
		_kyle.kyleAnim = _kyle.kyleRightRunAnim;
	}

	else if (_kyleState == leftRun)
	{
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleRun");
		_kyle.kyleAnim = _kyle.kyleLeftRunAnim;
	}
}

void kyle::kyleHitted(int damage)
{
	if (_kyleState != guard)
	{
		_kyle.HP -= damage;
	}
	else
	{
		_kyle.HP -= damage / 10;
	}
}

void kyle::kyleRectRemove(RECT rc)
{
	rc = RectMake(0,0,0,0);
}

void kyle::kyleJump()
{
	_kyle.y -= _kyle.jumpPower;
	_kyle.jumpPower -= _kyle.gravity;

	if (KEYMANAGER->isOnceKeyDown('W') && !_kyle.isJump && _kyleState != attack1 && _kyleState != attack2 && _kyleState != attack3)
	{
		_kyle.jumpPower = JUMPPOWER;
		_kyle.gravity = GRAVITY;
		_kyle.isJump = true;

		if (_kyleState == rightIdle || _kyleState == rightRun)
		{
			_kyleState = rightJump;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleJump");
			_kyle.kyleAnim = _kyle.kyleRightJumpAnim;
		}

		else if (_kyleState == leftIdle || _kyleState == leftRun)
		{
			_kyleState = leftJump;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleJump");
			_kyle.kyleAnim = _kyle.kyleLeftJumpAnim;
		}
	}

	if (_kyleState == rightJump && _kyle.jumpPower <= 0)
	{
		_kyleState = rightFall;
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleFall");
		_kyle.kyleAnim = _kyle.kyleRightFallAnim;
	}
	else if (_kyleState == leftJump && _kyle.jumpPower <= 0)
	{
		_kyleState = leftFall;
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleFall");
		_kyle.kyleAnim = _kyle.kyleLeftFallAnim;
	}
	if (_kyle.y > _maxY)
	{
		_kyle.isJump = false;
		_kyle.y = _maxY;
		_kyle.jumpPower = 0;
		_kyle.gravity = 0;

		if (_kyleState == leftFall)
		{
			_kyleState = leftIdle;
		}
		else if (_kyleState == rightFall)
		{
			_kyleState = rightIdle;
		}

	}
}

void kyle::kyleMove()
{
	_kyle.x += _kyle.currentSpeed;
	_kyle.currentSpeed -= _kyle.friction;

	if (KEYMANAGER->isStayKeyDown('A') && _kyleState != rightRun && _kyle.currentSpeed >= -MAXSPEED)
	{
		_kyle.currentSpeed -= ACCELERATION;
	}

	if (KEYMANAGER->isOnceKeyDown('A') && _kyleState != rightRun)
	{
		_kyle.friction = 0;

	}

	if (KEYMANAGER->isOnceKeyUp('A') && _kyleState != rightRun)
	{
		_kyle.friction = -FLICTION;
	}

	////////////////////////////////////////////////////////////////
	if (KEYMANAGER->isStayKeyDown('D') && _kyleState != leftRun && _kyle.currentSpeed <= MAXSPEED)
	{
		_kyle.currentSpeed += ACCELERATION;
	}

	if (KEYMANAGER->isOnceKeyDown('D') && _kyleState != leftRun)
	{
		_kyle.friction = 0;
	}

	if (KEYMANAGER->isOnceKeyUp('D') && _kyleState != leftRun)
	{
		_kyle.friction = FLICTION;
	}
}

void kyle::frameUpdate()
{
	_kyle.kyleRightIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);
	_kyle.kyleRightRunAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_kyle.kyleLeftIdleAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);
	_kyle.kyleLeftRunAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_kyle.kyleLeftStopAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_kyle.kyleRightStopAnim->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_kyle.kyleAttack1Anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	_kyle.kyleAttack2Anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	_kyle.kyleAttack3Anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
	_kyle.kyleWasa1Anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_kyle.kyleWasa2Anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void kyle::animStart()
{
	_kyle.kyleRightIdleAnim->start();
	_kyle.kyleLeftIdleAnim->start();
	_kyle.kyleRightRunAnim->start();
	_kyle.kyleLeftRunAnim->start();
	_kyle.kyleRightStopAnim->start();
	_kyle.kyleLeftStopAnim->start();
	_kyle.kyleHitAnim->start();
}

void kyle::animInit()
{
	//애니메이션
	int arrRightIdle[] = { 0, 1, 2, 3, 4 ,5,6,7,8,9 };
	_kyle.kyleRightIdleAnim = new animation;
	_kyle.kyleRightIdleAnim->init(_kyle.kyleImg->getWidth(), _kyle.kyleImg->getHeight(), 230, 180);
	_kyle.kyleRightIdleAnim->setPlayFrame(arrRightIdle, 10, true);
	_kyle.kyleRightIdleAnim->setFPS(1);

	int arrLeftIdle[] = { 10,11,12,13,14,15,16,17,18,19 };
	_kyle.kyleLeftIdleAnim = new animation;
	_kyle.kyleLeftIdleAnim->init(_kyle.kyleImg->getWidth(), _kyle.kyleImg->getHeight(), 230, 180);
	_kyle.kyleLeftIdleAnim->setPlayFrame(arrLeftIdle, 10, true);
	_kyle.kyleLeftIdleAnim->setFPS(1);

	int arrRightRun[] = { 0, 1, 2, 3, 4 ,5 };
	_kyle.kyleRightRunAnim = new animation;
	_kyle.kyleRightRunAnim->init(IMAGEMANAGER->findImage("kyleRun")->getWidth(), IMAGEMANAGER->findImage("kyleRun")->getHeight(),
		230, 180);
	_kyle.kyleRightRunAnim->setPlayFrame(arrRightRun, 6, true);
	_kyle.kyleRightRunAnim->setFPS(1);

	int arrLeftRun[] = { 6 ,7 ,8 ,9 ,10 , 11 };
	_kyle.kyleLeftRunAnim = new animation;
	_kyle.kyleLeftRunAnim->init(IMAGEMANAGER->findImage("kyleRun")->getWidth(), IMAGEMANAGER->findImage("kyleRun")->getHeight(),
		230, 180);
	_kyle.kyleLeftRunAnim->setPlayFrame(arrLeftRun, 5, true);
	_kyle.kyleLeftRunAnim->setFPS(1);


	int arrLeftStop[] = { 1 };
	_kyle.kyleLeftStopAnim = new animation;
	_kyle.kyleLeftStopAnim->init(IMAGEMANAGER->findImage("kyleStop")->getWidth(), IMAGEMANAGER->findImage("kyleStop")->getHeight(),
		230, 180);
	_kyle.kyleLeftStopAnim->setPlayFrame(arrLeftStop, 1, false);
	_kyle.kyleLeftStopAnim->setFPS(1);

	int arrRightStop[] = { 0 };
	_kyle.kyleRightStopAnim = new animation;
	_kyle.kyleRightStopAnim->init(IMAGEMANAGER->findImage("kyleStop")->getWidth(), IMAGEMANAGER->findImage("kyleStop")->getHeight(),
		230, 180);
	_kyle.kyleRightStopAnim->setPlayFrame(arrRightStop, 1, false);
	_kyle.kyleRightStopAnim->setFPS(1);

	int arrRightJump[] = { 0 };
	_kyle.kyleRightJumpAnim = new animation;
	_kyle.kyleRightJumpAnim->init(IMAGEMANAGER->findImage("kyleJump")->getWidth(), IMAGEMANAGER->findImage("kyleJump")->getHeight(),
		230, 180);
	_kyle.kyleRightJumpAnim->setPlayFrame(arrRightJump, 1, false);
	_kyle.kyleRightJumpAnim->setFPS(1);

	int arrLeftJump[] = { 1 };
	_kyle.kyleLeftJumpAnim = new animation;
	_kyle.kyleLeftJumpAnim->init(IMAGEMANAGER->findImage("kyleJump")->getWidth(), IMAGEMANAGER->findImage("kyleJump")->getHeight(),
		230, 180);
	_kyle.kyleLeftJumpAnim->setPlayFrame(arrLeftJump, 1, false);
	_kyle.kyleLeftJumpAnim->setFPS(1);

	int arrAttack1[] = { 0,1,2,3,4,5 };
	_kyle.kyleAttack1Anim = new animation;
	_kyle.kyleAttack1Anim->init(IMAGEMANAGER->findImage("kyleAttack1")->getWidth(), IMAGEMANAGER->findImage("kyleAttack1")->getHeight(),
		230, 180);
	_kyle.kyleAttack1Anim->setPlayFrame(arrAttack1, 6, false);
	_kyle.kyleAttack1Anim->setFPS(1);

	int arrAttack2[] = { 0,1,2,3,4,5,6,7 };
	_kyle.kyleAttack2Anim = new animation;
	_kyle.kyleAttack2Anim->init(IMAGEMANAGER->findImage("kyleAttack2")->getWidth(), IMAGEMANAGER->findImage("kyleAttack2")->getHeight(),
		230, 180);
	_kyle.kyleAttack2Anim->setPlayFrame(arrAttack2, 8, false);
	_kyle.kyleAttack2Anim->setFPS(1);

	int arrAttack3[] = { 0,1,2,3 ,4, 5 };
	_kyle.kyleAttack3Anim = new animation;
	_kyle.kyleAttack3Anim->init(IMAGEMANAGER->findImage("kyleAttack3")->getWidth(), IMAGEMANAGER->findImage("kyleAttack3")->getHeight(),
		230, 180);
	_kyle.kyleAttack3Anim->setPlayFrame(arrAttack3, 6, false);
	_kyle.kyleAttack3Anim->setFPS(1);

	int arrWasa1[] = { 0,1,2,3,4,5 };
	_kyle.kyleWasa1Anim = new animation;
	_kyle.kyleWasa1Anim->init(IMAGEMANAGER->findImage("kyleWasa1")->getWidth(), IMAGEMANAGER->findImage("kyleWasa1")->getHeight(),
		230, 180);
	_kyle.kyleWasa1Anim->setPlayFrame(arrWasa1, 6, false);
	_kyle.kyleWasa1Anim->setFPS(1);

	int arrWasa2[] = { 0,1,2,3,4,5,6,7 };
	_kyle.kyleWasa2Anim = new animation;
	_kyle.kyleWasa2Anim->init(IMAGEMANAGER->findImage("kyleWasa2")->getWidth(), IMAGEMANAGER->findImage("kyleWasa2")->getHeight(),
		230, 180);
	_kyle.kyleWasa2Anim->setPlayFrame(arrWasa2, 8, false);
	_kyle.kyleWasa2Anim->setFPS(1);

	int arrHit[] = { 0 };
	_kyle.kyleHitAnim = new animation;
	_kyle.kyleHitAnim->init(IMAGEMANAGER->findImage("kyleHit")->getWidth(), IMAGEMANAGER->findImage("kyleHit")->getHeight(),
		30 * joom, 49 * joom);
	_kyle.kyleHitAnim->setPlayFrame(arrHit, 1, false);
	_kyle.kyleHitAnim->setFPS(1);


	_kyle.kyleGuardAnim = new animation;
	_kyle.kyleGuardAnim->init(IMAGEMANAGER->findImage("kyleGuard")->getWidth(), IMAGEMANAGER->findImage("kyleGuard")->getHeight(),
		230, 180);
	_kyle.kyleGuardAnim->setPlayFrame(arrHit, 1, false);
	_kyle.kyleGuardAnim->setFPS(1);

	_kyle.kyleRightFallAnim = new animation;
	_kyle.kyleRightFallAnim->init(IMAGEMANAGER->findImage("kyleFall")->getWidth(), IMAGEMANAGER->findImage("kyleFall")->getHeight(),
		230, 180);
	_kyle.kyleRightFallAnim->setPlayFrame(arrHit, 1, false);
	_kyle.kyleRightFallAnim->setFPS(1);

	int arrHit2[] = { 1 };
	_kyle.kyleLeftFallAnim = new animation;
	_kyle.kyleLeftFallAnim->init(IMAGEMANAGER->findImage("kyleFall")->getWidth(), IMAGEMANAGER->findImage("kyleFall")->getHeight(),
		230, 180);
	_kyle.kyleLeftFallAnim->setPlayFrame(arrHit2, 1, false);
	_kyle.kyleLeftFallAnim->setFPS(1);

}

void kyle::kyleGuard()
{

	if (KEYMANAGER->isStayKeyDown('S') && _kyleState == rightIdle)
	{
		_kyleState = guard;
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleGuard");
		_kyle.kyleAnim = _kyle.kyleGuardAnim;
	}
	if (KEYMANAGER->isOnceKeyUp('S') && _kyleState == guard)
	{
		_kyleState = rightIdle;
	}
}

void kyle::kyleStateDebug()
{
	char str[25];

	if (_kyleState == leftIdle)
	{
		sprintf_s(str, "enum : leftIdle");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == rightIdle)
	{
		sprintf_s(str, "enum : rightIdle");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == rightRun)
	{
		sprintf_s(str, "enum : rightRun");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == leftRun)
	{
		sprintf_s(str, "enum : leftRun");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == leftJump)
	{
		sprintf_s(str, "enum : leftJump");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == rightJump)
	{
		sprintf_s(str, "enum : rightJump");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == attack1)
	{
		sprintf_s(str, "enum : attack1");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == attack2)
	{
		sprintf_s(str, "enum : attack2");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == attack3)

	{
		sprintf_s(str, "enum : attack3");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}

	else if (_kyleState == guard)
	{
		sprintf_s(str, "enum : guard");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == leftFall)
	{
		sprintf_s(str, "enum : leftFall");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}
	else if (_kyleState == rightFall)
	{
		sprintf_s(str, "enum : rightFall");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}

	else if (_kyleState == wasa1)
	{
		sprintf_s(str, "enum : wasa1");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}

	else if (_kyleState == wasa2)
	{
		sprintf_s(str, "enum : wasa2");
		TextOut(getMemDC(), 20, 150, str, strlen(str));
	}

	sprintf_s(str, "SP : %d", _kyle.SP);
	TextOut(getMemDC(), 20, 160, str, strlen(str));
}

void kyle::kyleAttack()
{
	if (KEYMANAGER->isOnceKeyDown('K') && !_kyle.isJump && _kyle.SP >= 50)
	{
		_kyle.blast += 5;

		_kyle.SP -= 50;


		if (_kyle.isBlast && _kyleState == wasa1)
		{
			_kyle.isBioe = true;
		}

		else if (_kyleState != attack1 && _kyleState != attack2)
		{
			_count = 0;
			_kyleState = attack1;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleAttack1");
			_kyle.kyleAnim = _kyle.kyleAttack1Anim;
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
			_kyle.kyleAnim->start();
			_kyle.attack1 = RectMake(_kyle.x - _camera.Screen.left + 100, _kyle.y - _camera.Screen.top+ 50, 100,100);

		}
		else if (_kyleState == attack1)
		{
			_count = 0;
			_kyleState = attack2;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleAttack2");
			_kyle.kyleAnim = _kyle.kyleAttack2Anim;
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
			_kyle.kyleAnim->start();
			_kyle.attack2 = RectMake(_kyle.x - _camera.Screen.left + 100, _kyle.y - _camera.Screen.top + 50,100,100);

		}

		else if (_kyleState == attack2)
		{
			_count = 0;
			_kyleState = attack3;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleAttack3");
			_kyle.kyleAnim = _kyle.kyleAttack3Anim;
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
			_kyle.kyleAnim->start();
			_kyle.attack3 = RectMake(_kyle.x - _camera.Screen.left + 100, _kyle.y - _camera.Screen.top + 50, 100, 100);

		}


	}

	if (_kyleState == attack1)
	{
		_count++;
		if (_count >= 40)
		{
			_kyleState = rightIdle;
			_count = 0;
		}
		if (_count >= 10)
		{
			_kyle.attack1 = RectMake(0, 0, 0, 0);
		}
	}

	else if (_kyleState == attack2)
	{
		_count++;
		if (_count >= 40)
		{
			_kyleState = rightIdle;
			_count = 0;
		}
		if (_count >= 10)
		{
			_kyle.attack2 = RectMake(0, 0, 0, 0);
		}
	}

	else if (_kyleState == attack3)
	{
		_count++;
		if (_count >= 40)
		{
			_kyleState = rightIdle;
			_count = 0;
		}
		if (_count >= 10)
		{
			_kyle.attack3 = RectMake(0, 0, 0, 0);
		}
	}
};

void kyle::kyleSkill()
{
	if (KEYMANAGER->isOnceKeyDown('L') && _kyle.MP > 30 && _kyle.SP > 200)
	{
		if (_kyleState == guard && !_kyle.isJump)
		{
			_kyle.SP -= 100;
			_kyle.MP -= 30;
			_count = 0;
			_kyleState = wasa1;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleWasa1");
			_kyle.kyleAnim = _kyle.kyleWasa1Anim;
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
			_kyle.kyleAnim->start();
			_kyle.wasa1 = RectMake(_kyle.x - _camera.Screen.left + 100, _kyle.y - _camera.Screen.top, 150, 150);
		}
		else if (_kyleState != wasa1 && _kyleState == rightJump)
		{
			_kyle.MP -= 30;
			_kyle.SP -= 100;
			_count = 0;
			_kyleState = wasa2;
			_kyle.isJump = true;
			_kyle.kyleImg = IMAGEMANAGER->findImage("kyleWasa2");
			_kyle.kyleAnim = _kyle.kyleWasa2Anim;
			_kyle.currentSpeed = 0;
			_kyle.friction = 0;
			_kyle.kyleAnim->start();
			_kyle.wasa2 = RectMake(_kyle.x - _camera.Screen.left+ 100, _kyle.y - _camera.Screen.top, 150, 150);

		}
	}


	if (_kyleState == wasa1)
	{
		_count++;
		if (_count >= 40)
		{
			_kyleState = rightIdle;
			_count = 0;
		}

		if (_count >= 10)
		{
			_kyle.wasa1 = RectMake(0, 0, 0, 0);
		}
	}

	else if (_kyleState == wasa2)
	{
		_count++;
		if (_count >= 40)
		{
			_kyleState = rightFall;
			_count = 0;
		}

		if (_count >= 10)
		{
			_kyle.wasa2 = RectMake(0, 0, 0, 0);
		}
	}
}

void kyle::kyleBlast()
{
	if (_kyle.blast >= 100 && !_kyle.isBlast)
	{
		EFFECTMANAGER->play("blastEffect", 240, WINSIZEY - 100);
		_kyle.isBlast = true;
		_kyle.blastCount = 1000;
	}

	if (_kyle.isBlast)
	{
		_kyle.blastCount--;

		_kyle.SP = 500;

		if (_kyle.MP <= 200) _kyle.MP += 1;

		if (_kyle.blastCount <= 0)
		{
			_kyle.isBlast = false;
			_kyle.blast = 0;
		}

		if (_kyle.blastCount % 290 == 130)
		{
			EFFECTMANAGER->play("blastEffect", 240, WINSIZEY - 100);
		}
	}


}

void kyle::kyleBieo()
{
	if (_kyle.isBioe)
	{
		_kyle.bioeRc = RectMake(_kyle.x - _camera.Screen.left + 100, _kyle.y - _camera.Screen.top, 150, 150);
		_frameCount++;
		_kyle.isBlast = false;
		_kyle.kyleImg = IMAGEMANAGER->findImage("kyleBioe");

		if (_frameCount % 5 == 0)
		{
			_kyle.kyleImg->setFrameX(_index);

			_index++;

			if (_index >= 29 && _index <= 31)
			{
				_kyle.y -= 10;
				_kyle.x += 1;
			}
			else if (_index > 31 && _index <= 34)
			{
				_kyle.y += 10;
				_kyle.x += 1;
			}

		}

		if (_kyle.kyleImg->getFrameX() >= _kyle.kyleImg->getMaxFrameX())
		{
			_kyle.isBioe = false;
			_kyle.blastCount = 0;
			_kyle.blast = 0;
			_index = 0;
			_kyle.SP = 0;
			_kyle.kyleImg->setFrameX(_index);
			_kyle.bioeRc = RectMake(0, 0, 0, 0);
		}
	}

	
}