#pragma once
class DXLogger
{
protected:
	std::string									strLogFile;
public:
	DXLogger();
	virtual ~DXLogger();

	void										Print( const char * pszFormat );

	const char *								ResultToString( HRESULT hr );
};

