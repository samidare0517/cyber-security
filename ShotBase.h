#pragma once
#include "Vec2.h"

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	void setHandle(int handle) { m_handle = handle; }


	// ショット開始
	virtual void start (Vec2 pos);

	// 更新
	virtual void update();

	// 表示
	virtual void draw();

	

	// 存在するか
	bool isExist() const { return m_isExist; }

	// 当たり判定の半径取得
	virtual float getRadius() const;

	// 当たり判定の中心位置取得
	virtual Vec2 getCenter() const;

	

protected:

	// グラフィックハンドル
	int m_handle;


	// 表示位置
	Vec2 m_pos;

	// 移動
	Vec2 m_vec;

	// 存在するか
	bool m_isExist;


};