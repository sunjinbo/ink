/* ====================================================================
 * File: MenuButton.cpp
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <fbs.h>
#include <barsread.h>
#include <gulicon.h>
#include <eikenv.h>
#include <button.mbg>
#include "MenuButton.h"
#include "ButtonObserver.h"
#include "BmpUtils.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmButtonFileName, "Z:\\resource\\apps\\button.mbm" );
#else
_LIT( KMbmButtonFileName, "\\resource\\apps\\button.mbm" );
#endif // __WINS__


// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CMenuButton::NewL
// ----------------------------------------------------------------------------
//
CMenuButton* CMenuButton::NewL( MButtonObserver& aObserver,
    CFbsBitGc*& aGc, const TRect& aRect )
    {
    CMenuButton* self = new (ELeave) CMenuButton( aObserver, aGc );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CMenuButton::~CMenuButton
// ----------------------------------------------------------------------------
//
CMenuButton::~CMenuButton()
    {
    delete iText;
    delete iUtils;
    }

// ----------------------------------------------------------------------------
// CMenuButton::DoDraw
// ----------------------------------------------------------------------------
//
void CMenuButton::DoDraw()
    {
    if ( iEnabled )
        {
         iGc->SetPenStyle( CGraphicsContext::ENullPen );
         iGc->SetBrushStyle( CGraphicsContext::ENullBrush );

         iGc->BitBltMasked( 
            iRect.iTl,
            iUtils->Bitmap( iBitmapId ),
            TRect( TPoint( 0, 0 ), iRect.Size() ),
            iUtils->Bitmap( iMaskId ),
            ETrue
            );
        
        if ( iText )
            {
             iGc->SetPenStyle( CGraphicsContext::ESolidPen );
             iGc->SetPenColor( iColor );
             iGc->UseFont( CEikonEnv::Static()->AnnotationFont() );
             iGc->DrawText( *iText, iRect, iTextBaseline, iAlign, 0 );
            }

        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::Id
// ----------------------------------------------------------------------------
//
TInt CMenuButton::Id() const
    {
    return iBtnId;
    }

// ----------------------------------------------------------------------------
// CMenuButton::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
void CMenuButton::ConstructFromResourceL( TResourceReader& aReader )
    {
    iBtnId = aReader.ReadInt32();
    iEnabled = (TBool)(aReader.ReadInt32());
    iAlign = (CGraphicsContext::TTextAlign)(aReader.ReadInt32());
    iBitmapId = aReader.ReadInt32 ();
    iMaskId = aReader.ReadInt32 ();
    iFontHeightInTwips = aReader.ReadInt32();
    iTextBaseline = aReader.ReadInt32();
    iColor = TRgb( aReader.ReadInt32() );

    HBufC* txt = aReader.ReadHBufCL();
    if ( iText )
        {
        delete iText;
        iText = NULL;
        }

    if ( txt )
        {
        iText =  HBufC::NewL( txt->Length() );
        TPtr text( iText->Des() );
        text.Copy( *txt );
        delete txt;
        txt = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CMenuButton::SetEnable
// ----------------------------------------------------------------------------
//
void CMenuButton::SetEnabled( TBool aEnabled )
    {
    iEnabled = aEnabled;
    }

// ----------------------------------------------------------------------------
// CMenuButton::IsEnable
// ----------------------------------------------------------------------------
//
TBool CMenuButton::IsEnabled() const
    {
    return iEnabled;
    }

// ----------------------------------------------------------------------------
// CMenuButton::SetRect
// ----------------------------------------------------------------------------
//
void CMenuButton::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    }

// ----------------------------------------------------------------------------
// CMenuButton::Rect
// ----------------------------------------------------------------------------
//
TRect CMenuButton::Rect() const
    {
    return iRect;
    }

// ----------------------------------------------------------------------------
// CMenuButton::ClickL
// ----------------------------------------------------------------------------
//
void CMenuButton::ClickL( const TPoint& /*aPos*/ )
    {
    iObserver.HandleClickedL( *this );
    }

// ----------------------------------------------------------------------------
// CMenuButton::ConstructL
// ----------------------------------------------------------------------------
//
void CMenuButton::ConstructL(const TRect& aRect)
    {
    iRect = aRect;
    
    iUtils = CBmpUtils::NewL( 
                    KMbmButtonFileName, 
                    EMbmButtonStart,
                    EMbmButtonLastElement 
                    );
    }

// ----------------------------------------------------------------------------
// CMenuButton::CMenuButton
// ----------------------------------------------------------------------------
//
CMenuButton::CMenuButton( MButtonObserver& aObserver,CFbsBitGc*& aGc )
    : iObserver( aObserver ), iGc( aGc ), iEnabled( ETrue )
    { // no implementation required
    }

// End of File
