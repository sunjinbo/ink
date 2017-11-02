/* ====================================================================
 * File: InkAppView.cpp
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <bautils.h>
#include <coemain.h>
#include <AknUtils.h>
#include <aknsutils.h>
#include <StringLoader.h>
#include <f32file.h>
#include <aknViewAppUi.h>
#include <eikenv.h>
#include <aknenv.h>
#include <Ink.rsg>
#include "InkAppView.h"
#include "LayoutManager.h"
#include "Canvas.h"
#include "MenuButton.h"
#include "InfoControl.h"
#include "LevelManager.h"
#include "Ink.pan"
#include "ResReader.h"
#include "Scorekeeper.h"
#include "InkAppUi.h"
#include "Title.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;
const TInt KDoExpireTimeout = 1000000;
const TInt KDoExpireUpdateTimeout = 5000000;
const TInt KBufferLen = 8;
const TInt KInitScore = 0;
const TInt KKickoffInkdotNbr = 7;

#if defined( __WINS__ )
_LIT( KInkResourceFile, "z:\\resource\\apps\\ink.rsc" );
#else
_LIT( KInkResourceFile, "\\resource\\apps\\ink.rsc" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkAppView::NewL
// Standard construction sequence
// ----------------------------------------------------------------------------
//
CInkAppView* CInkAppView::NewL( const TRect& aRect )
    {
    CInkAppView* self = CInkAppView::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkAppView::NewLC
// ----------------------------------------------------------------------------
//
CInkAppView* CInkAppView::NewLC( const TRect& aRect )
    {
    CInkAppView* self = new (ELeave) CInkAppView;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkAppView::CInkAppView
// ----------------------------------------------------------------------------
//
CInkAppView::CInkAppView()
    : iCoeEnv( *CCoeEnv::Static() )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkAppView::~CInkAppView
// ----------------------------------------------------------------------------
//
CInkAppView::~CInkAppView()
    {
    delete iResReader;
    delete iLayoutManager;
    delete iCanvas;
    delete iStartButton;
    delete iBackButton;
    delete iWebButton;
    delete iQuitButton;
    delete iHighScore;
    delete iCurrentLevel;
    delete iCurrentScore;
    delete iTooltip;
    delete iResultInfo;
    delete iLevelManager;
    delete iScorekeeper;
    delete iTitle;
    Stop(); // iPeriodic
    ReleaseBmpBuffer();

    if ( iExpire )
        {  
        iExpire->Cancel();
        delete iExpire;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::Draw
// Draw this application's view to the screen
// ----------------------------------------------------------------------------
//
void CInkAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context 
    CWindowGc& gc = SystemGc();
    
    // Gets the control's extent
    TRect rect = Rect();

    // Clears the screen
    gc.Clear( rect );
    }

// ----------------------------------------------------------------------------
// CInkAppView::SizeChanged
// ----------------------------------------------------------------------------
//
void CInkAppView::SizeChanged()
    {
    TRAP_IGNORE( CreateBmpBufferL() );
    if( iLayoutManager )
        {
        TRect rect;
        if ( iCanvas )
            {
            iLayoutManager->LayoutRect( ECanvas, rect );
            iCanvas->SetRect( rect );
            iCanvas->Reverse();
            }

        if ( iTitle )
            {
            iLayoutManager->LayoutRect( EInkTitle, rect );
            iTitle->SetRect( rect );
            }

        if ( iStartButton )
            {
            iLayoutManager->LayoutRect( EStartButton, rect );
            iStartButton->SetRect( rect );
            }
            
        if ( iBackButton )
            {
            iLayoutManager->LayoutRect( EBackButton, rect );
            iBackButton->SetRect( rect );
            }
            
        if ( iWebButton )
            {
            iLayoutManager->LayoutRect( EWebButton, rect );
            iWebButton->SetRect( rect );
            }

        if ( iQuitButton )
            {
            iLayoutManager->LayoutRect( EQuitButton, rect );
            iQuitButton->SetRect( rect );
            }
            
        if ( iHighScore )
            {
            iLayoutManager->LayoutRect( EHighScore, rect );
            iHighScore->SetRect( rect );
            }

        if ( iCurrentLevel )
            {
            iLayoutManager->LayoutRect( ECurrentLevel, rect );
            iCurrentLevel->SetRect( rect );
            }

        if ( iCurrentScore )
            {
            iLayoutManager->LayoutRect( ECurrentScore, rect );
            iCurrentScore->SetRect( rect );
            }

        if ( iTooltip )
            {
            iLayoutManager->LayoutRect( ETooltip, rect );
            iTooltip->SetRect( rect );
            }

        if ( iResultInfo )
            {
            iLayoutManager->LayoutRect( EResultInfo, rect );
            iResultInfo->SetRect( rect );
            }

        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CInkAppView::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iStartButton 
            && iStartButton->Rect().Contains( aPointerEvent.iPosition ) )
            {
            iStartButton->ClickL( aPointerEvent.iPosition );
            return;
            }

        if ( iBackButton 
            && iBackButton->Rect().Contains( aPointerEvent.iPosition ) )
            {
            iBackButton->ClickL( aPointerEvent.iPosition );
            return;
            }

        if ( iWebButton 
            && iWebButton->Rect().Contains( aPointerEvent.iPosition ) )
            {
            iWebButton->ClickL( aPointerEvent.iPosition );
            return;
            }

        if ( iQuitButton 
            && iQuitButton->Rect().Contains( aPointerEvent.iPosition ) )
            {
            iQuitButton->ClickL( aPointerEvent.iPosition );
            return;
            }

        if ( iCanvas
            && iCanvas->Rect().Contains( aPointerEvent.iPosition )
            && iMode == EGame )
            {
            iCanvas->HandlePointerEventL( aPointerEvent );
            return;
            }
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::CountComponentControls
// ----------------------------------------------------------------------------
//
TInt CInkAppView::CountComponentControls() const
    {
    TInt count( 0 );

    if ( iCanvas )
        {
        ++count;
        }

    return count;
    }

// ----------------------------------------------------------------------------
// CInkAppView::ComponentControl
// ----------------------------------------------------------------------------
//
CCoeControl* CInkAppView::ComponentControl( TInt aIndex ) const
    {
    switch( aIndex )
        {
        case 0:
            return iCanvas;
        default:
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CInkAppView::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TRect theRect;
        iLayoutManager->ResolutionChanged();
        iLayoutManager->LayoutRect( EScreen, theRect );
        SetRect( theRect );
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::HandleClickedL
// ----------------------------------------------------------------------------
//
void CInkAppView::HandleClickedL( const CMenuButton& aBtn )
    {
    switch( aBtn.Id() )
        {
        case EInkCmdStart:
            DoStartL();
            break;
        case EInkCmdBack:
            DoBackL();
            break;
        case EInkCmdWeb:
            static_cast<CInkAppUi*>( iCoeEnv.AppUi() )->LaunchBrowserL();
            break;
        case EInkCmdQuit:
            static_cast<CAknAppUi*>( iCoeEnv.AppUi() )->Exit();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::CompletedL
// ----------------------------------------------------------------------------
//
void CInkAppView::CompletedL( TInt /*aCount*/ )
    {
    iExpire->Cancel();
    iExpire->Start(
                KDoExpireTimeout,
                KDoExpireUpdateTimeout,
                TCallBack( ExpireCallbackL, this ) 
                );
    iExpireDelay = ETrue;
    }

