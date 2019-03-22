#include "GUI.h"
#include <algorithm>
#include "tinyxml2.h"
#include "../main.h"

CGUI GUI;

//float G::MenuAlpha = 0.f;

CGUI::CGUI()
{

}

// Draws all windows 
void CGUI::Draw()
{

	bool ShouldDrawCursor = false;

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			ShouldDrawCursor = true;
			DrawWindow(window);
		}
	}

	
	if (ShouldDrawCursor)
	{
		d::draw_filled_rect(Mouse.x + 1, Mouse.y, 1, 17, color(0, 0, 0, 255));
		for (int i = 0; i < 11; i++)
		d::draw_filled_rect(Mouse.x + 2 + i, Mouse.y + 1 + i, 1, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 8, Mouse.y + 12, 5, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 8, Mouse.y + 13, 1, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 9, Mouse.y + 14, 1, 2, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 10, Mouse.y + 16, 1, 2, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 8, Mouse.y + 18, 2, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 7, Mouse.y + 16, 1, 2, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 6, Mouse.y + 14, 1, 2, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 5, Mouse.y + 13, 1, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 4, Mouse.y + 14, 1, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 3, Mouse.y + 15, 1, 1, color(0, 0, 0, 255));
		d::draw_filled_rect(Mouse.x + 2, Mouse.y + 16, 1, 1, color(0, 0, 0, 255));
		for (int i = 0; i < 4; i++)
		d::draw_filled_rect(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), color(125, 5, 255, 255));
		d::draw_filled_rect(Mouse.x + 6, Mouse.y + 6, 1, 8, color(125, 5, 255, 255));
		d::draw_filled_rect(Mouse.x + 7, Mouse.y + 7, 1, 9, color(125, 5, 255, 255));
		for (int i = 0; i < 4; i++)
			d::draw_filled_rect(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, color(125, 5, 255, 255));
		d::draw_filled_rect(Mouse.x + 8, Mouse.y + 14, 1, 4, color(125, 5, 255, 255));
		d::draw_filled_rect(Mouse.x + 9, Mouse.y + 16, 1, 2, color(125, 5, 255, 255));
	}
	
}

