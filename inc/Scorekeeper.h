/* ====================================================================
 * File: Scorekeeper.h
 * Created: 03/20/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREKEEPER_H
#define C_SCOREKEEPER_H

// INCLUDS
#include <e32base.h>

// FORWARD DECLARATIONS

class CScorekeeper : public CBase
    {
public:
    static CScorekeeper* NewL();
    virtual ~CScorekeeper();

public: // New functions
    void SetHighScoreL( TInt aHighScore );
    TInt HighScore() const;
    TBool NoLocalHighScore() const;

private: // Constructor
    void ConstructL();
    CScorekeeper();

private: // Data
    TInt iHighScore;
    };

#endif // C_SCOREKEEPER_H

// End of File