// ----------------------------------------------------------------------------
// CInkAppView::AddScoreL
// ----------------------------------------------------------------------------
//
void CInkAppView::AddScoreL( TInt aScore )
    {
    iScore += aScore;
    ++iCompleted;
    
    TBuf<KBufferLen> buffer;
    buffer.AppendNum( iScore );
    iCurrentScore->SetTextL( buffer );
    
    if ( iCompleted < iLevelManager->Pass() )
        {
        TBuf<KBufferLen> tooltipBuffer;
        tooltipBuffer.AppendNum( iLevelManager->Pass() - iCompleted  );
        iTooltip->SetTextL( tooltipBuffer );
        }
    else
        {
        HBufC* tooltip = StringLoader::LoadL( R_INK_INFO_TOOLTIP_EXTRA_BONUS );
    	CleanupStack::PushL( tooltip );
    	iTooltip->SetTextL( *tooltip );
    	CleanupStack::PopAndDestroy( tooltip );
        tooltip = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::GameOverL
// ----------------------------------------------------------------------------
//
void CInkAppView::GameOverL()
    {
    iScorekeeper->SetHighScoreL( iScore );
    DoBackL();
    }

// ----------------------------------------------------------------------------
// CInkAppView::ConstructL
// ----------------------------------------------------------------------------
//
void CInkAppView::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    TFileName fileName;
    fileName.Append( KInkResourceFile );
    iResReader = CResReader::NewL( CCoeEnv::Static()->FsSession(), fileName );

    CreateBmpBufferL();

    iPeriodic = CPeriodic::NewL( CActive::EPriorityLow );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoDelayTimeout,
            KDoFrameUpdateTimeout,
            TCallBack( TimerCallback, this ) 
            );

    iExpire = CPeriodic::NewL( CActive::EPriorityStandard );
    iExpire->Cancel();

    iScorekeeper = CScorekeeper::NewL();

    iMode = EKickoff;

    iLayoutManager = CLayoutManager::NewL();

    TRect theRect;
    iLayoutManager->LayoutRect( ECanvas, theRect );
    iCanvas = CCanvas::NewL( *this, iBmpBufferContext, theRect );
    iCanvas->SetContainerWindowL( *this );
    iCanvas->StartL( KKickoffInkdotNbr );

    iLayoutManager->LayoutRect( EHighScore, theRect );
    iHighScore = CInfoControl::NewL( iBmpBufferContext, theRect );
    _LIT( KHighScore, "No local high score" );
    iHighScore->SetAlign( ECenter );
    iHighScore->SetInfoFont( CInfoControl::ELatinBold12 );
    iHighScore->SetTextL( KHighScore );

    iLayoutManager->LayoutRect( EInkTitle, theRect );
    iTitle = CTitle::NewL( iBmpBufferContext, theRect );

    iStartButton = CreateButtonL( EInkCmdStart );
    iQuitButton = CreateButtonL( EInkCmdQuit );
    iWebButton = CreateButtonL( EInkCmdWeb );

    iLevelManager = CLevelManager::NewL( *this );

    // Enable Drag Events.
    EnableDragEvents();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CInkAppView::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CInkAppView::CreateBmpBufferL()
    {
    // If double buffer resouces has been created, 
    // release them at first.
    ReleaseBmpBuffer();
    TSize size( Size() );
    // Create double buffer bitmap
    iBmpBuffer = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBmpBuffer->Create( Size(), EColor16MAP ) );

    // Create double buffer graphics context
    iBmpBufferDevice = CFbsBitmapDevice::NewL( iBmpBuffer );
    User::LeaveIfError( iBmpBufferDevice->CreateContext( iBmpBufferContext ) );
    iBmpBufferContext->SetPenStyle( CGraphicsContext::ESolidPen );
    }

