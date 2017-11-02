/* ====================================================================
 * File: ResReader.h
 * Created: 03/20/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_RESREADER_H
#define C_RESREADER_H

// INCLUDE FILES
#include <e32base.h>

// FORWARD DECLARATIONS
class RFs;

// CLASS DECLARATION

/**
* MResReader class
*
* @since S60 5.0
*/
class MResReader
    {
public: // interface functions
    virtual HBufC8* ResourceData( TInt aResId ) = 0;
    };

/**
 * CResReader class
 *
 * @since S60 5.0
 */

class CResReader : public CBase, public MResReader
    {
public: // Constructor and destructor
    static CResReader* NewL( RFs& aFs, TFileName aFileName );
    virtual ~CResReader();

public: // from MResReader
    HBufC8* ResourceData( TInt aResId );

protected: // Constructor
    CResReader( RFs& aFs, TFileName aFileName );
    void ConstructL();

private: // Data
    RFs& iFs;
    TFileName iFileName;
    HBufC8* iResData; // Own.
    };

#endif // C_RESREADER_H

// End of file
