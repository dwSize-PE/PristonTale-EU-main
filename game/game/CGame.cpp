#include "stdafx.h"
#include "CGame.h"

extern BOOL bLootLabelViewToggleState;

CGame::CGame()
{
	pcGameEngine	= new CGameEngine();
	pcGameCore		= new GameCore();
	pcGameScreen	= new CGameScreen();
	pcGameTimer		= new CGameTimer();
	pcGameWorld		= new CGameWorld();
}

CGame::~CGame()
{
	SAFE_DELETE( pcGameEngine );
	SAFE_DELETE( pcGameCore );
	SAFE_DELETE( pcGameScreen );
	SAFE_DELETE( pcGameTimer );
	SAFE_DELETE( pcGameWorld );
}

BOOL CGame::Init()
{
	pcGameEngine->Init();
	pcGameCore->Init();
	pcGameScreen->Init();
	pcGameTimer->Init();
	pcGameWorld->Init();
	return TRUE;
}

void CGame::Shutdown()
{
	pcGameEngine->Shutdown();
	pcGameCore->Shutdown();
	pcGameScreen->Shutdown();
	pcGameTimer->Shutdown();
	pcGameWorld->Shutdown();
}

void CGame::Begin() //  Login of characters - Chaos
{


	GameCore::SetGameScreen( SCREEN_Login );

	CALL( 0x005058F0 );



	//ShowCursor( FALSE );
}

void CGame::End()
{
}

void CGame::Frame()
{
	pcGameScreen->Frame();

	pcGameCore->Frame();

	pcGameEngine->Frame();
}

void CGame::Update( float fTime )
{
	pcGameScreen->Update( fTime );

	pcGameCore->Update( fTime );

	pcGameEngine->Update( fTime );
}

void CGame::Render3D()
{
	pcGameScreen->Render3D();

	pcGameCore->Render3D();

	pcGameEngine->Render3D();
}

void CGame::Render2D()
{
	if( Game::GetGameMode() != GAMEMODE_InGame )
		GAMESCREEN->Render2D();

	pcGameCore->Render2D();
	pcGameEngine->Render2D();
}

BOOL CGame::OnKeyPress( CKeyboard * pcKeyboard )
{
	if( pcGameScreen->OnKeyPress( pcKeyboard ) )
		return TRUE;

	if ( pcGameCore->OnKeyPress( pcKeyboard ) )
		return TRUE;

	if (pcKeyboard->GetEvent() == EKeyboardEvent::KeyUp && tolower(pcKeyboard->GetKey()) == CHAR('a'))
	{
		if (UNITGAME && CHARACTERGAME && !CHARACTERGAME->IsStageVillage() && SETTINGSHANDLER->GetModel()->GetSettings().bItemViewTogglableA)
		{
			bLootLabelViewToggleState = !bLootLabelViewToggleState;

			if (bLootLabelViewToggleState)
				CHATBOX->AddMessage("Loot View Toggle: ON", CHATCOLOR_Notice);
			else
				CHATBOX->AddMessage("Loot View Toggle: OFF", CHATCOLOR_Notice);
		}
	}

	return FALSE;
}

BOOL CGame::OnKeyChar( CKeyboard * pcKeyboard )
{
	if( pcGameScreen->OnKeyChar( pcKeyboard ) )
		return TRUE;

	if ( pcGameCore->OnKeyChar( pcKeyboard ) )
		return TRUE;

	return FALSE;
}

void CGame::OnMouseMove( CMouse * pcMouse )
{
	pcGameCore->OnMouseMove( pcMouse );
	pcGameScreen->OnMouseMove( pcMouse );
}

BOOL CGame::OnMouseClick( CMouse * pcMouse )
{
	if( pcGameCore->OnMouseClick( pcMouse ) )
		return TRUE;

	if( pcGameScreen->OnMouseClick( pcMouse ) )
		return TRUE;

	return FALSE;
}

BOOL CGame::OnMouseScroll( CMouse * pcMouse )
{
	if( pcGameCore->OnMouseScroll( pcMouse ) )
		return TRUE;

	if( pcGameScreen->OnMouseScroll( pcMouse ) )
		return TRUE;

	return FALSE;
}

void CGame::OnResolutionChanged()
{
	pcGameScreen->OnResolutionChanged();
}


