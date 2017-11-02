/* ====================================================================
 * File: InkAppUi.cpp
 * Created: 03/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDES
#include <avkon.hrh>
#include <eikbtgpc.h>
#include <apgcli.h>
#include <AknUtils.h>
#include "Ink.pan"
#include "InkAppUi.h"
#include "InkAppView.h"
#include "Ink.hrh"

// CONSTANS
_LIT( KWebUrl, "http://nokia.mobi/" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkAppUi::NewL
// ConstructL is called by the application framework
// ----------------------------------------------------------------------------
//
void CInkAppUi::ConstructL()
    {
    BaseConstructL();

    Cba()->MakeVisible( EFalse ); 
    StatusPane()->MakeVisible( EFalse );
    
    TRect theRect ;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, theRect );

    iAppView = CInkAppView::NewL( theRect );

    AddToStackL(iAppView);
    }

// ----------------------------------------------------------------------------
// CInkAppUi::CInkAppUi
// ----------------------------------------------------------------------------
//
CInkAppUi::CInkAppUi()                              
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkAppUi::~CInkAppUi
// ----------------------------------------------------------------------------
//
CInkAppUi::~CInkAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack( iAppView );
        delete iAppView;
        iAppView = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppUi::LaunchBrowserL
// ----------------------------------------------------------------------------
//
void CInkAppUi::LaunchBrowserL()
    {
    TUid browserUid = TUid::Uid(  0x10008D39 );                          

    TApaTaskList taskList( iEikonEnv->WsSession() );
    TApaTask task = taskList.FindApp( browserUid );

    // browser is already running
    if ( task.Exists() )
        {
        HBufC8* param8 = HBufC8::NewLC( /*webUrl->Length()*/ 128 );
        param8->Des().Append( KWebUrl );
        task.SendMessage( TUid::Uid( 0 ), *param8 );
        CleanupStack::PopAndDestroy( param8 );
        }
    // browser is not running, start it
    else
        {
        RApaLsSession appArcSession;
        User::LeaveIfError( appArcSession.Connect() );       

        CleanupClosePushL( appArcSession );
        TThreadId id;
        appArcSession.StartDocument( KWebUrl, browserUid, id );
        CleanupStack::PopAndDestroy( &appArcSession );
       }
    }

// ----------------------------------------------------------------------------
// CInkAppUi::HandleCommandL
// handle any menu commands
// ----------------------------------------------------------------------------
//
void CInkAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        default:
            Panic( EInkBadCommands );
            break;
        }
    }

// ----------------------------------------------------------------------------
// CInkAppUi::HandleResourceChangeL
// ----------------------------------------------------------------------------
//
void CInkAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknAppUi::HandleResourceChangeL( aType );
    }

// End of File
