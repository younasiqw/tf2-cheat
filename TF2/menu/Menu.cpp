#include "../main.h"
#include "CRC32.h"

// Menu Window Size
#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650

MainWindow Menu::Window;


// Save Config to CSGO directory
void SaveCallbk()
{
	switch (Menu::Window.ConfigBox.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "config.ini");
		break;
	}
}

// Load Config from CSGO directory
void LoadCallbk()
{
	switch (Menu::Window.ConfigBox.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "config.ini");
		break;
	}
}

void MainWindow::Setup()
{
	SetPosition(400, 400);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	RegisterTab(&AimbotTab);
	RegisterTab(&TriggerbotTab);
	RegisterTab(&AccuracyTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	RegisterTab(&SkinTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	AimbotTab.Setup();
	TriggerbotTab.Setup();
	AccuracyTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();
	SkinTab.Setup();
}

void CAimbotTab::Setup()
{
	SetTitle("aimbot");

#pragma region Aimbot

	AimbotGroup.SetPosition(10, 20);
	AimbotGroup.SetText("aimbot");
	AimbotGroup.SetSize(260, 280);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aimbot_enable");
	AimbotGroup.PlaceLabledControl(1, "enabled", this, &AimbotEnable);

	AimbotKeyBind.SetFileId("aimbot_key");
	AimbotGroup.PlaceLabledControl(1, "", this, &AimbotKeyBind);

	AimbotAutoFire.SetFileId("aimbot_autofire");
	AimbotGroup.PlaceLabledControl(1, "auto shoot", this, &AimbotAutoFire);

	AimbotSilent.SetFileId("aimbot_silent");
	AimbotGroup.PlaceLabledControl(1, "silent aim", this, &AimbotSilent);

	AimbotHitscan.SetFileId("aimbot_hitscan");
	AimbotGroup.PlaceLabledControl(1, "hitscan", this, &AimbotHitscan);

	AimbotFov.SetFileId("aimbot_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.Extension = ((char*)"°");
	AimbotFov.SetValue(0.f);
	//AimbotFov.SetFormat(SliderFormat::FORMAT_DECDIG2);
	AimbotGroup.PlaceLabledControl(1, "fov", this, &AimbotFov);

	AimbotHitchance.SetFileId("aimbot_hitchance");
	AimbotHitchance.SetBoundaries(0.f, 100.f);
	AimbotHitchance.Extension = ((char*)"%%");
	AimbotHitchance.SetValue(0.f);
	AimbotGroup.PlaceLabledControl(1, "hitchance", this, &AimbotHitchance);

	AimbotMinimalDamage.SetFileId("aimbot_minimaldamage");
	AimbotMinimalDamage.SetBoundaries(0.f, 100.f);
	AimbotMinimalDamage.Extension = ((char*)"%%");
	AimbotMinimalDamage.SetValue(0.f);
	AimbotGroup.PlaceLabledControl(1, "minimal damage", this, &AimbotMinimalDamage);

	AimbotHitbox.SetFileId("aimbot_hitbox");
	AimbotHitbox.AddItem("head");
	AimbotHitbox.AddItem("chest");
	AimbotHitbox.AddItem("stomach");
	AimbotGroup.PlaceLabledControl(1, "hitbox", this, &AimbotHitbox);

	AimbotBacktrack.SetFileId("aimbot_backtrack");
	AimbotGroup.PlaceLabledControl(1, "backtrack", this, &AimbotBacktrack);

	AimbotBacktrackRecord.SetFileId("aimbot_backtrackrecord");
	AimbotBacktrackRecord.AddItem("single record");
	AimbotBacktrackRecord.AddItem("all records");
	AimbotGroup.PlaceLabledControl(1, "hitbox", this, &AimbotBacktrackRecord);

#pragma endregion Aimbot Controls Get Setup in here

#pragma region AntiAim

	AntiAimGroup.SetPosition(280, 20);
	AntiAimGroup.SetText("anti-aimbot");
	AntiAimGroup.SetSize(260, 280);
	RegisterControl(&AntiAimGroup);

	AntiAimCorrection.SetFileId("antiaimbot_correction");
	AntiAimGroup.PlaceLabledControl(1, "anti-aim correction", this, &AntiAimCorrection);

	AntiAimYawRealManipulation.SetFileId("antiaimbot_yreal_enabled");
	AntiAimGroup.PlaceLabledControl(1, "yaw real manipulation", this, &AntiAimYawRealManipulation);

	AntiAimTemplate.SetFileId("antiaimbot_template");
	AntiAimTemplate.AddItem("custom");
	AntiAimTemplate.AddItem("spin");
	AntiAimGroup.PlaceLabledControl(1, "yaw template", this, &AntiAimTemplate);

	AntiAimWhileMoving.SetFileId("antiaimbot_whilemoving");
	AntiAimWhileMoving.AddItem("off");
	AntiAimWhileMoving.AddItem("slow spin");
	AntiAimGroup.PlaceLabledControl(1, "yaw while moving", this, &AntiAimWhileMoving);

	/*
	AntiAimInAir.SetFileId("antiaimbot_inair");
	AntiAimInAir.AddItem("off");
	AntiAimInAir.AddItem("backwards");
	AntiAimGroup.PlaceLabledControl(1, "yaw in air", this, &AntiAimInAir);
	*/

	AntiAimYDelta.SetFileId("antiaimbot_delta");
	AntiAimYDelta.SetBoundaries(0.f, 360.f);
	AntiAimYDelta.Extension = ((char*)"°");
	AntiAimYDelta.SetValue(0.f);
	AntiAimGroup.PlaceLabledControl(1, "custom delta", this, &AntiAimYDelta);

	AntiAimYRealAngle.SetFileId("antiaimbot_realangle");
	AntiAimYRealAngle.SetBoundaries(0.f, 360.f);
	AntiAimYRealAngle.Extension = ((char*)"°");
	AntiAimYRealAngle.SetValue(0.f);
	AntiAimGroup.PlaceLabledControl(1, "custom real angle", this, &AntiAimYRealAngle);

	AntiAimYFakeAngle.SetFileId("antiaimbot_fakeangle");
	AntiAimYFakeAngle.SetBoundaries(0.f, 360.f);
	AntiAimYFakeAngle.Extension = ((char*)"°");
	AntiAimYFakeAngle.SetValue(0.f);
	AntiAimGroup.PlaceLabledControl(1, "custom fake angle", this, &AntiAimYFakeAngle);

	AntiAimOnKnife.SetFileId("antiaimbot_onknife");
	AntiAimGroup.PlaceLabledControl(1, "on knife", this, &AntiAimOnKnife);

	AntiAimInUse.SetFileId("antiaimbot_inuse");
	AntiAimGroup.PlaceLabledControl(1, "in use", this, &AntiAimInUse);

#pragma endregion AntiAim

}

void CTriggerbotTab::Setup()
{
	SetTitle("triggerbot");

#pragma region TriggerMain

	TriggerMainGroup.SetPosition(10, 20);
	TriggerMainGroup.SetText("triggerbot");
	TriggerMainGroup.SetSize(260, 280);
	RegisterControl(&TriggerMainGroup);

	TriggerMainEnable.SetFileId("triggebot_enabled");
	TriggerMainGroup.PlaceLabledControl(1, "enabled", this, &TriggerMainEnable);

	TriggerMainKeyBind.SetFileId("triggebot_key");
	TriggerMainGroup.PlaceLabledControl(1, "", this, &TriggerMainKeyBind);


#pragma endregion TriggerMain

#pragma region Triggerbot

	TriggerGroup.SetPosition(280, 20);
	TriggerGroup.SetText("filter");
	TriggerGroup.SetSize(260, 280);
	RegisterControl(&TriggerGroup);

	TriggerHead.SetFileId("triggebot_filter_head");
	TriggerGroup.PlaceLabledControl(1, "head", this, &TriggerHead);

	TriggerArms.SetFileId("triggebot_filter_arms");
	TriggerGroup.PlaceLabledControl(1, "arms", this, &TriggerArms);

	TriggerChest.SetFileId("triggebot_filter_chest");
	TriggerGroup.PlaceLabledControl(1, "chest", this, &TriggerChest);

	TriggerStomach.SetFileId("triggebot_filter_stomach");
	TriggerGroup.PlaceLabledControl(1, "stomach", this, &TriggerStomach);

	TriggerLegs.SetFileId("triggebot_filter_legs");
	TriggerGroup.PlaceLabledControl(1, "legs", this, &TriggerLegs);

#pragma endregion Triggerbot

}

void CAccuracyTab::Setup()
{
	SetTitle("accuracy");

#pragma region Recoil

	RecoilGroup.SetPosition(10, 20);
	RecoilGroup.SetText("recoil");
	RecoilGroup.SetSize(260, 280);
	RegisterControl(&RecoilGroup);

	NoRecoil.SetFileId("accuracy_norecoil");
	RecoilGroup.PlaceLabledControl(1, "no recoil", this, &NoRecoil);

	NoRecoilFactor.SetFileId("accuracy_norecoilfactor");
	NoRecoilFactor.SetBoundaries(0.f, 2.f);
	NoRecoilFactor.Extension = ((char*)"");
	NoRecoilFactor.SetValue(0.0f);
	NoRecoilFactor.SetFormat(SliderFormat::FORMAT_DECDIG2);
	RecoilGroup.PlaceLabledControl(1, "", this, &NoRecoilFactor);

	CompensationGroup.SetPosition(280, 20);
	CompensationGroup.SetText("compensation");
	CompensationGroup.SetSize(260, 280);
	RegisterControl(&CompensationGroup);

	Backtracking.SetFileId("accuracy_backtracking");
	CompensationGroup.PlaceLabledControl(1, "backtracking", this, &Backtracking);


}

void CVisualTab::Setup()
{
	SetTitle("visuals");

#pragma region ESP

	ESPGroup.SetText("esp");
	ESPGroup.SetPosition(10, 20);
	ESPGroup.SetSize(180, 350);
	RegisterControl(&ESPGroup);

	Box.SetFileId("visuals_box");
	ESPGroup.PlaceLabledControl(1, "box", this, &Box);

	Name.SetFileId("visuals_name");
	ESPGroup.PlaceLabledControl(1, "name", this, &Name);

	HealthBar.SetFileId("visuals_healthbar");
	ESPGroup.PlaceLabledControl(1, "healthbar", this, &HealthBar);

	Weapon.SetFileId("visuals_weapon");
	ESPGroup.PlaceLabledControl(1, "weapon", this, &Weapon);

	Bones.SetFileId("visuals_bones");
	ESPGroup.PlaceLabledControl(1, "bones", this, &Bones);

	Teammates.SetFileId("visuals_teammates");
	ESPGroup.PlaceLabledControl(1, "teammates", this, &Teammates);

	Chams.SetFileId("visuals_chams");
	ESPGroup.PlaceLabledControl(1, "chams", this, &Chams);

#pragma endregion ESP

#pragma region World

	WorldGroup.SetText("world");
	WorldGroup.SetPosition(200, 20);
	WorldGroup.SetSize(180, 350);
	RegisterControl(&WorldGroup);

	C4.SetFileId("visuals_c4");
	WorldGroup.PlaceLabledControl(1, "c4", this, &C4);

	Weapons.SetFileId("visuals_weapons");
	WorldGroup.PlaceLabledControl(1, "weapons", this, &Weapons);

	Grenades.SetFileId("visuals_grenades");
	WorldGroup.PlaceLabledControl(1, "grenades", this, &Grenades);

#pragma endregion World

#pragma region Removals

	RemovalsGroup.SetText("removals");
	RemovalsGroup.SetPosition(390, 20);
	RemovalsGroup.SetSize(180, 350);
	RegisterControl(&RemovalsGroup);

	RemoveFlash.SetFileId("visuals_removeflash");
	RemovalsGroup.PlaceLabledControl(1, "flash", this, &RemoveFlash);

	RemoveSmoke.SetFileId("visuals_removesmoke");
	RemovalsGroup.PlaceLabledControl(1, "smoke", this, &RemoveSmoke);

	RemoveScope.SetFileId("visuals_removescope");
	RemovalsGroup.PlaceLabledControl(1, "scope", this, &RemoveScope);

	RemoveSleeves.SetFileId("visuals_removesleeves");
	RemovalsGroup.PlaceLabledControl(1, "sleeves", this, &RemoveSleeves);

	RemoveVisualRecoil.SetFileId("visuals_removevisualrecoil");
	RemovalsGroup.PlaceLabledControl(1, "visual recoil", this, &RemoveVisualRecoil);

	RemovePostProcessing.SetFileId("visuals_removepostprocessing");
	RemovalsGroup.PlaceLabledControl(1, "post processing", this, &RemovePostProcessing);

#pragma endregion Removals
}



void CMiscTab::Setup()
{
	SetTitle("misc");

#pragma region Misc

	MiscGroup.SetPosition(10, 20);
	MiscGroup.SetSize(260, 355);
	MiscGroup.SetText("misc");
	RegisterControl(&MiscGroup);

	DebugFOV.SetFileId("misc_debugfov");
	DebugFOV.SetBoundaries(0.f, 45.f);
	DebugFOV.Extension = ((char*)"°");
	DebugFOV.SetValue(0.f);
	MiscGroup.PlaceLabledControl(1, "debug fov", this, &DebugFOV);

	ViewmodelFOV.SetFileId("misc_viewmodelfov");
	ViewmodelFOV.SetBoundaries(0.f, 45.f);
	ViewmodelFOV.Extension = ((char*)"°");
	ViewmodelFOV.SetValue(0.f);
	MiscGroup.PlaceLabledControl(1, "viewmodel fov", this, &ViewmodelFOV);

	Bunnyhop.SetFileId("misc_bunnyhop");
	MiscGroup.PlaceLabledControl(1, "bunnyhop", this, &Bunnyhop);

	AutoStrafe.SetFileId("misc_autostrafe");
	MiscGroup.PlaceLabledControl(1, "auto strafe", this, &AutoStrafe);

	AutoPistol.SetFileId("misc_autopistol");
	MiscGroup.PlaceLabledControl(1, "auto pistol", this, &AutoPistol);

	Fakelag.SetFileId("misc_fakelag");
	MiscGroup.PlaceLabledControl(1, "fakelag", this, &Fakelag);

	FakelagFactor.SetFileId("misc_fakelag_factor");
	FakelagFactor.SetBoundaries(0.f, 14.f);
	FakelagFactor.Extension = ((char*)"*");
	FakelagFactor.SetValue(0.f);
	//AimbotFov.SetFormat(SliderFormat::FORMAT_DECDIG2);
	MiscGroup.PlaceLabledControl(1, "factor", this, &FakelagFactor);

	PingSpike.SetFileId("misc_pingspike");
	MiscGroup.PlaceLabledControl(1, "ping spike", this, &PingSpike);

	PingSpikeFactor.SetFileId("misc_pingspike_factor");
	PingSpikeFactor.SetBoundaries(0.15f, 1.00f);
	PingSpikeFactor.Extension = ((char*)"ms");
	PingSpikeFactor.SetValue(0.15f);
	PingSpikeFactor.SetFormat(SliderFormat::FORMAT_DECDIG2);
	MiscGroup.PlaceLabledControl(1, "delay", this, &PingSpikeFactor);

	RadarReveal.SetFileId("misc_radarreveal");
	MiscGroup.PlaceLabledControl(1, "radar reveal", this, &RadarReveal);

	SpectatorList.SetFileId("misc_spectatorlist");
	MiscGroup.PlaceLabledControl(1, "spectator list", this, &SpectatorList);

	EventLog.SetFileId("misc_logevents");
	MiscGroup.PlaceLabledControl(1, "log events", this, &EventLog);

	GrenadePrediction.SetFileId("misc_grenadeprediction");
	MiscGroup.PlaceLabledControl(1, "grenade prediction", this, &GrenadePrediction);

	BacktrackLine.SetFileId("misc_backtrackline");
	MiscGroup.PlaceLabledControl(1, "backtrack line", this, &BacktrackLine);

	//LocalSteamID.SetFileId("misc_overwatchrevealer");
	//MiscGroup.PlaceLabledControl(1, "overwatch revealer", this, &LocalSteamID);

	DamageIndicator.SetFileId("misc_damageindicator");
	MiscGroup.PlaceLabledControl(1, "damage indicator", this, &DamageIndicator);

	Hitsound.SetFileId("misc_hitsound");
	MiscGroup.PlaceLabledControl(1, "hitsound", this, &Hitsound);

	Hitmarker.SetFileId("misc_hitmarker");
	MiscGroup.PlaceLabledControl(1, "hitmarker", this, &Hitmarker);

	ThirdPerson.SetFileId("misc_thirdperson");
	MiscGroup.PlaceLabledControl(1, "thirdperson", this, &ThirdPerson);

	Nightmode.SetFileId("misc_nightmode");
	MiscGroup.PlaceLabledControl(1, "nightmode", this, &Nightmode);

	/*
	Clantags.SetFileId("misc_clantags");
	Clantags.AddItem("off");
	Clantags.AddItem("advertisement");
	Clantags.AddItem("puschelbot");
	MiscGroup.PlaceLabledControl(1, "clantags", this, &Clantags);
	*/

#pragma endregion Misc


#pragma region Config

	AdvancedGroup.SetPosition(280, 20);
	AdvancedGroup.SetSize(260, 355);
	AdvancedGroup.SetText("config");
	RegisterControl(&AdvancedGroup);

	LoadButton.SetText("Load");
	LoadButton.SetCallback(LoadCallbk);
	AdvancedGroup.PlaceLabledControl(0, "", this, &LoadButton);

	SaveButton.SetText("Save");
	SaveButton.SetCallback(SaveCallbk);
	AdvancedGroup.PlaceLabledControl(0, "", this, &SaveButton);

#pragma endregion Config
}

void Menu::SetupMenu()
{
	Window.Setup();
	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
	GUI.Update();
	GUI.Draw();
}