#include "stdafx.h"
#include "CWorld.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

CWorld::CWorld( EWorldID _iWorldID, string _strName, unsigned long _lIP, USHORT _uPort, string _strGameName, string _strShortGameName, string _strWebsite, unsigned long _lIP2, unsigned long _lIP3 )
{
	iWorldID			= _iWorldID;
	strName				= _strName;
	lIP					= _lIP;
	uPort				= _uPort;

	strGameName			= _strGameName;
	strShortGameName	= _strShortGameName;
	strWebsite			= _strWebsite;

	lIP2				= _lIP2;
	lIP3				= _lIP3;

	char szIP[32];
	//IP longs to Strings
	STRINGCOPY( szIP, inet_ntoa( (*((in_addr*)&lIP)) ) );
	strIP				= szIP;

	STRINGCOPY( szIP, inet_ntoa( (*((in_addr*)&lIP2)) ) );
	strIP2				= szIP;

	STRINGCOPY( szIP, inet_ntoa( (*((in_addr*)&lIP3)) ) );
	strIP3				= szIP;
}

CWorld::~CWorld()
{
}

void CWorld::SetIP( unsigned long _lIP )
{
	lIP			= _lIP;

	char szIP[32];
	//IP long to Strings
	STRINGCOPY( szIP, inet_ntoa( (*((in_addr*)&lIP)) ) );
	strIP		= szIP;
}