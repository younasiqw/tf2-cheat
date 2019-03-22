#pragma once

#include "GUI.h"
#include "Controls.h"

class CAimbotTab : public CTab
{
public:
	void Setup();

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotSilent;
	CSlider AimbotPointscale;
	CCheckBox AimbotHitscan;
	CCheckBox AimbotAutowall;
	CCheckBox AimbotTeammates;
	CKeyBind  AimbotKeyBind;
	CSlider  AimbotFov;
	CSlider AimbotHitchance;
	CSlider AimbotMinimalDamage;
	CComboBox AimbotHitbox;
	CCheckBox AimbotBacktrack;
	CComboBox AimbotBacktrackRecord;

	// Anti-Aim Settings
	CGroupBox AntiAimGroup;
	CCheckBox AntiAimCorrection;
	CCheckBox AntiAimYawRealManipulation;
	CComboBox AntiAimTemplate;
	CComboBox AntiAimWhileMoving;
	CComboBox AntiAimInAir;
	CSlider  AntiAimYDelta;
	CSlider AntiAimYRealAngle;
	CSlider AntiAimYFakeAngle;
	CCheckBox AntiAimOnKnife;
	CCheckBox AntiAimInUse;

};

class CTriggerbotTab : public CTab
{
public:
	void Setup();

	// Triggerbot
	CGroupBox TriggerMainGroup;
	CCheckBox TriggerMainEnable;
	CKeyBind  TriggerMainKeyBind;

	// Filter
	CGroupBox TriggerGroup;
	CCheckBox TriggerHead;
	CCheckBox TriggerArms;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerLegs;
};

class CAccuracyTab : public CTab
{
public:
	void Setup();

	// Recoil
	CGroupBox RecoilGroup;
	CCheckBox NoRecoil;
	CSlider NoRecoilFactor;

	// Exploits
	CGroupBox CompensationGroup;
	CCheckBox Backtracking;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	// ESP
	CGroupBox ESPGroup;
	CCheckBox Box;
	CCheckBox Name;
	CCheckBox HealthBar;
	CCheckBox Weapon;
	CCheckBox Bones;
	CCheckBox Chams;
	CCheckBox Teammates;

	// World
	CGroupBox WorldGroup;
	CCheckBox C4;
	CCheckBox Weapons;
	CCheckBox Grenades;

	// Removals
	CGroupBox RemovalsGroup;
	CCheckBox RemoveFlash;
	CCheckBox RemoveSmoke;
	CCheckBox RemoveScope;
	CCheckBox RemoveSleeves;
	CCheckBox RemovePostProcessing;
	CCheckBox RemoveVisualRecoil;
};

class CMiscTab : public CTab
{
public:
	void Setup();

	// Other Settings
	CGroupBox MiscGroup;

	CSlider DebugFOV;
	CSlider ViewmodelFOV;
	CCheckBox Bunnyhop;
	CCheckBox AutoStrafe;
	CCheckBox RadarReveal;
	CCheckBox RankReveal;
	CCheckBox AutoPistol;
	CCheckBox Hitsound;
	CCheckBox Hitmarker;
	CCheckBox EventLog;
	CCheckBox ClantagChanger;
	CCheckBox SpectatorList;
	CCheckBox NameStealer;
	CCheckBox NewlineClantag;
	CCheckBox AutoAccept;
	CCheckBox Nightmode;
	CCheckBox ThirdPerson;
	CCheckBox Fakelag;
	CSlider FakelagFactor;
	CKeyBind FakeLagKey;
	CCheckBox PingSpike;
	CSlider PingSpikeFactor;
	CCheckBox SpreadCircle;
	CCheckBox ZeusBot;
	CCheckBox KnifeBot;
	CCheckBox DamageIndicator;
	CCheckBox GrenadePrediction;
	CCheckBox Thirdperson;
	CComboBox Clantags;
	CCheckBox BulletTracers;
	CCheckBox BacktrackLine;
	CCheckBox CrouchExploit;

	CGroupBox AdvancedGroup;
	CComboBox ConfigList;
	CCheckBox QuickConfigs;
	CButton LoadButton;
	CButton SaveButton;

};

class CSkinTab : public CTab
{
public:
	void Setup();

	// Knife
	CGroupBox KnifeGroup;

	CComboBox KnifeModel;
	CComboBox KnifeSkin;

	// Gloves
	CGroupBox GloveGroup;

	CComboBox GloveModel;
	CComboBox GloveSkin;
	CComboBox GloveWear;

	// Pistols
	CGroupBox PistolGroup;

	CComboBox GlockSkin;
	CComboBox CZ75Skin;
	CComboBox USPSkin;
	CComboBox DeagleSkin;
	CComboBox RevolverSkin;
	CComboBox DualBerettasSkin;
	CComboBox Tec9Skin;
	CComboBox FiveSevenSkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	// MP's
	CGroupBox MPGroup;

	CComboBox Mac10Skin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;
	CComboBox PPBizonSkin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;

	// Sniper
	CGroupBox SniperGroup;

	CComboBox AWPSkin;
	CComboBox SSG08Skin;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;

	// Rifles
	CGroupBox RifleGroup;

	CComboBox AK47Skin;
	CComboBox M4A1SSkin;
	CComboBox M4A4Skin;
	CComboBox AUGSkin;
	CComboBox SG553Skin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;

	// Heavy
	CGroupBox HeavyGroup;

	CComboBox MAG7Skin;
	CComboBox NOVASkin;
	CComboBox SAWEDOFFSkin;
	CComboBox XM1014Skin;
	CComboBox M249Skin;
	CComboBox NEGEVSkin;


	// General
	CGroupBox GeneralGroup;

	CCheckBox SkinsEnabled;
	CButton Update;
};

// Elements that can be placed anywhere in any tabs, should be decleared here.

class MainWindow : public CWindow
{
public:
	void Setup();

	CAimbotTab AimbotTab;
	CTriggerbotTab TriggerbotTab;
	CAccuracyTab AccuracyTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CSkinTab SkinTab;

	CComboBox ConfigBox;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern MainWindow Window;
};