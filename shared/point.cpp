#include "stdafx.h"
#include "point.h"

bool Point2D::Inside(const Rectangle2D* psRectangle2D) const
{
	return (this->iX >= psRectangle2D->iX && this->iX < (psRectangle2D->iX + psRectangle2D->iWidth)) &&
		(this->iY >= psRectangle2D->iY && this->iY < (psRectangle2D->iY + psRectangle2D->iHeight));
}

bool Point2D::Equals(const Point2D* psPoint2D) const
{
	return this->iX == psPoint2D->iX && this->iY == psPoint2D->iY;
}

Point2D Point2D::operator<<(int shift)
{
	Point2D shiftedPoint;
	shiftedPoint.iX = iX << shift;
	shiftedPoint.iY = iY << shift;

	return shiftedPoint;
}

Point2D Point2D::operator>>(int shift)
{
	Point2D shiftedPoint;
	shiftedPoint.iX = iX >> shift;
	shiftedPoint.iY = iY >> shift;

	return shiftedPoint;
}

int Point3D::GetPTDistance( const Point3D & sCompare ) const
{
	int iXD = (sCompare.iX - iX) >> 8;
	int iZD = (sCompare.iZ - iZ) >> 8;
	int iYD = (sCompare.iY - iY) >> 8;

	iXD *= iXD;
	iZD *= iZD;
	iYD *= iYD;

	return (iXD + iZD + iYD);
}

int Point3D::GetPTDistanceXZ( const Point3D * psCompare, int & xz, int & x, int & z ) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;

	xz = (iXDM + iZDM);
	x = abs( iXD );
	z = abs( iZD );

	return xz;
}

int Point3D::GetPTDistanceXZ(const Point3D* psCompare) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;

	int iXZDM = (iXDM + iZDM);

	if (iXZDM < 0)
		iXZDM = 0;

	return iXZDM;
}


int Point3D::GetPTDistanceXZY( const Point3D * psCompare, int & xzy, int & xz, int & x, int & z, int & y ) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;
	int iYD = (psCompare->iY - iY) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;
	int iYDM = iYD * iYD;

	xz =  (iXDM + iZDM);
	xzy = (iXDM + iZDM + iYDM);
	x = abs( iXD );
	z = abs( iZD );
	y = abs( iYD );

	return xzy;
}

int Point3D::GetPTDistanceXZ_Y( const Point3D * psCompare, int & xz, int & y ) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;
	int iYD = (psCompare->iY - iY) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;
	int iYDM = iYD * iYD;

	xz =  (iXDM + iZDM);
	y = abs( iYD );

	return xz;
}

BOOL Point3D::WithinXZYDistance(const Point3D* psCompare, int iDistanceXZY ) const
{
	int iDistXZY, iDistXZ, iDistX, iDistZ, iDistY;
	GetPTDistanceXZY(psCompare, iDistXZY, iDistXZ, iDistX, iDistZ, iDistY);

	return iDistXZY < (iDistanceXZY) && iDistX < DISTANCE_MISC && iDistZ < DISTANCE_MISC && iDistY < DISTANCE_MISC_Y;
}

BOOL Point3D::WithinXZYDistance ( const Point3D * psCompare, int iDistanceXZ, int iDistanceY ) const
{
	int iDistXZY, iDistXZ, iDistX, iDistZ, iDistY;
	GetPTDistanceXZY ( psCompare, iDistXZY, iDistXZ, iDistX, iDistZ, iDistY );

	return iDistXZY < ( iDistanceXZ ) && iDistY < iDistanceY;
}


BOOL Point3D::WithinXZDistance( const Point3D * psCompare, int iDistanceXZ, int iDistanceY ) const
{
	int iDistXZY, iDistXZ, iDistX, iDistZ, iDistY;
	GetPTDistanceXZY( psCompare, iDistXZY, iDistXZ, iDistX, iDistZ, iDistY);

	return iDistXZ < (iDistanceXZ) && iDistX < DISTANCE_MISC && iDistZ < DISTANCE_MISC && iDistY < iDistanceY;
}


