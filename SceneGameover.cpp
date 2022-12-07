#include "SceneGameover.h"
#include "DxLib.h"
#include "Pad.h"


void SceneGameover::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

}

void SceneGameover::end()
{

}

void SceneGameover::update()
{

	if (Pad::isTrigger(PAD_INPUT_4))
	{
		m_isEnd = false;
	}
}

void SceneGameover::draw()
{
	DrawString(615, 360, "ゲームオーバー", GetColor(255, 255, 255));
	DrawString(540, 400, "ESCを押すとゲームが終了します。", GetColor(225, 225, 225));
}

