#pragma once

#include "party.h"

#include "CPartyWindow.h"

#define PARTYWINDOW					(PARTYHANDLER->GetPartyWindow())

class CPartyHandler
{
public:
	//Constructor
									CPartyHandler();
								   ~CPartyHandler();

	//Handle Packets
	void							HandlePacket( PacketUpdateParty * psPacket );
	void							HandlePacket( PacketRequestParty * psPacket );
	void							HandlePacket( PacketUpdatePartyData * psPacket );
	void							HandlePacket( PacketRequestRaid * psPacket );

	void							ProcessPacket( PacketJoinParty  * psPacket );
	void							ProcessPacket( PacketJoinRaid * psPacket );
	void							ProcessPacket( PacketRequestParty  * psPacket );
	void							ProcessPacket( PacketRequestRaid  * psPacket );
	void							ProcessPacket( PacketActionParty * psPacket );

	//Getters and Setters
	CPartyData						GetPartyData(){ return sPartyData; }
	CPartyWindow				  * GetPartyWindow(){ return pcPartyWindow; }

	void							Init();
	void							Render();

	void							Update( float fTime );

	void							OnMouseMove( class CMouse * pcMouse );
	BOOL							OnMouseClick( class CMouse * pcMouse );

	void							AcceptPartyRequest();
	void							JoinPartyRequest();
	void							JoinRaidRequest();

	BOOL							IsPartyMember( int iID );
	BOOL							IsRaidMember( int iID );

	std::vector<UnitData*>			GetPartyMembers( bool bRaid = true );
private:
	CPartyWindow				  * pcPartyWindow;
	CPartyData						sPartyData;

	PacketRequestParty			    sPacketRequestParty;
	PacketRequestRaid				sPacketRequestRaid;

	void							UpdateSafeMembers( BOOL bSafe );
};

