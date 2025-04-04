#include "stdafx.h"
#include "SettingsModel.h"


CSettingsModel::CSettingsModel()
{
}


CSettingsModel::~CSettingsModel()
{
}


CSettingsModel::sSettings & CSettingsModel::GetSettings()
{
	return sSettingsData;
}
CSettingsModel::sSettings & CSettingsModel::GetOldSettings()
{
	return sOldSettingsData;
}

BOOL CSettingsModel::IsLootFiltersChanged()
{
	if (bFirstRead == FALSE)
		return FALSE;

	if (sOldSettingsData.bEnableLootFilter != sSettingsData.bEnableLootFilter)
		return TRUE;

	if (sOldSettingsData.iLootFilterFlags != sSettingsData.iLootFilterFlags)
		return TRUE;

	if (sOldSettingsData.bEnableEquipmentMinLevelFilter != sSettingsData.bEnableEquipmentMinLevelFilter)
		return TRUE;

	if (sOldSettingsData.iMinEquipmentLevelReq != sSettingsData.iMinEquipmentLevelReq)
		return TRUE;

	return FALSE;
}

BOOL CSettingsModel::ReadSettings()
{
	INI::CReader cReader( "game.ini" );

	if ( bFirstRead )
		CopyMemory( &sOldSettingsData, &sSettingsData, sizeof( sSettings ) );

	//Screen
	{
		sSettingsData.bWindowed				= cReader.ReadBool( "Screen", "Windowed" );
		sSettingsData.bAutoAdjust			= cReader.ReadBool( "Screen", "AutoAdjust" );
		sSettingsData.dwWidth				= cReader.ReadInt( "Screen", "Width" );
		sSettingsData.dwHeight				= cReader.ReadInt( "Screen", "Height" );
		sSettingsData.bStartMaximized		= cReader.ReadBool( "Screen", "StartMaximized" );

		if ( STRINGCOMPARE( cReader.ReadString( "Screen", "Ratio" ).c_str(), "4:3" ) )
			sSettingsData.bWidescreen = FALSE;
		else
			sSettingsData.bWidescreen = TRUE;
	}

	//Graphics
	{
		sSettingsData.dwBitDepth			= cReader.ReadInt( "Graphics", "BitDepth" );
		sSettingsData.bHighTextureQuality	= cReader.ReadBool( "Graphics", "HighTextureQuality" );
		sSettingsData.bVSync				= cReader.ReadBool( "Graphics", "VSync" );
		sSettingsData.bNoEffects			= cReader.ReadBool( "Graphics", "NoEffects" );
		sSettingsData.bAntiAliasing = FALSE; // cReader.ReadBool("Graphics", "AntiAliasing");
	}

	//Camera
	{
		sSettingsData.bFarCameraSight		= cReader.ReadBool( "Camera", "FarCameraSight" );
		sSettingsData.bInvertedCamera		= cReader.ReadOnOff( "Camera", "InvertedCamera" );
		sSettingsData.bARPGCamera			= cReader.ReadOnOff( "Camera", "EnhancedLockedCamera" );
		sSettingsData.iCameraRange			= cReader.ReadInt( "Camera", "CameraRange" );
		sSettingsData.bCustomZoom			= cReader.ReadBool("Camera", "CustomZoom");
		sSettingsData.iZoomLevel			= cReader.ReadInt("Camera", "CustomZoomAmount");
		sSettingsData.bCustomZoomTown		= cReader.ReadBool("Camera", "CustomZoomTown");
		sSettingsData.iZoomTownLevel		= cReader.ReadInt("Camera", "CustomZoomTownAmount");
	}

	//Audio
	{
		sSettingsData.bNoSoundEffects		= cReader.ReadBool( "Audio", "NoEffects" );
		sSettingsData.bNoMusic				= cReader.ReadBool( "Audio", "NoMusic" );
		sSettingsData.iMusicVolume			= cReader.ReadInt( "Audio", "MusicVolume" );
		sSettingsData.iEffectVolume			= cReader.ReadInt( "Audio", "EffectVolume" );
	}

	//Game
	{
		STRINGCOPY( sSettingsData.szLastAccount, cReader.ReadString( "Game", "LastAccount" ).c_str() );

		//Copy Macros
		char szMacro[ 16 ] = { 0 };
		for ( int i = 0; i < 10; i++ )
		{
			STRINGFORMAT( szMacro, "Macro%d", i+1 );
			STRINGCOPY( sSettingsData.szaMacro[ i ], cReader.ReadString( "Game", szMacro ).c_str() );
			STRINGCOPYLEN( (char*)(0x00CDC144 + (i * 100)), 100, sSettingsData.szaMacro[ i ] );
		}

		// Settings
		sSettingsData.bNoWhisper		= cReader.ReadBool( "Game", "NoWhisper" );
		sSettingsData.bNoTradeChat		= cReader.ReadBool( "Game", "NoTradeChat" );
		sSettingsData.bNoTradeRequest	= cReader.ReadBool( "Game", "NoTradeRequest" );
		sSettingsData.bNoPartyRequest	= cReader.ReadBool( "Game", "NoPartyRequest" );

		sSettingsData.bEnableLootFilter		= cReader.ReadBool( "Game", "EnableLootFilter" );

		int lootFilterFlagsV2 = cReader.ReadInt( "Game", "LootFilterFlagsV2", -1 );

		if (lootFilterFlagsV2 == -1)
			sSettingsData.iLootFilterFlags = LOOTFILTER_All;
		else
			sSettingsData.iLootFilterFlags = lootFilterFlagsV2;
	}

	//Weapon Enchantment
	{

#ifdef ENCHANTWEAPON_SETTING
		sSettingsData.bWeaponEnchantPerference = (EElementID)cReader.ReadInt( "Skills", "EnchantWeaponPerference", 0);
#endif
	}

	//Personalization
	{
		// Settings
		sSettingsData.bDebugDamage			 = cReader.ReadBool( "Personalization", "DebugDamage" );
		sSettingsData.bHPBarOnTarget		 = !cReader.ReadBool( "Personalization", "HideHPBarOnTarget" );
		sSettingsData.bHPBarOnSelf			 = cReader.ReadBool( "Personalization", "ShowHPBarOnSelf" );
		sSettingsData.bFPS					 = cReader.ReadBool( "Personalization", "FPS" );
		sSettingsData.bPing					 = cReader.ReadBool( "Personalization", "Ping" );
		sSettingsData.bDebugKill			 = cReader.ReadBool( "Personalization", "KillInfo" );
		sSettingsData.bItemViewTogglableA    = cReader.ReadBool( "Personalization", "ItemViewTogglableA" );
		sSettingsData.bDefaultPetModeAggressive    = !cReader.ReadBool( "Personalization", "PetModePassive" );
		sSettingsData.bChatBoxRemoveFocusOnEnter    = !cReader.ReadBool( "Personalization", "ChatBoxKeepFocusOnEnter" );
		sSettingsData.bAutoSelectNearestTargetForAoE    = cReader.ReadBool( "Personalization", "AutoSelectNearestTarget" );
		sSettingsData.iMinEquipmentLevelReq	 = cReader.ReadInt(  "Personalization", "LootFilterEquipmentMinLevel" );
		sSettingsData.bEnableEquipmentMinLevelFilter	 = cReader.ReadBool(  "Personalization", "EnableEquipmentMinLevelFilter" );

		if (sSettingsData.iMinEquipmentLevelReq < 0)
			sSettingsData.iMinEquipmentLevelReq = 0;

		else if (sSettingsData.iMinEquipmentLevelReq > 150)
			sSettingsData.iMinEquipmentLevelReq = 150;
	}

	//User Interface
	{
		//Settings
		sSettingsData.bLockUI = cReader.ReadBool( "UI", "Lock" );
//		sSettingsData.bSaveUI = cReader.ReadBool( "UI", "SaveChanges" );
		sSettingsData.bShowPartyMembers = cReader.ReadBool( "UI", "ShowPartyMembers" );
		sSettingsData.bShowRaidMembers = cReader.ReadBool( "UI", "ShowRaidMembers" );
		sSettingsData.bShowClanMembers = cReader.ReadBool( "UI", "ShowClanMembers" );
		sSettingsData.bShowEnemies = cReader.ReadBool( "UI", "ShowEnemies" );
		sSettingsData.bShowNPCs = cReader.ReadBool( "UI", "ShowNPCS" );
		//sSettingsData.bMinimapAlwaysActive = cReader.ReadBool( "UI", "MinimapAlwaysActive" );
		sSettingsData.bShowNextBossTimer = cReader.ReadBool( "UI", "ShowNextBossTimer" );
		sSettingsData.bShowNameAboveHead = cReader.ReadBool("UI", "ShowNameAboveHead");
		sSettingsData.bShowFrameAboveHead = cReader.ReadBool("UI", "ShowFrameAboveHead");
		sSettingsData.bShowNotice = cReader.ReadBool( "UI", "ShowNotice" );
		sSettingsData.bTargetDistance = cReader.ReadBool( "UI", "TargetDistance" );
		sSettingsData.bTargetHPValue = cReader.ReadBool( "UI", "TargetHPValue" );
		sSettingsData.bTargetHPPercent = cReader.ReadBool( "UI", "TargetHPPercent" );
	}

	//Is First Read?
	if ( !bFirstRead )
	{
		CopyMemory( &sOldSettingsData, &sSettingsData, sizeof( sSettings ) );
		bFirstRead = TRUE;
	}

	return TRUE;
}

