/* ====================================================================
 * File: Inkdot.cpp
 * Created: 03/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include <bitstd.h>
#include <gdi.h>
#include <AknUtils.h>
#include <fbs.h>
#include <barsread.h>
#include "Inkdot.h"
#include "Ink.pan"
#include "InkdotAssistor.h"
#include "Canvas.h"
#include "InkdotConstants.h"

// CONSTANS
const TInt KReverse = 2;
const TInt KMaxVector = 6;
const TInt KBufferLen = 8;
const TInt KTextBaseline = KMaxInkdotRadius + 6;
const TInt KDoMoveTimeout = 50000;
const TInt KDoSplashDelayTimeout = 50000;
const TInt KDoSplashTimeout = 50000;
const TInt KDoExpireDelayTimeout = 2000000;
const TInt KDoExpireTimeout = 200000;

_LIT( KPlusText, "+" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkdot::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CInkdot* CInkdot::NewL( CCanvas& aCanvas, const TInkdotData& aInkdotData )
    {
    CInkdot* self = new (ELeave) CInkdot( aCanvas, aInkdotData );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkdot::~CInkdot
// ----------------------------------------------------------------------------
//
CInkdot::~CInkdot()
    {
    // Cancels the wait for 
    // completion of an outstanding request.
    Cancel();

    Stop();
    }

// ----------------------------------------------------------------------------
// CInkdot::DoDraw
// ----------------------------------------------------------------------------
//
void CInkdot::DoDraw()
    {
    TRect theRect( ClientRect() );
    iCanvas.Gc().SetPenStyle( CGraphicsContext::ENullPen );
    iCanvas.Gc().SetBrushStyle( CGraphicsContext::ENullBrush );

    // Draw inkdot
    iCanvas.Gc().BitBltMasked(
        theRect.iTl,
        iCanvas.Assistor().Bitmap( iData.Type() ),
        TRect( TPoint( 0, 0 ), TSize( KMaxInkdotDiameter, KMaxInkdotDiameter ) ),
        iCanvas.Assistor().Mask( iData.Radius() ),
        ETrue
        );
 
    // Draw score
    if ( iData.IsSplash() && iData.Type() != ETouchInkdot )
        {
        iCanvas.Gc().UseFont( LatinBold13() );
        iCanvas.Gc().SetPenStyle( CGraphicsContext::ESolidPen );
        iCanvas.Gc().SetPenColor( KRgbBlack );
        iCanvas.Gc().SetBrushStyle( CGraphicsContext::ENullBrush );

        TBuf<KBufferLen> buf;
        buf.Append( KPlusText );
        buf.AppendNum( iScore );
        
        iCanvas.Gc().DrawText( 
                    buf, 
                    theRect, 
                    KTextBaseline, 
                    CGraphicsContext::ECenter, 
                    0 
                    );
        }

    }

// ----------------------------------------------------------------------------
// CInkdot::SetVector
// ----------------------------------------------------------------------------
//
void CInkdot::SetVector( TInt aVectorX, TInt aVectorY )
    {
    iVectorX = aVectorX;
    iVectorY = aVectorY;
    }

// ----------------------------------------------------------------------------
// CInkdot::IsSplash
// ----------------------------------------------------------------------------
//
TBool CInkdot::IsSplash() const
    {
    return ( iPeriodic && iPeriodic->IsActive() ) || iData.IsSplash();
    }

// ----------------------------------------------------------------------------
// CInkdot::Intersects
// ----------------------------------------------------------------------------
//
TBool CInkdot::Intersects( const CInkdot& aInkdot ) const
    {
    TInkdotData inkdotData( aInkdot.iData );
    TInt a = Abs( aInkdot.iData.Position().iX 
        - iData.Position().iX );
    TInt b = Abs( aInkdot.iData.Position().iY 
        - iData.Position().iY );
    TReal len( 0.0 );
    Math::Sqrt( len, a * a + b * b );
    if ( len <= aInkdot.iData.Radius() + iData.Radius() )
        {
        return ETrue;
        }
    return EFalse;
    }

// ----------------------------------------------------------------------------
// CInkdot::SetScore
// ----------------------------------------------------------------------------
//
void CInkdot::SetScore( TInt aScore )
    {
    iScore = aScore;
    }

// ----------------------------------------------------------------------------
// CInkdot::Score
// ----------------------------------------------------------------------------
//
TInt CInkdot::Score() const
    {
    return iScore;
    }

// ----------------------------------------------------------------------------
// CInkdot::Reverse
// ----------------------------------------------------------------------------
//
void CInkdot::Reverse()
    {
    TInt x( 0 ), y( 0 );
    if ( iCanvas.Rect().Width() > iCanvas.Rect().Height() )
        {
        x = iData.Position().iY;
        y = iCanvas.Rect().Height() - iData.Position().iX;
        iVectorX = -iVectorX;
        }
    else
        {
        x = iCanvas.Rect().Width() - iData.Position().iY;
        y = iData.Position().iX;
        iVectorY = -iVectorY;
        }
    iData.SetXY( x, y );
    }

// ----------------------------------------------------------------------------
// CInkdot::RunL
// ----------------------------------------------------------------------------
//
void CInkdot::RunL()
    {
    DoMove();
    }

// ----------------------------------------------------------------------------
// CInkdot::ConstructL
// ----------------------------------------------------------------------------
//
void CInkdot::CInkdot::ConstructL()
    {
    // Call the base class ConstructL
    CTimer::ConstructL();

    // Add this timer to the active scheduler
    CActiveScheduler::Add( this );
    
    iData.SetRadius( KMinInkdotRadius );

    if ( iData.Type() == ETouchInkdot )
        {
        iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
        iPeriodic->Cancel();
        iPeriodic->Start(
                KDoSplashDelayTimeout,
                KDoSplashTimeout,
                TCallBack( TimerCallback, this ) );
        }
    else
        {
        InitVector();

        After( KDoMoveTimeout );
        }

    }

// ----------------------------------------------------------------------------
// CInkdot::ConstructL
// ----------------------------------------------------------------------------
//
CInkdot::CInkdot( CCanvas& aCanvas, const TInkdotData& aInkdotData )
    : CTimer( CActive::EPriorityUserInput ), iCanvas( aCanvas ), iData( aInkdotData )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkdot::InitVector
// ----------------------------------------------------------------------------
//
void CInkdot::InitVector()
    {
    TBool reverseX( Rand( KReverse ) );
    iVectorX = Rand( KMaxVector );
    if ( reverseX )
        {
        iVectorX = -iVectorX;
        }

    TBool reverseY( Rand( KReverse ) );
    iVectorY = Rand( KMaxVector );
    if ( reverseY )
        {
        iVectorY = -iVectorY;
        }
        
    /*
     * If the sum of vx and vx is less than 3
     * we will reset the both vector again..
     */
    if ( Abs( iVectorX ) + Abs( iVectorY ) < KMaxVector / 2 )
        {
        InitVector();
        }
    }

