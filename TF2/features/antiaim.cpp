// Anti-Aimbot
#include "../main.h"




void movementfix(user_cmd* pCmd, vector vOldAngles, float fOldSidemove, float fOldForward)
{
	int e = rand() % 3;

	vector curAngs = pCmd->viewangles;
	float fRot = 90;

	float deltaView = pCmd->viewangles.y - vOldAngles.y;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	pCmd->forward_move = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->side_move = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

void CAntiAim::run(user_cmd* cmd)
{
	user_cmd* pCmd = cmd;
	vector vOldAngles = cmd->viewangles;
	float fOldForward = cmd->forward_move;
	float fOldSidemove = cmd->side_move;
	vector/*&*/ angles = cmd->viewangles;

	auto base = reinterpret_cast<uintptr_t>(_AddressOfReturnAddress()) - sizeof(uintptr_t);
	bool& bSendPacket = *(***reinterpret_cast<bool****>(base) - 1);

	static int ticks = 0;

	if (GetAsyncKeyState(VK_XBUTTON2)) /*&& !cmd->buttons & IN_ATTACK)*/
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			bSendPacket = true;
		}
		else
		{
			bSendPacket = false;
			cmd->viewangles.y = -90; // real
			ChokedPackets = -1;
		}
	}

	movementfix(pCmd, vOldAngles, fOldSidemove, fOldForward);
}