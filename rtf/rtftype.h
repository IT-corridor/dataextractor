#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define fTrue 1
#define fFalse 0

typedef struct char_prop
{
    char fBold;
    char fUnderline;
    char fItalic;
} CHP;                  // Character Properties

typedef enum {justL, justR, justC, justF } JUST;
typedef struct para_prop
{
    int xaLeft;                 // left indent in twips
    int xaRight;                // right indent in twips
    int xaFirst;                // first line indent in twips
    JUST just;                  // justification
} PAP;                  // Paragraph Properties

typedef enum {sbkNon, sbkCol, sbkEvn, sbkOdd, sbkPg} SBK;
typedef enum {pgDec, pgURom, pgLRom, pgULtr, pgLLtr} PGN;
typedef struct sect_prop
{
    int cCols;                  // number of columns
    SBK sbk;                    // section break type
    int xaPgn;                  // x position of page number in twips
    int yaPgn;                  // y position of page number in twips
    PGN pgnFormat;              // how the page number is formatted
} SEP;                  // Section Properties
typedef struct doc_prop
{
    int xaPage;                 // page width in twips
    int yaPage;                 // page height in twips
    int xaLeft;                 // left margin in twips
    int yaTop;                  // top margin in twips
    int xaRight;                // right margin in twips
    int yaBottom;               // bottom margin in twips
    int pgnStart;               // starting page number in twips
    char fFacingp;              // facing pages enabled?
    char fLandscape;            // landscape or portrait?
} DOP;                  // Document Properties

typedef enum { rdsNorm, rdsSkip } RDS;              // Rtf Destination State
typedef enum { risNorm, risBin, risHex } RIS;       // Rtf Internal State

typedef struct save             // property save structure
{
    struct save *pNext;         // next save
    CHP chp;
    PAP pap;
    SEP sep;
    DOP dop;
    RDS rds;
    RIS ris;
} SAVE;

// What types of properties are there?
typedef enum {ipropBold, ipropItalic, ipropUnderline, ipropLeftInd,
              ipropRightInd, ipropFirstInd, ipropCols, ipropPgnX,
              ipropPgnY, ipropXaPage, ipropYaPage, ipropXaLeft,
              ipropXaRight, ipropYaTop, ipropYaBottom, ipropPgnStart,
              ipropSbk, ipropPgnFormat, ipropFacingp, ipropLandscape,
              ipropJust, ipropPard, ipropPlain, ipropSectd,
              ipropMax } IPROP;

typedef enum {actnSpec, actnByte, actnWord} ACTN;
typedef enum {propChp, propPap, propSep, propDop} PROPTYPE;

typedef struct propmod
{
    ACTN actn;              // size of value
    PROPTYPE prop;          // structure containing value
    int  offset;            // offset of value from base of structure
} PROP;

typedef enum {ipfnBin, ipfnHex, ipfnSkipDest } IPFN;
typedef enum {idestPict, idestSkip } IDEST;
typedef enum {kwdChar, kwdDest, kwdProp, kwdSpec} KWD;
typedef struct symbol
{
    char *szKeyword;        // RTF keyword
    int  dflt;              // default value to use
    char fPassDflt;         // true to use default value from this table
    KWD  kwd;               // base action to take
    int  idx;               // index into property table if kwd == kwdProp
                            // index into destination table if kwd == kwdDest
                            // character to print if kwd == kwdChar
} SYM;
