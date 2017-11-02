/* ====================================================================
 * File: LayoutValues.h
 * Created: 03/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef LAYOUTVALUES_H
#define LAYOUTVALUES_H

// INCLUDE FILES
#include <avkon.hrh>

/////////////////////////////////////////////////////////////////////////////
//
// SUPPORTED UI RESOLUTIONS ARE:
//
// QVGA RESOLUTION PORTRAIT     360 x 640
// QVGA RESOLUTION LANDSCAPE    640 x 360
//
////////////////////////////////////////////////////////////////////////////

// Supported screen resolutions
enum TResolution
    {
    EQvgaPortrait,
    EQvgaLandscape,
    ENotSupported
    };

// Supported screen orientation
enum TOrientation
    {
    EAutomatic,
    EPortrait,
    ELandscape
    };

// Component enumerations
enum TComponent
    {
    EScreen = 0, // welcome view
    ECanvas, 
    EInkTitle,
    EStartButton,
    EBackButton,
    EWebButton,
    EQuitButton,
    EHighScore,
    ECurrentLevel,
    ECurrentScore,
    ETooltip,
    EResultInfo
    };

/////////////////////////////////////////////////////////////////////////////
//
// SCALLOP COMPONENTS VALUES
//
/////////////////////////////////////////////////////////////////////////////

static const TInt KQvgaLandscapeWidth = 640;
static const TInt KQvgaLandscapeHeight = 360;
static const TInt KQvgaPortraitWidth = 360;
static const TInt KQvgaPortraitHeight = 640;

// Screen
static const TInt KQvgaLscScreenLeft = 0;
static const TInt KQvgaLscScreenTop = 0;
static const TInt KQvgaLscScreenRight = 640;
static const TInt KQvgaLscScreenBottom = 360;
static const TInt KQvgaLscScreenWidth = 640;
static const TInt KQvgaLscScreenHeight = 360;

static const TInt KQvgaPrtScreenLeft = 0;
static const TInt KQvgaPrtScreenTop = 0;
static const TInt KQvgaPrtScreenRight = 360;
static const TInt KQvgaPrtScreenBottom = 640;
static const TInt KQvgaPrtScreenWidth = 360;
static const TInt KQvgaPrtScreenHeight = 640;


// Canvas
static const TInt KQvgaLscCanvasLeft = 0;
static const TInt KQvgaLscCanvasTop = 0;
static const TInt KQvgaLscCanvasRight = 640;
static const TInt KQvgaLscCanvasBottom = 360;
static const TInt KQvgaLscCanvasWidth = 640;
static const TInt KQvgaLscCanvasHeight = 360;

static const TInt KQvgaPrtCanvasLeft = 0;
static const TInt KQvgaPrtCanvasTop = 0;
static const TInt KQvgaPrtCanvasRight = 360;
static const TInt KQvgaPrtCanvasBottom = 640;
static const TInt KQvgaPrtCanvasWidth = 360;
static const TInt KQvgaPrtCanvasHeight = 640;


// InkTitle
static const TInt KQvgaLscInkTitleLeft = 240;
static const TInt KQvgaLscInkTitleTop = 50;
static const TInt KQvgaLscInkTitleRight = 375;
static const TInt KQvgaLscInkTitleBottom = 140;
static const TInt KQvgaLscInkTitleWidth = 135;
static const TInt KQvgaLscInkTitleHeight = 90;

static const TInt KQvgaPrtInkTitleLeft = 100;
static const TInt KQvgaPrtInkTitleTop = 100;
static const TInt KQvgaPrtInkTitleRight = 235;
static const TInt KQvgaPrtInkTitleBottom = 190;
static const TInt KQvgaPrtInkTitleWidth = 135;
static const TInt KQvgaPrtInkTitleHeight = 90;


// StartButton
static const TInt KQvgaLscStartButtonLeft = 236;
static const TInt KQvgaLscStartButtonTop = 160;
static const TInt KQvgaLscStartButtonRight = 404;
static const TInt KQvgaLscStartButtonBottom = 212;
static const TInt KQvgaLscStartButtonWidth = 168;
static const TInt KQvgaLscStartButtonHeight = 52;

static const TInt KQvgaPrtStartButtonLeft = 96;
static const TInt KQvgaPrtStartButtonTop = 250;
static const TInt KQvgaPrtStartButtonRight = 264;
static const TInt KQvgaPrtStartButtonBottom = 302;
static const TInt KQvgaPrtStartButtonWidth = 168;
static const TInt KQvgaPrtStartButtonHeight = 52;


// BackButton
static const TInt KQvgaLscBackButtonLeft = 585;
static const TInt KQvgaLscBackButtonTop = 305;
static const TInt KQvgaLscBackButtonRight = 635;
static const TInt KQvgaLscBackButtonBottom = 355;
static const TInt KQvgaLscBackButtonWidth = 50;
static const TInt KQvgaLscBackButtonHeight = 50;

static const TInt KQvgaPrtBackButtonLeft = 305;
static const TInt KQvgaPrtBackButtonTop = 585;
static const TInt KQvgaPrtBackButtonRight = 355;
static const TInt KQvgaPrtBackButtonBottom = 635;
static const TInt KQvgaPrtBackButtonWidth = 50;
static const TInt KQvgaPrtBackButtonHeight = 50;


// WebButton
static const TInt KQvgaLscWebButtonLeft = 5;
static const TInt KQvgaLscWebButtonTop = 305;
static const TInt KQvgaLscWebButtonRight = 55;
static const TInt KQvgaLscWebButtonBottom = 355;
static const TInt KQvgaLscWebButtonWidth = 50;
static const TInt KQvgaLscWebButtonHeight = 50;

static const TInt KQvgaPrtWebButtonLeft = 5;
static const TInt KQvgaPrtWebButtonTop = 585;
static const TInt KQvgaPrtWebButtonRight = 55;
static const TInt KQvgaPrtWebButtonBottom = 635;
static const TInt KQvgaPrtWebButtonWidth = 50;
static const TInt KQvgaPrtWebButtonHeight = 50;


// QuitButton
static const TInt KQvgaLscQuitButtonLeft = 585;
static const TInt KQvgaLscQuitButtonTop = 305;
static const TInt KQvgaLscQuitButtonRight = 635;
static const TInt KQvgaLscQuitButtonBottom = 355;
static const TInt KQvgaLscQuitButtonWidth = 50;
static const TInt KQvgaLscQuitButtonHeight = 50;

static const TInt KQvgaPrtQuitButtonLeft = 305;
static const TInt KQvgaPrtQuitButtonTop = 585;
static const TInt KQvgaPrtQuitButtonRight = 355;
static const TInt KQvgaPrtQuitButtonBottom = 635;
static const TInt KQvgaPrtQuitButtonWidth = 50;
static const TInt KQvgaPrtQuitButtonHeight = 50;

// HighScore
static const TInt KQvgaLscHighScoreLeft = 255;
static const TInt KQvgaLscHighScoreTop = 325;
static const TInt KQvgaLscHighScoreRight = 385;
static const TInt KQvgaLscHighScoreBottom = 355;
static const TInt KQvgaLscHighScoreWidth = 130;
static const TInt KQvgaLscHighScoreHeight = 30;

static const TInt KQvgaPrtHighScoreLeft = 90;
static const TInt KQvgaPrtHighScoreTop = 605;
static const TInt KQvgaPrtHighScoreRight = 270;
static const TInt KQvgaPrtHighScoreBottom = 635;
static const TInt KQvgaPrtHighScoreWidth = 180;
static const TInt KQvgaPrtHighScoreHeight = 30;


// CurrentLevel
static const TInt KQvgaLscCurrentLevelLeft = 0;
static const TInt KQvgaLscCurrentLevelTop = 0;
static const TInt KQvgaLscCurrentLevelRight = 50;
static const TInt KQvgaLscCurrentLevelBottom = 30;
static const TInt KQvgaLscCurrentLevelWidth = 50;
static const TInt KQvgaLscCurrentLevelHeight = 30;

static const TInt KQvgaPrtCurrentLevelLeft = 0;
static const TInt KQvgaPrtCurrentLevelTop = 0;
static const TInt KQvgaPrtCurrentLevelRight = 50;
static const TInt KQvgaPrtCurrentLevelBottom = 30;
static const TInt KQvgaPrtCurrentLevelWidth = 50;
static const TInt KQvgaPrtCurrentLevelHeight = 30;

// CurrentScore
static const TInt KQvgaLscCurrentScoreLeft = 0;
static const TInt KQvgaLscCurrentScoreTop = 330;
static const TInt KQvgaLscCurrentScoreRight = 30;
static const TInt KQvgaLscCurrentScoreBottom = 360;
static const TInt KQvgaLscCurrentScoreWidth = 30;
static const TInt KQvgaLscCurrentScoreHeight = 30;

static const TInt KQvgaPrtCurrentScoreLeft = 0;
static const TInt KQvgaPrtCurrentScoreTop = 610;
static const TInt KQvgaPrtCurrentScoreRight = 80;
static const TInt KQvgaPrtCurrentScoreBottom = 640;
static const TInt KQvgaPrtCurrentScoreWidth = 80;
static const TInt KQvgaPrtCurrentScoreHeight = 30;


// Tooltip
static const TInt KQvgaLscTooltipLeft = 510;
static const TInt KQvgaLscTooltipTop = 0;
static const TInt KQvgaLscTooltipRight = 640;
static const TInt KQvgaLscTooltipBottom = 30;
static const TInt KQvgaLscTooltipWidth = 130;
static const TInt KQvgaLscTooltipHeight = 30;

static const TInt KQvgaPrtTooltipLeft = 180;
static const TInt KQvgaPrtTooltipTop = 0;
static const TInt KQvgaPrtTooltipRight = 360;
static const TInt KQvgaPrtTooltipBottom = 30;
static const TInt KQvgaPrtTooltipWidth = 180;
static const TInt KQvgaPrtTooltipHeight = 30;


// ResultInfo
static const TInt KQvgaLscResultInfoLeft = 220;
static const TInt KQvgaLscResultInfoTop = 150;
static const TInt KQvgaLscResultInfoRight = 420;
static const TInt KQvgaLscResultInfoBottom = 210;
static const TInt KQvgaLscResultInfoWidth = 200;
static const TInt KQvgaLscResultInfoHeight = 60;

static const TInt KQvgaPrtResultInfoLeft = 80;
static const TInt KQvgaPrtResultInfoTop = 300;
static const TInt KQvgaPrtResultInfoRight = 280;
static const TInt KQvgaPrtResultInfoBottom = 360;
static const TInt KQvgaPrtResultInfoWidth = 200;
static const TInt KQvgaPrtResultInfoHeight = 60;


#endif // LAYOUTVALUES_H

// End of File
