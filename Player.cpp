#include "DxLib.h"
#include "game.h"
#include "Player.h"
#include "SceneMain.h"

namespace
{
	// 当たり半径の半径
	constexpr float kColRadius = 20.0f;

	// X方向、Y方向の最大速度
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc	  = 0.4f;

	// ショットの発射間隔
	constexpr int kShotInterval = 20.0f;
}

Player::Player()
{
	m_handle	   = -1;
	m_pMain		   = nullptr;
	m_shotInterval = 0;
}

Player::~Player()
{

}

// プレイヤーの初期化
void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_shotInterval = 0;
}

// 処理
void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ショットを打つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)
	{
		m_shotInterval = 0;
	}
	
	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	// Playerのパッド移動処理

	if (padState & PAD_INPUT_UP)
	{
		m_vec.y -= kAcc;
		if (m_vec.y < -kSpeedMax)
		{
			m_vec.y = -kSpeedMax;
		}
	}
	else if (padState & PAD_INPUT_DOWN)
	{
		m_vec.y += kAcc;

		if (m_vec.y > kSpeedMax)
		{
			m_vec.y = kSpeedMax;
		}

	}
	else
	{
		m_vec.y *= 0.9f;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		m_vec.x -= kAcc;

		if (m_vec.x < kSpeedMax)
		{
			m_vec.x = -kSpeedMax;
		}
		
	}
	else if (padState & PAD_INPUT_RIGHT)
	{
		m_vec.x += kAcc;
		
		if (m_vec.x > kSpeedMax)
		{
			m_vec.x = kSpeedMax;
		}
	}
	else
	{
		m_vec.x *= 0.9f;
	}
	m_pos += m_vec;
	
	// playerが外に出そうになったら画面内に戻す
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.x > Game::kScreenWindth -118)
	{
		m_pos.x = Game::kScreenWindth -118;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}
	if (m_pos.y > Game::kScreenHeight -118)
	{
		m_pos.y = Game::kScreenHeight -118;
	}
}

// 描画
void Player::draw()
{
	if (m_isDead) return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}

// 当たり判定の半径取得
float Player::getRadius() const
{
	return kColRadius;
}

// 当たり判定の中心位置取得
Vec2 Player::getCenter() const
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
