/******************************************************************************/
/*                           file name : gefont.h                             */
/*                    descriptive name : Graphic Engine Font Module           */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                                                                            */
/*                        created date : 43250409-43250409                    */
/*                        updated date : 06/01/93                             */
/*                                       ....                                 */
/*                        updated date : 43300831                             */
/*                        updated date : 43320303-0431                        */
/*                                                                            */
/******************************************************************************/
#ifndef gefont_header_INSTALLED
#define gefont_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"
#include "blob.h"
#include "gecore.h"

/******************************************************************************/

typedef union {
   struct {
#if defined(_UNIXC_) || defined(_HP715C_)
          unsigned int row1 : 4;
          unsigned int col1 : 4;
          unsigned int row2 : 4;
          unsigned int col2 : 4;
#elif defined(_MSC_)
          unsigned int col1 : 4;
          unsigned int row1 : 4;
          unsigned int col2 : 4;
          unsigned int row2 : 4;
#else
#error Compiler type (_UNIXC_/_HP715C_/_MSC_/..) must be defined.
#endif
          } part;
   struct {
          unsigned int word : 16;
          } whole;
} GESTROKEFONT;

extern unsigned int STROKEFONT[128][36];

/*----------------------------------------------------------------------------*/

int GESetFontMatrixDefault _(());
int GESetFontMatrix _((BLOB2DMDATA *ptr));
int GEGetFontMatrix _((BLOB2DMDATA *ptr));
int GESetFontScale _((double scale));
int GESetStrokeTextFormat _((int format));
int myDrawTextStroke (); //_((MYDISPNODE *,double,double,char*));

/******************************************************************************/
#endif /* gefont.h */


