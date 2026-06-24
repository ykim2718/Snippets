/******************************************************************************/
/*                        module name : geplot.c                              */
/*                   descriptive name : Graphic Engine (BLOB) PLOT Module     */
/*                           compiler : cc                                    */
/*                        environment : X-Window                              */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                                                                            */
/*                       creating date : 43260812-43260902                    */
/*                         update date : 930902                               */
/*                         update date : 43290416,0417,0515,0521,0612         */
/*                         update date : 43300307                             */
/*                         update date : 43320304                             */
/*                         update date : 43320301-0331                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(_XnMOTIF_)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#endif

#include "myCore.h"
#include "myWindow.h"
#include "blob.h"
#include "any.h"
#include "gecore.h"
#include "geprint.h"
#include "geplot.h"
#include "number.h"

/******************************************************************************/

#define GESelectionName "GESelection"

/*----------------------------------------------------------------------------*/

       int GEPlotProcesser();           /* for Selection Requestor */

static int GEPlotOpen();                /* for Selection Requestor */
static int GEPlotClose();               /* for Selection Requestor */
static int GEPlotProcess();             /* for Selection Requestor */

       int GEPlotCommander();           /* for Selection Owner */

#define PacketSize 32768

static int GEAlloPacket();
static int GEFreePacket();
static int GEBLOBToPacket();            /* for Selection Owner */
static int GEPacketToBLOB();            /* for Selection Requestor */
static int GEBLOBProcess();             /* for Selection Requestor */
static int GEWindowMatrixChange();
static int GEPlotWindowKeyProcess();    /* for Selection Requestor */

       int SetPlotCommand();
       int ChkPlotCommand();

       int GEPlotWindowViewer();

/******************************************************************************/

int GEPlotProcesser( list )
   MYDISPLIST *list;
{
   if (!list)
      return FALSE;
   GEPlotOpen(list);
   GEPlotProcess(list);
   GEPlotClose();
   fprintf(stdout,"Echo, ... \"GEPlotProcesser()\" closed.\n");
   return TRUE;
}

static
int GEPlotOpen( list )
   MYDISPLIST *list;
{
   MYDISPNODE *dispNode;

   dispNode=list->head;
   while (dispNode) {
      GEWindowShow(dispNode,GECoreName,0,0,400,600); 
      dispNode=dispNode->next;
   }
#if defined(_XnMOTIF_)
   sleep(1);
#endif
   return TRUE;
}

static
int GEPlotClose()
{
   return TRUE;
}

static
int GEPlotProcess( displayList ) /* SelectionRequestor */
   MYDISPLIST *displayList;
{
#if defined(_XnMOTIF_)
   MYDISPNODE *displayNode;
   Display *display;
   Window window;
   Atom selection,atom;
   static GERECT geom;

   Atom ret_atom;
   int ret_format;
   unsigned long ret_len,ret_after;
   unsigned char *ret_prop;
   XEvent event;
   static int i=0;
   BLOBLIST *list,*ret_list;

   displayNode=displayList->head;
   while (displayNode) {
      XSelectInput(displayNode->display,displayNode->window,
                   KeyPressMask|ExposureMask|StructureNotifyMask);
      XFlush(displayNode->display);
      GECopyToBackingStore(displayNode);
      displayNode=displayNode->next;
   }

   display=displayList->head->display;
   window=displayList->head->window;
   selection=XInternAtom(display,GESelectionName,0);
   atom=XInternAtom(display,GECoreName,0);
   GEGetGeometry(displayList->head,&geom);

   BLOpenList(&list);
   XConvertSelection(display,selection,XA_CARDINAL,atom,window,0);

   while (1) {
      XPeekEvent(display,&event);
      if (event.type==SelectionNotify) {
         if (event.xselection.selection!=selection
         ||  event.xselection.target!=XA_CARDINAL
         ||  event.xselection.property!=atom) {
            XNextEvent(display,&event);
            XConvertSelection(display,selection,XA_CARDINAL,atom,window,0);
            if (i==1000) {
               printf("Echo, Too Many \"XConvertSelection()\" ");
               printf("from GEPlotProcess()\n");
               printf("Echo, \"GEPlotProcess()\" closed.\n");
               exit(1);
            }
            printf("Echo, \"XConvertSelection()\" trying ... %3d .. ",i++);
            printf("from GEPlotProcess\n");
            sleep(1);
         } else
            i=0;
      }
      displayNode=displayList->head;
      while (displayNode) {
/*
 ?
 */
         if (XEventsQueued(displayNode->display,QueuedAfterReading)<=0)
            goto n;
         XNextEvent(displayNode->display,&event);
         i=0;

         switch (event.type) {
            case SelectionNotify :
                 XGetWindowProperty(display,window,atom,
                                    0L,8192L,True,XA_CARDINAL,
                                    &ret_atom,&ret_format,&ret_len,&ret_after,
                                    &ret_prop);
                 if (ret_after)
                    errExit("ret_after!=0 in GEPlotProcess()");
                 GEPacketToBLOB(ret_prop,ret_len,&ret_list);
                 printf("Echo, *GEPacketToBLOB : %d !\n",ret_len);
                 if (!GEBLOBProcess(displayList,&list,ret_list)) {
                    XFree(ret_prop);
                    goto c;
                 }
                 XFree(ret_prop);
                 XConvertSelection(display,selection,XA_CARDINAL,atom,window,0);
                 break;
            case KeyPress :
                 switch (GEPlotWindowKeyProcess(displayNode,
                                                &geom,&event,list)) {
                    case  1 : GECopyToBackingStore(displayNode);break;
                    case -1 : break;
                 }
                 break;
            case Expose :
                 GECopyFromBackingStore(displayNode,&event);
                 break;
            case ConfigureNotify : 
                 GEGetGeometry(displayNode,&geom);
                 break;
         }
n:       displayNode=displayNode->next;
      }
   }

c: BLCloseList(list);
   return TRUE;
#elif defined(_MSWINDOW_)
   return TRUE;
#endif
}

