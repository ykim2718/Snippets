#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "yCore.h"

static char qErrorMessage[1024]={0}; /* 20030317 */

void errWarning( qMessage )
   const char *qMessage;
{
   fprintf(stderr,"Warning, %s\n",qMessage);
   strncpy(qErrorMessage,qMessage,sizeof(qErrorMessage)); /* 20030317 */
}

void errExit( qMessage )
   const char *qMessage;
{
   fprintf(stderr,"Error, %s\n",qMessage);
   exit(1);
}

const char *errMessage()
{
   return qErrorMessage;
}
