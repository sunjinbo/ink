/* ====================================================================
 * File: InkLevel.h
 * Created: 03/08/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INKLEVEL_H
#define C_INKLEVEL_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS
class TResourceReader;

class CInkLevel : public CBase
    {
public:
    static CInkLevel* NewL( TResourceReader& aReader );
    virtual ~CInkLevel();

public: // New functions
    TInt Id() const;
    TInt Count() const;
    TInt Pass() const;
    TInt Bonus() const;
    TInt Timeout() const;
    static TInt Compare( const CInkLevel& aFirst, const CInkLevel& aSecond );

private:
    void ConstructL( TResourceReader& aReader );
    CInkLevel();

private: // Data
    TInt iId;
    TInt iCount;
    TInt iPass;
    TInt iBonus;
    TInt iTimeout;
    };

#endif // C_INKLEVEL_H

// End of File
