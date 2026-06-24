/******************************************************************************/
/*                                                                            */
/*                    descriptive name : grm                                  */
/*                         environment : X11R5,MOTIF1.2                       */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
#define                        version  "0.65"            
/*                       creating date : 43280328                             */
/*                         update date : 43280328-0512,0608-0905,1022-1121    */
/*                         update date : 43300430-0531,0625,0701,0705,        */
/*                                           0811-0823,0916-0917,1207-1227    */
/*                                       43310114-0202                        */
#define                    update_date  "950328-980202"
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xmu/Drawing.h>

#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/RowColumn.h>
#include <Xm/BulletinB.h>
#include <Xm/Form.h>
#include <Xm/ScrolledW.h>
#include <Xm/Frame.h>
#include <Xm/CascadeBG.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/ArrowB.h>
#include <Xm/ArrowBG.h>
#include <Xm/ToggleBG.h>
#include <Xm/SeparatoG.h>
#include <Xm/LabelG.h>
#include <Xm/Scale.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/ScrollBar.h>
#include <Xm/DrawingA.h>
#include <Xm/FileSB.h>
#include <Xm/SelectioB.h>
#include <Xm/MessageB.h>

#include "myCore.h"
#include "motif.h"
#include "any.h"
#include "str.h"
#include "tools.h"
#include "plotse.h"
#include "geresource.h"

#define GrMotifVersion "gr@Motif,Ver." version "," update_date

#ifndef salloc
#define salloc(type,no) (type*)malloc((unsigned int)((no)*sizeof(type)))
#endif

/******************************************************************************/

static Widget topLevel,container,currentCmndWidget,currentWorkWidget,workW;
static Widget LogoLabel;
static Widget fileNewD,fileOpenD,exitD,infoD,workingD,errorD,
              messageWindow,messageL,message2L,
              viewScriptD,viewMessageD;

/******************************************************************************/

static Display *grmDisplay;
static Screen *grmScreen;
static int grmDepth;
static GC grmGC;
static XGCValues values;
static unsigned long valueMask=0L;

/******************************************************************************/

static char buf1024[1024];
static int isFileOpened=0;

       int motifMain();

static int CBfileNew();
static int CBfileOpen();
static int CBfileSave();
static int CBfileSaveAs();
static int CBfileClose();
static int CBfilePrint();
static int CBfileExit();
static int CBhelp();

static int CBgxfmScaleValueChanged();
static int CBgxfmToggleButtonValueChanged();
static int FNgxfmPutXscale();
static int FNgxfmPutYscale();
static int FNgxfmPutXtranslate();
static int FNgxfmPutYtranslate();
static int FNgxfmPutAngle();
static int FNgxfmGetXscale();
static int FNgxfmGetYscale();
static int FNgxfmGetXtranslate();
static int FNgxfmGetYtranslate();
static int FNgxfmGetAngle();
static int CBgxfm();

static int CBgtxt();

static int CBgoutFileName();
static int CBgout();

static int CBplotAdd();
static int CBplotDelete();
static int CBplotValueChanged();
static int CBplot();

static int CBattr();

static int CBdataFileName();
static int CBdata();

static int CBslct();

static int CBsymbPrevious();
static int CBsymbNext();
static int CBsymbDelete();
static int CBsymb();

static int CBaxisPrevious();
static int CBaxisNext();
static int CBaxisAdd();
static int CBaxisDelete();
static int CBaxis();

static int CBtextPrevious();
static int CBtextNext();
static int CBtextAdd();
static int CBtextDelete();
static int CBtext();

static int CBtextPrevious();
static int CBufunPrevious();
static int CBufunNext();
static int CBufunAdd();
static int CBufunDelete();
static int CBufun();

static int CBviewLscaleValueChanged();
static int CBviewUscaleValueChanged();
static int CBviewDefault();
static int CBview();

static int CBgcAttributeOk();
static int CBgcAttributeCancel();
static int CBgcAttributeUndo();
static int CBgcAttributeDefault();
static int CBgcAttribute();

static int CBviewPlot();
static int CBviewScript();
static int CBviewMessage();
static int CBmenuToggle();

static int manageWorkWidget();
static Widget makeUpCW();

static Widget MYdialogStack[16];
static int MYdialogStackIndex=-1;
static int CBpushDialog();
static int CBpopDialog();

/******************************************************************************/

typedef struct {
   Widget widget;
   char *varString;
   enum {
      UD_Char,UD_Integer,UD_Float,UD_Double,UD_HeapString,UD_StackString
   } dataType;
   XtPointer dataDef,dataPre; /* currentData -> XmNuserData of the widget */
   VPTRFN PutDataToWidget,GetDataFrWidget;
} UserDataNode;

typedef struct {
  int total,index;
  UserDataNode *udn;
} UserDataStack;

static void UDOpen();
static void UDClose();
static void UDSet();
static void UDReset();
static void UDUndo();
static void UDGet();
static void UDAddNode();
static void UDSetWidgetUserData();
static void UDGetWidgetUserData();
static void UDSetArrowButtonTextValue();
static void UDGetArrowButtonTextValue();
static void UDSetTextString();
static void UDGetTextString();
static void UDGetToggleButtonGadgetState();
static void UDGetScaleValue();
static void UDSetOptionMenuLabel();
static void UDGetOptionMenuLabel();
static void UDSetOptionMenuUserData();
static void UDGetOptionMenuUserData();

/******************************************************************************/

static DLL *scriptList=0;
static DLN *scriptNode=0;
static int openScriptList();
static int closeScriptList();
static int gotoGlobCommand();
static int gotoPlotCommand();
static int doScriptToken();

/******************************************************************************/

main( argc,argv )
   unsigned int argc;
   char **argv;
{
   openScriptList();
   motifMain(argc,argv);
}

