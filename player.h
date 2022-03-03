#pragma once
#include "gameNode.h"
#include "gameData.h"

enum playerState
{
	plLeftIdle,
	plRightIdle,
	plLeftWalk,
	plRightWalk
};

class player : public gameNode
{
private:


	int _playerX;
	int _playerY;
	int _backgroundX;
	int _backgroundY;
	int _cameraPosX;
	int _cameraPosY;
	int _count,_index;
	
	RECT _cameraScreen;

	image* _playerImg;

	animation* _playerAnim;
	animation* _playerRightWalk;
	animation* _playerLeftWalk;
	animation* _playerRightIdle;
	animation* _playerLeftIdle;

	playerState _playerState;

protected:
	int joom;
public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	int getPlayerX() { return _playerX; }
	int getPlayerY() { return _playerY; }

	int setPlayerX(int x) { _playerX = x; return _playerX; }
	int setPlayerY(int y) { _playerY = y; return _playerY; }

	int getBackgroundX() {  return _backgroundX; }
	int getBackgroundY() {  return _backgroundY; }

	int setBackgroundX(int x) { _backgroundX = x; return _backgroundX; }
	int setBackgroundY(int y) { _backgroundY = y; return _backgroundY; }

	int getPlayerImgHeight() { return _playerImg->getHeight(); }
	int getPlayerImgWidth() { return _playerImg->getWidth(); }



	RECT getCameraScreen() { return _cameraScreen; }

	int getCameraX(){ return _cameraScreen.left; }
	int getCameraY() { return _cameraScreen.top; }
	
	void setCameraLeft(int left) { _cameraScreen.left = left; }
	void setCameraRight(int right) { _cameraScreen.right = right; }
	void setCameraTop(int top) { _cameraScreen.top = top; }
	void setCameraBottom(int bottom) { _cameraScreen.bottom = bottom; }

	void playerMove();
	void playerAnimation();
	
};