/* ====================================================================
 * File: Scorekeeper.cpp
 * Created: 03/20/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Scorekeeper.h"

// CONSTANTS
const TInt KNoLocalHighScore = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CEventControl::NewL
// ----------------------------------------------------------------------------
//
CScorekeeper* CScorekeeper::NewL()
    {
    CScorekeeper* self = new (ELeave) CScorekeeper;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::~CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::~CScorekeeper()
    {
    }

// ----------------------------------------------------------------------------
// CScorekeeper::SetHighScoreL
// ----------------------------------------------------------------------------
//
void CScorekeeper::SetHighScoreL( TInt aHighScore )
    {
    if ( aHighScore > iHighScore  )
        {
        iHighScore = aHighScore;
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::HighScore
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::HighScore() const
    {
    return iHighScore;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::NoLocalHighScore
// ----------------------------------------------------------------------------
//
TBool CScorekeeper::NoLocalHighScore() const
    {
    return ( iHighScore > KNoLocalHighScore ? EFalse : ETrue ); 
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ConstructL
// ----------------------------------------------------------------------------
//
void CScorekeeper::ConstructL()
    {
    }

// ----------------------------------------------------------------------------
// CScorekeeper::CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::CScorekeeper()
    { // no implementation required
    }

// End of File
