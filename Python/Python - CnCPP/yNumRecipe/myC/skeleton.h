/******************************************************************************/
/*                           file name : skeleton.h                           */
/*                    descriptive name : skeleton font header                 */
/*                         environment : SUN UNIX 4.0.3                       */
/*                            compiler : cc                                   */
/*                            producer : kim, yong shik                       */
/*                             version : 1.0                                  */
/*                                                                            */
/*                             43250408-43250408                              */
/******************************************************************************/

#ifndef skeleton_font_header_INSTALLED
#define skeleton_font_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"

typedef union {
   struct {
          unsigned int att  : 2;
          unsigned int row  : 7; /* 128 */
          unsigned int col  : 7; /* 128 */
          } part;
   struct {
          unsigned int word : 16;
          } whole;
} SKELETON_FONT;

/******************************************************************************/

/* unsigned int SKELETONFONT[][]; */

/******************************************************************************/
#endif /* skeleton.h */
