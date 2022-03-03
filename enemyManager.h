#pragma once
#include "gameNode.h"
#include "elaine.h"
#include <vector>

class kyle;


enum valkyrieState
{
	valkyrieIdle,
	valkyrieWalk,
	valkyrieAttack1,
	valkyrieAttack2,
	valkyrieAttack3
};

struct tagValkyrie
{
	animation* anim;
	image* Img;
	RECT rc;
	RECT attackRc;
	int x, y; // left top
	int HP;



	valkyrieState state;

	bool isAttack, isAttack1, isAttack2, isAttack3;
};



class enemyManager : public gameNode
{
private:

	    vector<tagValkyrie>					_vValkyrie;
		vector<tagValkyrie>::iterator		_viValkyrie;

		kyle* _kl;
		elaine* _elaine;

		animation* _valkyrieIdleAnim;
		animation* _valkyrieWalkAnim;
		animation* _valkyrieAttack1;
		animation* _valkyrieAttack2;
		animation* _valkyrieAttack3;

		int _rndSummonCount;

		int _attackCount,_checkingCount;
public:

	enemyManager();
	~enemyManager();
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void release();

	void removeValkyrie(int arrNum);

	void valkyrieRender(int x,int y);

	void valkyrieFrameUpdate();

	void valkyrieRectUpdate();

	void valkyrieAttackSetting();

	void valkyrieTracking();


	void animInit();

	void animStart();

	void setValkyrie();


	//getter

	int getRndCount() { return _rndSummonCount; }
	//setter
	void valkyrieDamaged(int damage, int t);
	void setValkyrieback(int i);	

	void setRndCount() { _rndSummonCount--; }


	//¼³Á¤ÀÚ
	void setKyleMemoryAddressLink(kyle* kl) { _kl = kl; }

	//getter
	vector<tagValkyrie>			  getVValkyrie()  { return _vValkyrie; }
	vector<tagValkyrie>::iterator getVIvalkyrie() { return _viValkyrie; }
};

