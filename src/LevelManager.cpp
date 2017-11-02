/* ====================================================================
 * File: LevelManager.cpp
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include <Ink.rsg>
#include "LevelManager.h"
#include "LevelObserver.h"
#include "InkLevel.h"

// CONSTANS
const TInt KDefaultLevel = 0;
_LIT( KInkResourceFile, "\\resource\\apps\\ink.rsc" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CLevelManager::NewL
// ----------------------------------------------------------------------------
//
CLevelManager* CLevelManager::NewL( MLevelObserver& aObserver )
    {
    CLevelManager* self = new (ELeave) CLevelManager( aObserver );
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CLevelManager::~CLevelManager
// ----------------------------------------------------------------------------
//
CLevelManager::~CLevelManager()
    {
    iLevelList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Id
// ----------------------------------------------------------------------------
//
TInt CLevelManager::Id() const
    {
    return iLevelList[ iCurrentLevel ]->Id();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Count
// ----------------------------------------------------------------------------
//
TInt CLevelManager::Count() const
    {
    return iLevelList[ iCurrentLevel ]->Count();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Pass
// ----------------------------------------------------------------------------
//
TInt CLevelManager::Pass() const
    {
    return iLevelList[ iCurrentLevel ]->Pass();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Bonus
// ----------------------------------------------------------------------------
//
TInt CLevelManager::Bonus() const
    {
    return iLevelList[ iCurrentLevel ]->Bonus();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Timeout
// ----------------------------------------------------------------------------
//
TInt CLevelManager::Timeout() const
    {
    return iLevelList[ iCurrentLevel ]->Timeout();
    }

// ----------------------------------------------------------------------------
// CLevelManager::NextL
// ----------------------------------------------------------------------------
//
TInt CLevelManager::NextL()
    {
    TInt err( KErrNone );
    if ( iCurrentLevel + 1 < iLevelList.Count() )
        {
        iCurrentLevel++;
        }
    else
        {
        iObserver.GameOverL();
        err = KErrCompletion;
        }
    return err;
    }

// ----------------------------------------------------------------------------
// CLevelManager::Reset
// ----------------------------------------------------------------------------
//
void CLevelManager::Reset()
    {
    iCurrentLevel = KDefaultLevel;
    }

// ----------------------------------------------------------------------------
// CLevelManager::ConstructL
// ----------------------------------------------------------------------------
//
void CLevelManager::ConstructL()
    {
    RFs& fs = iCoeEnv.FsSession();
    TFileName fileName( KInkResourceFile );
    TInt err = CompleteWithAppPath( fileName );
    if ( err != KErrNotSupported )
        {
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fs, fileName );
    
    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fs, fileName ) )
        {
        User::Leave( KErrNotFound );
        }

    TRAP( err, iResFileOffset = iCoeEnv.AddResourceFileL( fileName ) );

    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, R_INK_LEVELS );

    TRAP( err, ReadLevelL( reader ) );
    if ( err )
        {
        iLevelList.ResetAndDestroy();
        User::Leave( err );
        }

    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( iResFileOffset );
    iResFileOffset = 0;
    
    iCurrentLevel = KDefaultLevel;
    }

// ----------------------------------------------------------------------------
// CLevelManager::CLevelManager
// ----------------------------------------------------------------------------
//
CLevelManager::CLevelManager( MLevelObserver& aObserver )
    : iCoeEnv( *CCoeEnv::Static() ), iObserver( aObserver )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CLevelManager::ReadLevelL
// ----------------------------------------------------------------------------
//
void CLevelManager::ReadLevelL( TResourceReader& aReader )
    {
    TInt num = aReader.ReadInt16();

    // Add all newly created CInkLevel objects to the array
    for ( TInt ix = 0; ix < num; ix++ )
        {
        CInkLevel* level = CInkLevel::NewL( aReader );
        iLevelList.Append( level );
        }
    // Sorts these levels by id
    Sort();
    }

// ----------------------------------------------------------------------------
// CLevelManager::Sort
// ----------------------------------------------------------------------------
//
void CLevelManager::Sort()
    {
    TLinearOrder<CInkLevel> order( CInkLevel::Compare );
    iLevelList.Sort( order );
    }

// End of File