int GEPlotCommander( display_name,list ) /* Selection Owner */
   char *display_name;
   BLOBLIST *list;
{
#if defined(_XnMOTIF_)
   Display *display;
   Window owner;
   Atom selection,atom;
   XEvent event,es;
   char *packet;
   int size;
   BLOBNODE *node;

   display=XOpenDisplay(display_name);
   if (!display)
      errExit("Display Environment in GEPlotCommander()");
   owner=RootWindow(display,0);
   selection=XInternAtom(display,GESelectionName,0);
   atom=XInternAtom(display,GECoreName,0);

   XSetSelectionOwner(display,selection,owner,0);
   if (owner!=XGetSelectionOwner(display,selection))
      errExit("XSetSelectionOwner() in GEPlotCommander()");

   printf("Echo, \"GEPlotCommander()\" open ...\n");
   GEAlloPacket(&packet);

   node=list->head;
   while (node) {
      XNextEvent(display,&event);
      switch (event.type) {
         case SelectionClear :
              printf("Echo, \"SelectionClear\" from GEPlotCommander()\n");
              exit(1);
         case SelectionRequest :
              if (event.xselectionrequest.selection!=selection
              ||  event.xselectionrequest.target!=XA_CARDINAL
              ||  event.xselectionrequest.property!=atom)
                  continue;
              es.type=SelectionNotify;
              es.xselection.requestor=event.xselectionrequest.requestor;
              es.xselection.selection=event.xselectionrequest.selection;
              es.xselection.target=event.xselectionrequest.target;
              es.xselection.property=event.xselectionrequest.property;
              es.xselection.time=event.xselectionrequest.time;
              GEBLOBToPacket(packet,&node,&size);
              printf("Echo, *GEBLOBToPacket : %d !\n",size);
              XChangeProperty(display,  
                              event.xselectionrequest.requestor,atom,
                              XA_CARDINAL,8,PropModeReplace,
                              packet,size);
              XSendEvent(display,event.xselectionrequest.requestor,0,0,&es);
              XFlush(display);
              break;
      }
   }

   GEFreePacket(packet);
   printf("Echo, \"GEPlotCommander()\" closed.\n");
   return TRUE;
#elif defined(_MSWINDOW_)
   return TRUE;
#endif
}

static
int GEAlloPacket( packet )
   char **packet;
{
   *packet=(char*)malloc(sizeof(char)*PacketSize);
   return TRUE;
}

static
int GEFreePacket( packet )
   char *packet;
{
   free(packet);
   return TRUE;
}

static
int GEBLOBToPacket( packet,node,size )
   char *packet;
   BLOBNODE **node;
   int *size;
{
   BLOBNODE *ptr;
   int node_size,cum_size=0;

   ptr=*node;
   while (ptr) {
      node_size=BLNodeTotalSize(ptr);
      if (cum_size+node_size>PacketSize)
         break;
      memcpy(packet,ptr,node_size);
      node_size+=my_aligner(node_size);
      packet+=node_size;
      cum_size+=node_size;
      ptr=ptr->next;
   }
   *node=ptr;
   *size=cum_size;
   return TRUE;
}

