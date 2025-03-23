#pragma once


#define _TESTMAP_DPS_SPAWN_COUNT		140

class CTestMapHandler
{
	enum ETestMode : int
	{
		Unknown = -1,
		DPS = 1,
		DEF = 2,
	};

public:
	CTestMapHandler ();
	virtual ~CTestMapHandler ();

	void SetTestMonsterName ( std::string name ) { sTestMon = name; }
	std::string GetTestMonsterName () { return sTestMon; }

	void SetMonsterHP ( int iHP );
	void SpawnTestMonstersDps ( User * pcUser );
	void SpawnTestMonstersDef ( User * pcUser );
	void ClearUnitsFromMap ();
	void SendSpawnFlagMarkersAoE ( User * pcUser );
	BOOL UnitCanTargetPlayer ( UnitData * pcUnitData );
	BOOL UnitCanMove ( UnitData * pcUnitData );
	void Reset ();
	void Tick1s ();
	BOOL GetExperienceRatePerFlag ( User * pcUser, char * DPS, char * HSFlagCount );

private:

	double	GetPlayerAccuracyPercent(User * pcUser, int iAttackRating );
	int GetStat ( std::string MonsterStatName, std::string MonsterName );
	UnitData * pcUnitDataDps[_TESTMAP_DPS_SPAWN_COUNT];

	std::string sTestMon = "KH_60";

	ETestMode eTestMode = ETestMode::Unknown;
	BOOL bActive = FALSE;
	BOOL bSpawned = FALSE;

	int iMonsterHP = 50000;
	int iMonsterHPBlockValue = 1000;

	//All positions in this array was captured using
	//testmap_log_pos while in MAP ID = 32
	//Generated by
    //https://docs.google.com/spreadsheets/d/1pEgs0nQYAunHSPRBHixnImycB50cprKgeBwL1FbGDwU/edit#gid=0
	const Point3D saDpsSpawns[_TESTMAP_DPS_SPAWN_COUNT]
	{
		//5 x 5 grid at 40 spacing apart
		{22666,1486,9276},
		{22626,1486,9276},
		{22586,1486,9276},
		{22546,1486,9276},
		{22506,1486,9276},
		{22666,1486,9316},
		{22626,1486,9316},
		{22586,1486,9316},
		{22546,1486,9316},
		{22506,1486,9316},
		{22666,1486,9356},
		{22626,1486,9356},
		//{22586,1486,9356}, center
		{22546,1486,9356},
		{22506,1486,9356},
		{22666,1486,9396},
		{22626,1486,9396},
		{22586,1486,9396},
		{22546,1486,9396},
		{22506,1486,9396},
		{22666,1486,9436},
		{22626,1486,9436},
		{22586,1486,9436},
		{22546,1486,9436},
		{22506,1486,9436},

		//5 x 5 grid at 50 spacing apart
		{22360,1486,9276},
		{22310,1486,9276},
		{22260,1486,9276},
		{22210,1486,9276},
		{22160,1486,9276},
		{22360,1486,9326},
		{22310,1486,9326},
		{22260,1486,9326},
		{22210,1486,9326},
		{22160,1486,9326},
		{22360,1486,9376},
		{22310,1486,9376},
		//{22260,1486,9376}, center
		{22210,1486,9376},
		{22160,1486,9376},
		{22360,1486,9426},
		{22310,1486,9426},
		{22260,1486,9426},
		{22210,1486,9426},
		{22160,1486,9426},
		{22360,1486,9476},
		{22310,1486,9476},
		{22260,1486,9476},
		{22210,1486,9476},
		{22160,1486,9476},

		//5 x 5 grid at 60 spacing apart
		{21990,1486,9276},
		{21930,1486,9276},
		{21870,1486,9276},
		{21810,1486,9276},
		{21750,1486,9276},
		{21990,1486,9336},
		{21930,1486,9336},
		{21870,1486,9336},
		{21810,1486,9336},
		{21750,1486,9336},
		{21990,1486,9396},
		{21930,1486,9396},
		//{21870,1486,9396}, center
		{21810,1486,9396},
		{21750,1486,9396},
		{21990,1486,9456},
		{21930,1486,9456},
		{21870,1486,9456},
		{21810,1486,9456},
		{21750,1486,9456},
		{21990,1486,9516},
		{21930,1486,9516},
		{21870,1486,9516},
		{21810,1486,9516},
		{21750,1486,9516},

		//5 x 5 grid at 70 spacing apart
		{22160,1486,9790},
		{22090,1486,9790},
		{22020,1486,9790},
		{21950,1486,9790},
		{21880,1486,9790},
		{22160,1486,9860},
		{22090,1486,9860},
		{22020,1486,9860},
		{21950,1486,9860},
		{21880,1486,9860},
		{22160,1486,9930},
		{22090,1486,9930},
		//{22020,1486,9930}, center
		{21950,1486,9930},
		{21880,1486,9930},
		{22160,1486,10000},
		{22090,1486,10000},
		{22020,1486,10000},
		{21950,1486,10000},
		{21880,1486,10000},
		{22160,1486,10070},
		{22090,1486,10070},
		{22020,1486,10070},
		{21950,1486,10070},
		{21880,1486,10070},

		//2 x 12 grid at 30 spacing apart
		{ 22620,1486,9600 },
		{ 22620,1486,9630 },
		{ 22620,1486,9660 },
		{ 22620,1486,9690 },
		{ 22620,1486,9720 },
		{ 22620,1486,9750 },
		{ 22620,1486,9780 },
		{ 22620,1486,9810 },
		{ 22620,1486,9840 },
		{ 22620,1486,9870 },
		{ 22620,1486,9900 },
		{ 22620,1486,9930 },
		{ 22590,1486,9600 },
		{ 22590,1486,9630 },
		{ 22590,1486,9660 },
		{ 22590,1486,9690 },
		{ 22590,1486,9720 },
		{ 22590,1486,9750 },
		{ 22590,1486,9780 },
		{ 22590,1486,9810 },
		{ 22590,1486,9840 },
		{ 22590,1486,9870 },
		{ 22590,1486,9900 },
		{ 22590,1486,9930 },

		//3 x 3 grid at 25 spacing apart
		{ 22430,1486,9760 },
		{ 22405,1486,9760 },
		{ 22380,1486,9760 },
		{ 22430,1486,9785 },
		{ 22405,1486,9785 },
		{ 22380,1486,9785 },
		{ 22430,1486,9810 },
		{ 22405,1486,9810 },
		{ 22380,1486,9810 },
		{ 22430,1486,9835 },
		{ 22405,1486,9835 },
		{ 22380,1486,9835 },
		{ 22430,1486,9860 },
		{ 22405,1486,9860 },
		{ 22380,1486,9860 },

		//Single Target
		{ 22451,1486,10178 },
	};
};