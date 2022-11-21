#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include <cassert>
#include "ShotNormal.h"
#include "enemy.h"
#include "SceneTitle.h"

namespace
{
	Enemy enemy[7];
	EnemySin enemysin[5];

	bool kCheck;

	int EnemyNum = 7;
	int EnemySinNum = 5;

	// ショットの発射間隔
	constexpr int kShotInterval = 16;

	
}

void SceneMain::init()
{
	m_textPosX = 0;
	m_textVecX = 4;

	m_EnemyNum = EnemyNum;

	m_isEnd = false;

	// 画像データ
	m_hPlayerGraohic = LoadGraph("data/player.png");
	m_hShotGraphic = LoadGraph("data/shot.png");
	m_hEnemyGraphc = LoadGraph("data/enemy.png");
	m_hEnemySinGraphc = LoadGraph("data/enemy2.png");
	m_hBackGraphic = LoadGraph("data/Back.png");
	
	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();

	float posX = 400.0f;
	for (auto& m_enemy : enemy)
	{
		m_enemy.setHandle(m_hEnemyGraphc);
		m_enemy.init();
		m_enemy.setPos(posX, 160.0f);
		posX += 80.0f;
	}

	float posx = 300.0f;
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.setHandle(m_hEnemySinGraphc);
		m_enemysin.init();
		m_enemysin.setPos(posx, 300.0f);
		posx += 100.0f;
	}

	m_player.setMain(this);
	m_enemy.setMain(this);

}

void SceneMain::end()
{
	// 画像の開放
	DeleteGraph(m_hPlayerGraohic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphc);
	DeleteGraph(m_hEnemySinGraphc);
	DeleteGraph(m_hBackGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

void SceneMain::update()
{
	m_player.update();

	for (auto& m_enemy : enemy)
	{
		m_enemy.update();
	}
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.update();

	}

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();

	// enemyバウンド判定
	for (int i = 0; i < EnemyNum; i++)
	{
		for (int j = i + 1; j < EnemyNum; j++)
		{
			if (enemy[i].isDead())continue;

			// enemy[i]とenemy[j]の当たり判定をとる
			Vec2  dist = enemy[i].getCenter() - enemy[j].getCenter();
			float radiusAdd = enemy[i].getRadius() + enemy[j].getRadius();
			if (dist.length() < radiusAdd)
			{
				// 当たった場合の処理
				enemy[i].bound(enemy[j].getCenter());
				enemy[j].bound(enemy[i].getCenter());
			}
		}
	}
	

	// enemyとplayerの当たり判定
	for (int i = 0; i < EnemyNum; i++)
	{
		// Playerのflag (false = 生存)
		bool isEnd = false;
		// enemyが死んでいたら死んだenemy表示しない
		if (enemy[i].isDead())continue;		
		
		Vec2  dist = m_player.getCenter() - enemy[i].getCenter();
		float radiusAdd = enemy[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// 当たった場合の処理
			DrawFormatString(400, 0, GetColor(255, 0, 0), "ぶつかってしまった!");
			
			// Playerが敵と接触した時点でゲームを終了する
		//	isEnd = true;
		//	DxLib_End();

		}
	}

	// enemysinとplayerの当たり判定
	for (int i = 0; i < EnemySinNum; i++)
	{
		// player生存フラグ
		bool isEnd = false;

		// enemysinが死んでいたら死んだenemysinは表示しない
		if (enemysin[i].isDead())continue;

		Vec2 dist = m_player.getCenter() - enemysin[i].getCenter();
		float radiusAdd = enemysin[i].getRadius() + m_player.getRadius();
		if(dist.length() < radiusAdd)
		{
			// デバック用：当たった場合の処理
			DrawFormatString(800, 0, GetColor(225, 255, 0), "ぶつかってしまった。");

			// Playerが敵と接触した時点でゲームを終了する
		//	isEnd = true;
		//	DxLib_End();
		}
	}
	
	while (it != m_pShotVt.end())
	{

		auto& pShot = (*it);

		assert(pShot);

		pShot->update();

		// enemyと弾の当たり判定
		for (int i = 0; i < EnemyNum; i++)
		{
			
			if (enemy[i].isDead())continue;

			Vec2 dist = (*pShot).getCenter() - enemy[i].getCenter();
			float radiusAdd = enemy[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
			//	DrawFormatString(200, 0, GetColor(225, 0, 0), "ヒット！");
				kCheck = true;
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemy[i].setDead();
				m_EnemyNum--;
			}
		}
	
		// enemysinと玉の当たり判定
		for (int i = 0; i < EnemySinNum; i++)
		{
			if (enemysin[i].isDead())continue;

			Vec2 dist = (*pShot).getCenter() - enemysin[i].getCenter();
			float radiusAdd = enemysin[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
				DrawFormatString(800, 100, GetColor(225, 225, 0), "ヒット");
				kCheck = true;
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemysin[i].setDead();
				m_EnemySinNum--;
			}

		}


		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			// vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
	}

	
	//if (Pad::isTrigger(PAD_INPUT_2))
	//{
	//	m_isEnd = false;
	//	// デバック用
	//	DrawString(m_textPosX, 100, "ゲーム画面", GetColor(255, 255, 255));
	//}

	if (m_EnemyNum == 0)
	{
		m_isEnd = true;

		// デバック用
	//	DrawString(m_textPosX, 100, "ゲームクリア", GetColor(255, 255, 255));
	}

}


void SceneMain::draw()
{
//	DrawGraph(0, 0, m_hBackGraphic, false);
	m_player.draw();

	for (auto& m_enemy : enemy)
	{
		m_enemy.draw();
	}
	for (auto& m_enemysin : enemysin)
	{
		m_enemysin.draw();
	}

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	// 現在存在している玉の数を表示(デバック用)
//	DrawFormatString(0, 0, GetColor(225, 225, 225), "弾の数:%d", m_pShotVt.size());
}

// 生死判定のチェック
bool SceneMain::isCol()
{
	if(kCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}