static
int GEPacketToBLOB( packet,packet_size,list )
   char *packet;
   int packet_size;
   BLOBLIST **list;
{
   BLOBNODE *ptr,*node;
   int node_size,cum_size=0;

   if (!packet)
      return FALSE;
   OpenAnyDLObject(list,sizeof(BLOBLIST));
   while (cum_size<packet_size) {
      ptr=(BLOBNODE*)packet;
      node_size=BLNodeTotalSize(ptr);
      node=(BLOBNODE*)malloc(node_size);
      memcpy(node,ptr,node_size);
      AddAnyDLObject(*list,node);
      node_size+=my_aligner(node_size);
      packet+=node_size;
      cum_size+=node_size;
   }
   return TRUE;
}

static
int GEBLOBProcess( displayList,list,ret_list )
   MYDISPLIST *displayList;
   BLOBLIST **list,*ret_list;
{
   BLOBNODE *node;
   char *ptr;
   static char CONTINUE=0;
   int cmd1,cmd2;
   char *name="GEPlot.psf";

   node=ret_list->head;
   while (node) {
      ptr=BLNodeObjAddr(node);
      if (node->any.type==BL_COMMAND) {
         ChkPlotCommand(ptr,&cmd1,&cmd2);
         switch ((GEPLOTCOMMANDTYPE)cmd1) {
            case GE_PlotPrint :
                 switch (cmd2) {
                    case 'L' : case 'l' :
                       GEprintOpen(name,GE_PSColor,GE_Landscape,0);
                       break;
                    case 'P' : case 'p' :
                       GEprintOpen(name,GE_PSColor,GE_Portrait,0);
                       break;
                 }
                 GEprintSetProcedure();
                 GEprintProcess(*list);
                 GEprintClose();
                 printf("\"%s\" written .....\n",name);
                 break;
            case GE_PlotOpen  :
                 if (CONTINUE) {
                    AddAnyDLObjects(*list,ret_list);
                    free(ret_list);
                 } else {
                    BLCloseList(*list);
                    *list=ret_list;
                 }
                 GEDrawOpen(displayList,GE_WinScaleByObject,NULL);
                 GEDrawSetProcedure(1);
                 break;
            case GE_PlotClose :
                 CONTINUE=0;
                 GEDrawClose();
                 break;
            case GE_PlotContinue :
                 CONTINUE=1;
                 GEDrawClose();
                 break;
            case GE_PlotClear :
                 break;
            case GE_PlotExit  :
                 exit(0); /* GE_PlotExit */
            default           :
                 printf("Echo from GEBLOBProcess(), ");
                 printf("invalid GEPLOTCOMMANDTYPE - %d\n",cmd1);
         }
      } else {
/*
static int i=0;
PrintBLOBNode(i++,node);
*/
         if (BLOBTABLE[(int)node->any.type].proc)
            (*BLOBTABLE[(int)node->any.type].proc)(ptr,node->any.total);
      }
      node=node->next;
   }
   return TRUE;
}

static
int GEWindowMatrixChange( node,event,win_scale,mtx,geom )
   MYDISPNODE *node;
#if defined(_XnMOTF_)
   XEvent *event;
#elif defined(_MSWINDOW_)
   char *event;
#endif
   int win_scale;
   XMTX2DATTR *mtx;
   GERECT *geom;
{
#if defined(_XnMOTF_)
   double x,y;

   switch (win_scale) {
      case GE_WinScaleByWindow : 
           x=(double)(*(XKeyEvent*)event).x/geom->width;
           y=1.0-(double)(*(XKeyEvent*)event).y/geom->height;
           break;
      case GE_WinScaleByObject :
           if (geom->width>=geom->height) {
            x=(double)(*(XKeyEvent*)event).x;
            x-=(double)(geom->width-geom->height)/2.0;
            x/=geom->height;
              y=1.0-(double)(*(XKeyEvent*)event).y/geom->height;
           } else {
              x=(double)(*(XKeyEvent*)event).x/geom->width;
              y=(double)(*(XKeyEvent*)event).y;
              y-=(double)(geom->height-geom->width)/2.0;
              y=1.0-y/geom->width;
           }
           break;
   }
   x=0.5-x;
   y=0.5-y;
   XMatrix2DTranslate(*mtx,x,y,ComXMatrix2D);
   return TRUE;
#elif defined(_MSWINDOW_)
   return TRUE;
#endif
}

