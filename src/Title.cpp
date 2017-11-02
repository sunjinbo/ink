/* ====================================================================
 * File: Title.cpp
 * Created: 03/26/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <fbs.h>
#include <barsread.h>
#include <gulicon.h>
#include <eikenv.h>
#include <title.mbg>
#include "Title.h"
#include "BmpUtils.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmTitleFileName, "Z:\\resource\\apps\\title.mbm" );
#else
_LIT( KMbmTitleFileName, "\\resource\\apps\\title.mbm" );
#endif // __WINS__

const TInt KDoEffectsDelayTimeout = 0;
const TInt KDoEffectsTimeout = 300000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CTitle::NewL
// ----------------------------------------------------------------------------
//
CTitle* CTitle::NewL( CFbsBitGc*& aGc, const TRect& aRect )
    {
    CTitle* self = new (ELeave) CTitle( aGc );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CTitle::~CTitle
// ----------------------------------------------------------------------------
//
CTitle::~CTitle()
    {
    delete iUtils;
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CTitle::DoDraw
// ----------------------------------------------------------------------------
//
void CTitle::DoDraw()
    {
    if ( iEnabled )
        {
         iGc->SetPenStyle( CGraphicsContext::ENullPen );
         iGc->SetBrushStyle( CGraphicsContext::ENullBrush );

         iGc->BitBltMasked( 
            iRect.iTl,
            iUtils->Bitmap( iBitmap ),
            TRect( TPoint( 0, 0 ), iRect.Size() ),
            iUtils->Bitmap( EMbmTitleMask ),
            ETrue
            );

        }
    }

// ----------------------------------------------------------------------------
// CTitle::SetEnable
// ----------------------------------------------------------------------------
//
void CTitle::SetEnabled( TBool aEnabled )
    {
    iEnabled = aEnabled;
    }

// ----------------------------------------------------------------------------
// CTitle::IsEnable
// ----------------------------------------------------------------------------
//
TBool CTitle::IsEnabled() const
    {
    return iEnabled;
    }

// ----------------------------------------------------------------------------
// CTitle::SetRect
// ----------------------------------------------------------------------------
//
void CTitle::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Rect
// ----------------------------------------------------------------------------
//
TRect CTitle::Rect() const
    {
    return iRect;
    }

// ----------------------------------------------------------------------------
// CTitle::ConstructL
// ----------------------------------------------------------------------------
//
void CTitle::ConstructL(const TRect& aRect)
    {
    SetRect( aRect );

    iUtils = CBmpUtils::NewL( 
                    KMbmTitleFileName, 
                    EMbmTitle0,
                    EMbmTitleLastElement 
                    );
    
    iBitmap = EMbmTitle0;

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoEffectsDelayTimeout,
            KDoEffectsTimeout,
            TCallBack( TimerCallback, this ) );
    }

// ----------------------------------------------------------------------------
// CTitle::CTitle
// ----------------------------------------------------------------------------
//
CTitle::CTitle( CFbsBitGc*& aGc )
    : iGc( aGc ), iEnabled( ETrue )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CTitle::DoEffects
// ----------------------------------------------------------------------------
//
void CTitle::DoEffects()
    {
    if ( !iReverse )
        {
        iBitmap += 2;
        if ( iBitmap == EMbmTitle5 )
            {
            iReverse = ETrue;
            }
        }
    else
        {
        iBitmap -= 2;
        if ( iBitmap == EMbmTitle0 )
            {
            iReverse = EFalse;
            }
        }
    }

// ----------------------------------------------------------------------------
// CInkdot::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CTitle::TimerCallback( TAny* aPtr )
    {
    CTitle* self = static_cast<CTitle*> ( aPtr );
    self->DoEffects();
    return 0;
    }

// End of File
