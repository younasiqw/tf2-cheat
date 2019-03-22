#include "../main.h"
#include "../global/fonts/fonts.h"

#define UI_COL_SHADOW	Color(56, 58, 61, 255)


#pragma region Base Control
void CControl::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CControl::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CControl::GetSize(int &w, int &h)
{
	w = m_iWidth;
	h = m_iHeight;
}

bool CControl::Flag(int f)
{
	if (m_Flags & f)
		return true;
	else
		return false;
}

POINT CControl::GetAbsolutePos()
{
	POINT p;
	RECT client = parent->GetClientArea();
	if (parent)
	{
		p.x = m_x + client.left;
		p.y = m_y + client.top + 29;
	}

	return p;
}

void CControl::SetFileId(std::string fid)
{
	FileIdentifier = fid;
}
#pragma endregion Implementations of the Base control functions

#pragma region CheckBox
CCheckBox::CCheckBox()
{
	Checked = false;

	m_Flags = UIFlags::UI_Clickable | UIFlags::UI_Drawable | UIFlags::UI_SaveFile;
	m_iWidth = 10;
	m_iHeight = 10;

	FileControlType = UIControlTypes::UIC_CheckBox;
}

void CCheckBox::SetState(bool s)
{
	Checked = s;
}

bool CCheckBox::GetState()
{
	return Checked;
}

void CCheckBox::Draw(bool hover)
{

	POINT a = GetAbsolutePos();

	d::draw_gradient_v(a.x, a.y, 10, 10, color(50, 50, 50, 255), color(60, 60, 60, 255));
	d::draw_outlined_rect(a.x, a.y, 10, 10, color(0, 0, 0, 255));

	if (Checked)
	{
		d::draw_gradient_v(a.x + 1, a.y + 1, 10 - 2, 10 - 2, color(125, 5, 255, 255), color(40, 40, 40, 255));
	}
}

void CCheckBox::OnUpdate() { m_iHeight = 10; }

void CCheckBox::OnClick()
{
	Checked = !Checked;
}

#pragma endregion Implementations of the Check Box functions

#pragma region Label

CLabel::CLabel()
{
	m_Flags = UIFlags::UI_Drawable;
	Text = "Default";
	FileIdentifier = "Default";
}

void CLabel::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	d::draw_text(a.x, a.y, color(245, 245, 245, 255), f::menu_main, Text.c_str());
}

void CLabel::SetText(std::string text)
{
	Text = text;
}

void CLabel::OnUpdate() {}
void CLabel::OnClick() {}

#pragma endregion Implementations of the Label functions

#pragma region GroupBox

CGroupBox::CGroupBox()
{
	Items = 1;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox::Draw(bool hover)
{

	POINT a = GetAbsolutePos();
	RECT txtSize = d::get_text_size(f::menu_main, Text.c_str());
	//g_Render->Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(8, 8, 8, 255)); // menu mini box color
	d::draw_string(a.x + (m_iWidth / 2) - (txtSize.right / 2), a.y - (txtSize.bottom / 2) - 1, color(255, 255, 255, 255), f::menu_main, Text.c_str());

	//Top Left
	d::draw_line(a.x, a.y, a.x + (m_iWidth / 2) - (txtSize.right / 2) - 2, a.y, color(48, 48, 48, 255));
	d::draw_line(a.x - 1, a.y - 1, a.x + (m_iWidth / 2) - (txtSize.right / 2) - 1, a.y - 1, color(0, 0, 0, 255));

	//Top Right
	d::draw_line(a.x + (m_iWidth / 2) + (txtSize.right / 2) + 2, a.y, a.x + m_iWidth, a.y, color(48, 48, 48, 255));
	d::draw_line(a.x + (m_iWidth / 2) + (txtSize.right / 2) + 2, a.y - 1, a.x + m_iWidth + 1, a.y - 1, color(0, 0, 0, 255));

	//Left
	d::draw_line(a.x, a.y, a.x, a.y + m_iHeight, color(49, 49, 49, 255));
	d::draw_line(a.x - 1, a.y, a.x - 1, a.y + m_iHeight, color(0, 0, 0, 255));

	//Bottom
	d::draw_line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, color(48, 48, 48, 255));
	d::draw_line(a.x - 1, a.y + m_iHeight + 1, a.x + m_iWidth + 2, a.y + m_iHeight + 1, color(0, 0, 0, 255));

	//Right
	d::draw_line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight + 1, color(48, 48, 48, 255));
	d::draw_line(a.x + m_iWidth + 1, a.y, a.x + m_iWidth + 1, a.y + m_iHeight + 1, color(0, 0, 0, 255));
}