static
int GEPlotWindowKeyProcess( dispNode,geom,event,blobList )
   MYDISPNODE *dispNode;
   GERECT *geom;
#if defined(_XnMOTIF_)
   XEvent *event;
#elif defined(_MSWINDOW_)
   char *event;
#endif
   BLOBLIST *blobList;
{
#if defined(_XnMOTIF_)
   char buf[32],buf256[256];
   int buf_size=32;
   KeySym key;
   int count;
   double x,y;

   static XMTX2DATTR mtx;
   static int WinScale=GE_WinScaleByObject,markerMode=0;

   static Window subWindow;
   static BLOBNODE *blobNode=NULL;
   BLOBNODE *blobNodeTmp;

   static int i; /* for blob debug */

   count=XLookupString(event,buf,buf_size,&key,NULL);
   buf[count]=0;

   GEDrawSetProcedure(0);
   if (!mtx)
      AlloXMatrix2D(&mtx);
   MXFreeGC(dispNode);
   MXAlloGC(dispNode);
   switch (*buf) {
      case 'z' : case 'Z' :
                 GEWindowMatrixChange(dispNode,event,WinScale,&mtx,geom);
                 GESetMouseXY(dispNode,geom->width/2,geom->height/2);
                 switch (*buf) {
                    case 'z' : XMatrix2DScale(mtx,0.5,0.5,0.5,0.5,
                                              ComXMatrix2D);
                               break;
                    case 'Z' : XMatrix2DScale(mtx,0.5,0.5,2.0,2.0,
                                              ComXMatrix2D);
                               break;
                 }
                 GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 't' : GEWindowMatrixChange(dispNode,event,WinScale,&mtx,geom);
                 GESetMouseXY(dispNode,geom->width/2,geom->height/2);
                 GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 'h' : case 'j' : case 'k' : case 'l' :
                 switch (*buf) {
                    case 'h' : x= 0.1;y= 0.0;break;
                    case 'j' : x= 0.0;y= 0.1;break;
                    case 'k' : x= 0.0;y=-0.1;break;
                    case 'l' : x=-0.1;y= 0.0;break;
                 }
                 XMatrix2DTranslate(mtx,x,y,ComXMatrix2DAdobe);
                 GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 'f' : WinScale=GE_WinScaleByObject;
                 SetXMatrix2DDefault(mtx);
                 GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 'F' : WinScale=GE_WinScaleByWindow;
                 SetXMatrix2DDefault(mtx);
                 GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 'r' : GEDraw(dispNode,WinScale,mtx,blobList);
                 return 1;
      case 'M' : if (markerMode==TRUE) return;
                 markerMode=TRUE;
                 blobNode=blobList->head;
                 MXopenDefChildWin(dispNode,&subWindow,"black",1,1,200,15);
                 sprintf(buf256,"x=? y=?\n");
                 XDrawImageString(dispNode->display,subWindow,
                    dispNode->gc[MX_GCDefault],1,11,buf256,strlen(buf256));
                 break;
      case 'm' : if (markerMode==FALSE) return;
                 markerMode=FALSE;
                 blobNode=0;
                 MXcloseDefChildWin(dispNode,subWindow);
                 break;
      case '<' : case ',' : case '>' : case '.' :
                 if (markerMode==FALSE) return 1;
                 blobNodeTmp=blobNode;
                 if (BLFindObject(blobList,&blobNode,BL_DATA,
                                  *buf=='<' ? 'H' :
                                  *buf==',' ? 'h' :
                                  *buf=='>' ? 'L' :
                                  *buf=='.' ? 'l' : 'l')) {
                    sprintf(buf256,"x=%+1.3e y=%+1.3e\n",
                       ((BLOBDATA*)BLNodeObjAddr(blobNode))->x,
                       ((BLOBDATA*)BLNodeObjAddr(blobNode))->y);
                    XDrawImageString(dispNode->display,subWindow,
                       dispNode->gc[MX_GCDefault],1,11,buf256,strlen(buf256));
                    XFlush(dispNode->display);
                    if (isDoubleNaN(((BLOBDATA*)BLNodeObjAddr(blobNode))->x)
                    ||  isDoubleNaN(((BLOBDATA*)BLNodeObjAddr(blobNode))->y))
                       break;
                    GEMarkerXY(dispNode,blobList,blobNode,WinScale,mtx,&x,&y);
                    if ((int)x<0)
                       x=0.0;
                    else if ((int)x>geom->width)
                       x=(double)geom->width;
                    if ((int)y<0)
                       y=0.0;
                    else if ((int)y>geom->height)
                       y=(double)geom->height;
                    GESetMouseXY(dispNode,(int)x,(int)y);
                 } else
                    blobNode=blobNodeTmp;
                 break;
      case 'd' : case 'D' : /* Postscript Window Dump */
                 GEPSFDumpWindow(dispNode);
                 fprintf(stdout,"GEPlotWindowKeyProcess() in geplot.c : "
                                "<GEpixmDump.psf> written ...\n");
                 break;
      case 'p' : case 'P' : /* Postscript BLOB Dump */
                 GEprintOpen("GE-blobDump.psf",GE_PSColor,GE_Portrait,mtx);
                 GEprintSetProcedure();
                 GEprintProcess(blobList);
                 GEprintClose();
                 fprintf(stdout,"GEPlotWindowKeyProcess() in geplot.c : "
                                "<GEblobDump.psf> written ...\n");
                 break;
      case '?' : blobNode=NULL; break;
      case 'Q' : GEMyWinDemo(dispNode); break;
      case 3   : return 0;
      default  : break;
      /* for Debug */
      case '{' : case '[' : case '}' : case ']' :
                 if (!blobNode) {
                    blobNode=blobList->head;
                    PrintBLOBNode(i=1,blobNode);
                    break;
                 }
                 switch (*buf) {
                    case '{' : blobNode=blobList->head;
                               PrintBLOBNode(i=1,blobNode);
                               break;
                    case '}' : for (blobNode=blobList->head,
                                    i=1;
                                    blobNode!=blobList->tail;
                                    blobNode=blobNode->next,
                                    i++);
                               PrintBLOBNode(i,blobNode);
                               break;
                    case '[' : if (blobNode!=blobList->head) {
                                  blobNode=blobNode->prev;
                                  PrintBLOBNode(--i,blobNode);
                               }
                               break;
                    case ']' : if (blobNode!=blobList->tail) {
                                  blobNode=blobNode->next;
                                  PrintBLOBNode(++i,blobNode);
                               }
                               break;
                 }
                 if (blobNode==blobList->head)
                    printf("blob-head .....\n");
                 else if (blobNode==blobList->tail)
                    printf("blob-tail .....\n");
                 return -1;
   }
   return -1;
#elif defined(_MSWINDOW_)
   return TRUE;
#endif
}