// Handle all input etc
void CGUI::Update()
{
	static int bWasntHolding = false;
	static int bGrabbing = false;
	static int iOffsetX = 0, iOffsetY = 0;

	//Key Array
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		//oldKeys[x] = oldKeys[x] & keys[x];
		keys[x] = (GetAsyncKeyState(x));
	}

	// Mouse Location
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;

	RECT Screen = d::get_view_port();

	// Window Binds
	for (auto& bind : WindowBinds)
	{
		if (GetKeyPress(bind.first))
		{
			bind.second->Toggle();
		}
	}

	// Stop dragging
	if (IsDraggingWindow && !GetKeyState(VK_LBUTTON))
	{
		IsDraggingWindow = false;
		DraggingWindow = nullptr;
	}

	// If we are in the proccess of dragging a window
	if (IsDraggingWindow && GetKeyState(VK_LBUTTON) && !GetKeyPress(VK_LBUTTON))
	{
		if (DraggingWindow)
		{
			DraggingWindow->m_x = Mouse.x - DragOffsetX;
			DraggingWindow->m_y = Mouse.y - DragOffsetY;
		}
	}

	// Process some windows
	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			// Used to tell the widget processing that there could be a click
			bool bCheckWidgetClicks = false;
			// If the user clicks inside the window
			if (GetKeyPress(VK_LBUTTON) || GetKeyPress(VK_RETURN))
			{
				//if (IsMouseInRegion(window->m_x, window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight))
				//{
				// Is it inside the client area?
				if (IsMouseInRegion(window->GetClientArea1()))
				{
					// User is selecting a new tab
					if (IsMouseInRegion(window->GetTabArea()))
					{
						// Loose focus on the control
						window->IsFocusingControl = false;
						window->FocusedControl = nullptr;

						int iTab = 0;
						int TabCount = window->Tabs.size();
						if (TabCount) // If there are some tabs
						{
							int TabSize = (window->m_iWidth - 4 - 12) / TabCount;
							int Dist = Mouse.x - (window->m_x + 8);
							while (Dist > TabSize)
							{
								if (Dist > TabSize)
								{
									iTab++;
									Dist -= TabSize;
								}
							}
							window->SelectedTab = window->Tabs[iTab];
						}

					}
					else
						bCheckWidgetClicks = true;
				}
				else if (IsMouseInRegion(window->m_x, window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight))
				{
					// Must be in the around the title or side of the window
					// So we assume the user is trying to drag the window
					IsDraggingWindow = true;

					DraggingWindow = window;

					DragOffsetX = Mouse.x - window->m_x;
					DragOffsetY = Mouse.y - window->m_y;

					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}

				//else
				//{
				//	// Loose focus on the control
				//	window->IsFocusingControl = false;
				//	window->FocusedControl = nullptr;
				//}
			}


			// Controls 
			if (window->SelectedTab != nullptr)
			{
				// Focused widget
				bool SkipWidget = false;
				CControl* SkipMe = nullptr;

				// this window is focusing on a widget??
				if (window->IsFocusingControl)
				{
					if (window->FocusedControl != nullptr)
					{
						// We've processed it once, skip it later
						SkipWidget = true;
						SkipMe = window->FocusedControl;

						POINT cAbs = window->FocusedControl->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, window->FocusedControl->m_iWidth, window->FocusedControl->m_iHeight };
						window->FocusedControl->OnUpdate();

						if (window->FocusedControl->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							window->FocusedControl->OnClick();

							// If it gets clicked we loose focus
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
							bCheckWidgetClicks = false;
						}
					}
				}

				// Itterate over the rest of the control
				for (auto control : window->SelectedTab->Controls)
				{
					if (control != nullptr)
					{
						if (SkipWidget && SkipMe == control)
							continue;

						POINT cAbs = control->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
						control->OnUpdate();

						if (control->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							control->OnClick();
							bCheckWidgetClicks = false;

							// Change of focus
							if (control->Flag(UIFlags::UI_Focusable))
							{
								window->IsFocusingControl = true;
								window->FocusedControl = control;
							}
							else
							{
								window->IsFocusingControl = false;
								window->FocusedControl = nullptr;
							}

						}
					}
				}

				// We must have clicked whitespace
				if (bCheckWidgetClicks)
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}
		}
	}
}

// Returns 
bool CGUI::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

bool CGUI::GetKeyState(unsigned int key)
{
	return keys[key];
}

bool CGUI::IsMouseInRegion(int x, int y, int x2, int y2)
{
	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
		return true;
	else
		return false;
}

bool CGUI::IsMouseInRegion(RECT region)
{
	return IsMouseInRegion(region.left, region.top, region.left + region.right, region.top + region.bottom);
}

POINT CGUI::GetMouse()
{
	return Mouse;
}