void CGroupBox::SetText(std::string text)
{
	Text = text;
}

void CGroupBox::PlaceLabledControl(int g_tab, std::string Label, CTab *Tab, CControl* control)
{
	bool has_tabs = group_tabs.size() ? 1 : 0;

	if (has_tabs)
	{
		bool has_reset = false;

		for (int i = 0; i < reset_tabs.size(); i++)
		{
			if (reset_tabs[i] == g_tab)
				has_reset = true;
		}

		if (!has_reset)
		{
			initialized = false;
			reset_tabs.push_back(g_tab);
		}
	}

	if (!initialized)
	{
		Items = 0;
		last_y = has_tabs ? m_y + 48 : m_y + 8;
		initialized = true;
	}

	bool add_label_y = true;
	bool is_checkbox = control->FileControlType == UIControlTypes::UIC_CheckBox;
	bool is_label = control->FileControlType == UIControlTypes::UIC_Label;
	bool is_keybind = control->FileControlType == UIControlTypes::UIC_KeyBind;
	bool is_color = control->FileControlType == UIControlTypes::UIC_ColorSelector;

	int x = m_x + 38;
	int y = last_y;
	int control_width, control_height;
	control->GetSize(control_width, control_height);

	CLabel* label = new CLabel;
	label->SetPosition(x, y);
	label->SetText(Label);
	label->parent_group = this;
	label->g_tab = g_tab ? g_tab : 0;
	Tab->RegisterControl(label);

	if (is_checkbox || is_label || is_color) add_label_y = false;

	if (Label != "" && add_label_y && !is_keybind)
	{
		RECT label_size = d::get_text_size_secondary(Label.c_str(), f::menu_main);
		last_y += 14;
		y = last_y;
	}

	if (!is_keybind)
		last_control_height = control_height + 7;

	if (is_keybind || (is_color && Label == ""))
	{
		y -= last_control_height;
		x = m_x + m_iWidth - 36;
	}
	if (is_color && Label != "")
		x = m_x + m_iWidth - 36;
	if (is_checkbox)
		x -= 24;

	control->SetPosition(x, is_checkbox ? y + 1 : y);
	control->SetSize(m_iWidth - (38 * 2), control_height);
	control->parent_group = this;
	control->g_tab = g_tab ? g_tab : 0;
	Tab->RegisterControl(control);

	if (!is_keybind)
	{
		if (!is_color || is_color && Label != "")
			last_y += control_height + 7;
	}
}

void CGroupBox::OnUpdate() {}
void CGroupBox::OnClick() {}

#pragma endregion Implementations of the Group Box functions

#pragma region Sliders

CSlider::CSlider()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	Format = FORMAT_INT;
	m_iHeight = 10;
	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	d::draw_gradient_v(a.x, a.y, m_iWidth, 7, color(62, 62, 62, 255), color(55, 55, 55, 255));

	float Ratio = (Value - Min) / (Max - Min);
	float Location = Ratio*m_iWidth;

	d::draw_gradient_v(a.x, a.y, Location, 7, color(125, 5, 255, 255), color(12, 12, 12, 255));

	d::draw_outlined_rect(a.x, a.y, m_iWidth, 7, color(2, 2, 2, 255));

	char buffer[24];
	const char* format;
	if (Format == FORMAT_DECDIG2)
		sprintf_s(buffer, "%.2f%s", Value, Extension);
	else if (Format == FORMAT_DECDIG1)
		sprintf_s(buffer, "%.1f%s", Value, Extension);
	else if (Format == FORMAT_INT)
		sprintf_s(buffer, "%1.0f%s", Value, Extension);

	RECT txtSize = d::get_text_size_secondary(buffer, f::menu_main_verdana);
	d::draw_menu_string(a.x + Location - (txtSize.right / 2), a.y + 7 - (txtSize.bottom / 2), buffer, f::menu_main_verdana, color(180, 180, 180, 255)); // menu text
}