int SetPlotCommand( str,cmd1,cmd2 ) /* 16 */
   char *str;
   int cmd1,cmd2;
{
   sprintf(str,"%%%%%-14s,%-3d,%-3d.\n",GECoreName,cmd1,cmd2); 
   return strlen(str);
}

int ChkPlotCommand( str,cmd1,cmd2 )
   char *str;
   int *cmd1,*cmd2;
{
   char expression[17];

   sprintf(expression,"%%%%%-14s",GECoreName);
   *cmd1=*cmd2=0;
   if (strncmp(str,expression,16))
      return 0;
   str+=16;
   if (str[0]==',') {
      str++;
      *cmd1=atoi(str);
      if (str[3]==',') {
         str+=4;
         if (str[3]=='.') {
            *cmd2=atoi(str);
         }
      }
   }
   return TRUE;
}

int GEPlotWindowViewer( dispNode,blobList )
   MYDISPNODE *dispNode;
   BLOBLIST *blobList;
{
#if defined(_XnMOTIF_)
   XEvent event;
   static GERECT geom;

   XSelectInput(dispNode->display,dispNode->window,
                KeyPressMask|ExposureMask|StructureNotifyMask);
   GECopyToBackingStore(dispNode);
   GEGetGeometry(dispNode,&geom);
   while (1) {
      XNextEvent(dispNode->display,&event);
      switch (event.type) {
         case KeyPress : 
              switch (GEPlotWindowKeyProcess(dispNode,&geom,&event,blobList)) {
                 case  0 : return;
                 case  1 : GECopyToBackingStore(dispNode);break;
                 case -1 : break;
              }
              break;
         case Expose : 
              GECopyFromBackingStore(dispNode,&event);
              break;
         case ConfigureNotify : 
              GEGetGeometry(dispNode,&geom);
              break;
      }
   }
   return TRUE;
#elif defined(_MSWINDOW_)
   return TRUE;
#endif
}

/******************************************************************************/
/* geplot.c */