int Point3D::GetLength() const
{
	return (int)sqrt((iX * iX) + (iY * iY) + (iZ * iZ));
}

Point3D Point3D::GetNormal( Point3D v1 )
{
	const Point3D & v0 = *this;

	Point3D s;

	//Cross product
	s.iX = (v0.iY * v1.iZ) - (v0.iZ * v1.iY);
	s.iY = (v0.iZ * v1.iX) - (v0.iX * v1.iZ);
	s.iZ = (v0.iX * v1.iY) - (v0.iY * v1.iX);

	//Dot
	int i = s.GetLength();
	i += (i == 0 ? 1 : 0);


	//Normalize
	s.iX /= i;
	s.iY /= i;
	s.iZ /= i;

	return s;
}

void Point3D::operator=( const Point3D & sOther )
{
	this->iX	= sOther.iX;
	this->iY	= sOther.iY;
	this->iZ	= sOther.iZ;
}

Point3D Point3D::operator<<( int i ) const
{
	Point3D s;
	s.iX = iX << i;
	s.iY = iY << i;
	s.iZ = iZ << i;

	return s;
}

Point3D Point3D::operator>>( int i ) const
{
	Point3D s;
	s.iX = iX >> i;
	s.iY = iY >> i;
	s.iZ = iZ >> i;

	return s;
}

void Point3D::operator<<=( int i )
{
	iX <<= i;
	iY <<= i;
	iZ <<= i;
}

void Point3D::operator>>=( int i )
{
	iX >>= i;
	iY >>= i;
	iZ >>= i;
}

bool Point3D::operator==( const Point3D & sOther ) const
{
	if( this->iX == sOther.iX )
		if( this->iY == sOther.iY )
			if( this->iZ == sOther.iZ )
				return true;

	return false;
}

bool Point3D::operator!=( const Point3D & sOther ) const
{
	return !(*this == sOther);
}

void Point3D::operator+=( const Point3D & sOther )
{
	this->iX += sOther.iX;
	this->iY += sOther.iY;
	this->iZ += sOther.iZ;
}

void Point3D::operator-=( const Point3D & sOther )
{
	this->iX -= sOther.iX;
	this->iY -= sOther.iY;
	this->iZ -= sOther.iZ;
}

Point3D Point3D::operator-( const Point3D & sOther ) const
{
	Point3D sReturn = *this;
	sReturn -= sOther;
	return sReturn;
}

Point3D Point3D::operator+( const Point3D & sOther ) const
{
	Point3D sReturn = *this;
	sReturn += sOther;
	return sReturn;
}

bool Rectangle2D::Inside( const Point2D * psPosition, int iLowX, int iLowY ) const
{
	if( ((psPosition->iX - iLowX) >= iX) && ((psPosition->iX - iLowX) < (iX + iWidth)) )
		if( ((psPosition->iY - iLowY) >= iY) && ((psPosition->iY - iLowY) < (iY + iHeight)) )
			return true;

	return false;
}

bool Rectangle2D::Equals( const Rectangle2D * psRectangle2D ) const
{
	if( (iX == psRectangle2D->iX) && (iY == psRectangle2D->iY) )
		if( (iWidth == psRectangle2D->iWidth) && (iHeight == psRectangle2D->iHeight) )
			return true;

	return false;
}

void Rectangle2D::CopyFrom( const Rectangle2D * psRectangle2D )
{
	iX = psRectangle2D->iX;
	iY = psRectangle2D->iY;
	iWidth = psRectangle2D->iWidth;
	iHeight = psRectangle2D->iHeight;
}

