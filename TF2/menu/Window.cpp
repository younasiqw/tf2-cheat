#pragma once

#include "GUI.h"

void CWindow::SetPosition(int x, int y)
{
	m_x = x; m_y = y;
}

void CWindow::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CWindow::SetTitle(std::string title)
{
	Title = title;
}

void CWindow::RegisterTab(CTab* Tab)
{
	if (Tabs.size() == 0)
	{
		SelectedTab = Tab;
	}
	Tab->parent = this;
	Tabs.push_back(Tab);
}

RECT CWindow::GetClientArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = m_iHeight - 2 - 8 - 26;
	return client;
}

RECT CWindow::GetTabArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = 29;
	return client;
}

RECT CWindow::GetClientArea1()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = m_iHeight - 2 - 8 - 26 + 500;
	return client;
}

void CWindow::Open()
{
	m_bIsOpen = true;
}

void CWindow::Close()
{
	m_bIsOpen = false;
}

void CWindow::Toggle()
{
	m_bIsOpen = !m_bIsOpen;
}

CControl* CWindow::GetFocus()
{
	return FocusedControl;
}

void CTab::SetTitle(std::string name)
{
	Title = name;
}

void CTab::RegisterControl(CControl* control)
{
	control->parent = parent;
	Controls.push_back(control);
}