/* ====================================================================
 * File: InkLevel.cpp
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

// INCLUDS 
#include <barsread.h>
#include <Ink.rsg>
#include "InkLevel.h"

// CONSTANS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInkLevel::NewL
// ----------------------------------------------------------------------------
//
CInkLevel* CInkLevel::NewL( TResourceReader& aReader )
    {
    CInkLevel* self = new (ELeave) CInkLevel;
    CleanupStack::PushL(self);
    self->ConstructL(aReader);
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CInkLevel::~CInkLevel
// ----------------------------------------------------------------------------
//
CInkLevel::~CInkLevel()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CInkLevel::Id
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Id() const
    {
    return iId;
    }

// ----------------------------------------------------------------------------
// CInkLevel::Count
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Count() const
    {
    return iCount;
    }

// ----------------------------------------------------------------------------
// CInkLevel::Pass
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Pass() const
    {
    return iPass;
    }

// ----------------------------------------------------------------------------
// CInkLevel::Bonus
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Bonus() const
    {
    return iBonus;
    }

// ----------------------------------------------------------------------------
// CInkLevel::Timeout
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Timeout() const
    {
    return iTimeout;
    }

// ----------------------------------------------------------------------------
// CInkLevel::Compare
// ----------------------------------------------------------------------------
//
TInt CInkLevel::Compare( const CInkLevel& aFirst, const CInkLevel& aSecond )
    {
     if ( aFirst.Id() > aSecond.Id() )
      return 1; 
     if ( aFirst.Id() < aSecond.Id() )
      return -1;
    return 0;
    }

// ----------------------------------------------------------------------------
// CInkLevel::ConstructL
// ----------------------------------------------------------------------------
//
void CInkLevel::ConstructL( TResourceReader& aReader )
    {
    iId = aReader.ReadUint32();
    iCount = aReader.ReadUint32();
    iPass = aReader.ReadUint32();
    iBonus = aReader.ReadUint32();
    iTimeout = aReader.ReadUint32();
    }

// ----------------------------------------------------------------------------
// CInkLevel::CInkLevel
// ----------------------------------------------------------------------------
//
CInkLevel::CInkLevel()
    { // no implementation required
    }

// End of File
