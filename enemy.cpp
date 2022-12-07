#include "DxLib.h"
#include "enemy.h"
#include "game.h"
#include <cmath>

namespace
{
	// 当たり半径の半径
	constexpr float kColRadius = 21.0f;

	// キャラクターの移動速度
	constexpr int kSpeedX = 8;
	constexpr int kSpeedY = 8;
	
	// EnemySinが右移動しているかどうかのフラグをリセット 
	bool enemyRightMove = true;
}

Enemy::Enemy()
{
	sizeX = 0;
	sizeY = 0;

	// 画像データ
	m_handle = -1;		// 画像のハンドル

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


// EnemySinの処理
EnemySin::EnemySin()
{

}

void EnemySin::init()
{
	m_vec.x = 1.0f;
	m_vec.y = 0.0f;
}

void EnemySin::setPos(float x, float y)
{
	Enemy::setPos(x, y);
	m_basePos = m_pos;

}

void EnemySin::update()
{
	m_basePos += m_vec;
	m_sinRate += 0.05f;

	m_pos = m_basePos;
	m_pos.y += sinf(m_sinRate) * 128.0f;

	// 画面外に出そうになったら左端からリピートさせる
	if (m_basePos.x > Game::kScreenWindth)
	{
		m_basePos.x = 0;
	}
}

void EnemySin::draw()
{
	if (m_isDead) return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}


// 当たり判定の半径取得
float EnemySin::getRadius()const
{
	return kColRadius;
}

// 当たり判定の中心位置取得
Vec2 EnemySin::getCenter()const
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


EnemyDeside::EnemyDeside()
{

}

void EnemyDeside::init()
{
	m_vec.x = -3.0f;
	m_vec.y = 0.0f;
}

void EnemyDeside::setPos(float x, float y)
{
	Enemy::setPos(x, y);
	m_basePos = m_pos;
}

void EnemyDeside::update()
{
	m_basePos += m_vec;
	m_pos = m_basePos;

	if (0 > m_basePos.x)
	{
		m_basePos.x = Game::kScreenWindth;
	}
}

void EnemyDeside::draw()
{
	if (m_isDead) return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);	
}


// 当たり判定の半径取得
float EnemyDeside::getRadius()const
{
	return kColRadius;
}

// 当たり判定の中心位置取得
Vec2 EnemyDeside::getCenter()const
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