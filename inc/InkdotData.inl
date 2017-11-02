/* ====================================================================
 * File: InkdotData.inl
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TInkdotData::TInkdotData
// ----------------------------------------------------------------------------
//
TInkdotData::TInkdotData()  : iType( EInkdotNull ),
    iPos( EUninitialized, EUninitialized ), iSplash( EFalse )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// TInkdotData::TInkdotData
// ----------------------------------------------------------------------------
//
inline TInkdotData::TInkdotData( TInkdotType aType )
    : iType( aType ),
    iPos( EUninitialized, EUninitialized ),
    iSplash( EFalse )
    { // no implementation required 
    }

// ----------------------------------------------------------------------------
// TInkdotData::TInkdotData
// ----------------------------------------------------------------------------
//
inline TInkdotData::TInkdotData( TInkdotType aType, TInt aX, TInt aY )
    : iType( aType ), iPos( aX, aY ), iSplash( EFalse )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TInkdotData::TInkdotData
// ----------------------------------------------------------------------------
//
inline TInkdotData::TInkdotData( TInkdotType aType, const TPoint& aPos )
    : iType( aType ), iPos( aPos ), iSplash( EFalse )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TInkdotData::TInkdotData
// ----------------------------------------------------------------------------
//
inline TInkdotData::TInkdotData( const TInkdotData& aInkdotData )
    : iType( aInkdotData.Type() ),
    iPos( aInkdotData.Position() ),
    iRadius( aInkdotData.Radius() ),
    iSplash( aInkdotData.IsSplash() )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TInkdotData::operator==
// ----------------------------------------------------------------------------
//
inline TBool TInkdotData::operator==( const TInkdotData& aInkdotData ) const
    {
    TBool retVal( EFalse );
    if ( ( aInkdotData.Type() == iType )
        && ( aInkdotData.Position() == iPos )
        && ( aInkdotData.IsSplash() == iSplash ) )
        {
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// TInkdotData::operator!=
// ----------------------------------------------------------------------------
//
inline TBool TInkdotData::operator!=( const TInkdotData& aInkdotData ) const
    {
    return ( *this == aInkdotData ) ? ETrue : EFalse ;
    }

// ----------------------------------------------------------------------------
// TInkdotData::SetXY
// ----------------------------------------------------------------------------
//
inline void TInkdotData::SetXY( TInt aX, TInt aY )
    {
    iPos.SetXY( aX, aY );
    }

// ----------------------------------------------------------------------------
// TInkdotData::SetXY
// ----------------------------------------------------------------------------
//
inline void TInkdotData::SetXY( const TPoint& aPos )
    {
    iPos = aPos;
    }

// ----------------------------------------------------------------------------
// TInkdotData::SetXY
// ----------------------------------------------------------------------------
//
void TInkdotData::SetRadius( TInt aRadius )
    {
    iRadius = aRadius;
    }

// ----------------------------------------------------------------------------
// TInkdotData::SetType
// ----------------------------------------------------------------------------
//
inline void TInkdotData::SetType( TInkdotType aType )
    {
    iType = aType;
    }

// ----------------------------------------------------------------------------
// TInkdotData::SetType
// ----------------------------------------------------------------------------
//
void TInkdotData::SetSplash()
    {
    iSplash = ETrue;
    }

// ----------------------------------------------------------------------------
// TInkdotData::Type
// ----------------------------------------------------------------------------
//
inline TInkdotType TInkdotData::Type() const
    {
    return iType;
    }

// ----------------------------------------------------------------------------
// TInkdotData::Position
// ----------------------------------------------------------------------------
//
inline TPoint TInkdotData::Position() const
    {
    return iPos;
    }

// ----------------------------------------------------------------------------
// TInkdotData::Position
// ----------------------------------------------------------------------------
//
TBool TInkdotData::IsSplash() const
    {
    return iSplash;
    }

// ----------------------------------------------------------------------------
// TInkdotData::Radius
// ----------------------------------------------------------------------------
//
TInt TInkdotData::Radius() const
    {
    return iRadius;
    }

// ----------------------------------------------------------------------------
// TInkdotData::Reverse
// ----------------------------------------------------------------------------
//
void TInkdotData::Reverse()
    {
    TInt temp = iPos.iX;
    iPos.iX = iPos.iY;
    iPos.iY = temp;
    }

// ----------------------------------------------------------------------------
// TInkdotData::InternalizeL
// ----------------------------------------------------------------------------
//
void TInkdotData::InternalizeL( RReadStream& aRStream )
    {
    iType = static_cast<TInkdotType>( aRStream.ReadInt8L() );
    iSplash = static_cast<TBool>( aRStream.ReadInt8L() );
    iPos.iX = static_cast<TInt>( aRStream.ReadInt32L() );
    iPos.iY = static_cast<TInt>( aRStream.ReadInt32L() );
    iRadius = static_cast<TInt>( aRStream.ReadInt32L() );
    }

// ----------------------------------------------------------------------------
// TInkdotData::ExternalizeL
// ----------------------------------------------------------------------------
//
void TInkdotData::ExternalizeL( RWriteStream& aWStream ) const
    {
    aWStream.WriteInt8L( iType );
    aWStream.WriteInt8L( iSplash );
    aWStream.WriteInt32L( iPos.iX );
    aWStream.WriteInt32L( iPos.iY );
    aWStream.WriteInt32L( iRadius );
    }

// End of file
