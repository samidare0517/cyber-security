#include "DxLib.h"
#include "SelectMenu.h"
#include "Pad.h"

namespace
{
	// メニュー項目の間隔
	constexpr int kMenuItemInterval = 32;
}

//=================================
//SlectMenu::Item
//=================================

SelectMenu::Item::Item()
{
	m_text = nullptr;
}

SelectMenu::Item::~Item()
{

}

void SelectMenu::Item::draw(int x, int y)
{
	DrawString(x, y, m_text, GetColor(225, 225, 225));
}


void::SelectMenu::Item::setText(const char* text)
{
	m_text = text;
}

int SelectMenu::Item::getTextWidth()
{
	return GetDrawStringWidth(m_text, strlen(m_text));
}

//=================================
//SelectMenu::Cursor
//=================================

SelectMenu::Cursor::Cursor()
{
	m_itemNum = 0;
	m_selectIndex = 0;
	m_repeatUp = 0;
	m_repeatDown = 0;

}


SelectMenu::Cursor::~Cursor()
{

}

void SelectMenu::Cursor::update()
{
	if (Pad::isPress (PAD_INPUT_UP))
	{
		if (m_repeatUp == 0)
		{
			m_selectIndex--;
			m_repeatUp = 8;
			// 上下ループ
			if (m_selectIndex < 0)
			{
				if (Pad::isTrigger(PAD_INPUT_UP))
				{
					m_selectIndex = m_itemNum - 1;
				}
				else
				{
					m_selectIndex = 0;
				}
			}
		}
		else
		{
			m_repeatUp--;
		}
	}
	else
	{
		m_repeatUp = 0;
	}

	if (Pad::isPress (PAD_INPUT_DOWN))
	{
		if (m_repeatDown <= 0)
		{
			m_selectIndex++;
			m_repeatDown = 8;
			if (m_selectIndex > m_itemNum -1)
			{
				if (Pad::isTrigger(PAD_INPUT_DOWN))
				{
					m_selectIndex = 0;
				}
				else
				{
					m_selectIndex = m_itemNum -1;
				}
			}
		}
		else
		{
			m_repeatDown--;
		}
	}
	else
	{
		m_repeatDown = 0;
	}

}

void SelectMenu::Cursor::draw()
{
	int posX = m_menuPos.x;
	int posY = m_menuPos.y + kMenuItemInterval * m_selectIndex;
	DrawBox(posX, posY, posX + m_size.x, posY + m_size.y, GetColor(225, 0, 0), false);
}



//=================================
//SlectMenu
//=================================

SelectMenu::SelectMenu()
{

}

SelectMenu::~SelectMenu()
{

}

void SelectMenu::init()
{

}

void SelectMenu::end()
{
	for (auto& pItem : m_pItem)		// メモリの開放
	{
		delete pItem;
	}
	m_pItem.clear();
}


void SelectMenu::update()
{
	m_cursor.update();
}

void SelectMenu::draw()
{
	int width = getWindowWidth();
	int height = getWindowHeight();

	

	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i]->draw(m_pos.x, m_pos.y + i * kMenuItemInterval);
	}
	m_cursor.draw();
}

void SelectMenu::setupCursor()
{
	m_cursor.setMenuPos(m_pos);
	m_cursor.setSize(Vec2(getWindowWidth(), kMenuItemInterval));
	m_cursor.setItemNum(m_pItem.size());
}



void SelectMenu::setPos(float x, float y)
{
	setPos(Vec2(x, y));
}

void SelectMenu::setPos(Vec2 pos)
{
	m_pos = pos;
}



void SelectMenu::addItem(const char* text)

{
	Item* pItem = new Item;
	pItem->setText(text);
	m_pItem.push_back(pItem);
}


int SelectMenu::getWindowWidth()
{
	int width = 0;

	// 一番横幅の広いメニュー項目の幅をウインドウサイズにする
	for (auto& pItem : m_pItem)
	{
		if (width < pItem->getTextWidth())
		{
			width = pItem->getTextWidth();
		}
	}
	return width;
}

int SelectMenu::getWindowHeight()
{
	return kMenuItemInterval * m_pItem.size();
}