void CSlider::OnUpdate()
{
	POINT a = GetAbsolutePos();
	m_iHeight = 15;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x;//-1
			if (NewX < 0)
				NewX = 0;
			if (NewX > m_iWidth)
				NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider::GetValue()
{
	return Value;
}

void CSlider::SetValue(float v)
{
	Value = v;
}

void CSlider::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}

void CSlider::SetFormat(SliderFormat type)
{
	Format = type;
}

#pragma endregion Implementations of the Item Selector functions

#pragma region KeyBinders

char* KeyStrings[254] = { (char*)"[ _ ]", (char*)"[M1]", (char*)"[M2]", (char*)"[BRK]", (char*)"[M3]", (char*)"[M4]", (char*)"[M5]",
(char*)"[ _ ]", (char*)"[BSPC]", (char*)"[TAB]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ENTER]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[SHI]",
(char*)"[CTRL]", (char*)"[ALT]",(char*)"[PAU]",(char*)"[CAPS]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ESC]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[SPACE]", (char*)"[PGUP]", (char*)"[PGDOWN]", (char*)"[END]", (char*)"[HOME]", (char*)"[LEFT]",
(char*)"[UP]", (char*)"[RIGHT]", (char*)"[DOWN]", (char*)"[ _ ]", (char*)"[PRNT]", (char*)"[ _ ]", (char*)"[PRTSCR]", (char*)"[INS]",(char*)"[DEL]", (char*)"[ _ ]", (char*)"[0]", (char*)"[1]",
(char*)"[2]", (char*)"[3]", (char*)"[4]", (char*)"[5]", (char*)"[6]", (char*)"[7]", (char*)"[8]", (char*)"[9]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[A]", (char*)"[B]", (char*)"[C]", (char*)"[D]", (char*)"[E]", (char*)"[F]", (char*)"[G]", (char*)"[H]", (char*)"[I]", (char*)"[J]", (char*)"[K]", (char*)"[L]", (char*)"[M]", (char*)"[N]", (char*)"[O]", (char*)"[P]", (char*)"[Q]", (char*)"[R]", (char*)"[S]", (char*)"[T]", (char*)"[U]",
(char*)"[V]", (char*)"[W]", (char*)"[X]", (char*)"[Y]", (char*)"[Z]", (char*)"[LFTWIN]", (char*)"[RGHTWIN]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[NUM0]", (char*)"[NUM1]",
(char*)"[NUM2]", (char*)"[NUM3]", (char*)"[NUM4]", (char*)"[NUM5]", (char*)"[NUM6]",(char*)"[NUM7]", (char*)"[NUM8]", (char*)"[NUM9]", (char*)"[*]", (char*)"[+]", (char*)"[_]", (char*)"[-]", (char*)"[.]", (char*)"[/]", (char*)"[F1]", (char*)"[F2]", (char*)"[F3]",
(char*)"[F4]", (char*)"[F5]", (char*)"[F6]", (char*)"[F7]", (char*)"[F8]", (char*)"[F9]", (char*)"[F10]", (char*)"[F11]", (char*)"[F12]", (char*)"[F13]", (char*)"[F14]", (char*)"[F15]", (char*)"[F16]", (char*)"[F17]", (char*)"[F18]", (char*)"[F19]", (char*)"[F20]", (char*)"[F21]",
(char*)"[F22]", (char*)"[F23]", (char*)"[F24]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[NUM LOCK]", (char*)"[SCROLL LOCK[", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[LSHFT]", (char*)"[RSHFT]", (char*)"[LCTRL]",
(char*)"[RCTRL]", (char*)"[LMENU]", (char*)"[RMENU]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[NTRK]", (char*)"[PTRK]", (char*)"[STOP]", (char*)"[PLAY]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[;]", (char*)"[+]", (char*)"[,]", (char*)"[-]", (char*)"[.]", (char*)"[/?]", (char*)"[~]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[{]", (char*)"[\\|]", (char*)"[}]", (char*)"['\"]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]", (char*)"[ _ ]",
(char*)"[ _ ]", ((char*)"[ _ ]") };

CKeyBind::CKeyBind()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	m_iHeight = 12;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

