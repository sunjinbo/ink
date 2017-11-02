/* ====================================================================
 * File: InkAppView.h
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKAPPVIEW_H
#define C_INKAPPVIEW_H

// INCLUDE FILES
#include <coecntrl.h>
#include "ButtonObserver.h"
#include "CanvasObserver.h"
#include "LevelObserver.h"
#include "Ink.hrh"

// FORWARD DECLARATIONS
class CCoeEnv;
class CLayoutManager;
class CCanvas;
class CMenuButton;
class CInfoControl;
class CWebButton;
class CLevelManager;
class CResReader;
class CScorekeeper;
class CTitle;

/*
* Class CInkAppView
*
*/
class CInkAppView : public CCoeControl,
    public MButtonObserver,
    public MCanvasObserver,
    public MLevelObserver
    {
public:
    enum TMode {
        EKickoff, // Reject touch event, and shown 3 bigger inkdots
        EGame, // Receive touch event, and shown some inkdots specify
        EInformation  // Reject touch event, and don't shown any inkdots
        };

public: // Constructor and destructor
    static CInkAppView* NewL( const TRect& aRect );
    static CInkAppView* NewLC( const TRect& aRect );
    virtual  ~CInkAppView();

public:  // from CCoeControl

    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void HandleResourceChange( TInt aType );

public: // from MButtonObserver
    void HandleClickedL( const CMenuButton& aBtn );

public: // from MCanvasObserver
    void CompletedL( TInt aCount );
    void AddScoreL( TInt aScore );

public: // from MLevelObserver
    void GameOverL();

private:
    void ConstructL(const TRect& aRect);
    CInkAppView();

private: 
    // New methods
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    void Stop();
    void DoFrame();
    static TInt TimerCallback( TAny* aPtr );
    void DoDraw();
    CMenuButton* CreateButtonL( TInkCmdIds aId );
    void DoStartL();
    void DoBackL();
    static TInt ExpireCallbackL( TAny* aPtr );
    void DoExpireL();

private: // Member data
    CCoeEnv& iCoeEnv;
    CResReader* iResReader; // Own
    CPeriodic* iPeriodic; // Own
    CPeriodic* iExpire; // Own
    CFbsBitmap* iBmpBuffer; // Own
    CFbsBitmapDevice* iBmpBufferDevice; // Own
    CFbsBitGc* iBmpBufferContext; // Own
    CLayoutManager* iLayoutManager; // Own
    CLevelManager* iLevelManager; // Own
    CScorekeeper* iScorekeeper; // Own
    CCanvas* iCanvas; // Own
    CMenuButton* iStartButton; // Own
    CMenuButton* iBackButton; // Own
    CMenuButton* iWebButton; // Own
    CMenuButton* iQuitButton; // Own
    CInfoControl* iHighScore; // Own
    CInfoControl* iCurrentLevel; // Own
    CInfoControl* iCurrentScore; // Own
    CInfoControl* iTooltip; // Own
    CInfoControl* iResultInfo; // Own
    CTitle* iTitle; // Own
    TMode iMode;
    TInt iScore;
    TInt iCompleted;
    TBool iExpireDelay;
    };

#endif // C_INKAPPVIEW_H

// End of File
