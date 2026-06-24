/******************************************************************************/
/*                           file name : geprint.h                            */
/*                    descriptive name : Graphic Engine (BLOB) PRINT Module   */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                             version : 1.0                                  */
/*                       creating date : 43241116-43250310                    */
/*                         update date : 43260519-43260519                    */
/*                         update date : 930802                               */
/*                         update date : 950525                               */
/*                         update date : 970307,0829-0831                     */
/*                         update date : 43330222-0309                        */
/*                                                                            */
/******************************************************************************/

#ifndef geprint_header_INSTALLED
#define geprint_header_INSTALLED 1

/******************************************************************************/

typedef enum {
   GE_PSColor,         /* color */
   GE_PSGray,          /* gray scale */
   GE_PSBlackAndWhite, /* black and white */
   GE_PSEncapsulated,
   GE_HPGL2,
   GE_PCL5,
   GE_DOT
} GEPRINTTYPE;

typedef enum {
   GE_Landscape,GE_Portrait
} GEPRINTDIRECTION;

typedef enum {
   GE_PageA4=0,GE_PageA4Small,GE_PageLetter
} GEPAGETYPE;

/******************************************************************************/

int GEPrintOpen();
int GEPrintClose();
int GEPrintSetProcedure();
int GEPrintProcess();

int GEPSFdumpWindow();

int GEPrintBlobAsText();

/******************************************************************************/
#endif /* geprint.h */