void CKeyBind::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	if (this->Getting_New_Key)
	{
		d::draw_menu_string(a.x, a.y, "[ ? ]", f::menu_main, color(110, 110, 110, 255));
	}
	else
	{
		if (key == -1)
			d::draw_menu_string(a.x, a.y, "[ - ]", f::menu_main, color(110, 110, 110, 255));
		else
		{
			char* NameOfKey = KeyStrings[key];
			d::draw_menu_string(a.x, a.y, NameOfKey, f::menu_main, color(110, 110, 110, 255));
		}
	}

}

void CKeyBind::OnUpdate()
{
	m_iHeight = 13;
	RECT text_area;
	if (key == -1)
		text_area = d::get_text_size_secondary("[ - ]", f::menu_main);
	else
		text_area = d::get_text_size_secondary(text, f::menu_main);
	m_iWidth = text_area.right;
	POINT a = GetAbsolutePos();
	if (Getting_New_Key)
	{
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE)
				{
					Getting_New_Key = false;
					key = -1;
					text = (char *)"[ - ]";
					return;
				}

				key = i;
				Getting_New_Key = false;
				text = KeyStrings[i];
				return;
			}
		}
	}
}

void CKeyBind::OnClick() {
	POINT a = GetAbsolutePos();
	if (!Getting_New_Key)
		Getting_New_Key = true;
}

int CKeyBind::GetKey()
{
	return key;
}

void CKeyBind::SetKey(int k)
{
	key = k;
	text = KeyStrings[k];
}

#pragma endregion Implementations of the KeyBind Control functions

#pragma region Button

CButton::CButton()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	FileControlType == UIControlTypes::UIC_Button;
	Text = "Default";
	m_iHeight = 25;
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButton::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT TextSize = d::get_text_size_secondary(Text.c_str(), f::menu_main); // Button
	int TextX = a.x + (m_iWidth / 2) - (TextSize.right / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	if (hover && GetAsyncKeyState(VK_LBUTTON))
	{
		d::draw_gradient_v(a.x, a.y, m_iWidth, m_iHeight, color(25, 25, 25, 255), color(35, 35, 35, 255));
		d::draw_menu_string(TextX, TextY, Text.c_str(), f::menu_main_verdana, color(180, 180, 180, 255));
	}
	else
	{
		d::draw_gradient_v(a.x, a.y, m_iWidth, m_iHeight, color(35, 35, 35, 255), color(25, 25, 25, 255));
		d::draw_menu_string(TextX, TextY, Text.c_str(), f::menu_main_verdana, color(180, 180, 180, 255));
	}

	if (hover && !GetAsyncKeyState(VK_LBUTTON))
	{
		d::draw_gradient_v(a.x, a.y, m_iWidth, m_iHeight, color(45, 45, 45, 255), color(25, 25, 25, 255));
		d::draw_menu_string(TextX, TextY, Text.c_str(), f::menu_main_verdana, color(180, 180, 180, 255));
	}

	d::draw_outlined_rect(a.x, a.y, m_iWidth, m_iHeight, color(2, 2, 2, 255));
	d::draw_outlined_rect(a.x + 1, a.y + 1, m_iWidth - 2, m_iHeight - 2, color(50, 50, 50, 255));

}

void CButton::SetText(std::string text)
{
	Text = text;
}

void CButton::SetCallback(CButton::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButton::OnUpdate()
{
	m_iHeight = 25;
}

void CButton::OnClick()
{
	if (CallBack)
		CallBack();
}

#pragma region ComboBox
CComboBox::CComboBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	m_iHeight = 20;
	FileControlType = UIControlTypes::UIC_ComboBox;
}

void CComboBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };
	d::draw_gradient_v(a.x, a.y, m_iWidth, 20, color(45, 45, 45, 255), color(45, 45, 45, 255));
	if (GUI.IsMouseInRegion(Region)) d::draw_gradient_v(a.x, a.y, m_iWidth, 20, color(55, 55, 55, 255), color(55, 55, 55, 255));
	d::draw_outlined_rect(a.x, a.y, m_iWidth, 20, color(2, 2, 2, 255));

	if (Items.size() > 0)
	{
		RECT txtSize = d::get_text_size_secondary(GetItem().c_str(), f::menu_main);
		d::draw_menu_string(a.x + 4, a.y + (Region.bottom / 2) - (txtSize.bottom / 2), GetItem().c_str(), f::menu_main, color(180, 180, 180, 255));

		if (IsOpen)
		{
			d::draw_gradient_v(a.x, a.y + 20, m_iWidth, Items.size() * 20, color(45, 45, 45, 255), color(45, 45, 45, 255));

			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 17 + i * 20, m_iWidth, 20 };

				if (GUI.IsMouseInRegion(ItemRegion))
				{
					d::draw_gradient_v(a.x, a.y + 20 + i * 20, m_iWidth, 20, color(35, 35, 35, 255), color(35, 35, 35, 255));
				}

				RECT control_textsize = d::get_text_size_secondary(Items[i].c_str(), f::menu_main);
				if (i == SelectedIndex)
					d::draw_menu_string(a.x + 10, a.y + 20 + (i * 20) + 10 - (control_textsize.bottom / 2), Items[i].c_str(), f::menu_main, color(125, 5, 255, 255));
				else
					d::draw_menu_string(a.x + 10, a.y + 20 + (i * 20) + 10 - (control_textsize.bottom / 2), Items[i].c_str(), f::menu_main, color(180, 180, 180, 255));
			}
			d::draw_outlined_rect(a.x, a.y + 20, m_iWidth, Items.size() * 20, color(2, 2, 2, 255));
		}
	}


	
	/* - 2lazy
	Vertex_t Verts2[3];
	Verts2[0].m_Position.x = a.x + m_iWidth - 10;
	Verts2[0].m_Position.y = a.y + 9;
	Verts2[1].m_Position.x = a.x + m_iWidth - 5;
	Verts2[1].m_Position.y = a.y + 9;
	Verts2[2].m_Position.x = a.x + m_iWidth - 7.5;
	Verts2[2].m_Position.y = a.y + 12;

	g_Render->Polygon(3, Verts2, Color(92, 92, 92, 255));
	*/
}

void CComboBox::AddItem(std::string text)
{
	Items.push_back(text);
	SelectedIndex = 0;
}

void CComboBox::OnUpdate()
{
	if (IsOpen)
	{
		m_iHeight = 20 + 20 * Items.size();

		if (parent->GetFocus() != this)
			IsOpen = false;
	}
	else
	{
		m_iHeight = 20;
	}

}

void CComboBox::OnClick()
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };

	if (IsOpen)
	{
		// If we clicked one of the items(Not in the top bar)
		if (!GUI.IsMouseInRegion(Region))
		{
			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 20 + i * 20, m_iWidth, 20 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					SelectedIndex = i;
				}
			}
		}

		// Close the drop down
		IsOpen = false;
	}
	else
	{
		IsOpen = true;
	}

}

int CComboBox::GetIndex()
{
	return SelectedIndex;
}

void CComboBox::SetIndex(int index)
{
	SelectedIndex = index;
}

std::string CComboBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "";
}

void CComboBox::SelectIndex(int idx)
{
	if (idx >= 0 && idx < Items.size())
	{
		SelectedIndex = idx;
	}
}

#pragma endregion Implementations of the ComboBox functions

#pragma region ListBox

#define LIST_ITEM_HEIGHT 16
#define LIST_SCROLL_WIDTH 8

CListBox::CListBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	SelectedIndex = 0;
	FileControlType = UIControlTypes::UIC_ListBox;
}

