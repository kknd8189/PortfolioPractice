#pragma once
#include "gameNode.h"
#include "progressbar.h"
#include "gameData.h"
#include "effect.h"


#define FLICTION 0.15f
#define GRAVITY 0.18f
#define JUMPPOWER 5.0f
#define ACCELERATION 2.0f
#define MAXSPEED 6.0f


enum kyleState
{
	rightIdle,
	leftIdle,
	leftRun,
	rightRun,
	leftJump,
	rightJump,
	attack1,
	attack2,
	attack3,
	wasa1,
	wasa2,
	guard,
	leftFall,
	rightFall
};
struct TagKyle
{
	float speed;
	float currentSpeed;
	int x, y; //left top
	float jumpPower;
	float gravity;
	bool isJump;
	float friction;

	bool isBlast;
	bool isBioe;

	int blastCount;

	int SP,HP,MP,blast;

	image* kyleImg;

	RECT rc;
	RECT attack1;
	RECT attack2;
	RECT attack3;
	RECT wasa1;
	RECT wasa2;
	RECT bioeRc;

	animation* kyleAnim;

	animation* kyleRightIdleAnim;
	animation* kyleRightRunAnim;
	animation* kyleLeftIdleAnim;
	animation* kyleLeftRunAnim;

	animation* kyleLeftWalkAnim;


	animation* kyleLeftStopAnim;
	animation* kyleRightStopAnim;

	animation* kyleLeftJumpAnim;
	animation* kyleRightJumpAnim;
	animation* kyleLeftFallAnim;
	animation* kyleRightFallAnim;

	animation* kyleAttack1Anim;
	animation* kyleAttack2Anim;
	animation* kyleAttack3Anim;

	animation* kyleWasa1Anim;
	animation* kyleWasa2Anim;

	animation* kyleHitAnim;
	animation* kyleGuardAnim;

};
struct tagCamera
{
	RECT Screen;
	int PosX, PosY;
};


class enemyManager;

class kyle :public gameNode,gameData
{

private:
	TagKyle _kyle;
	kyleState _kyleState;
	tagCamera _camera;
	enemyManager* _em;

	float joom;
	int _index;
	int _frameCount;
	int _count;
	int _maxY;

public:
	kyle();
	~kyle();


	virtual HRESULT init();
	virtual void release();
	virtual void update();

	virtual void render();


	//getter
	int getKyleX(){  return _kyle.x; }
	int getKyleY(){  return _kyle.y; }

	int getCameraX() { return _camera.Screen.left; }
	int getCameraY() { return _camera.Screen.top; }

	int getKyleHP() { return _kyle.HP; }
	int getKyleMP() { return _kyle.MP; }
	int getKyleSP() { return _kyle.SP; }
	bool getkyleBioe() { return _kyle.isBioe; }
	int getKyleBlast() { return _kyle.blast; }
	float getKyleCurrentSpeed() { return _kyle.currentSpeed; }
	float getKyleFriction() { return _kyle.friction; }

	RECT getkyleRC() { return _kyle.rc; }
	RECT getkyleAttack1() { return _kyle.attack1; }
	RECT getkyleAttack2() { return _kyle.attack2; }
	RECT getkyleAttack3() { return _kyle.attack3; }
	RECT getkyleWasa1() { return _kyle.wasa1; }
	RECT getkyleWasa2() { return _kyle.wasa2; }
	RECT getkyleBioeRC() { return _kyle.bioeRc; }
	


	TagKyle getTagKyle() { return _kyle; }



	//setter
	void setCameraX(int x) { _camera.Screen.left = x; }
	void setCameraY(int y) { _camera.Screen.top  = y; }
	void setKyleX(int x) { _kyle.x = x; }
	void setKyleY(int y) { _kyle.y = y; }
	void setKyleHP(int hp) { _kyle.HP = hp; }
	void setKyleMP(int mp) { _kyle.MP = mp; }
	void setKyleBlast(int blast) { _kyle.blast = blast; }
	void setKyleBlastCount(int blastCount) { _kyle.blastCount = blastCount; }
	void setKyleIsBlast(bool isBlast) { _kyle.isBlast = isBlast; }

	void SetrcAttack1(RECT rc) { _kyle.attack1 = rc; }
	void SetrcAttack2(RECT rc) { _kyle.attack2 = rc; }
	void SetrcAttack3(RECT rc) { _kyle.attack3 = rc; }
	void SetrcWasa1(RECT rc) { _kyle.wasa1 = rc; }
	void SetrcWasa2(RECT rc) { _kyle.wasa2 = rc; }

	float setKyleCurrentSpeed(float speed) { _kyle.currentSpeed = speed; return _kyle.currentSpeed; }
	float setKyleFriction(float fliction) { _kyle.friction = fliction; return _kyle.friction; }


	void kyleHitted(int damage);

	void kyleRectRemove(RECT rc);

	void kyleJump();
	void kyleMove();
	void frameUpdate();
	void animStart();
	void animInit();
	void kyleGuard();
	void kyleStateDebug();
	void kyleAttack();
	void kyleSkill();
	void kyleState();
	void kyleBlast();
	void kyleBieo();

	//¼³Á¤ÀÚ
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

};