#pragma once

struct ManufactureRune
{
	int RecipeCode;
	int NeedRuneIndex[3];
};


class CManufactureHandler
{

public:
	CManufactureHandler();
	virtual ~CManufactureHandler();

	void												SetManufactureAreaCheck( class ItemData * pcItem );

	BOOL												OnClickItemSlotPut( class ItemData * pcItem );

	void												SetManufacture();

	void												Update();

private:
	BOOL												IsRecipe( EItemID eID );

	BOOL												CanRespec( EItemID eID );

	BOOL												IsRespecStone( EItemID eID );

	BOOL												IsRune( EItemID eID );

	BOOL												IsValidRuneTullaAmulet( EItemID eID );
	BOOL												IsValidRuneAbyssRing( EItemID eID );


};