void CSettingsModel::WriteSettings()
{
	INI::CReader cReader( "game.ini" );

	//Screen
	{
		cReader.WriteBool( "Screen", "Windowed", sSettingsData.bWindowed );
		cReader.WriteBool( "Screen", "AutoAdjust", sSettingsData.bAutoAdjust );
		cReader.WriteInt( "Screen", "Width", sSettingsData.dwWidth );
		cReader.WriteInt( "Screen", "Height", sSettingsData.dwHeight );
		cReader.WriteBool( "Screen", "StartMaximized", sSettingsData.bStartMaximized );

		if ( sSettingsData.bWidescreen )
			cReader.WriteString( "Screen", "Ratio", "16:9" );
		else
			cReader.WriteString( "Screen", "Ratio", "4:3" );
	}

	//Graphics
	{
		cReader.WriteInt( "Graphics", "BitDepth", sSettingsData.dwBitDepth );
		cReader.WriteBool( "Graphics", "HighTextureQuality", sSettingsData.bHighTextureQuality );
		cReader.WriteBool( "Graphics", "VSync", sSettingsData.bVSync );
		cReader.WriteBool( "Graphics", "NoEffects", sSettingsData.bNoEffects );
		cReader.WriteBool( "Graphics", "AntiAliasing", sSettingsData.bAntiAliasing );
	}

	//Camera
	{
		cReader.WriteBool( "Camera", "FarCameraSight", sSettingsData.bFarCameraSight );
		cReader.WriteOnOff( "Camera", "InvertedCamera", sSettingsData.bInvertedCamera );
		cReader.WriteOnOff( "Camera", "EnhancedLockedCamera", sSettingsData.bARPGCamera );
		cReader.WriteInt( "Camera", "CameraRange", sSettingsData.iCameraRange );
		cReader.WriteBool("Camera", "CustomZoom", sSettingsData.bCustomZoom);
		cReader.WriteInt("Camera", "CustomZoomAmount", sSettingsData.iZoomLevel);
		cReader.WriteBool("Camera", "CustomZoomTown", sSettingsData.bCustomZoomTown);
		cReader.WriteInt("Camera", "CustomZoomTownAmount", sSettingsData.iZoomTownLevel);
	}

	//Audio
	{
		cReader.WriteBool( "Audio", "NoEffects", sSettingsData.bNoSoundEffects );
		cReader.WriteBool( "Audio", "NoMusic", sSettingsData.bNoMusic );
		cReader.WriteInt( "Audio", "MusicVolume", sSettingsData.iMusicVolume );
		cReader.WriteInt( "Audio", "EffectVolume", sSettingsData.iEffectVolume );
	}

	//Game
	{
		STRINGCOPY( sSettingsData.szLastAccount, (char*)0x039033E8 );
		cReader.WriteString( "Game", "LastAccount", sSettingsData.szLastAccount );

		//Copy Macros
		char szMacro[ 16 ] = { 0 };
		for ( int i = 0; i < 10; i++ )
		{
			STRINGFORMAT( szMacro, "Macro%d", i+1 );
			STRINGCOPYLEN( (char*)(0x00CDC144 + (i * 100)), 100, sSettingsData.szaMacro[ i ] );
			cReader.WriteString( "Game", szMacro, sSettingsData.szaMacro[ i ] );
		}

		// Setttings
		cReader.WriteBool( "Game", "NoWhisper", sSettingsData.bNoWhisper );
		cReader.WriteBool( "Game", "NoTradeChat", sSettingsData.bNoTradeChat );
		cReader.WriteBool( "Game", "NoPartyRequest", sSettingsData.bNoPartyRequest );
		cReader.WriteBool( "Game", "NoTradeRequest", sSettingsData.bNoTradeRequest );

		//Loot
		cReader.WriteBool( "Game", "EnableLootFilter", sSettingsData.bEnableLootFilter );
		cReader.WriteInt( "Game", "LootFilterFlagsV2", sSettingsData.iLootFilterFlags);
		cReader.WriteInt( "Game", "LootFilterSpecFlags", sSettingsData.iLootFilterSpecFlags );
	}

	//Skills
	{
#ifdef ENCHANTWEAPON_SETTING
		cReader.WriteInt( "Skills", "EnchantWeaponPerference", (int)sSettingsData.bWeaponEnchantPerference );
#endif
	}

	//Personalization
	{
		cReader.WriteBool( "Personalization", "DebugDamage", sSettingsData.bDebugDamage );
		cReader.WriteBool( "Personalization", "HideHPBarOnTarget", !sSettingsData.bHPBarOnTarget );
		cReader.WriteBool( "Personalization", "ShowHPBarOnSelf", sSettingsData.bHPBarOnSelf );
		cReader.WriteBool( "Personalization", "FPS", sSettingsData.bFPS );
		cReader.WriteBool( "Personalization", "Ping", sSettingsData.bPing );
		cReader.WriteBool( "Personalization", "KillInfo", sSettingsData.bDebugKill );
		cReader.WriteBool( "Personalization", "ItemViewTogglableA", sSettingsData.bItemViewTogglableA);
		cReader.WriteBool( "Personalization", "PetModePassive", !sSettingsData.bDefaultPetModeAggressive);
		cReader.WriteBool( "Personalization", "ChatBoxKeepFocusOnEnter", !sSettingsData.bChatBoxRemoveFocusOnEnter);
		cReader.WriteBool( "Personalization", "AutoSelectNearestTarget", sSettingsData.bAutoSelectNearestTargetForAoE);
		cReader.WriteInt(  "Personalization",  "LootFilterEquipmentMinLevel", sSettingsData.iMinEquipmentLevelReq);
		cReader.WriteBool(  "Personalization",  "EnableEquipmentMinLevelFilter", sSettingsData.bEnableEquipmentMinLevelFilter);
	}

	//User Interface
	{
		cReader.WriteBool( "UI", "Lock", sSettingsData.bLockUI );
	//	cReader.WriteBool( "UI", "SaveChanges", sSettingsData.bSaveUI );
		cReader.WriteBool( "UI", "ShowPartyMembers", sSettingsData.bShowPartyMembers );
		cReader.WriteBool( "UI", "ShowRaidMembers", sSettingsData.bShowRaidMembers );
		cReader.WriteBool( "UI", "ShowClanMembers", sSettingsData.bShowClanMembers );
		cReader.WriteBool( "UI", "ShowEnemies", sSettingsData.bShowEnemies );
		cReader.WriteBool( "UI", "ShowNPCS", sSettingsData.bShowNPCs );
		//cReader.WriteBool( "UI", "MinimapAlwaysActive", sSettingsData.bMinimapAlwaysActive );
		cReader.WriteBool( "UI", "ShowNextBossTimer", sSettingsData.bShowNextBossTimer );
		cReader.WriteBool("UI", "ShowNameAboveHead", sSettingsData.bShowNameAboveHead);
		cReader.WriteBool("UI", "ShowFrameAboveHead", sSettingsData.bShowFrameAboveHead);
		cReader.WriteBool( "UI", "ShowNotice", sSettingsData.bShowNotice );
		cReader.WriteBool( "UI", "TargetDistance", sSettingsData.bTargetDistance );
		cReader.WriteBool( "UI", "TargetHPValue", sSettingsData.bTargetHPValue );
		cReader.WriteBool( "UI", "TargetHPPercent", sSettingsData.bTargetHPPercent );
	}
}

