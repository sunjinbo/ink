/* ====================================================================
 * File: InkdotData.h
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef T_INKDOTDATA_H
#define T_INKDOTDATA_H

// INCLUDE FILES
#include <e32std.h>
#include <s32strm.h>
#include "Inkdot.hrh"

// CLASS DECLARATION
/**
* TInkdotData class
*
* @since S60 5.0
*/
class TInkdotData
    {
public:
    enum TUninitialized { EUninitialized = -1 };
    inline TInkdotData();
    inline TInkdotData( TInkdotType aType );
    inline TInkdotData( TInkdotType aType, TInt aX, TInt aY );
    inline TInkdotData( TInkdotType aType, const TPoint& aPos );
    inline TInkdotData( const TInkdotData& aInkdotData );
    inline TBool operator == ( const TInkdotData& aInkdotData ) const;
    inline TBool operator != ( const TInkdotData& aInkdotData ) const;
    inline void SetXY( TInt aX, TInt aY );
    inline void SetXY( const TPoint& aPos );
    inline void SetRadius( TInt aRadius );
    inline void SetType( TInkdotType aType );
    inline void SetSplash();
    inline TInkdotType Type() const;
    inline TPoint Position() const;
    inline TInt Radius() const;
    inline TBool IsSplash() const;
    inline void Reverse();
    inline void InternalizeL( RReadStream& aRStream );
    inline void ExternalizeL( RWriteStream& aWStream ) const;

private: // Member data
    /**
    The aquatic type
    */
    TInkdotType iType;

    /**
    The x,y co-ordinate.
    */
    TPoint iPos;

    /**
    The radius of inkdot.
    */
    TInt iRadius;

    /**
    To specify if inkdot was splash or not.
    */
    TBool iSplash;

    };
#include "InkdotData.inl"

#endif // T_INKDOTDATA_H

// End of file
