#pragma once
#define KYLEMAXHP 1000
#define KYLEMAXMP 200
#define LIARAMAXMP 600
#define LIARAMAXMP 400

class gameData
{
private:

	int _playerCurrentX = 510;
	int _playerCurrentY = 2275;

	int _kyleHP = KYLEMAXHP;
	int _kyleMP = KYLEMAXMP;
	int _kyleBlast = 0; 


	int _liaraHP = LIARAMAXMP;
	int _liaraMP = LIARAMAXMP;

public:

	//getter
	int getPlayerCurrentX() { return _playerCurrentX; }
	int getPlayerCurrentY() { return _playerCurrentY; }
	int getDataKyleBlast() { return _kyleBlast; }
	int getDataKyleHP() { return _kyleHP; }
	int getDataKyleMP() { return _kyleMP; }

	//setter
	void setPlayerCurrentX(int x) { _playerCurrentX = x; }
	void setPlayerCurrentY(int y) { _playerCurrentY = y; }
	void setKyleBlast(int x) { _kyleBlast = x; }
	void setKyleDataHP(int hp) { _kyleHP = hp; }
	void setKyleDataMP(int mp) { _kyleMP = mp; }


};