BOOL CSettingsModel::CanViewLoot( ELootFilter e )
{
	return ((GetSettings().iLootFilterFlags & e) == e);
}

void CSettingsModel::ResetViewLoot()
{
	GetSettings().iLootFilterFlags = LOOTFILTER_None;
}

void CSettingsModel::RemoveViewLoot( ELootFilter e )
{
	if ( CanViewLoot( e ) )
		GetSettings().iLootFilterFlags -= e;
}

void CSettingsModel::AddViewLoot( ELootFilter e )
{
	if ( CanViewLoot( e ) == FALSE )
		GetSettings().iLootFilterFlags |= e;
}

void CSettingsModel::SetViewLoot( ELootFilter e, BOOL b )
{
	if ( b )
		AddViewLoot( e );
	else
		RemoveViewLoot( e );
}

BOOL CSettingsModel::CanViewLootSpec( ELootFilterSpec e )
{
	return ((GetSettings().iLootFilterSpecFlags & e) == e);
}

void CSettingsModel::RemoveViewLootSpec( ELootFilterSpec e )
{
	if ( CanViewLootSpec( e ) )
		GetSettings().iLootFilterSpecFlags -= e;
}

void CSettingsModel::AddViewLootSpec( ELootFilterSpec e )
{
	if ( CanViewLootSpec( e ) == FALSE )
		GetSettings().iLootFilterSpecFlags |= e;
}

