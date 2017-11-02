/* ====================================================================
 * File: InkdotAssistor.cpp
 * Created: 03/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <fbs.h>
#include <bitdev.h>
#include <inkdot.mbg>
#include "InkdotAssistor.h"
#include "BmpUtils.h"
#include "Ink.pan"
#include "InkdotConstants.h"

// CONSTANTS

const TInt KBrinkDepth = 2;

#if defined( __WINS__ )
_LIT( KMbmInkdotFileName, "Z:\\resource\\apps\\inkdot.mbm" );
#else
_LIT( KMbmInkdotFileName, "\\resource\\apps\\inkdot.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkdotAssistor::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CInkdotAssistor* CInkdotAssistor::NewL()
    {
    CInkdotAssistor* self = new (ELeave) CInkdotAssistor;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkdotAssistor::~CInkdotAssistor
// ----------------------------------------------------------------------------
//
CInkdotAssistor::~CInkdotAssistor()
    {
    delete iUtils;
    delete iMaskContext;
    delete iMaskDevice;
    delete iMask;
    }

// ----------------------------------------------------------------------------
// CInkdotAssistor::Bitmap
// ----------------------------------------------------------------------------
//
CFbsBitmap* CInkdotAssistor::Bitmap( TInkdotType aInkdot )
    {
    __ASSERT_ALWAYS( ( aInkdot > EInkdotNull ) && ( aInkdot < EInkdotLastElement ), Panic( EInkBadInkdotType ) );
    return iUtils->Bitmap( EMbmInkdotTouch + aInkdot * 2 );
    }

// ----------------------------------------------------------------------------
// CInkdotAssistor::Mask
// ----------------------------------------------------------------------------
//
CFbsBitmap* CInkdotAssistor:: Mask( TInt aRadius )
    {
    __ASSERT_ALWAYS( ( aRadius >= KMinInkdotRadius ) && ( aRadius <= KMaxInkdotRadius ), Panic( EInkBadRadius ) );
    CFbsBitmap* mask( NULL );
    if ( aRadius + KBrinkDepth >= KMaxInkdotRadius )
        {
        mask = iUtils->Bitmap( EMbmInkdotMask );  
        }
    else
        {
        TRect theRect( TPoint( 0, 0 ), iMaskSize );

        iMaskContext->SetPenStyle( CGraphicsContext::ESolidPen );
        iMaskContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
        iMaskContext->SetPenColor( KRgbWhite );
        iMaskContext->SetBrushColor( KRgbWhite );
        iMaskContext->DrawRect( theRect );

        iMaskContext->SetPenColor( KRgbDarkGray );
        iMaskContext->SetBrushColor( KRgbDarkGray );
        TInt offset = KMaxInkdotRadius - aRadius;
        theRect.Shrink( offset, offset );
        iMaskContext->DrawEllipse( 
            TRect( TPoint( offset, offset ), theRect.Size() ) );
        mask = iMask;
        }
    return mask;
    }

// ----------------------------------------------------------------------------
// CInkdotAssistor::ConstructL
// ----------------------------------------------------------------------------
//
void CInkdotAssistor::ConstructL()
    {
    iUtils = CBmpUtils::NewL( 
            KMbmInkdotFileName, 
            EMbmInkdotTouch,
            EMbmInkdotLastElement 
            );

    iMaskSize = TSize( KMaxInkdotDiameter, KMaxInkdotDiameter );

    // Create double buffer bitmap
    iMask = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iMask->Create( iMaskSize, EColor16MAP ) );

    // Create double buffer graphics context
    iMaskDevice = CFbsBitmapDevice::NewL( iMask );
    User::LeaveIfError( iMaskDevice->CreateContext( iMaskContext ) );
    }

// ----------------------------------------------------------------------------
// CInkdotAssistor::CInkdotAssistor
// ----------------------------------------------------------------------------
//
CInkdotAssistor::CInkdotAssistor()
    { // no implementation required
    }

// End of file