bool Rectangle2D::Overlaps( const Rectangle2D * psRectangle2D ) const
{
	int iX11 = iX;
	int iX12 = iX + iWidth;
	int iY11 = iY;
	int iY12 = iY + iHeight;
	int iX21 = psRectangle2D->iX;
	int iX22 = psRectangle2D->iX + psRectangle2D->iWidth;
	int iY21 = psRectangle2D->iY;
	int iY22 = psRectangle2D->iY + psRectangle2D->iHeight;

    bool noOverlap = iX11 >= iX22 ||
                     iX21 >= iX12 ||
                     iY11 >= iY22 ||
                     iY21 >= iY12;

	return !noOverlap;
}

bool Rectangle2D::Contains( const Rectangle2D * psRectangle2D ) const
{
	if( (psRectangle2D->iX >= iX) && (psRectangle2D->iX + psRectangle2D->iWidth) <= (iX + iWidth) )
		if( (psRectangle2D->iY >= iY) && (psRectangle2D->iY + psRectangle2D->iHeight) <= (iY + iHeight) )
			return true;

	return false;
}

Rectangle2D Rectangle2D::operator+( const Rectangle2D & sOther ) const
{
	Rectangle2D sReturn;

	sReturn.iX			= iX + sOther.iX;
	sReturn.iY			= iY + sOther.iY;
	sReturn.iWidth		= high( iWidth, sOther.iWidth );
	sReturn.iHeight		= high( iHeight, sOther.iHeight );

	return sReturn;
}

Rectangle2D & Rectangle2D::operator+=( const Rectangle2D & sOther )
{
	iX			+= sOther.iX;
	iY			+= sOther.iY;
	iWidth		+= sOther.iWidth;
	iHeight		+= sOther.iHeight;

	return *this;
}

bool Rectangle3D::Inside( const Point3D * psPosition ) const
{
	if( (psPosition->iX >= iX) && (psPosition->iX < (iX + iWidth)) )
		if( (psPosition->iY >= iY) && (psPosition->iY < (iY + iHeight)) )
			if( (psPosition->iZ >= iZ) && (psPosition->iZ < (iZ + iDepth)) )
				return true;

	return false;
}

float Vector4DF::Dot( const Vector4DF & c ) const
{
	float fReturn = fX * c.fX;
	fReturn += fY * c.fY;
	fReturn += fZ * c.fZ;
	fReturn += fW * c.fW;

	return fReturn;
}

void Vector4DF::Normalize()
{
	float f = (float)sqrt( (fX * fX) + (fY * fY) + (fZ * fZ) + (fW * fW) );

	float inverse = 1.0f / f;

	if ( inverse != 0.0f )
	{
		fX *= inverse;
		fY *= inverse;
		fZ *= inverse;
		fW *= inverse;
	}
}

void Vector4DF::Scale( float f )
{
	fX *= f;
	fY *= f;
	fZ *= f;
	fW *= f;
}

void Vector4DF::Negative()
{
	fX = -fX;
	fY = -fY;
	fZ = -fZ;
	fW = -fW;
}

Vector4DF Vector4DF::operator-( const Vector4DF & c ) const
{
	Vector4DF s;

	s.fX = fX - c.fX;
	s.fY = fY - c.fY;
	s.fZ = fZ - c.fZ;
	s.fW = fW - c.fW;

	return s;
}

Vector4DF Vector4DF::operator+( const Vector4DF & c ) const
{
	Vector4DF s;

	s.fX = fX + c.fX;
	s.fY = fY + c.fY;
	s.fZ = fZ + c.fZ;
	s.fW = fW + c.fW;

	return s;
}

void Vector4DF::operator=( const Vector4DF & c )
{
	this->fX = c.fX;
	this->fY = c.fY;
	this->fZ = c.fZ;
	this->fW = c.fW;
}

Vector4DF Vector4DF::operator*( const float c ) const
{
	Vector4DF s;

	s.fX = fX * c;
	s.fY = fY * c;
	s.fZ = fZ * c;
	s.fW = fW * c;

	return s;
}
