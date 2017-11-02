/* ====================================================================
 * File: InkdotFactory.h
 * Created: 03/22/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKDOTFACTORY_H
#define C_INKDOTFACTORY_H

// INCLUDS
#include <e32base.h>
#include "Inkdot.hrh"

// FORWARD DECLARATIONS
class CInkdot;
class CCanvas;

class CInkdotFactory : public CBase
    {
public: 
    // Enums
    enum TFactoryMode
            {
            EUnsplashInkdot, // samll inkdot
            ESplashInkdot // big inkdot
            };
 
public: // Constructors and destructor
    static CInkdotFactory* NewL( CCanvas& aCanvas );
    virtual ~CInkdotFactory();

public:
    // New methods
    void CreateL( RPointerArray<CInkdot>& aInkdots, TInt aCount );
    void SetFactoryMode( TFactoryMode aMode );

private:
    void ConstructL();
    CInkdotFactory( CCanvas& aCanvas  );

private:
    TInt Rand( TInt aRange ) const;
    void ConstructConfigurationL( TResourceReader& aReader );
    TInt Find( TInkdotType aType, TInt& aScore );
    TInt Radius() const;

private: 
    // - Inner class - //
    class CInkdotConfiguration : public CBase
        {
public: // Constructors and destructor
        static CInkdotConfiguration* NewL( TResourceReader& aReader );
        virtual ~CInkdotConfiguration();
public: // New methods
        TInkdotType Type() const;
        TInt Score() const;
private:
        void ConstructL( TResourceReader& aReader );
        CInkdotConfiguration();
private: // Data
        TInkdotType iType;
        TInt iScore;
        };

private: // Data
    CCanvas& iCanvas;
    CCoeEnv& iCoeEnv;
    RPointerArray<CInkdotConfiguration> iConfigurationList;
    TFactoryMode iMode;
    TInt iResFileOffset;
    };

#endif // C_INKDOTFACTORY_H

// End of File
