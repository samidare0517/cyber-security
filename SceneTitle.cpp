#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

	m_menu.init();
	m_menu.addItem("ゲームスタート");


	m_menu.setPos(540, 360);

	m_menu.setupCursor();
}

void SceneTitle::end()
{
	m_menu.end();
}

void SceneTitle::update()
{
	m_menu.update();
	Fade();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = true;
	}
}

void SceneTitle::Fade()
{
	fadeValue_ -= 5;
	if (fadeValue_ < 0)
	{
		fadeValue_ = 0;
	}
	if (fadeValue_ > 255)
	{
		fadeValue_ = 255;
	}
}

void SceneTitle::draw()
{
	m_menu.draw();

	
	// 今から各画像と、すでに描画されているスクリーンとの
	// ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	// 画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 1280, 700, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	// デバック用
//	DrawFormatString(0, 100, GetColor(255,255,255), "%d", fadeValue_);

	// デバック用	
//	DrawString(400, 100, "タイトル画面", GetColor(255, 255, 255));
}

