/* ====================================================================
 * File: LayoutManager.cpp
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h>
#include <e32property.h>
#include "LayoutManager.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CLayoutManager::NewL
// ----------------------------------------------------------------------------
//
CLayoutManager* CLayoutManager::NewL()
    {
    CLayoutManager* self = new (ELeave) CLayoutManager;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CLayoutManager::~CLayoutManager
// ----------------------------------------------------------------------------
//
CLayoutManager::~CLayoutManager()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CLayoutManager::ResolutionChanged
//
// Function can be used to update internal resolution value.
// Typically called by container in startup,
// and when dynamic layout variant switch has occured.
//
// ----------------------------------------------------------------------------
//
void CLayoutManager::ResolutionChanged( TOrientation aOrientation )
    {
    // Get screen parameters for solving layout
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    TInt w = screenRect.Width();
    switch ( screenRect.Width() )
        {
        case KQvgaPortraitWidth:
            {
                {
                if ( aOrientation == ELandscape )
                    iResolution = EQvgaLandscape;
                else
                    iResolution = EQvgaPortrait;
                }
            }
            break;
        case KQvgaLandscapeWidth: // Also KHvgaPortraitWidth
            {
            if ( screenRect.Height() == KQvgaLandscapeHeight )
                {
                if ( aOrientation == EPortrait )
                    iResolution = EQvgaPortrait;
                else
                    iResolution = EQvgaLandscape;
                }
            }
            break;
        default:
            iResolution = ENotSupported;
            break;
        }
    }

// ----------------------------------------------------------------------------
// CLayoutManager::LayoutRect
// LayoutRect should be called from control's SizeChanged() method.
// ----------------------------------------------------------------------------
//
void CLayoutManager::LayoutRect( TComponent aComponent, TRect& aRect ) const
    {
    switch ( aComponent )
        {
        // Screen
        case EScreen:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscScreenLeft,
                            KQvgaLscScreenTop,
                            KQvgaLscScreenRight,
                            KQvgaLscScreenBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtScreenLeft,
                            KQvgaPrtScreenTop,
                            KQvgaPrtScreenRight,
                            KQvgaPrtScreenBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Canvas
        case ECanvas:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscCanvasLeft,
                            KQvgaLscCanvasTop,
                            KQvgaLscCanvasRight,
                            KQvgaLscCanvasBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtCanvasLeft,
                            KQvgaPrtCanvasTop,
                            KQvgaPrtCanvasRight,
                            KQvgaPrtCanvasBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // InkTitle
        case EInkTitle:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscInkTitleLeft,
                            KQvgaLscInkTitleTop,
                            KQvgaLscInkTitleRight,
                            KQvgaLscInkTitleBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtInkTitleLeft,
                            KQvgaPrtInkTitleTop,
                            KQvgaPrtInkTitleRight,
                            KQvgaPrtInkTitleBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // StartButton
        case EStartButton:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscStartButtonLeft,
                            KQvgaLscStartButtonTop,
                            KQvgaLscStartButtonRight,
                            KQvgaLscStartButtonBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtStartButtonLeft,
                            KQvgaPrtStartButtonTop,
                            KQvgaPrtStartButtonRight,
                            KQvgaPrtStartButtonBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // BackButton
        case EBackButton:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscBackButtonLeft,
                            KQvgaLscBackButtonTop,
                            KQvgaLscBackButtonRight,
                            KQvgaLscBackButtonBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtBackButtonLeft,
                            KQvgaPrtBackButtonTop,
                            KQvgaPrtBackButtonRight,
                            KQvgaPrtBackButtonBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // WebButton
        case EWebButton:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscWebButtonLeft,
                            KQvgaLscWebButtonTop,
                            KQvgaLscWebButtonRight,
                            KQvgaLscWebButtonBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtWebButtonLeft,
                            KQvgaPrtWebButtonTop,
                            KQvgaPrtWebButtonRight,
                            KQvgaPrtWebButtonBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // QuitButton
        case EQuitButton:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscQuitButtonLeft,
                            KQvgaLscQuitButtonTop,
                            KQvgaLscQuitButtonRight,
                            KQvgaLscQuitButtonBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtQuitButtonLeft,
                            KQvgaPrtQuitButtonTop,
                            KQvgaPrtQuitButtonRight,
                            KQvgaPrtQuitButtonBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HighScore
        case EHighScore:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHighScoreLeft,
                            KQvgaLscHighScoreTop,
                            KQvgaLscHighScoreRight,
                            KQvgaLscHighScoreBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHighScoreLeft,
                            KQvgaPrtHighScoreTop,
                            KQvgaPrtHighScoreRight,
                            KQvgaPrtHighScoreBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // CurrentLevel
        case ECurrentLevel:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscCurrentLevelLeft,
                            KQvgaLscCurrentLevelTop,
                            KQvgaLscCurrentLevelRight,
                            KQvgaLscCurrentLevelBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtCurrentLevelLeft,
                            KQvgaPrtCurrentLevelTop,
                            KQvgaPrtCurrentLevelRight,
                            KQvgaPrtCurrentLevelBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // CurrentScore
        case ECurrentScore:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscCurrentScoreLeft,
                            KQvgaLscCurrentScoreTop,
                            KQvgaLscCurrentScoreRight,
                            KQvgaLscCurrentScoreBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtCurrentScoreLeft,
                            KQvgaPrtCurrentScoreTop,
                            KQvgaPrtCurrentScoreRight,
                            KQvgaPrtCurrentScoreBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Tooltip
        case ETooltip:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscTooltipLeft,
                            KQvgaLscTooltipTop,
                            KQvgaLscTooltipRight,
                            KQvgaLscTooltipBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtTooltipLeft,
                            KQvgaPrtTooltipTop,
                            KQvgaPrtTooltipRight,
                            KQvgaPrtTooltipBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ResultInfo
        case EResultInfo:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscResultInfoLeft,
                            KQvgaLscResultInfoTop,
                            KQvgaLscResultInfoRight,
                            KQvgaLscResultInfoBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtResultInfoLeft,
                            KQvgaPrtResultInfoTop,
                            KQvgaPrtResultInfoRight,
                            KQvgaPrtResultInfoBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CLayoutManager::LayoutRect
// ----------------------------------------------------------------------------
//
CLayoutManager::CLayoutManager()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CLayoutManager::ConstructL
// ----------------------------------------------------------------------------
//
void CLayoutManager::ConstructL()
    {
    ResolutionChanged( EAutomatic );
    }

// End of File