void CListBox::Draw(bool hover)
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	d::draw_filled_rect(a.x + 1, a.y + 1, m_iWidth - 2, m_iHeight - 2, color(90, 90, 90, 1));

	//Top Left
	d::draw_line(a.x, a.y, a.x + m_iWidth - 2, a.y, color(48, 48, 48, 255));
	d::draw_line(a.x - 1, a.y - 1, a.x + (m_iWidth / 2) - 1, a.y - 1, color(0, 0, 0, 255));

	//Top Right
	d::draw_line(a.x + (m_iWidth / 2) + 2, a.y, a.x + m_iWidth, a.y, color(48, 48, 48, 255));
	d::draw_line(a.x + (m_iWidth / 2) + 2, a.y - 1, a.x + m_iWidth + 1, a.y - 1, color(0, 0, 0, 255));

	//Left
	d::draw_line(a.x, a.y, a.x, a.y + m_iHeight, color(49, 49, 49, 255));
	d::draw_line(a.x - 1, a.y, a.x - 1, a.y + m_iHeight, color(0, 0, 0, 255));

	//Bottom
	d::draw_line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, color(48, 48, 48, 255));
	d::draw_line(a.x - 1, a.y + m_iHeight + 1, a.x + m_iWidth + 2, a.y + m_iHeight + 1, color(0, 0, 0, 255));

	//Right
	d::draw_line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight + 1, color(48, 48, 48, 255));
	d::draw_line(a.x + m_iWidth + 1, a.y, a.x + m_iWidth + 1, a.y + m_iHeight + 1, color(0, 0, 0, 255));

	if (Items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < Items.size() && drawnItems < ItemsToDraw); i++)
		{
			color textColor = color(92, 92, 92, 255);
			RECT ItemRegion = { a.x + 1, a.y + 1 + drawnItems * 16, m_iWidth - LIST_SCROLL_WIDTH - 2 , 16 };

			if (i == SelectedIndex)
			{
				textColor = color(245, 245, 245, 245);

				d::draw_gradient_v(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, color(125, 5, 255, 255), color(125, 5, 255, 255));
			}
			else if (GUI.IsMouseInRegion(ItemRegion))
			{
				textColor = color(245, 245, 245, 245);
				d::draw_filled_rect(ItemRegion.left, ItemRegion.top, ItemRegion.right, ItemRegion.bottom, color(92, 92, 92, 255));
			}

			d::draw_menu_string(ItemRegion.left + 4, ItemRegion.top + 2, Items[i].c_str(), f::menu_main, textColor);
			drawnItems++;
		}

		// Ratio of how many visible to how many are hidden
		float sizeRatio = float(ItemsToDraw) / float(Items.size());
		if (sizeRatio > 1.f) sizeRatio = 1.f;
		float posRatio = float(ScrollTop) / float(Items.size());
		if (posRatio > 1.f) posRatio = 1.f;

		sizeRatio *= m_iHeight;
		posRatio *= m_iHeight;

		d::draw_filled_rect(a.x + m_iWidth - LIST_SCROLL_WIDTH, a.y + posRatio, LIST_SCROLL_WIDTH, sizeRatio, color(52, 52, 52, 255));
	}

}

void CListBox::AddItem(std::string text, int value)
{
	Items.push_back(text);
	Values.push_back(value);
}

void CListBox::OnClick()
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	// Check the items
	if (Items.size() > 0)
	{
		int drawnItems = 0;
		for (int i = ScrollTop; (i < Items.size() && drawnItems < ItemsToDraw); i++)
		{
			color textColor = color(92, 92, 92, 255);
			RECT ItemRegion = { a.x + 1, a.y + 1 + drawnItems * 16, m_iWidth - LIST_SCROLL_WIDTH - 2 , 16 };
			if (GUI.IsMouseInRegion(ItemRegion))
			{
				SelectItem(i);
				return;
			}
			drawnItems++;
		}
	}
}

void CListBox::OnUpdate()
{
	int ItemsToDraw = m_iHeight / LIST_ITEM_HEIGHT;
	POINT a = GetAbsolutePos();

	// Did we click in the scrollbar??
	RECT Scroll = { a.x + m_iWidth - LIST_SCROLL_WIDTH , a.y + 1, LIST_SCROLL_WIDTH - 2 ,m_iHeight };

	if (GUI.IsMouseInRegion(Scroll) && GetAsyncKeyState(VK_LBUTTON)) dragging = true;
	else if (!GetAsyncKeyState(VK_LBUTTON) && dragging) dragging = false;

	if (dragging)
	{
		// Ratio of how many visible to how many are hidden
		float ratio = float(ItemsToDraw) / float(Items.size());
		POINT m = GUI.GetMouse();
		m.y -= a.y;

		float sizeRatio = float(ItemsToDraw) / float(Items.size());
		sizeRatio *= m_iHeight;
		float heightDelta = m.y + sizeRatio - m_iHeight;
		if (heightDelta > 0)
			m.y -= heightDelta;

		float mPosRatio = float(m.y) / float(m_iHeight);
		ScrollTop = mPosRatio*Items.size();
		if (ScrollTop < 0)
			ScrollTop = 0;
	}
}

void CListBox::SetHeightInItems(int items)
{
	m_iHeight = items*LIST_ITEM_HEIGHT;
}

std::string CListBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "Error";
}

#pragma endregion Implementations of the ListBox functions