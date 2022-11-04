#pragma once
#include "Vec2.h"
#include "game.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void setHandle(int handle) { m_handle = handle; }
	void init();
	void setPos(float x, float y);
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	void update();
	void draw();
	void setDead() { m_isDead = true; }
	

	Vec2 getPos() const { return m_pos; }

	// 当たり判定の半径取得
	virtual float getRadius() const;

	// 当たり判定の中心位置取得
	virtual Vec2 getCenter() const;
	
	// ほかの敵に当たった場ありの反射処理
	virtual void bound(Vec2 targetPos);
	
	bool isDead()const{return m_isDead;}


private:

	int m_handle;	// 画像のハンドル
	int sizeX;
	int sizeY;
	SceneMain* m_pMain;

	

	// 位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// 左上座標
	Vec2 m_size;

	bool m_isDead;

};
