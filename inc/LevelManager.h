/* ====================================================================
 * File: LevelManager.h
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LEVELMANAGER_H
#define C_LEVELMANAGER_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CCoeEnv;
class CInkLevel;
class MLevelObserver;

class CLevelManager : public CBase
    {
public: // Symbian 2nd phase constructor and destructor
    static CLevelManager* NewL( MLevelObserver& aObserver );
    virtual ~CLevelManager();

public: // New methods
    TInt Id() const;
    TInt Count() const;
    TInt Pass() const;
    TInt Bonus() const;
    TInt Timeout() const;
    TInt NextL();
    void Reset();

private:
    void ConstructL();
    CLevelManager( MLevelObserver& aObserver );

private:
    void ReadLevelL( TResourceReader& aReader );
    void Sort();

private: // Data
    CCoeEnv& iCoeEnv;
    MLevelObserver& iObserver;
    RPointerArray<CInkLevel> iLevelList;
    TInt iCurrentLevel;
    TInt iResFileOffset;
    };

#endif // C_LEVELMANAGER_H

// End of File