int motifMain( argc,argv )
   unsigned int argc;
   char **argv;
{
   Widget menuBar,menuPane,W,W1,W2;

   topLevel=XtInitialize(argv[0],"grm.rs",NULL,NULL,&argc,argv);
   XtVaSetValues(topLevel,XmNtitle,GrMotifVersion,NULL);
/* main window ---------------------------------------------------------------*/
   container=MMaddWidget(topLevel,MM_MainWindow,"",
      XmNwidth,500,
      XmNheight,300,
      XmNshowSeparator,1,
      XmNcommandWindowLocation,XmCOMMAND_BELOW_WORKSPACE,
      NULL);
   MMopen(container);

/* menu bar ------------------------------------------------------------------*/
   menuBar=MMaddWidget(container,MM_MenuBar,"menuBar",
      NULL);
   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"file",
      XmNmnemonic,'f',
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   fileNewD=MMaddWidget(container,MM_PromptDialog,"",
      XmNtitle,GrMotifVersion,
      XmNselectionLabelString,"write file name in",
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,1,
      XzNaddCallback,XmNokCallback,CBfileNew,0,
      XzNaddCallback,XmNcancelCallback,CBdeactivate,0,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      NULL);
   fileOpenD=MMaddWidget(container,MM_FileSelectionDialog,"",
      XmNtitle,GrMotifVersion,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,1,
      XzNaddCallback,XmNokCallback,CBfileOpen,0,
      XzNaddCallback,XmNcancelCallback,CBdeactivate,0,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"new               ",
      XmNmnemonic,'n',
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBactivate,fileNewD,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"open ...",
      XmNmnemonic,'o',
      XmNaccelerator,"Ctrl<Key>o",
      XmNacceleratorText,"^o",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBactivate,fileOpenD,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"save",
      XmNmnemonic,'s',
      XmNsensitive,0,
      XzNaddCallback,XmNactivateCallback,CBfileSave,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"save as ...",
      XmNsensitive,0,
      XzNaddCallback,XmNactivateCallback,CBfileSave,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"closeB",
      XmNlabelString,"close",
      XmNmnemonic,'c',
      XzNaddCallback,XmNactivateCallback,CBfileClose,0,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"print",
      XmNmnemonic,'p',
      XmNaccelerator,"Ctrl<Key>p",
      XmNacceleratorText,"^p",
      XmNsensitive,0,
      XzNaddCallback,XmNactivateCallback,CBfilePrint,0,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   exitD=MMaddWidget(container,MM_QuestionDialog,"",
      XmNtitle,GrMotifVersion,
      XmNmessageString,"really exit ..",
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,1,
      XzNaddCallback,XmNokCallback,CBfileExit,0,
      XmNnoResize,1,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"exit",
      XmNmnemonic,'x',
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBactivate,exitD,
      NULL);

   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"glob",
      XmNmnemonic,'g',
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"transformation     ",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBgxfm,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"title",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBgtxt,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"out file (format) ..  ",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBgout,0,
      NULL);

   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"plot",
      XmNmnemonic,'p',
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"goto nth plot    ",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBplot,0,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"attribute        ",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBattr,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"data",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBdata,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"selection : [xy]no,n[rc][lh],range,[xy][lu]b ",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBslct,0,
      XmNsensitive,1,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"symbol",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBsymb,0,
      XmNsensitive,1,
      NULL);
   W=MMaddWidget(container,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuPane,MM_CascadeButtonG,"",
      XmNlabelString,"axis",
      XmNsubMenuId,W,
      XmNsensitive,1,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"x axis",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBaxis,'x',
      XmNsensitive,1,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"y axis",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBaxis,'y',
      XmNsensitive,1,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"z axis",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBaxis,'z',
      XmNsensitive,0,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"radial axis",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBaxis,'z',
      XmNsensitive,0,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"theta axis",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBaxis,'z',
      XmNsensitive,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"text",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBtext,0,
      XmNsensitive,1,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"user's function",
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBufun,0,
      XmNsensitive,1,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"viewport",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBview,0,
      NULL);

   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"view",
      XmNmnemonic,'v',
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"plot",
      XmNmnemonic,'p',
      XmNaccelerator,"Ctrl<Key>r",
      XmNacceleratorText,"^r",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBviewPlot,0,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"script",
      XmNmnemonic,'s',
      XmNaccelerator,"Ctrl<Key>s",
      XmNacceleratorText,"^s",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBviewScript,0,
      NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"message",
      XmNmnemonic,'m',
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBviewMessage,0,
      NULL);

   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"option",
      XmNsensitive,0,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"window",
      XmNsensitive,0,
      NULL);

   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"menu",
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   MMaddWidget(menuPane,MM_ToggleButtonG,"toggleButton",
      XmNlabelString,"grapher             ",
      XmNset,1,
      XzNaddCallback,XmNvalueChangedCallback,CBmenuToggle,0,
      XmNsensitive,1,
      NULL);
   MMaddWidget(menuPane,MM_ToggleButtonG,"toggleButton",
      XmNlabelString,"wafer map (contour) ",
      XzNaddCallback,XmNvalueChangedCallback,CBmenuToggle,0,
      XmNsensitive,1,
      NULL);

   menuPane=MMaddWidget(menuBar,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   W=MMaddWidget(menuBar,MM_CascadeButtonG,"",
      XmNlabelString,"help",
      XmNmnemonic,'h',
      XmNsensitive,1,
      XmNsubMenuId,menuPane,
      NULL);
   XtVaSetValues(menuBar,XmNmenuHelpWidget,W,NULL);
   W=MMaddWidget(container,MM_PulldownMenu,"",
      XmNtearOffModel,XmTEAR_OFF_DISABLED,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(menuPane,MM_CascadeButtonG,"",
      XmNlabelString,"examples",
      XmNsensitive,1,
      XmNsubMenuId,W,
      XmNsensitive,0,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"script 1 ",
      XmNsensitive,1,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"script 2 : log-normal plot ",
      XmNsensitive,1,
      NULL);
   MMaddWidget(W,MM_PushButtonG,"",
      XmNlabelString,"script 3 ...  ",
      XmNsensitive,1,
      NULL);
   MMaddWidget(menuPane,MM_SeparatorG,"",NULL);
   MMaddWidget(menuPane,MM_PushButtonG,"",
      XmNlabelString,"about ...     ",
      XmNsensitive,1,
      XzNaddCallback,XmNactivateCallback,CBpopDialog,0,
      XzNaddCallback,XmNactivateCallback,CBhelp,0,
      NULL);

/* command area --------------------------------------------------------------*/

   ;

/* working area --------------------------------------------------------------*/

   workW=MMaddWidget(container,MM_ScrolledWindow,"workW",
      XmNscrollBarDisplayPolicy,XmAS_NEEDED,
      XmNscrollingPolicy,XmAUTOMATIC,
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   LogoLabel=MMaddWidget(workW,MM_Label,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   currentWorkWidget=LogoLabel;

/* message area --------------------------------------------------------------*/
   messageWindow=MMaddWidget(container,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   messageL=MMaddWidget(messageWindow,MM_LabelG,"",
      XmNlabelString,"(c)shik",
      XmNleftAttachment,XmATTACH_FORM,
      XmNmarginHeight,4,
      NULL);
   message2L=MMaddWidget(messageWindow,MM_LabelG,"",
      XmNlabelString,"{1/1}",
      XmNrightAttachment,XmATTACH_FORM,
      XmNmarginHeight,4,
      NULL);
   XtVaSetValues(container,XmNmessageWindow,messageWindow,NULL);
   XtManageChild(messageWindow);

/* main loop -----------------------------------------------------------------*/
   workingD=MMaddWidget(container,MM_WorkingDialog,"",
      XmNtitle,GrMotifVersion,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageChild,XmDIALOG_CANCEL_BUTTON,
      XzNunmanageWidget,1,
      XmNnoResize,1,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      XzNaddCallback,XmNokCallback,CBdeactivate,0,
      NULL);
   errorD=MMaddWidget(container,MM_ErrorDialog,"",
      XmNtitle,GrMotifVersion,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageChild,XmDIALOG_CANCEL_BUTTON,
      XzNunmanageWidget,1,
      XmNnoResize,1,
      XzNaddCallback,XmNokCallback,CBdeactivate,0,
      NULL);

   XtRealizeWidget(topLevel);

   grmDisplay=XtDisplay(container);
   grmScreen=XtScreen(container);
   grmDepth=XDefaultDepthOfScreen(grmScreen);
   grmGC=XCreateGC(grmDisplay,XtWindow(container),valueMask,&values);

   {
   Pixmap pixmap;
   Window root,window;
   Status status;
   int x,y,w,h,border_width,depth_return;

   window=XtWindow(workW);
   status=XGetGeometry(grmDisplay,window,&root,&x,&y,&w,&h,
      &border_width,&depth_return);
   pixmap=XCreatePixmap(grmDisplay,XtWindow(container),w,h,grmDepth);
   XSetForeground(grmDisplay,grmGC,MMcolor("black"));
   XChangeGC(grmDisplay,grmGC,valueMask,&values);
   XFillRectangle(grmDisplay,pixmap,grmGC,0,0,w,h);
   valueMask=GCFunction|GCForeground|GCFillStyle|GCStipple;
   values.function=GXcopy;
   values.foreground=MMcolor("red");
   values.fill_style=FillStippled;
   values.stipple=XCreateBitmapFromData(
      grmDisplay,XtWindow(container),GEgetMyStipple8x8(26),8,8);
   XChangeGC(grmDisplay,grmGC,valueMask,&values);
   XFillRectangle(grmDisplay,pixmap,grmGC,0,0,w,h);
   XtVaSetValues(LogoLabel,
      XmNlabelType,XmPIXMAP,
      XmNlabelPixmap,pixmap,
      XmNwidth,w,
      XmNheight,h,
      NULL);
/*
   XmuDrawLogo(grmDisplay,pixmap,grmGC,grmGC,0,0,w,h);
*/
   }

   XtMainLoop();
}

static
int CBfileNew( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   Widget w;
   char *name;

   w=XmSelectionBoxGetChild(W,XmDIALOG_TEXT);
   name=XmTextGetString(w);
   XtUnmanageChild(W);
   if (isFileOpened) {
      MMsetString(errorD,XmNmessageString,"","file already opened. close it.");
      XtManageChild(errorD);
   } else if (strlen(name)) {
      XtVaSetValues(topLevel,XmNtitle,name,NULL);
      isFileOpened=1;
   }
}

static
int CBfileOpen( WIDGET,client_data,call_data )
   Widget WIDGET;
   XtPointer client_data;
   XtPointer call_data;
{
   Widget W;
   char *name;
   int liveOnly;

   W=XmFileSelectionBoxGetChild(WIDGET,XmDIALOG_TEXT);
   name=XmTextGetString(W);
   XtUnmanageChild(WIDGET);
   if (isFileOpened) {
      MMsetString(errorD,XmNmessageString,"","file already opened. close it.");
      XtManageChild(errorD);
   } else if (strlen(name)) {
      XtVaSetValues(topLevel,XmNtitle,name,NULL);
      isFileOpened=1;
   }
}

static
int CBfileSave()
{
}

static
int CBfileSaveAs( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
}

static
int CBfileClose()
{
   XtVaSetValues(topLevel,XmNtitle,GrMotifVersion,NULL);
   isFileOpened=0;
}

static
int CBfilePrint()
{
   fprintf(stdout,"CBfilePrint() : not yet ...\n");
}

static
int CBfileExit( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   XmAnyCallbackStruct *any=(XmAnyCallbackStruct*)call_data;
   exit(0);
}

static
int CBhelp()
{
   static int created=0;

   if (created) {
      XtManageChild(infoD);
      return;
   }
   created=1;
   infoD=MMaddWidget(container,MM_InformationDialog,"infoD",
      XmNtitle,"gr",
      XmNmessageString,"grapher MOTIF version,\n"
                       "X11R5+Motif1.2\n"
                       update_date "\n"
                       "Ver."version ",(c)Kim,YongShik\n"
                       "shik96@samsung.co.kr",
      XzNunmanageChild,XmDIALOG_CANCEL_BUTTON,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,0,
      XmNnoResize,1,
      NULL);
}

static
int CBgxfmScaleValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA; /* aspectRatio widget */
   XtPointer CALL_DATA;
{
   Widget Wx,Wy;
   int Vx,Vy;

   if (!XmToggleButtonGetState((Widget)CLIENT_DATA)) return;
   Wx=XtNameToWidget(XtParent(WIDGET),"xScale");
   Wy=XtNameToWidget(XtParent(WIDGET),"yScale");
   XmScaleGetValue(Wx,&Vx);
   XmScaleGetValue(Wy,&Vy);
   if (Wx==WIDGET)
      XmScaleSetValue(Wy,Vx);
   else if (Wy==WIDGET)
      XmScaleSetValue(Wx,Vy);
}

static
int CBgxfmToggleButtonValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   Widget Wx,Wy;
   int Vx;

   if (!XmToggleButtonGetState(WIDGET)) return;
   Wx=XtNameToWidget(XtParent(WIDGET),"xScale");
   Wy=XtNameToWidget(XtParent(WIDGET),"yScale");
   XmScaleGetValue(Wx,&Vx);
   XmScaleSetValue(Wy,Vx);
}

static
int FNgxfmPutXscale( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
}

static
int FNgxfmGetXscale( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
}

static
int FNgxfmPutYscale()
{
}

static
int FNgxfmPutXtranslate()
{
}

static
int FNgxfmPutYtranslate()
{
}

static
int FNgxfmPutAngle()
{
}

static
int FNgxfmGetYscale
    (WIDGET) Widget WIDGET;
{
}

static
int FNgxfmGetXtranslate
    (WIDGET) Widget WIDGET;
{
}

static
int FNgxfmGetYtranslate
    (WIDGET) Widget WIDGET;
{
}

static
int FNgxfmGetAngle
    (WIDGET) Widget WIDGET;
{
}

static
int CBgxfm( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW;
   Widget w1,w2,w3;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   w1=MMaddWidget(WW,MM_Scale,"xScale",
      XmNtitleString,"xscale [%]",
      XmNshowValue,True,
      XmNminimum,10, XmNmaximum,200, XmNvalue,100,
      XmNscaleMultiple,10,
      XmNorientation,XmHORIZONTAL,
      XmNwidth,200,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w2=MMaddWidget(WW,MM_ToggleButtonG,"",
      XmNlabelString,"equal aspect ratio",
      XzNaddCallback,XmNvalueChangedCallback,
         CBgxfmToggleButtonValueChanged,0,
      XmNset,1,
      MMformLeftAttach(w1),
      NULL);
   w3=MMaddWidget(WW,MM_Scale,"yScale",
      XmNtitleString,"yscale [%]",
      XmNshowValue,True,
      XmNminimum,10, XmNmaximum,200, XmNvalue,100,
      XmNscaleMultiple,10,
      XmNorientation,XmHORIZONTAL,
      XmNwidth,200,
      XmNmarginHeight,1,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   XtAddCallback(w1,XmNvalueChangedCallback,
      CBgxfmScaleValueChanged,w2);
   XtAddCallback(w3,XmNvalueChangedCallback,
      CBgxfmScaleValueChanged,w2);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"xtranslation :",
      XmNtopWidget,w3,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w3,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,16,XmNcolumns,16,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"ytranslation :",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,16,XmNcolumns,16,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   MMaddWidget(WW,MM_Scale,"",
      XmNtitleString,"rotation angle [degree]",
      XmNshowValue,True,
      XmNminimum,-180, XmNmaximum,180, XmNvalue,0,
      XmNscaleMultiple,10,
      XmNorientation,XmHORIZONTAL,
      XzNaddCallback,XmNvalueChangedCallback,CBscaleSnapValue,10,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
SKIP:
   manageWorkWidget(0,WW,"/glob/transformation");
}

static
int CBgtxt( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW;
   Widget w1,w2;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"text :",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"null",
      XmNmaxLength,32,XmNcolumns,32,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   MMaddWidget(WW,MM_PushButtonG,"textAttribute@glob",
      XmNlabelString,"gc attribute",
      XzNaddCallback,XmNactivateCallback,CBgcAttribute,0,
      XmNtopWidget,w2,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
SKIP:
   manageWorkWidget(0,WW,"/glob/title");
}

static
int CBgoutFileName( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   Widget W;
   char *fileName;

   W=XmFileSelectionBoxGetChild(WIDGET,XmDIALOG_TEXT);
   fileName=XmTextGetString(W);
   XtUnmanageChild(WIDGET);
   XtVaSetValues(CLIENT_DATA,XmNvalue,fileName,NULL);
   XtFree(fileName);
}

static
int CBgout( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW;
   Widget FRAME,PM,RB,DIALOG,w1;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   PM=MMaddWidget(WW,MM_PulldownMenu,"",
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"",
      XmNlabelString,"portrait",
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"",
      XmNlabelString,"landscape",
      NULL);
   w1=MMaddWidget(WW,MM_OptionMenu,"",
      XmNlabelString,"direction :",
      XmNsubMenuId,PM,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"file type",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,0,
      XmNspacing,0,
      XmNmarginWidth,2,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"HPGL/2",  XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"PCL5",    XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"Adobe Postscript Level 2 (color)",
                                             XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"Encapsulated Postscript",
                                             XmNset,0,XmNmarginHeight,0,NULL);
   DIALOG=MMaddWidget(container,MM_FileSelectionDialog,"",
      XmNtitle,GrMotifVersion,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,1,
      /* XmNokCallback -> see ~20 lines below */
      XzNaddCallback,XmNcancelCallback,CBdeactivate,0,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"file name :",
      XzNaddCallback,XmNactivateCallback,CBactivate,DIALOG,
      XmNtopWidget,FRAME,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopOffset,2,
      XmNleftWidget,FRAME,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"null",
      XmNmaxLength,50,XmNcolumns,50,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   XtAddCallback(DIALOG,XmNokCallback,CBgoutFileName,w1);
SKIP:
   manageWorkWidget(0,WW,"/glob/out file (format)");
}

static
int CBplotAdd( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   char *string,*s1,*s2,*skip="{}/";
   int i,j;

   MMgetString(message2L,XmNlabelString,"",&string);
   s1=strtok(string,skip);
   s2=strtok(NULL,skip);
   i=atoi(s1);
   j=atoi(s2);
   i++;j++;
   sprintf(buf1024,"{%d/%d}",i,j);
   MMsetString(message2L,XmNlabelString,"",buf1024);
   XtVaSetValues(CLIENT_DATA,XmNmaximum,j,NULL);
   XtVaSetValues(CLIENT_DATA,XmNvalue,i,NULL);
   XtFree(string);
}

static
int CBplotDelete( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   char *string,*s1,*s2,*skip="{}/";
   int i,j;

   MMgetString(message2L,XmNlabelString,"",&string);
   s1=strtok(string,skip);
   s2=strtok(NULL,skip);
   i=atoi(s1);
   j=atoi(s2);
   if (j==1)
      goto e;
   else if (i==1) {
      j--;
   } else {
      i--;j--;
   }
   sprintf(buf1024,"{%d/%d}",i,j);
   MMsetString(message2L,XmNlabelString,"",buf1024);
   XtVaSetValues(CLIENT_DATA,XmNvalue,i,NULL);
   XtVaSetValues(CLIENT_DATA,XmNmaximum,j==1 ? 2:j,NULL);
e: XtFree(string);
}

static
int CBplotValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   char *string,*s2,*skip="{}/";
   int i,j;

   XmScaleGetValue(WIDGET,&i);
   MMgetString(message2L,XmNlabelString,"",&string);
   s2=strtok(string,skip);
   s2=strtok(NULL,skip);
   j=atoi(s2);
   if (i>j) {
      XtVaSetValues(WIDGET,XmNvalue,j,NULL);
      return;
   }
   sprintf(buf1024,"{%d/%d}",i,j);
   MMsetString(message2L,XmNlabelString,"",buf1024);
   XtFree(string);
}

static
int CBplot( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW; /* workWindow */
   Widget w[3];
   char *p;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   w[0]=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"add",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w[1]=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"delete",
      MMformLeftAttach(w[0]),
      NULL);
   w[2]=MMaddWidget(WW,MM_Scale,"",
      XmNtitleString,"plot",
      XmNshowValue,True,
      XmNminimum,1, XmNmaximum,2, XmNvalue,1,
      XmNscaleMultiple,1,
      XmNorientation,XmHORIZONTAL,
      XzNaddCallback,XmNvalueChangedCallback,CBplotValueChanged,0,
      /* XmNsensitive,0, */
      XmNwidth,250,
      XmNtopWidget,w[0],
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w[0],
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   XtAddCallback(w[0],XmNactivateCallback,CBplotAdd,w[2]);
   XtAddCallback(w[1],XmNactivateCallback,CBplotDelete,w[2]);
SKIP:
   MMgetString(WIDGET,XmNlabelString,"",&p);
   manageWorkWidget(0,WW,p);
   XtFree(p);
}

static
int CBattr( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW; /* workWindow */
   Widget FRAME,RB;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"plot",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,1,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"scatter",XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"moment", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"area",   XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"bar",    XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"column", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"pie",    XmNset,0,XmNmarginHeight,0,NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"x scale",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,1,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"linear", XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"logarithmic",XmNset,0,XmNmarginHeight,0,0);
   MMaddWidget(RB,MM_ToggleButtonG,"normal", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"weibull",XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"serial", XmNset,0,XmNmarginHeight,0,NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"y scale",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,1,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"linear", XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"logarithmic",XmNset,0,XmNmarginHeight,0,0);
   MMaddWidget(RB,MM_ToggleButtonG,"normal", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"weibull",XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"serial", XmNset,0,XmNmarginHeight,0,NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"z scale",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,1,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"linear", XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"logarithmic",XmNset,0,XmNmarginHeight,0,0);
   MMaddWidget(RB,MM_ToggleButtonG,"normal", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"weibull",XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"serial", XmNset,0,XmNmarginHeight,0,NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"overlapped",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,2,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"Yes",    XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"No",     XmNset,1,XmNmarginHeight,0,NULL);
SKIP:
   manageWorkWidget(0,WW,"/plot/attribute");
}

static
int CBdataFileName( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   Widget W;
   char *fileName;

   W=XmFileSelectionBoxGetChild(WIDGET,XmDIALOG_TEXT);
   fileName=XmTextGetString(W);
   XtUnmanageChild(WIDGET);
   XtVaSetValues(CLIENT_DATA,XmNvalue,fileName,NULL);
   XtFree(fileName);
}

static
int CBdata( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW; /* workWindow */
   Widget FRAME,RB,DIALOG,w1,w2;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   DIALOG=MMaddWidget(container,MM_FileSelectionDialog,"",
      XmNtitle,GrMotifVersion,
      XzNunmanageChild,XmDIALOG_HELP_BUTTON,
      XzNunmanageWidget,1,
      /* XmNokCallback -> see ~20 lines below */
      XzNaddCallback,XmNcancelCallback,CBdeactivate,0,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"matrix :",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   RB=MMaddWidget(FRAME,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,1,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"generated from ASCII file",
                                             XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"sharing the previous matrix memory",
                                             XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"duplicated the previous matrix",
                                             XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"created by user's function",
                                             XmNset,0,XmNmarginHeight,0,NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"file/matrix name :",
      XzNaddCallback,XmNactivateCallback,CBactivate,DIALOG,
      XmNtopWidget,FRAME,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopOffset,2,
      XmNleftWidget,FRAME,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"null",
      XmNmaxLength,50,XmNcolumns,50,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   XtAddCallback(DIALOG,XmNokCallback,CBdataFileName,w2);
   MMaddWidget(WW,MM_ToggleButtonG,"",
      XmNlabelString,"switch",
      XmNset,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
SKIP:
   manageWorkWidget(0,WW,"/plot/data");
}

static
int CBslct( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW; /* workWindow */
   Widget FRAME,FORM,w[30];

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"column selection",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w[1]=MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"x number :",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   w[2]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"1",
      XmNmaxLength,32,XmNcolumns,1,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[1]),
      NULL);
   w[3]=MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"y number :",
      XmNtopWidget,w[1],
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w[1],
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w[4]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"2",
      XmNmaxLength,32,XmNcolumns,1,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[3]),
      NULL);
   w[5]=MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"z number :",
      XmNsensitive,0,
      XmNtopWidget,w[3],
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w[3],
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w[6]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"3",
      XmNmaxLength,32,XmNcolumns,1,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNsensitive,0,
      MMformLeftAttach(w[5]),
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopWidget,FRAME,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopOffset,2,
      XmNleftWidget,FRAME,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"row/column boundary",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w[8]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"nrl :",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   w[9]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[8]),
      NULL);
   w[10]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," ncl :",
      MMformLeftAttach(w[9]),
      NULL);
   w[11]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[10]),
      NULL);
   w[12]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"nrh :",
      XmNtopWidget,w[8],
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w[8],
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w[13]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[12]),
      NULL);
   w[14]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," nch :",
      MMformLeftAttach(w[13]),
      NULL);
   w[15]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[14]),
      NULL);
   w[16]=MMaddWidget(WW,MM_Scale,"",
      XmNtitleString,"range [%]",
      XmNshowValue,True,
      XmNminimum,50, XmNmaximum,100, XmNvalue,100,
      XmNscaleMultiple,5,
      XmNorientation,XmHORIZONTAL,
      /* XzNaddCallback,XmNvalueChangedCallback,CBscaleSnapValue,5, */
      XmNwidth,100,
      XmNheight,60,
      MMformLeftAttach(FRAME),
      XmNleftOffset,2,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopWidget,FRAME,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopOffset,2,
      XmNleftWidget,FRAME,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"xyz-scale boundary",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w[18]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"xlb :",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   w[19]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[18]),
      NULL);
   w[20]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," ylb :",
      MMformLeftAttach(w[19]),
      NULL);
   w[21]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[20]),
      NULL);
   w[22]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," zlb :",
      MMformLeftAttach(w[21]),
      NULL);
   w[23]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[22]),
      NULL);
   w[24]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"xub :",
      XmNtopWidget,w[18],
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w[18],
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w[25]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[24]),
      NULL);
   w[26]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," yub :",
      MMformLeftAttach(w[25]),
      NULL);
   w[27]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[26]),
      NULL);
   w[28]=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString," zub :",
      MMformLeftAttach(w[27]),
      NULL);
   w[29]=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w[28]),
      NULL);
