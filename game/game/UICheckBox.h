#pragma once

namespace UI
{
typedef std::shared_ptr<class CheckBox> CheckBox_ptr;
class CheckBox : public Element
{
public:
	//Constructor
											CheckBox(Rectangle2D rRectangle);
	virtual								   ~CheckBox();
private:
	std::string								strText;
	int										iEventID		= -1;
	int										iFontHandler	= -1;
	class Image								* pImage		= NULL;
	class Image								* pImage2		= NULL;
	int										iFontHeight		= 0;
	BOOL									bHover			= FALSE;
	BOOL									bDisable		= FALSE;
	BOOL									bSelect			= FALSE;
	BOOL									bSelectType		= FALSE;
	BOOL									bParentChild	= TRUE;
	std::shared_ptr<class Group>			pGroupMain		= NULL;
	DWORD									dwColorText		= -1;
	DWORD									dwDisableColorText	= D3DCOLOR_ARGB(255, 120, 120, 120);

public:

	void									Clear();

	//Getters and Setters
	void									SetFont( const char * pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor );
	void									SetText( std::string str ) { strText = str; };
	void									SetDisableTextColor( Color c ) { dwDisableColorText = c.Get(); }
	void									SetGroup( std::shared_ptr<class Group> pGroup ) { pGroupMain = pGroup; };
	void									SetImage( class Image * pImage, class Image * pImage2 ) { this->pImage = pImage; this->pImage2 = pImage2; };
	void									SetEvent( int iEvent ) { iEventID = iEvent; };
	void									SetCheck( BOOL bCheck ) { bSelect = bCheck; };
	BOOL									IsChecked() { return bSelect; };

	void									SetEnabled(BOOL bEnabled) { bDisable = !bEnabled;  };
	void									SetVisible(BOOL bVisible) { bVisible ? Show() : Hide(); }

	//Render
	void									Render( int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY );

	//Event Handlers
	BOOL									OnMouseClick( class CMouse * pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY );
};
}