// ----------------------------------------------------------------------------
// CInkdot::DoMove
// ----------------------------------------------------------------------------
//
void CInkdot::DoMove()
    {
    After( KDoMoveTimeout );

    TInt x( iData.Position().iX );
    TInt y( iData.Position().iY );
    iData.SetXY( x + iVectorX, y + iVectorY );

    HitTest();

    if ( iCanvas.SplashTest( *this  ) )
        {
        Cancel();
        iPeriodic = CPeriodic::NewL( CActive::EPriorityUserInput );
        iPeriodic->Cancel();
        iPeriodic->Start(
                KDoSplashDelayTimeout,
                KDoSplashTimeout,
                TCallBack( TimerCallback, this ) );
        }
    }

// ----------------------------------------------------------------------------
// CInkdot::DoSplash
// ----------------------------------------------------------------------------
//
void CInkdot::DoSplash()
    {
    TInt radius( iData.Radius() );
    if ( radius < KMaxInkdotRadius )
        {
        iData.SetRadius( ++radius );
        }
    else
        {
        iData.SetSplash();
        iPeriodic->Cancel();
        iPeriodic->Start(
                KDoExpireDelayTimeout,
                KDoExpireTimeout,
                TCallBack( ExpireCallback, this ) );
        }
    }

// ----------------------------------------------------------------------------
// CInkdot::DoExpire
// ----------------------------------------------------------------------------
//
void CInkdot::DoExpire()
    {
    Stop();
    TRAP_IGNORE( iCanvas.WipeL( *this ) );
    }

// ----------------------------------------------------------------------------
// CInkdot::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CInkdot::TimerCallback( TAny* aPtr )
    {
    CInkdot* self = static_cast<CInkdot*> ( aPtr );
    self->DoSplash();
    return 0;
    }

// ----------------------------------------------------------------------------
// CInkdot::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CInkdot::ExpireCallback( TAny* aPtr )
    {
    CInkdot* self = static_cast<CInkdot*> ( aPtr );
    self->DoExpire();
    return 0;
    }

// ----------------------------------------------------------------------------
// CInkdot::Rand
// ----------------------------------------------------------------------------
//
TInt CInkdot::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CInkdot::ClientRect
// ----------------------------------------------------------------------------
//
TRect CInkdot::ClientRect() const
    {
    TRect theRect;
    theRect.iTl.iX = iData.Position().iX - KMaxInkdotRadius;
    theRect.iTl.iY = iData.Position().iY - KMaxInkdotRadius;
    theRect.SetWidth( KMaxInkdotDiameter );
    theRect.SetHeight( KMaxInkdotDiameter );
    return theRect;
    }

// ----------------------------------------------------------------------------
// CInkdot::HitTest
// ----------------------------------------------------------------------------
//
void CInkdot::HitTest()
    {
    // Reach to left side
    if ( iData.Position().iX - iData.Radius() < iCanvas.Rect().iTl.iX )
        {
        iVectorX = -iVectorX;
        }

    // Reach to top side
    if ( iData.Position().iY - iData.Radius() < iCanvas.Rect().iTl.iY )
        {
        iVectorY = -iVectorY;
        }

    // Reach to right side
    if ( iData.Position().iX + iData.Radius() > iCanvas.Rect().iBr.iX )
        {
        iVectorX = -iVectorX;
        }

    // Reach to bottom side
    if ( iData.Position().iY + iData.Radius() > iCanvas.Rect().iBr.iY )
        {
        iVectorY = -iVectorY;
        }
    }

// ----------------------------------------------------------------------------
// CInkdot::Stop
// ----------------------------------------------------------------------------
//
void CInkdot::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    }

// End of File