SKIP:
   manageWorkWidget(0,WW,"/plot/selection");
}


static
int CBlegendSizeValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   int value;

   XmScaleGetValue(WIDGET,&value);
   XmScaleSetValue((Widget)CLIENT_DATA,value);
}

static
int CBsymbPrevious( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBsymbPrevious()\n");
}

static
int CBsymbNext( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBsymbNext()\n");
}

static
int CBsymbAdd( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBsymbAdd()\n");
}

static
int CBsymbDelete( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBsymbDelete()\n");
}

int CBsymb( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW=0,CW; /* workWindow,commandWindow */
   Widget FRAME,FORM,PM,RB,w1,w2;
   Widget WsymbSize;

   if (WW) goto SKIP;
   /* command window */
   CW=makeUpCW(topLevel,container,
               "1st set : x=?,y=?,z=?",
               CBsymbPrevious, 
               CBsymbNext, 
               CBsymbAdd, 
               CBsymbDelete);

   /* work window */
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"symbol",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"circle",       NULL);
   MMaddWidget(PM,MM_PushButtonG,"up-triangle",  NULL);
   MMaddWidget(PM,MM_PushButtonG,"down-triangle",NULL);
   MMaddWidget(PM,MM_PushButtonG,"square",       NULL);
   MMaddWidget(PM,MM_PushButtonG,"spade",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"diamond",      NULL);
   MMaddWidget(PM,MM_PushButtonG,"heart",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"club",         NULL);
   MMaddWidget(PM,MM_PushButtonG,"4-club",       NULL);
   MMaddWidget(PM,MM_PushButtonG,"cross",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"super-nova",   NULL);
   MMaddWidget(PM,MM_PushButtonG,"asterisk",     NULL);
   MMaddWidget(PM,MM_PushButtonG,"star",         NULL);
   MMaddWidget(PM,MM_PushButtonG,"half-moon",    NULL);
   MMaddWidget(PM,MM_PushButtonG,"bang",         NULL);
   MMaddWidget(PM,MM_PushButtonG,"-?-",          NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"type :",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   WsymbSize=w1=MMaddWidget(FORM,MM_Scale,"",
      XmNtitleString,"size :",
      XmNshowValue,True,
      XmNminimum,1, XmNmaximum,10, XmNvalue,5,
      XmNscaleMultiple,1,
      XmNorientation,XmHORIZONTAL,
      MMformTopAttach(w1),
      NULL);
   RB=MMaddWidget(FORM,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      MMformTopAttach(w1),
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"line visible",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"invisible",
               XmNmarginHeight,0,XmNset,0,NULL);
   w1=MMaddWidget(FORM,MM_Scale,"",
      XmNtitleString,"pen number",
      XmNshowValue,True,
      XmNminimum,1, XmNmaximum,8, XmNvalue,1,
      XmNscaleMultiple,1,
      XmNorientation,XmHORIZONTAL,
      MMformTopAttach(RB),
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNleftOffset,2,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"legend",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"text :",NULL);
   w2=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"null",
      XmNmaxLength,32,XmNcolumns,16,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(FORM,MM_Scale,"",
      XmNtitleString,"legend size :",
      XmNshowValue,True,
      XmNminimum,1, XmNmaximum,10, XmNvalue,5,
      XmNscaleMultiple,1,
      XmNorientation,XmHORIZONTAL,
      XzNaddCallback,XmNvalueChangedCallback,CBlegendSizeValueChanged,WsymbSize,
      XmNtopWidget,w2,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"x=",
      MMformTopAttach(w1),
      NULL);
   w2=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,6,XmNcolumns,6,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"y=",
      MMformTopAttach(w1),
      NULL);
   w2=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,6,XmNcolumns,6,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"gc attribute",
      XzNaddCallback,XmNactivateCallback,CBgcAttribute,2,
      MMformTopAttach(FRAME),
      XmNtopOffset,2,
      NULL);