bool CGUI::DrawWindow(CWindow* window)
{
	d::draw_filled_rect(window->m_x + 8 - 90, window->m_y + 1 + 8 * 2, window->m_iWidth - 4 - 12 + 90, window->m_iHeight - 2 - 8 - 26, color(28, 28, 28, 255)); // Background
	d::draw_outlined_rect(window->m_x + -88, window->m_y + 11, window->m_iWidth - -86, window->m_iHeight - 24, color(0, 0, 0, 255)); // Black Outline
	d::draw_outlined_rect(window->m_x + -87, window->m_y + 12, window->m_iWidth - -84, window->m_iHeight - 26, color(65, 65, 65, 255)); // Outside Gray Line
	d::draw_outlined_rect(window->m_x + -86, window->m_y + 13, window->m_iWidth - -82, window->m_iHeight - 28, color(45, 45, 45, 255)); // Inner 3
	d::draw_outlined_rect(window->m_x + -85, window->m_y + 14, window->m_iWidth - -80, window->m_iHeight - 30, color(45, 45, 45, 255)); // Inner 2 
	d::draw_outlined_rect(window->m_x + -84, window->m_y + 15, window->m_iWidth - -78, window->m_iHeight - 32, color(45, 45, 45, 255)); // Inner 1
	d::draw_outlined_rect(window->m_x + -83, window->m_y + 16, window->m_iWidth - -76, window->m_iHeight - 34, color(65, 65, 65, 255)); // Inner Gray Line

																																	// Tabs
	d::draw_gradient_v(window->m_x + 8, window->m_y + 1 + 27, window->m_iWidth - 4 - 12, 29, color(33, 33, 33, 255), color(22, 22, 22, 255));

	// Logo and Text

	d::draw_string(window->m_x - 60, window->m_y + 28, color(125, 5, 255, 255), f::menu_elements, "c"); // icon
	d::draw_string(window->m_x - 60, window->m_y + 80, color(125, 5, 255, 255), f::menu_elements, "compilerbau"); // text

	int TabCount = window->Tabs.size();
	if (TabCount) // If there are some tabs
	{

		for (int i = 0; i < TabCount; i++)
		{										// [1] = Tab number - 0 = 1 in numbers
			CTab *tab = window->Tabs[i];
			CTab *AimbotTab = window->Tabs[0];
			CTab *TriggerbotTab = window->Tabs[1];
			CTab *AccuracyTab = window->Tabs[2];
			CTab *VisualsTab = window->Tabs[3];
			CTab *MiscTab = window->Tabs[4];

			if (window->SelectedTab == AimbotTab) // Aimbot Tab
			{
				Menu::Window.SetSize(650, 650);
			}
			else if (window->SelectedTab == TriggerbotTab) // Misc Tab
			{
				Menu::Window.SetSize(650, 650);
			}
			else if (window->SelectedTab == AccuracyTab) // Triggerbot Tab 
			{
				Menu::Window.SetSize(650, 650);
			}
			else if (window->SelectedTab == VisualsTab) // Visuals Tab
			{
				Menu::Window.SetSize(650, 650);
			}
			else if (window->SelectedTab == MiscTab) // Misc Tab
			{
				Menu::Window.SetSize(650, 650);
			}
		}

		int TabSize = (window->m_iWidth - 4 - 12) / TabCount;
		for (int i = 0; i < TabCount; i++)
		{
			RECT TabArea = { window->m_x + 8 + (i*TabSize), window->m_y + 1 + 27, TabSize, 29 };
			CTab *tab = window->Tabs[i];

			RECT TextSize = d::get_text_size(f::menu_main_verdana, tab->Title.c_str());

			if (IsMouseInRegion(TabArea) && window->SelectedTab != tab)
			{
				d::draw_gradient_v(window->m_x + 8 + (i*TabSize), window->m_y + 1 + 27, TabSize, 29, color(35, 35, 35, 255), color(25, 25, 25, 255));
				d::draw_text(TabArea.left + (TabSize / 2) - (TextSize.right / 2), TabArea.top + 8, color(180, 180, 180, 255), f::menu_tabs, tab->Title.c_str());
			}
			else if (window->SelectedTab == tab)
			{
				d::draw_gradient_v(window->m_x + 8 + (i*TabSize), window->m_y + 1 + 27, TabSize, 29, color(25, 25, 25, 255), color(35, 35, 35, 255));
				d::draw_text(TabArea.left + (TabSize / 2) - (TextSize.right / 2), TabArea.top + 8, color(255, 255, 255, 255), f::menu_tabs, tab->Title.c_str());
			}
			else
			{
				d::draw_text(TabArea.left + (TabSize / 2) - (TextSize.right / 2), TabArea.top + 8, color(130, 130, 130, 255), f::menu_tabs, tab->Title.c_str());
			}

		}
	}

	// Controls 
	if (window->SelectedTab != nullptr)
	{
		// Focused widget
		bool SkipWidget = false;
		CControl* SkipMe = nullptr;

		// this window is focusing on a widget??
		if (window->IsFocusingControl)
		{
			if (window->FocusedControl != nullptr)
			{
				// We need to draw it last, so skip it in the regular loop
				SkipWidget = true;
				SkipMe = window->FocusedControl;
			}
		}

		// Itterate over all the other controls
		for (auto control : window->SelectedTab->Controls)
		{
			if (SkipWidget && SkipMe == control)
				continue;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

		// Draw the skipped widget last
		if (SkipWidget)
		{
			auto control = window->FocusedControl;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

	}


	return true;
}

void CGUI::RegisterWindow(CWindow* window)
{
	Windows.push_back(window);

	// Resorting to put groupboxes at the start
	for (auto tab : window->Tabs)
	{
		for (auto control : tab->Controls)
		{
			if (control->Flag(UIFlags::UI_RenderFirst))
			{
				CControl * c = control;
				tab->Controls.erase(std::remove(tab->Controls.begin(), tab->Controls.end(), control), tab->Controls.end());
				tab->Controls.insert(tab->Controls.begin(), control);
			}
		}
	}
}

void CGUI::BindWindow(unsigned char Key, CWindow* window)
{
	if (window)
		WindowBinds[Key] = window;
	else
		WindowBinds.erase(Key);
}

void CGUI::SaveWindowState(CWindow* window, std::string Filename)
{
	// Create a whole new document and we'll just save over top of the old one
	tinyxml2::XMLDocument Doc;

	// Root Element is called "ayy"
	tinyxml2::XMLElement *Root = Doc.NewElement("compilerbau");
	Doc.LinkEndChild(Root);

	//Utilities::Log("Saving Window %s", window->Title.c_str());

	// If the window has some tabs..
	if (Root && window->Tabs.size() > 0)
	{
		for (auto Tab : window->Tabs)
		{
			// Add a new section for this tab
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Tab->Title.c_str());
			Root->LinkEndChild(TabElement);

			//Utilities::Log("Saving Tab %s", Tab->Title.c_str());

			// Now we itterate the controls this tab contains
			if (TabElement && Tab->Controls.size() > 0)
			{
				for (auto Control : Tab->Controls)
				{
					// If the control is ok to be saved
					if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						// Create an element for the control
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						//Utilities::Log("Saving control %s", Control->FileIdentifier.c_str());

						if (!ControlElement)
						{
							//Utilities::Log("Error");
							return;
						}

						CCheckBox* cbx = nullptr;
						CComboBox* cbo = nullptr;
						CKeyBind* key = nullptr;
						CSlider* sld = nullptr;

						// Figure out what kind of control and data this is
						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (CCheckBox*)Control;
							ControlElement->SetText(cbx->GetState());
							break;
						case UIControlTypes::UIC_ComboBox:
							cbo = (CComboBox*)Control;
							ControlElement->SetText(cbo->GetIndex());
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (CKeyBind*)Control;
							ControlElement->SetText(key->GetKey());
							break;
						case UIControlTypes::UIC_Slider:
							sld = (CSlider*)Control;
							ControlElement->SetText(sld->GetValue());
							break;
						}
					}
				}
			}
		}
	}

	//Save the file
	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		//MessageBox(NULL,((char*)"Failed to save the config file.", (char*)"PUSCHELBOT", MB_OK);
	}

}

void CGUI::LoadWindowState(CWindow* window, std::string Filename)
{
	// Lets load our meme
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		// The root "ayy" element
		if (Root)
		{
			// If the window has some tabs..
			if (Root && window->Tabs.size() > 0)
			{
				for (auto Tab : window->Tabs)
				{
					// We find the corresponding element for this tab
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Tab->Title.c_str());
					if (TabElement)
					{
						// Now we itterate the controls this tab contains
						if (TabElement && Tab->Controls.size() > 0)
						{
							for (auto Control : Tab->Controls)
							{
								// If the control is ok to be saved
								if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									// Get the controls element
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										CCheckBox* cbx = nullptr;
										CComboBox* cbo = nullptr;
										CKeyBind* key = nullptr;
										CSlider* sld = nullptr;

										// Figure out what kind of control and data this is
										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (CCheckBox*)Control;
											cbx->SetState(ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_ComboBox:
											cbo = (CComboBox*)Control;
											cbo->SelectIndex(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (CKeyBind*)Control;
											key->SetKey(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (CSlider*)Control;
											sld->SetValue(atof(ControlElement->GetText()));
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}