// ----------------------------------------------------------------------------
// CInkAppView::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CInkAppView::ReleaseBmpBuffer()
    {
    delete iBmpBufferContext;
    iBmpBufferContext = NULL;
    delete iBmpBufferDevice;
    iBmpBufferDevice = NULL;
    delete iBmpBuffer;
    iBmpBuffer = NULL;
    }

// ----------------------------------------------------------------------------
// CInkAppView::Stop
// ----------------------------------------------------------------------------
//
void CInkAppView::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;   
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::DoFrame
// ----------------------------------------------------------------------------
//
void CInkAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    DoDraw();
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBmpBuffer );
    Window().EndRedraw();
    DeactivateGc();
    }

// ----------------------------------------------------------------------------
// CInkAppView::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CInkAppView::TimerCallback( TAny* aPtr )
    {
    CInkAppView* self = static_cast<CInkAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CInkAppView::DoDraw
// ----------------------------------------------------------------------------
//
void CInkAppView::DoDraw()
    {
    if ( iCanvas )
        {
        iCanvas->DoDraw();
        }

    if ( iTitle )
        {
        iTitle->DoDraw();
        }

    if ( iStartButton )
        {
        iStartButton->DoDraw();
        }

    if ( iBackButton )
        {
        iBackButton->DoDraw();
        }

    if ( iWebButton )
        {
        iWebButton->DoDraw();
        }

    if ( iQuitButton )
        {
        iQuitButton->DoDraw();
        }

    if ( iHighScore )
        {
        iHighScore->DoDraw();
        }

    if ( iCurrentLevel )
        {
        iCurrentLevel->DoDraw();
        }

    if ( iCurrentScore )
        {
        iCurrentScore->DoDraw();
        }

    if ( iTooltip )
        {
        iTooltip->DoDraw();
        }

    if ( iResultInfo )
        {
        iResultInfo->DoDraw();
        }
    }

// ----------------------------------------------------------------------------
// CInkAppView::CreateButtonL
// ----------------------------------------------------------------------------
//
CMenuButton* CInkAppView::CreateButtonL( TInkCmdIds aId )
    {
    CMenuButton* button = NULL;
    HBufC8* buffer = NULL;
    TResourceReader theReader;
    TRect theRect;
    switch( aId )
        {
        case EInkCmdStart:
            {
            iLayoutManager->LayoutRect( EStartButton, theRect );
            button = CMenuButton::NewL( *this, iBmpBufferContext, theRect );
            buffer = iResReader->ResourceData( R_INK_START );
            }
            break;
        case EInkCmdBack:
            iLayoutManager->LayoutRect( EBackButton, theRect );
            button = CMenuButton::NewL( *this, iBmpBufferContext, theRect );
            buffer = iResReader->ResourceData( R_INK_BACK );
            break;
        case EInkCmdWeb:
            iLayoutManager->LayoutRect( EWebButton, theRect );
            button = CMenuButton::NewL( *this, iBmpBufferContext, theRect );
            buffer = iResReader->ResourceData( R_INK_WEB );
            break;
        case EInkCmdQuit:
            iLayoutManager->LayoutRect( EQuitButton, theRect );
            button = CMenuButton::NewL( *this, iBmpBufferContext, theRect );
            buffer = iResReader->ResourceData( R_INK_QUIT );
            break;
        default:
            break;
        }

    // Constructs button from resource
    theReader.SetBuffer( buffer );
    button->ConstructFromResourceL( theReader );

    return button;
    }

// ----------------------------------------------------------------------------
// CInkAppView::DoStartL
// ----------------------------------------------------------------------------
//
void CInkAppView::DoStartL()
    {
    delete iTitle;
    iTitle = NULL;

    delete iStartButton;
    iStartButton = NULL;

    delete iWebButton;
    iWebButton = NULL;

    delete iQuitButton;
    iQuitButton = NULL;

    delete iHighScore;
    iHighScore = NULL;

    TRect theRect;
    iLayoutManager->LayoutRect( ECurrentLevel, theRect );
    iCurrentLevel = CInfoControl::NewL( iBmpBufferContext, theRect );
    iCurrentLevel->SetAlign( ELeft );
    iCurrentLevel->SetInfoFont( CInfoControl::EClockBold30 );
    iCurrentLevel->SetColor( KRgbGreen );

    iLayoutManager->LayoutRect( ECurrentScore, theRect );
    iCurrentScore = CInfoControl::NewL( iBmpBufferContext, theRect );
    iCurrentScore->SetAlign( ELeft );
    iCurrentScore->SetInfoFont( CInfoControl::ELatinClock14 );
    iCurrentScore->SetColor( KRgbRed );

    iLayoutManager->LayoutRect( ETooltip, theRect );
    iTooltip = CInfoControl::NewL( iBmpBufferContext, theRect );
    iTooltip->SetAlign( ERight );

    iBackButton = CreateButtonL( EInkCmdBack );

    iLevelManager->Reset();

    iCanvas->StartL( iLevelManager->Count() );

    TBuf<KBufferLen> levelBuffer;
    levelBuffer.AppendNum( iLevelManager->Id() );
    iCurrentLevel->SetTextL( levelBuffer );

    TBuf<KBufferLen> scoreBuffer;
    scoreBuffer.AppendNum( KInitScore );
    iCurrentScore->SetTextL( scoreBuffer );

    HBufC* tooltip = StringLoader::LoadL( R_INK_INFO_TOOLTIP_START );
	CleanupStack::PushL( tooltip );
	iTooltip->SetTextL( *tooltip );
	CleanupStack::PopAndDestroy( tooltip );
    tooltip = NULL;

    iMode = EGame;
    }

// ----------------------------------------------------------------------------
// CInkAppView::DoBackL
// ----------------------------------------------------------------------------
//
void CInkAppView::DoBackL()
    {
    delete iBackButton;
    iBackButton = NULL;
    
    delete iCurrentLevel;
    iCurrentLevel = NULL;
    
    delete iCurrentScore;
    iCurrentScore = NULL;
    
    delete iTooltip;
    iTooltip = NULL;
    
    delete iResultInfo;
    iResultInfo = NULL;

    TRect theRect;
    iLayoutManager->LayoutRect( EHighScore, theRect );
    iHighScore = CInfoControl::NewL( iBmpBufferContext, theRect );
    iHighScore->SetAlign( ECenter );
    iHighScore->SetInfoFont( CInfoControl::ELatinBold12 );
    
    if ( iScorekeeper->NoLocalHighScore() )
        {
        _LIT( KNoLocalHighScore, "No local high score" );
        iHighScore->SetTextL( KNoLocalHighScore );
        }
    else
        {
        TBuf<24> buffer;
        _LIT( KHighScore, "High score:" );
        buffer.Append( KHighScore );
        buffer.AppendNum( iScorekeeper->HighScore() );
        iHighScore->SetTextL( buffer );
        }

    iLayoutManager->LayoutRect( EInkTitle, theRect );
    iTitle = CTitle::NewL( iBmpBufferContext, theRect );

    iStartButton = CreateButtonL( EInkCmdStart );
    iQuitButton = CreateButtonL( EInkCmdQuit );
    iWebButton = CreateButtonL( EInkCmdWeb );

    iCanvas->Clear();
    iCanvas->StartL( KKickoffInkdotNbr );
    
    iMode = EKickoff;
    }

// ----------------------------------------------------------------------------
// CInkAppView::ExpireCallbackL
// ----------------------------------------------------------------------------
//
TInt CInkAppView::ExpireCallbackL( TAny* aPtr )
    {
    CInkAppView* self = static_cast<CInkAppView*> ( aPtr );
    self->DoExpireL();
    return 0;
    }

// ----------------------------------------------------------------------------
// CInkAppView::DoExpireL
// ----------------------------------------------------------------------------
//
void CInkAppView::DoExpireL()
    {
    if ( iExpireDelay )
        {
        iExpireDelay = EFalse;
        iCurrentLevel->SetEnabled( EFalse );
        iCurrentScore->SetEnabled( EFalse );
        iTooltip->SetEnabled( EFalse );
        iBackButton->SetEnabled( EFalse );
        
        TRect theRect;
        iLayoutManager->LayoutRect( EResultInfo, theRect );
        iResultInfo = CInfoControl::NewL( iBmpBufferContext, theRect );
        iResultInfo->SetAlign( ECenter );
        iResultInfo->SetInfoFont( CInfoControl::ELatinBold19 );
        iResultInfo->SetColor( KRgbWhite );
        _LIT( KResultInfo, "Mission completed!!" );
        iResultInfo->SetTextL( KResultInfo );
        }
    else
        {
        delete iResultInfo;
        iResultInfo = NULL;

        iExpire->Cancel();

        iCurrentLevel->SetEnabled( ETrue );
        iCurrentScore->SetEnabled( ETrue );
        iTooltip->SetEnabled( ETrue );
        iBackButton->SetEnabled( ETrue );

        TInt err = iLevelManager->NextL();
        if ( err == KErrNone )
            {
            iCanvas->Clear();
            iCanvas->StartL( iLevelManager->Count() );

            TBuf<KBufferLen> levelBuffer;
            levelBuffer.AppendNum( iLevelManager->Id() );
            iCurrentLevel->SetTextL( levelBuffer );

            TBuf<KBufferLen> scoreBuffer;
            scoreBuffer.AppendNum( iScore );
            iCurrentScore->SetTextL( scoreBuffer );

            HBufC* tooltip = StringLoader::LoadL( R_INK_INFO_TOOLTIP_START );
            CleanupStack::PushL( tooltip );
            iTooltip->SetTextL( *tooltip );
            CleanupStack::PopAndDestroy( tooltip );
            tooltip = NULL;
            }
        }
    }

// End of File
