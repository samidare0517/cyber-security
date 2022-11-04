#include "DxLib.h"
#include "ShotBase.h"

namespace
{
	// 当たり半径の半径
	constexpr float kColRadius = 16.0f;
}


ShotBase::ShotBase()
{

	m_handle = -1;
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

ShotBase::~ShotBase()
{

}



// ショット開始
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

// 更新
void ShotBase::update()
{
	if (!m_isExist) return;
}


// 当たり判定の半径取得
float ShotBase::getRadius() const
{
	return kColRadius;
}

// 当たり判定の中心位置取得
Vec2 ShotBase::getCenter() const
{
	int sizeX = 0;
	int sizeY = 0;

	if (GetGraphSize(m_handle, &sizeX, &sizeY) == -1)
	{
		// サイズが取得できなかった場合は左位置を渡しておく
		return m_pos;
	}

	Vec2 result = m_pos;
	result.x += sizeX / 2;
	result.y += sizeY / 2;

	return result;
}



// 表示
void ShotBase::draw()
{
	if (!m_isExist)return;
	DrawGraph(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}