void CSettingsModel::SetViewLootSpec( ELootFilterSpec e, BOOL b )
{
	if ( b )
		AddViewLootSpec( e );
	else
		RemoveViewLootSpec( e );
}

BOOL CSettingsModel::HaveViewLootSpec()
{
	return (GetSettings().iLootFilterSpecFlags > 0);
}


void CSettingsModel::OnCheckWindowState()
{

	// Get Window State
	WINDOWPLACEMENT wc;
	DWORD dwWidth = GetSystemMetrics( SM_CXSCREEN );
	DWORD dwHeight = GetSystemMetrics( SM_CYSCREEN );

	GetWindowPlacement( DX::Graphic::GetWindowHandler(), &wc );

	BOOL bAdjust = SETTINGSHANDLER->GetModel()->GetSettings().bAutoAdjust;

	// If window is maximizing, adjust it, if normalizing, reset.
	if ( (wc.showCmd == SW_MAXIMIZE) && !bMaximizedWindow && SETTINGSHANDLER->GetModel()->GetSettings().bWindowed )
	{
		if ( bAdjust )
		{
			RECT rc;
			rc.left = 0;
			rc.top = 0;
			rc.right = SETTINGSHANDLER->GetModel()->GetOldSettings().dwWidth;
			rc.bottom = SETTINGSHANDLER->GetModel()->GetOldSettings().dwHeight;
			GetWindowRect( DX::Graphic::GetWindowHandler(), &rc );

			UINT uWindowStyle = GetWindowLongA( DX::Graphic::GetWindowHandler(), GWL_STYLE );

			// Adjust Window
			AdjustWindowRect( &rc, uWindowStyle, FALSE );
			dwHeight = ( rc.bottom + rc.top );


			GRAPHICENGINE->ResolutionChange( FALSE, dwWidth, dwHeight );

			GRAPHICENGINE->Reset( SETTINGSHANDLER->GetModel()->GetSettings().bWindowed, dwWidth, dwHeight, TRUE );
			bMaximizedWindow = TRUE;
		}
	}
	else if ( wc.showCmd != SW_MAXIMIZE && wc.showCmd != SW_MINIMIZE && bMaximizedWindow && SETTINGSHANDLER->GetModel()->GetSettings().bWindowed )
	{
		if ( bAdjust )
		{
			GRAPHICENGINE->ResolutionChange( FALSE, SETTINGSHANDLER->GetModel()->GetOldSettings().dwWidth, SETTINGSHANDLER->GetModel()->GetOldSettings().dwHeight );

			GRAPHICENGINE->Reset( SETTINGSHANDLER->GetModel()->GetSettings().bWindowed, SETTINGSHANDLER->GetModel()->GetOldSettings().dwWidth, SETTINGSHANDLER->GetModel()->GetOldSettings().dwHeight, TRUE );
			bMaximizedWindow = FALSE;
		}
	}
}

