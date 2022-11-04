#include "DxLib.h"
#include "enemy.h"
#include "game.h"
#include <cmath>

namespace
{
	// 当たり半径の半径
	constexpr float kColRadius = 16.0f;

	// キャラクターの移動速度
	constexpr int kSpeedX = 8;
	constexpr int kSpeedY = 8;
}

Enemy::Enemy()
{
	

	sizeX = 0;
	sizeY = 0;

	// 画像データ
	m_handle = 0;		// 画像のハンドル

	// 位置
	m_pos;

	// 移動量
	m_vec;


}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	// 初期速度を設定
	m_vec.x = 6.5f;
	m_vec.y = 6.5f;

}

void Enemy::setPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Enemy::update()
{
	m_pos += m_vec;

	if (m_pos.x < 0.0f)
	{
		m_pos.x = 0.0f;
		m_vec.x *= -1.0f;
	}
	if (m_pos.x > Game::kScreenWindth - sizeX)
	{
		m_pos.x = static_cast<float>(Game::kScreenWindth - sizeX);
		m_vec.x *= -1.0f;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_vec.y *= -1.0f;
	}
	if (m_pos.y > Game::kScreenHeight - sizeY)
	{
		m_pos.y = static_cast<float>(Game::kScreenHeight - sizeY);
		m_vec.y *= -1.0f;
	}
}


void Enemy::draw()
{
	if (m_isDead) return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}

// 当たり判定の半径取得
float Enemy::getRadius()const
{
	return kColRadius;
}

// 当たり判定の中心位置取得
Vec2 Enemy::getCenter() const
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

void Enemy::bound(Vec2 targetPos)
{
	// 反射方向
	Vec2 boundDir = m_pos - targetPos;

	// 現在の速度と同じ速度にする
	float speed = m_vec.length();

	// 反対方向に現在の速度で移動するようにする
	m_vec = boundDir.normalize() * speed;
}