SKIP:
   manageWorkWidget(CW,WW,"/plot/symbol");
}

static
int CBaxisPrevious( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBaxisPrevious()\n");
}

static
int CBaxisNext( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBaxisNext()\n");
}

static
int CBaxisAdd( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBaxisAdd()\n");
}

static
int CBaxisDelete( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBaxisDelete()\n");
}

static
int CBaxis( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW=0,CW;
   Widget FRAME,FRAME1,FRAME2,FORM,FORM1,RB,w1,w2;

   if (WW) goto SKIP;
   /* command window */
   sprintf(buf1024,"1st set : %c=?",(int)CLIENT_DATA);
   CW=makeUpCW(topLevel,container,
               buf1024,
               CBaxisPrevious, 
               CBaxisNext, 
               CBaxisAdd, 
               CBaxisDelete);

   /* work window */
   /* axis */
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   FRAME=MMaddWidget(WW,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"axis",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   RB=MMaddWidget(FORM,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"none",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"lower",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"middle",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"upper",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"any",
               XmNmarginHeight,0,XmNset,0,NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"crosses at",
      XmNtopWidget,RB,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,RB,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"",
      XmNlabelString,"(low,upper)=",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);

   /* tick */
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"tick",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   FRAME1=MMaddWidget(FORM,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME1,MM_LabelG,"major",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM1=MMaddWidget(FRAME1,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   RB=MMaddWidget(FORM1,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"none",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"inside",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"outside",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"cross",
               XmNmarginHeight,0,XmNset,0,NULL);
   w1=MMaddWidget(FORM1,MM_LabelG,"",
      XmNlabelString,"space=",
      XmNtopWidget,RB,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,RB,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM1,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   FRAME2=MMaddWidget(FORM,MM_Frame,"",
      XmNtopWidget,FRAME1,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,FRAME1,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME2,MM_LabelG,"minor",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM1=MMaddWidget(FRAME2,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   RB=MMaddWidget(FORM1,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"none",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"inside",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"outside",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"cross",
               XmNmarginHeight,0,XmNset,0,NULL);
   w1=MMaddWidget(FORM1,MM_LabelG,"",
      XmNlabelString,"space=",
      XmNtopWidget,RB,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,RB,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM1,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);

   /* label */
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"label",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   RB=MMaddWidget(FORM,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"none",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"tick",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"space",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"byUser",
               XmNmarginHeight,0,XmNset,0,NULL);
   w1=MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"format=",
      XmNtopWidget,RB,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,RB,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"program=",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w1=MMaddWidget(FORM,MM_Text,"",
      XmNmaxLength,10,XmNcolumns,10,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);

   /* grid */
   FRAME=MMaddWidget(WW,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNmarginWidth,5,
      XmNmarginHeight,2,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"grid",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   RB=MMaddWidget(FORM,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,0,
      XmNorientation,XmVERTICAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"none",
               XmNmarginHeight,0,XmNset,1,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"on minor+major tick",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(RB,MM_ToggleButtonG,"on major tick",
               XmNmarginHeight,0,XmNset,0,NULL);
   MMaddWidget(FORM,MM_PushButtonG,"",
      XmNlabelString,"gc attribute",
      XzNaddCallback,XmNactivateCallback,CBgcAttribute,0,
      XmNtopWidget,RB,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,RB,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);

SKIP:
   manageWorkWidget(CW,WW,"/plot/axis");
}

static
int CBtextPrevious( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBtextPrevious()\n");
}

static
int CBtextNext( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBtextNext()\n");
}

static
int CBtextAdd( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBtextAdd()\n");
}

static
int CBtextDelete( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBtextDelete()\n");
}

static
int CBtext( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW=0,CW; /* workWindow,commandWindow */
   Widget PM,w1,w2;

   if (WW) goto SKIP;
   /* command window */
   CW=makeUpCW(topLevel,container,
               "1st set",
               CBtextPrevious, 
               CBtextNext, 
               CBtextAdd, 
               CBtextDelete);

   /* work window */
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   PM=MMaddWidget(WW,MM_PulldownMenu,"",
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"x axis (ID=1)",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"y axis (ID=2)",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"z axis (ID=3)",        NULL);
   MMaddWidget(PM,MM_PushButtonG,"main title (ID=4)",    NULL);
   MMaddWidget(PM,MM_PushButtonG,"sub title (ID=5)",     NULL);
   MMaddWidget(PM,MM_PushButtonG,"left title (ID=6)",    NULL);
   MMaddWidget(PM,MM_PushButtonG,"right title (ID=7)",   NULL);
   MMaddWidget(PM,MM_PushButtonG,"free position (ID=0)", NULL);
   w1=MMaddWidget(WW,MM_OptionMenu,"",
      XmNlabelString,"type :",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"text :",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"null",
      XmNmaxLength,32,XmNcolumns,32,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"x=",
      XmNtopWidget,w2,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,10,XmNcolumns,10,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"y=",
      XmNtopWidget,w2,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,10,XmNcolumns,10,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"gc attribute",
      XzNaddCallback,XmNactivateCallback,CBgcAttribute,0,
      XmNtopWidget,w2,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
SKIP:
   manageWorkWidget(CW,WW,"/plot/text");
}

static
int CBufunPrevious( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBufunPrevious()\n");
}

static
int CBufunNext( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBufunNext()\n");
}

static
int CBufunAdd( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBufunAdd()\n");
}

static
int CBufunDelete( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   printf("\nNA...in CBufunDelete()\n");
}

static
int CBufun( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW=0,CW; /* workWindow,commandWindow */
   Widget PM,RB1,RB2,w1,w2;

   if (WW) goto SKIP;
   /* command window */
   CW=makeUpCW(topLevel,container,
               "seqn=0",
               CBufunPrevious, 
               CBufunNext, 
               CBufunAdd, 
               CBufunDelete);

   /* work window */
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   PM=MMaddWidget(WW,MM_PulldownMenu,"",
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"demonstration : 4 leaved rose (0)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"polynomial fit (1)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"polynomial coeffs drawing (2)",NULL);
   MMaddWidget(PM,MM_PushButtonG,".(3)",NULL);
   MMaddWidget(PM,MM_PushButtonG,".(4)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"matrix print (5)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"matrix parser (6)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"math parser (7)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"matrix switch (8)",NULL);
   MMaddWidget(PM,MM_PushButtonG,".(9)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"standard norm. CDF (10)",NULL);
   MMaddWidget(PM,MM_PushButtonG,"CDF : Cumulative Density of Function (11)",
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"normalization (12)",NULL);
   w1=MMaddWidget(WW,MM_OptionMenu,"",
      XmNlabelString,"type=",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"option :",
      XmNtopWidget,w1,
      MMformLeftAttach(w1),
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"1",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"x no =",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,8,XmNcolumns,8,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"y no =",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,8,XmNcolumns,8,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"z no =",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,8,XmNcolumns,8,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"nrl=",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"ncl=",
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"drl=",
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"dcl=",
      MMformLeftAttach(w2),
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w1=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"nrh=",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"nch=",
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"drh=",
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w2=MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"dch=",
      MMformLeftAttach(w2),
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   w1=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"total=",
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   w2=MMaddWidget(WW,MM_LabelG,"",
      XmNlabelString,"program/name=",
      MMformLeftAttach(w2),
      NULL);
   MMaddWidget(WW,MM_Text,"",
      XmNvalue,"0",
      XmNmaxLength,16,XmNcolumns,16,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w2),
      NULL);
   RB1=MMaddWidget(WW,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,2,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   MMaddWidget(RB1,MM_ToggleButtonG,"line on", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB1,MM_ToggleButtonG,"line off",XmNset,1,XmNmarginHeight,0,NULL);
   RB2=MMaddWidget(WW,MM_RadioBox,"",
      XmNradioBehavior,1,
      XmNspacing,0,
      XmNmarginWidth,2,
      MMformLeftAttach(RB1),
      NULL);
   MMaddWidget(RB2,MM_ToggleButtonG,"text on", XmNset,0,XmNmarginHeight,0,NULL);
   MMaddWidget(RB2,MM_ToggleButtonG,"text off",XmNset,1,XmNmarginHeight,0,NULL);
   MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"graphic context",
      XzNaddCallback,XmNactivateCallback,CBgcAttribute,0,
      MMformLeftAttach(RB2),
      XmNtopOffset,3,
      NULL);
SKIP:
   manageWorkWidget(CW,WW,"/plot/user's function");
}

static
int CBviewLscaleValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;         /* Lower scale widget */
   XtPointer CLIENT_DATA; /* Upper scale widget */
   XtPointer CALL_DATA;
{
   int lower,upper;

   XmScaleGetValue(WIDGET,&lower);
   XmScaleGetValue((Widget)CLIENT_DATA,&upper);
   if (upper<lower+10)
   XmScaleSetValue(WIDGET,upper-10);
}

static
int CBviewUscaleValueChanged( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;         /* Upper scale widget */
   XtPointer CLIENT_DATA; /* Lower scale widget */
   XtPointer CALL_DATA;
{
   int lower,upper;

   XmScaleGetValue((Widget)CLIENT_DATA,&lower);
   XmScaleGetValue(WIDGET,&upper);
   if (upper<lower+10)
   XmScaleSetValue(WIDGET,lower+10);
}

static
int CBviewDefault( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   Widget W;

   W=XtNameToWidget(CLIENT_DATA,"x1");XmScaleSetValue(W,20);
   W=XtNameToWidget(CLIENT_DATA,"y1");XmScaleSetValue(W,20);
   W=XtNameToWidget(CLIENT_DATA,"x2");XmScaleSetValue(W,80);
   W=XtNameToWidget(CLIENT_DATA,"y2");XmScaleSetValue(W,80);
}

static
int CBview( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static Widget WW;
   Widget w1,w2,w3,w4;
   short width;

   if (WW) goto SKIP;
   WW=MMaddWidget(workW,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XzNunmanageWidget,1,
      NULL);
   w1=MMaddWidget(WW,MM_Scale,"x1",
      XmNtitleString,"x1 (lower left)",
      XmNshowValue,True,
      XmNminimum,0, XmNmaximum,100, XmNvalue,20,
      XmNdecimalPoints,2,
      XmNscaleMultiple,5,
      XmNwidth,width=150,
      XmNorientation,XmHORIZONTAL,
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNtopOffset,10,
      XmNleftOffset,10,
      NULL);
   w2=MMaddWidget(WW,MM_Scale,"x2",
      XmNtitleString,"x2 (upper right)",
      XmNshowValue,True,
      XmNminimum,0, XmNmaximum,100, XmNvalue,80,
      XmNdecimalPoints,2,
      XmNscaleMultiple,5,
      XmNwidth,width,
      XmNorientation,XmHORIZONTAL,
      MMformLeftAttach(w1),
      NULL);
   w3=MMaddWidget(WW,MM_Scale,"y1",
      XmNtitleString,"y1 (lower left)",
      XmNshowValue,True,
      XmNminimum,0, XmNmaximum,100, XmNvalue,20,
      XmNdecimalPoints,2,
      XmNscaleMultiple,5,
      XmNwidth,width,
      XmNorientation,XmHORIZONTAL,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w4=MMaddWidget(WW,MM_Scale,"y2",
      XmNtitleString,"y2 (upper right)",
      XmNshowValue,True,
      XmNminimum,0, XmNmaximum,100, XmNvalue,80,
      XmNdecimalPoints,2,
      XmNscaleMultiple,5,
      XmNwidth,width,
      XmNorientation,XmHORIZONTAL,
      MMformLeftAttach(w3),
      NULL);
   XtAddCallback(w1,XmNvalueChangedCallback,CBviewLscaleValueChanged,w2);
   XtAddCallback(w3,XmNvalueChangedCallback,CBviewLscaleValueChanged,w4);
   XtAddCallback(w2,XmNvalueChangedCallback,CBviewUscaleValueChanged,w1);
   XtAddCallback(w4,XmNvalueChangedCallback,CBviewUscaleValueChanged,w3);
   MMaddWidget(WW,MM_PushButtonG,"",
      XmNlabelString,"default",
      XzNaddCallback,XmNactivateCallback,CBviewDefault,WW,
      XmNtopWidget,w3,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w3,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
SKIP:
   manageWorkWidget(0,WW,"/plot/viewport");
}

static
int CBgcAttributeOk( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
  UserDataStack *ud=(UserDataStack *)CLIENT_DATA;
  UserDataNode *this;
  int i;
  XtPointer value;

printf("-v-----------------------------------------------\n");
  for (i=0;i<=ud->index;i++) {
     this=&(ud->udn[i]);
     UDSet(this);
     UDGet(this,&value);

if (this->dataType==UD_HeapString
||  this->dataType==UD_StackString)
printf("%s=%s,p=%s\n",this->varString,value,this->dataPre);
else
printf("%s=%d,p=%d\n",this->varString,value,this->dataPre);

  }
printf("-^-----------------------------------------------\n");
}

static
int CBgcAttributeCancel( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
  CBgcAttributeDefault(WIDGET,CLIENT_DATA,CALL_DATA);
}

static
int CBgcAttributeUndo( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
  UserDataStack *ud=(UserDataStack *)CLIENT_DATA;
  UserDataNode *this;
  int i;

  for (i=0;i<=ud->index;i++) {
     this=&(ud->udn[i]);
     UDUndo(this);
  }
}

static
int CBgcAttributeDefault( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
  UserDataStack *ud=(UserDataStack *)CLIENT_DATA;
  UserDataNode *this;
  int i;

  for (i=0;i<=ud->index;i++) {
     this=&(ud->udn[i]);
     UDReset(this);
  }
}

static
int CBgcAttribute( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   static isThisFirst=1;
   static Widget gcD=0;
   static UserDataStack *ud;
   int udTotal;
   Widget FRAME,FRAME1,FORM,PM,w1,w2,w3;
   short width;
   ArrowButtonTextUserData *TextWABUserData;

   if (gcD) goto SKIP;
   UDOpen(&ud,udTotal=32);
   gcD=MMaddWidget(container,MM_FormDialog,"",
      XmNtitle,"GC (Graphic Context)",
      XmNautoUnmanage,0,
      XzNunmanageWidget,0,
      XmNnoResize,1,
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      XmNmarginWidth,10,
      XmNmarginHeight,10,
      XzNunmanageWidget,1,
      XzNaddCallback,XmNmapCallback,CBpushDialog,0,
      NULL);
   FRAME=MMaddWidget(gcD,MM_Frame,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNmarginWidth,4,
      XmNmarginHeight,4,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"line",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"foreground",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
   UDAddNode(ud,udTotal,
      w1,"l.foreground",TRUE,"white",
      UDSetOptionMenuUserData,
      UDGetOptionMenuUserData);
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"background",
      MMformTopAttach(w1),
      XmNsensitive,0,
      NULL);
   w1=MMaddWidget(FORM,MM_LabelG,"width",
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=1;
   TextWABUserData->uppBoundary=10;
   TextWABUserData->snapValue=1;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"2",
      XmNmaxLength,2,XmNcolumns,2,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"l.width",FALSE,6,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"NotLast", NULL);
   MMaddWidget(PM,MM_PushButtonG,"Butt", NULL);
   MMaddWidget(PM,MM_PushButtonG,"Projecting", NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"cap",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w2,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   UDAddNode(ud,udTotal,
      w1,"l.cap",TRUE,"Butt",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"Meter",NULL);
   MMaddWidget(PM,MM_PushButtonG,"Round",NULL);
   MMaddWidget(PM,MM_PushButtonG,"Bevel",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"join",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   UDAddNode(ud,udTotal,
      w1,"l.join",TRUE,"Bevel",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"Solid",NULL);
   MMaddWidget(PM,MM_PushButtonG,"OnOffDash",NULL);
   MMaddWidget(PM,MM_PushButtonG,"DoubleDash",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"style",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   UDAddNode(ud,udTotal,
      w1,"l.style",TRUE,"Solid",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   w1=MMaddWidget(FORM,MM_LabelG,"dash list",
      XmNmarginHeight,1,
      XmNtopWidget,w1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      NULL);
   w2=MMaddWidget(FORM,MM_Text,"",
      XmNvalue,"2,2",
      XmNmaxLength,7,XmNcolumns,7,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      MMformLeftAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w2,"l.dashList",TRUE,"3,3",
      UDSetTextString,
      UDGetTextString);
   FRAME=MMaddWidget(gcD,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNleftOffset,2,
      XmNmarginWidth,4,
      XmNmarginHeight,4,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"polygon/arc",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"foreground",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
/*
   UDAddNode(ud,udTotal,
      w1,"p.foreground",TRUE,"red",
      MMsetColorPMButton,
      UDGetWidgetUserData);
*/
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"background",
      MMformTopAttach(w1),
      XmNsensitive,0,
      NULL);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"OUTLINE",NULL);
   MMaddWidget(PM,MM_PushButtonG,"AREA",NULL);
   MMaddWidget(PM,MM_PushButtonG,"BOTH",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"drawing",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"FillSolid",NULL);
   MMaddWidget(PM,MM_PushButtonG,"FillOpaqueSolid",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"fill style",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w1,"p.fillStyle",TRUE,"FillSolid",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"EvenOddRule",NULL);
   MMaddWidget(PM,MM_PushButtonG,"WindingRule",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"fill rule",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w1,"p.fillRule",TRUE,"EvenOddRule",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"ArcChord",NULL);
   MMaddWidget(PM,MM_PushButtonG,"ArcPieSlice",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"arc mode",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w1,"p.arcMode",TRUE,"ArcChord",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   w1=MMaddWidget(FORM,MM_StippleOMButton,"",
      XmNlabelString,"stipple",
      MMformTopAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w1,"p.stipple",FALSE,10,
      UDSetOptionMenuUserData,
      UDGetOptionMenuUserData);
   FRAME=MMaddWidget(gcD,MM_Frame,"",
      MMformLeftAttach(FRAME),
      XmNleftOffset,2,
      XmNmarginWidth,4,
      XmNmarginHeight,4,
      XmNrightAttachment,XmATTACH_FORM,
      XmNrightOffset,10,
      NULL);
   MMaddWidget(FRAME,MM_LabelG,"font/text",
      XmNchildType,XmFRAME_TITLE_CHILD,
      XmNchildVerticalAlignment,XmALIGNMENT_CENTER,
      NULL);
   FORM=MMaddWidget(FRAME,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"foreground",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      NULL);
/*
   UDAddNode(ud,udTotal,
      w1,"f.foreground",TRUE,"yellow",
      MMsetColorPMButton,
      UDGetWidgetUserData);
*/
   w1=MMaddWidget(FORM,MM_ColorOMButton,"",
      XmNlabelString,"background",
      MMformTopAttach(w1),
      XmNsensitive,0,
      NULL);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",XzNunmanageWidget,1,NULL);
   MMaddWidget(PM,MM_PushButtonG,"helvetica",NULL);
   MMaddWidget(PM,MM_PushButtonG,"helvetica-bold",NULL);
   MMaddWidget(PM,MM_PushButtonG,"courier",NULL);
   MMaddWidget(PM,MM_PushButtonG,"courier-bold",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"font",
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   UDAddNode(ud,udTotal,
      w1,"f.font",TRUE,"helvetica-bold",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   w1=MMaddWidget(FORM,MM_LabelG,"font width",
      XmNmarginHeight,1,
      MMformTopAttach(w1),
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=1;
   TextWABUserData->uppBoundary=49;
   TextWABUserData->snapValue=1;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"5",
      XmNmaxLength,2,XmNcolumns,2,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"f.width",FALSE,5,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   w1=MMaddWidget(FORM,MM_LabelG,"font height",
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w2,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=2;
   TextWABUserData->uppBoundary=99;
   TextWABUserData->snapValue=1;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"10",
      XmNmaxLength,2,XmNcolumns,2,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"f.height",FALSE,10,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   w1=MMaddWidget(FORM,MM_LabelG,"font space",
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w2,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=2;
   TextWABUserData->uppBoundary=99;
   TextWABUserData->snapValue=1;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"1",
      XmNmaxLength,2,XmNcolumns,2,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"f.space",FALSE,2,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   PM=MMaddWidget(FORM,MM_PulldownMenu,"",
      XmNorientation,XmHORIZONTAL,
      XmNpacking,XmPACK_COLUMN,
      XmNnumColumns,3,
      XzNunmanageWidget,1,
      NULL);
   MMaddWidget(PM,MM_PushButtonG,"upper.left",NULL);
   MMaddWidget(PM,MM_PushButtonG,"upper.center",NULL);
   MMaddWidget(PM,MM_PushButtonG,"upper.right",NULL);
   MMaddWidget(PM,MM_PushButtonG,"middle.left",NULL);
   MMaddWidget(PM,MM_PushButtonG,"middle.center",NULL);
   MMaddWidget(PM,MM_PushButtonG,"middle.right",NULL);
   w3=MMaddWidget(PM,MM_PushButtonG,"lower.left",NULL);
   MMaddWidget(PM,MM_PushButtonG,"lower.center",NULL);
   MMaddWidget(PM,MM_PushButtonG,"lower.right",NULL);
   w1=MMaddWidget(FORM,MM_OptionMenu,"",
      XmNlabelString,"center",
      XmNsubMenuId,PM,
      XmNmenuHistory,w3,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w2,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   UDAddNode(ud,udTotal,
      w1,"f.center",TRUE,"lower.left",
      UDSetOptionMenuLabel,
      UDGetOptionMenuLabel);
   w1=MMaddWidget(FORM,MM_LabelG,"line space",
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w1,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=1;
   TextWABUserData->uppBoundary=10;
   TextWABUserData->snapValue=1;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"1",
      XmNmaxLength,2,XmNcolumns,2,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"f.lineSpace",FALSE,2,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   w1=MMaddWidget(FORM,MM_LabelG,"text angle",
      XmNmarginHeight,1,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w2,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      NULL);
   TextWABUserData=(ArrowButtonTextUserData *)XtMalloc(
      sizeof(ArrowButtonTextUserData));
   TextWABUserData->lowBoundary=-180;
   TextWABUserData->uppBoundary=180;
   TextWABUserData->snapValue=15;
   w2=MMaddWidget(FORM,MM_ArrowButtonText,"",
      XmNvalue,"0",
      XmNmaxLength,4,XmNcolumns,4,
      XmNresizeWidth,1,
      XmNmarginHeight,1,
      MMformLeftAttach(w1),
      XmNuserData,TextWABUserData,
      NULL);
   UDAddNode(ud,udTotal,
      w2,"f.angle",FALSE,0,
      UDSetArrowButtonTextValue,
      UDGetArrowButtonTextValue);
   w1=MMaddWidget(gcD,MM_SeparatorG,"",
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,FORM,
      XmNtopOffset,5,
      XmNleftAttachment,XmATTACH_POSITION,
      XmNleftPosition,1,
      XmNrightAttachment,XmATTACH_POSITION,
      XmNrightPosition,99,
      NULL);
   w1=MMaddWidget(gcD,MM_PushButtonG,"",
      XmNlabelString,"ok",
      XzNaddCallback,XmNactivateCallback,CBgcAttributeOk,ud,
      XzNaddCallback,XmNactivateCallback,CBdeactivate,gcD,
      XmNtopAttachment,XmATTACH_WIDGET,
      XmNtopWidget,w1,
      XmNtopOffset,5,
      XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,w1,
      XmNleftOffset,5,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNbottomOffset,10,
      NULL);
   w1=MMaddWidget(gcD,MM_PushButtonG,"",
      XmNlabelString,"cancel",
      XzNaddCallback,XmNactivateCallback,CBgcAttributeCancel,ud,
      XzNaddCallback,XmNactivateCallback,CBdeactivate,gcD,
      MMformLeftAttach(w1),
      XmNbottomAttachment,XmATTACH_FORM,
      XmNbottomOffset,10,
      NULL);
   w1=MMaddWidget(gcD,MM_PushButtonG,"",
      XmNlabelString,"undo",
      XzNaddCallback,XmNactivateCallback,CBgcAttributeUndo,ud,
      MMformLeftAttach(w1),
      XmNbottomAttachment,XmATTACH_FORM,
      XmNbottomOffset,10,
      NULL);
   MMaddWidget(gcD,MM_PushButtonG,"",
      XmNlabelString,"default",
      XzNaddCallback,XmNactivateCallback,CBgcAttributeDefault,ud,
      MMformLeftAttach(w1),
      XmNbottomAttachment,XmATTACH_FORM,
      XmNbottomOffset,10,
      NULL);

SKIP:
   XtManageChild(gcD);
   if (isThisFirst) {
      isThisFirst=0;
      CBgcAttributeDefault(0,ud,0);
   }
}

static
int CBviewPlot( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   MMsetString(workingD,XmNmessageString,"","running ... \nhold on !");
   XtManageChild(workingD);
}

static
int CBviewScript()
{
   static Widget Wscript;
   Widget D,W;
   int x,y,w,h,column=100;
   char *stream;

   x=0;
   y=20;
   D=viewScriptD;
   if (!D) {
      D=MMaddWidget(container,MM_BulletinBoardDialog,"",
         XmNtitle,GrMotifVersion,
         XmNautoUnmanage,0,
         XzNunmanageWidget,1,
         XmNnoResize,1,
         NULL);
      W=MMaddWidget(D,MM_LabelG,"",
         XmNlabelString,"script:",
         MMbulletinBoardPosition(x,y,0,0),
         NULL);
      XtVaGetValues(W,XmNheight,&h,NULL);
      Wscript=W=MMaddWidget(D,MM_ScrolledText,"text",
         XmNvalue,"",
         XmNmaxLength,10240,XmNcolumns,column,XmNrows,30,
         /* XmNscrollBarDisplayPolicy,XmAS_NEEDED, */
         XmNeditMode,XmMULTI_LINE_EDIT,
         XmNscrollHorizontal,0,
         XmNscrollVertical,1,
         XmNwordWrap,1,
         XmNresizeWidth,0,
         XmNmarginHeight,1,
         XmNcursorPositionVisible,0,
         MMbulletinBoardPosition(x,y+=h+5,0,0),
         XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
         XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
         NULL);
      XtVaGetValues(W,XmNheight,&h,NULL);
      W=MMaddWidget(D,MM_PushButtonG,"",
         XmNlabelString,"refresh",
         MMbulletinBoardPosition(x,y+=h+5,0,0),
         XzNaddCallback,XmNactivateCallback,CBviewScript,0,
         NULL);
      XtVaGetValues(W,XmNwidth,&w,NULL);
      MMaddWidget(D,MM_PushButtonG,"",
         XmNlabelString,"return",
         MMbulletinBoardPosition(x+w+10,y,0,0),
         XzNaddCallback,XmNactivateCallback,CBdeactivate,D,
         NULL);
   }
   /***/
   gotoGlobCommand();
/*
DLLprint(scriptList);
   SCputListToStream(scriptList,column,&stream);
    *** 
   XtVaSetValues(Wscript,XmNvalue,stream,NULL);
   freeEx(stream);
   XtManageChild(D);
   CBpushDialog(D,0,0);
*/
   viewScriptD=D;
}

static
int CBviewMessage()
{
   Widget D,W;
   int x=5,y=20,h;
       x=0;

   D=viewMessageD;
   if (!D) {
      D=MMaddWidget(container,MM_BulletinBoardDialog,"",
         XmNtitle,GrMotifVersion,
         XmNautoUnmanage,0,
         XzNunmanageWidget,1,
         XmNnoResize,1,
         NULL);
      W=MMaddWidget(D,MM_LabelG,"",
         XmNlabelString,"message:",
         MMbulletinBoardPosition(x,y,0,0),
         NULL);
      XtVaGetValues(W,XmNheight,&h,NULL);
      W=MMaddWidget(D,MM_ScrolledText,"",
         XmNvalue,"",
         XmNmaxLength,10240,XmNcolumns,80,XmNrows,20,
         XmNeditMode,XmMULTI_LINE_EDIT,
         XmNscrollHorizontal,0,
         XmNscrollVertical,1,
         XmNwordWrap,1,
         XmNresizeWidth,0,
         XmNmarginHeight,1,
         XmNcursorPositionVisible,0,
         MMbulletinBoardPosition(x,y+=h+5,0,0),
         XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
         XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
         NULL);
      XtVaGetValues(W,XmNheight,&h,NULL);
      MMaddWidget(D,MM_PushButtonG,"",
         XmNlabelString,"return",
         MMbulletinBoardPosition(x,y+=h+5,0,0),
         XzNaddCallback,XmNactivateCallback,CBdeactivate,D,
         NULL);
   }
   XtManageChild(D);
   CBpushDialog(D,0,0);
   viewMessageD=D;
}

static
int CBmenuToggle( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   Widget parent=XtParent(WIDGET);
   Widget *children,W;
   int numChildren;
   char *name;

   XtVaGetValues(parent,XmNnumChildren,&numChildren,NULL);
   if (numChildren) {
      XtVaGetValues(parent,XmNchildren,&children,NULL);
      while (numChildren--) {
         W=children[numChildren];
         if (W==WIDGET) continue;
         name=XtName(W);
         if (!strcmp(name,"toggleButton")) XtVaSetValues(W,XmNset,0,NULL);
      }
   }
   XtVaSetValues(WIDGET,XmNset,1,NULL);
}

static
int manageWorkWidget( CW,WW,labelString )
   Widget CW,WW;
   char *labelString;
{
   if (CW!=currentCmndWidget
   &&  currentCmndWidget) {
      XtUnmanageChild(currentCmndWidget);
      currentCmndWidget=0;
   }
   if (CW) {
      XtVaSetValues(container,XmNcommandWindow,CW,NULL);
      XtManageChild(CW);
      currentCmndWidget=CW;
   }
      
   if (WW!=currentWorkWidget
   &&  currentWorkWidget) {
      XtUnmanageChild(currentWorkWidget);
      currentWorkWidget=0;
   }
   if (WW) {
      XtVaSetValues(workW,XmNworkWindow,WW,NULL);
      XtManageChild(WW);
      MMsetString(messageL,XmNlabelString,"",labelString);
      currentWorkWidget=WW;
/*
      XtVaSetValues(container,XmNmessageWindow,messageWindow,NULL);
      XtManageChild(messageWindow);
*/
   }
}

static
Widget makeUpCW( topLevel,container,label,
                 CBprevious,CBnext,CBadd,CBdelete )
   Widget topLevel,container;
   char *label;
   IPTRFN CBprevious,CBnext,CBadd,CBdelete;
{
   Widget CW,Wok,Wcancel,Wprevious,Wnext,Wadd,Wdelete,Wlabel;

   CW=MMaddWidget(topLevel,MM_Form,"",
      XmNtopAttachment,XmATTACH_FORM,
      XmNbottomAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNrightAttachment,XmATTACH_FORM,
      NULL);
   XtVaSetValues(container,
      XmNcommandWindow,CW,
      NULL);
   Wok=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"ok",
      XmNtopAttachment,XmATTACH_FORM,
      XmNleftAttachment,XmATTACH_FORM,
      XmNleftOffset,2,
      NULL);
   Wcancel=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"cancel",
      XmNtopWidget,Wok,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wok,
      XmNleftAttachment,XmATTACH_WIDGET,
      NULL);
   Wprevious=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"previous",
      XmNtopWidget,Wcancel,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wcancel,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNleftOffset,5,
      NULL);
   Wnext=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"next",
      XmNtopWidget,Wprevious,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wprevious,
      XmNleftAttachment,XmATTACH_WIDGET,
      NULL);
   Wadd=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"add",
      XmNtopWidget,Wnext,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wnext,
      XmNleftAttachment,XmATTACH_WIDGET,
      NULL);
   Wdelete=MMaddWidget(CW,MM_PushButtonG,"",
      XmNlabelString,"delete",
      XmNtopWidget,Wadd,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wadd,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNleftOffset,5,
      NULL);
   Wlabel=MMaddWidget(CW,MM_LabelG,"",
      XmNlabelString,label,
      XmNtopWidget,Wdelete,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNleftWidget,Wdelete,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNleftOffset,5,
      NULL);
   XtAddCallback(Wprevious,XmNactivateCallback,CBprevious,Wlabel);
   XtAddCallback(Wnext,XmNactivateCallback,CBnext,Wlabel);
   XtAddCallback(Wadd,XmNactivateCallback,CBadd,Wlabel);
   XtAddCallback(Wdelete,XmNactivateCallback,CBdelete,Wlabel);
   return CW;
}

static
int CBpushDialog( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   MYdialogStackIndex++;
   if (MYdialogStackIndex>=noof(MYdialogStack)) {
      fprintf(stderr,"Error, MYdialogStack overflow ... "
              "in CBpushDialog()\n");
      exit(1);
   }
   MYdialogStack[MYdialogStackIndex]=
      (Widget)CLIENT_DATA ? (Widget)CLIENT_DATA:WIDGET;
}

static
int CBpopDialog( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA;
   XtPointer CALL_DATA;
{
   while (MYdialogStackIndex>=0)
      XtUnmanageChild(MYdialogStack[MYdialogStackIndex--]);
}

static
void UDOpen( ud,total )
   UserDataStack **ud;
   int total;
{
   *ud=salloc(UserDataStack,1);
   (*ud)->udn=salloc(UserDataNode,total);
   (*ud)->total=total;
   (*ud)->index=-1;
   memset((*ud)->udn,sizeof(UserDataNode),0);
}

static
void UDClose( ud,total )
   UserDataStack *ud;
   int total;
{
   while (--total) free(ud[total].udn);
   free(ud);
}

static
void UDSet( this )
   UserDataNode *this;
{
   XtPointer value;

   (*this->GetDataFrWidget)(this->widget,&value);
   if (this->dataType==UD_HeapString)
         XtFree(this->dataPre);
   this->dataPre=value; /* Because "value" is a string pointer or number */
}

static
void UDReset( this )
   UserDataNode *this;
{
   XtPointer value;

   if (this->dataType==UD_HeapString) {
      (*this->GetDataFrWidget)(this->widget,&value);
      XtFree(value);
      (*this->PutDataToWidget)(this->widget,XtNewString(this->dataDef));
   } else
      (*this->PutDataToWidget)(this->widget,this->dataDef);
}

static
void UDUndo( this )
   UserDataNode *this;
{
   XtPointer value;

   if (this->dataType==UD_HeapString) {
      (*this->GetDataFrWidget)(this->widget,&value);
      XtFree(value);
      (*this->PutDataToWidget)(this->widget,XtNewString(this->dataPre));
   } else
      (*this->PutDataToWidget)(this->widget,this->dataPre);
}

static
void UDGet( this,value )
   UserDataNode *this;
   XtPointer *value;
{
   (*this->GetDataFrWidget)(this->widget,value);
}

static
void UDAddNode( ud,total,
               widget,varString,dataType,value,
               PutDataToWidget,GetDataFrWidget )
   UserDataStack *ud;
   int total;
   Widget widget;
   char *varString;
   int dataType;
   XtPointer value; /* donot care if allocated or not */
   VPTRFN PutDataToWidget,GetDataFrWidget;
{
   UserDataNode *this;

   ud->index++;
   if (ud->index>=ud->total) {
      fprintf(stderr,"Error, no more space to add child .... "
                     "in UDAddNode()\n");
      exit(1);
   }
   this=(ud->udn)+ud->index;
   this->widget=widget;
   this->varString=varString;
   this->dataType=dataType;
   this->dataDef=(dataType==UD_HeapString) ? XtNewString(value):value;
   this->dataPre=(dataType==UD_HeapString) ? XtNewString(value):value;
   this->PutDataToWidget=PutDataToWidget;
   this->GetDataFrWidget=GetDataFrWidget;
}

static
void UDSetWidgetUserData( widget,value )
   Widget widget;
   XtPointer value;
{
   XtVaSetValues(widget,XmNuserData,value,NULL);
}

static
void UDGetWidgetUserData( widget,value )
   Widget widget;
   XtPointer *value;
{
   XtVaGetValues(widget,XmNuserData,value,NULL);
}

static
void UDSetArrowButtonTextValue( widget,value )
   Widget widget;
   XtPointer value;
{
   char buf16[16];

   sprintf(buf16,"%d",value); 
   XmTextSetString(widget,buf16);
}

static
void UDGetArrowButtonTextValue( widget,value )
   Widget widget;
   XtPointer *value;
{
   char *string;

   string=XmTextGetString(widget);
   *value=(XtPointer)atoi(string);
   XtFree(string);
}

static
void UDSetTextString( widget,value )
   Widget widget;
   XtPointer value;
{
   XmTextSetString(widget,value);
}

static
void UDGetTextString( widget,value )
   Widget widget;
   XtPointer *value;
{
   *value=XmTextGetString(widget);
}

static
void UDGetToggleButtonGadgetState( widget,value )
   Widget widget;
   XtPointer *value;
{
   *value=(XtPointer)XmToggleButtonGadgetGetState(widget);
}

static
void UDGetScaleValue( widget,value )
   Widget widget;
   XtPointer *value;
{
   XmScaleGetValue(widget,value);
}

static
void UDSetOptionMenuLabel( widget,value )
   Widget widget;
   XtPointer value;
{
   Widget PM,*children,button;
   int numChildren,i;
   char *string;

   XtVaGetValues(widget,XmNsubMenuId,&PM,NULL);
   XtVaGetValues(PM,XmNnumChildren,&numChildren,NULL);
   XtVaGetValues(PM,XmNchildren,&children,NULL);
   for (i=0;i<numChildren;i++) {
      button=children[i];
      MMgetString(button,XmNlabelString,"",&string);
      if (!strcmp(string,value)) {
         XtVaSetValues(widget,XmNmenuHistory,button,NULL);
         XtFree(string);
         break;
      }
      XtFree(string);
   }
/*
   XtFree(children); ???????????/
*/
}

static
void UDGetOptionMenuLabel( widget,value )
   Widget widget;
   XtPointer *value;
{
   Widget button;
   char *string;

   XtVaGetValues(widget,XmNmenuHistory,&button,NULL);
   MMgetString(button,XmNlabelString,"",&string);
   *value=string;
}


static
void UDSetOptionMenuUserData( widget,value )
   Widget widget;
   XtPointer value;
{
   Widget PM,*children,button;
   int numChildren,i;
   XtPointer ud;

   XtVaGetValues(widget,XmNsubMenuId,&PM,NULL);
   XtVaGetValues(PM,XmNnumChildren,&numChildren,NULL);
   XtVaGetValues(PM,XmNchildren,&children,NULL);
   for (i=0;i<numChildren;i++) {
      button=children[i];
      XtVaGetValues(button,XmNuserData,&ud,NULL);
      if (ud==value) {
         XtVaSetValues(widget,XmNmenuHistory,button,NULL);
         break;
      }
   }
/*
   XtFree(children); ???????????/
*/
}

static
void UDGetOptionMenuUserData( widget,value )
   Widget widget;
   XtPointer *value;
{
   Widget button;

   XtVaGetValues(widget,XmNmenuHistory,&button,NULL);
   XtVaGetValues(button,XmNuserData,value,NULL);
}

static
int openScriptList()
{
   scriptList=0;
   DLLOpen(&scriptList);
   SCaddBlock(scriptList);
}

static
int closeScriptList()
{
}

static
int gotoGlobCommand()
{
/*
   return gotoNodeOfGlob(scriptList,&scriptNode);
*/
}

static
int gotoPlotCommand( i )
   int i; /* 0=current,1,2,3,... */
{
   char *string,*p,*skip="{}/";

   if (!i) {
      MMgetString(message2L,XmNlabelString,"",&string);
      p=strtok(string,skip);
      p=strtok(NULL,skip);
      i=atoi(p);
      XtFree(string);
   }
/*
   return gotoNodeOfNthPlot(scriptList,&scriptNode,i);
*/
}

static
int doScriptToken( targetStr,repetition,valueStr )
   char *targetStr,*valueStr;
   int repetition;
{
   char *new;
   int i;

   if (valueStr) { /* insert/add */
      if (strchr(targetStr,'=')) {
         new=salloc(char,strlen(targetStr)+strlen(valueStr)+1);
         strncpy(new,targetStr,i=strlen(targetStr));
         strcpy(new+i,valueStr);
      } else
         new=strdpl(valueStr);
      putScriptNode(scriptList,scriptNode,targetStr,repetition,new);
   } else { /* delete */
      delScriptNode(scriptList,scriptNode,targetStr,repetition);
   }

DLLprint(scriptList);
}

/******************************************************************************/
/* grm.c */