void CSettingsModel::ProcessGeneralSettings( BOOL bRead, BOOL bInitial )
{
	PacketSettingsData sPacket;
	sPacket.iLength			= sizeof( PacketSettingsData );
	sPacket.iHeader			= PKTHDR_SettingsData;

	sPacket.bInital			= bInitial;
	sPacket.bNoWhisper		= GetSettings().bNoWhisper;
	sPacket.bNoTradeChat	= GetSettings().bNoTradeChat;
	sPacket.bNoTradeRequest = GetSettings().bNoTradeRequest;
	sPacket.bNoPartyRequest = GetSettings().bNoPartyRequest;

#ifdef ENCHANTWEAPON_SETTING
	sPacket.bWeaponEnchantPerference = GetSettings().bWeaponEnchantPerference;
#endif

	if ( bRead )
	{
		FILE * pFile = NULL;
		fopen_s( &pFile, "savedata\\settings.dat", "rb" );
		if ( pFile )
		{
			fread( &sPacket, sizeof( PacketSettingsData ), 1, pFile );
			fclose( pFile );
		}
	}
	else
	{
		FILE * pFile = NULL;
		fopen_s( &pFile, "savedata\\settings.dat", "wb" );
		if ( pFile )
		{
			fwrite( &sPacket, sizeof( PacketSettingsData ), 1, pFile );
			fclose( pFile );
		}
	}

	if (SOCKETL)
		SENDPACKETL( &sPacket, TRUE );

	if (SOCKETG)
		SENDPACKETG( &sPacket, TRUE );

	extern bool						bNoShowDebugDamage;
	extern BOOL						bShowFps;

	bNoShowDebugDamage = GetSettings().bDebugDamage ? FALSE : TRUE;
	bShowFps = GetSettings().bFPS;

	WRITEDWORD( 0x04B0D9F0, GetSettings().bHPBarOnTarget );
}
