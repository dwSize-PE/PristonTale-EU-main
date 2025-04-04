#pragma once
#include "stdafx.h"

enum EWeaponSoundID
{
	WEAPONSOUND_None,
	WEAPONSOUND_OneHandAxe,
	WEAPONSOUND_TwoHandAxe,
	WEAPONSOUND_OneHandSword,
	WEAPONSOUND_TwoHandSword,
	WEAPONSOUND_OneHandSpear,
	WEAPONSOUND_TwoHandSpear,
	WEAPONSOUND_OneHandClaw,
	WEAPONSOUND_BowShoot,
	WEAPONSOUND_OneHandMace,
	WEAPONSOUND_TwoHandMace,
	WEAPONSOUND_Throwing,
	WEAPONSOUND_OneHandMiss,
	WEAPONSOUND_TwoHandMiss, //13
	WEAPONSOUND_PunchHit,
	WEAPONSOUND_OneHandSmall,
	WEAPONSOUND_CriticalHit,
	WEAPONSOUND_OneHandMagic,
	WEAPONSOUND_TwoHandMagic,

};


class CSound
{
private:
	LPDIRECTSOUND			    lpDSPrimary;
	LPDIRECTSOUND			    lpDSSecondary;
	LPDIRECTSOUNDBUFFER         lpdsbStatic;					//Pointer to a static buffer
	LPDIRECTSOUND				GetPrimaryDevice();
	LPDIRECTSOUND				GetSecondaryDevice();
	LPDIRECTSOUNDBUFFER			GetPrimarySndBuf();
	LPDIRECTSOUNDBUFFER			GetSecondarySndBuf( int Num );

	static const DWORD			pfnChangeBGM = 0x005444B0;
	static const DWORD			pfnPlayDirectBGM = 0x00544450;

	IMPFNC						pfnSetWeaponSound = 0x005448D0; //Leaked code: PlayWaponSoundDirect
	IMPFNC						pfnSetSkillSound = 0x00544870;

public:
	//Constructor
								CSound();
	virtual						~CSound();

	void						PlayWave( int Num );

	void						LoadMusic( int iNum );
	void						SetVolumeMusic( int iPercent );
	void						SetVolumeEffect( int iPercent );

	static void					ChangeMusic( int iID );
	static void					PlayMusic( int iID );

	BOOL						ChangeBackgroundMusic( int iID );

	void						Update();
	void						CreateDevices();

	void						SetWeaponSound( EWeaponSoundID iID, int iX, int iY, int iZ );
	void						SetWeaponSound( EWeaponSoundID iID, UnitData * pcUnitData );

	void						SetSkillSound( int iID, int iX, int iY, int iZ );

	void						ChangeFrequencySoundSkill( int iID, DWORD dwFrequency = 2205 );
	int							GetDistanceVolume( Point3D sPosition );
};

