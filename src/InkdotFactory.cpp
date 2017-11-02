/* ====================================================================
 * File: InkdotFactory.cpp
 * Created: 03/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include <e32math.h>
#include <Ink.rsg>
#include "InkdotFactory.h"
#include "Ink.pan"
#include "Inkdot.h"
#include "InkdotConstants.h"
#include "LayoutManager.h"
#include "InkdotConstants.h"

// CONSTANTS
_LIT( KInkResourceFile, "\\resource\\apps\\ink.rsc" );
const TInt KDefaultScore = 100;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkdotFactory::NewL
// Standard Symbian OS construction sequence
// ----------------------------------------------------------------------------
//
CInkdotFactory* CInkdotFactory::NewL( CCanvas& aCanvas )
    {
    CInkdotFactory* self = new (ELeave) CInkdotFactory( aCanvas );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::~CInkdotFactory
// ----------------------------------------------------------------------------
//
CInkdotFactory::~CInkdotFactory()
    {
    iConfigurationList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CreateL
// ----------------------------------------------------------------------------
//
void CInkdotFactory::CreateL( RPointerArray<CInkdot>& aInkdots, TInt aCount )
    {
    CLayoutManager* layout = CLayoutManager::NewL();
    CleanupStack::PushL ( layout  );
    
    TRect theRect;
    layout->LayoutRect( ECanvas, theRect );

    CleanupStack::Pop( layout );
    delete layout;
    layout = NULL;

    for ( TInt i = 0; i < aCount; i++ )
        {
        TInkdotType type = ( TInkdotType )( Rand( EInkdotLastElement - 1 ) + 1 );
        TInt x = Rand( theRect.Width() - 2 * Radius() ) + Radius();
        TInt y = Rand( theRect.Height() - 2 * Radius() ) + Radius();
        TInt score( 0 );
        TRAPD( err, Find( type, score ) );
        if ( err != KErrNone ) {
            __ASSERT_DEBUG( err == KErrNone, Panic( EInkLackConfiguration ) );
            score = KDefaultScore;
            }

        TInkdotData inkdotData;
        inkdotData.SetType( type );
        inkdotData.SetXY( x, y );

        CInkdot* inkdot = CInkdot::NewL( iCanvas, inkdotData );
        inkdot->SetScore( score );
        aInkdots.Append( inkdot );
        }

    }

// ----------------------------------------------------------------------------
// CInkdotFactory::SetFactoryMode
// ----------------------------------------------------------------------------
//
void CInkdotFactory::SetFactoryMode( TFactoryMode aMode )
    {
    iMode = aMode;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CInkdotFactory::ConstructL()
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
    iCoeEnv.CreateResourceReaderLC( reader, R_INK_INKDOT_CONFIGURATION_LIST );

    TRAP( err, ConstructConfigurationL( reader ) );
    if ( err )
        {
        iConfigurationList.ResetAndDestroy();
        User::Leave( err );
        }

    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( iResFileOffset );
    iResFileOffset = 0;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotFactory
// ----------------------------------------------------------------------------
//
CInkdotFactory::CInkdotFactory( CCanvas& aCanvas  )
    : iCanvas( aCanvas ), iCoeEnv( *CCoeEnv::Static() )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::Rand
// ----------------------------------------------------------------------------
//
TInt CInkdotFactory::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::ConstructConfigurationL
// ----------------------------------------------------------------------------
//
void CInkdotFactory::ConstructConfigurationL( TResourceReader& aReader )
    {
    TInt num = aReader.ReadInt16();

    // Add all newly created CInkLevel objects to the array
    for ( TInt ix = 0; ix < num; ix++ )
        {
        CInkdotConfiguration* inkdotConfig = CInkdotConfiguration::NewL( aReader );
        iConfigurationList.Append( inkdotConfig );
        }
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::Find
// ----------------------------------------------------------------------------
//
TInt CInkdotFactory::Find( TInkdotType aType, TInt& aScore )
    {
    TBool err ( KErrNotFound );
    for ( TInt i = 0; i < iConfigurationList.Count(); i++ )
        {
        if ( iConfigurationList[ i ]->Type() == aType )
            {
            aScore = iConfigurationList[ i ]->Score();
            err = KErrNone;
            break;
            }
        }
    return err;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::Radius
// ----------------------------------------------------------------------------
//
TInt CInkdotFactory::Radius() const
    {
    TInt radius( 0 );
    switch ( iMode )
        {
        case ESplashInkdot:
            radius = KMaxInkdotRadius;
            break;
        case EUnsplashInkdot:
            radius = KMinInkdotRadius;
            break;
        default:
            break;
        }
    return radius;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::NewL
// ----------------------------------------------------------------------------
//
CInkdotFactory::CInkdotConfiguration* CInkdotFactory::CInkdotConfiguration::NewL( 
    TResourceReader& aReader )
    {
    CInkdotConfiguration* self = new (ELeave) CInkdotConfiguration;
    CleanupStack::PushL( self );
    self->ConstructL( aReader );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::~CInkdotConfiguration
// ----------------------------------------------------------------------------
//
CInkdotFactory::CInkdotConfiguration::~CInkdotConfiguration()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::Type
// ----------------------------------------------------------------------------
//
TInkdotType CInkdotFactory::CInkdotConfiguration::Type() const
    {
    return iType;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::Score
// ----------------------------------------------------------------------------
//
TInt CInkdotFactory::CInkdotConfiguration::Score() const
    {
    return iScore;
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::ConstructL
// ----------------------------------------------------------------------------
//
void CInkdotFactory::CInkdotConfiguration::ConstructL( TResourceReader& aReader )
    {
    iType = ( TInkdotType )aReader.ReadUint32();
    iScore = aReader.ReadUint32();
    }

// ----------------------------------------------------------------------------
// CInkdotFactory::CInkdotConfiguration::CInkdotConfiguration
// ----------------------------------------------------------------------------
//
CInkdotFactory::CInkdotConfiguration::CInkdotConfiguration()
    { // no implementation required
    }

// End of file
