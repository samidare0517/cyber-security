#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	// プレイヤーの初期化
	void init();

	// ScneneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();

	// 描画
	void draw();
	
	void setDead() { m_isDead = true; }
	bool isDead()const { return m_isDead; }

	// 情報の取得
	Vec2 getPos() const { return m_pos; }


	// 当たり判定の半径取得
	virtual float getRadius() const;

	// 当たり判定の中心位置取得
	virtual Vec2 getCenter() const;


private:

	int m_handle;

	// SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;

	// 移動
	Vec2 m_vec;

	// ショットの発射間隔
	int m_shotInterval;

	bool m_isDead;
};
