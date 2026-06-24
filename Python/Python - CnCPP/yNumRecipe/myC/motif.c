/******************************************************************************/
/*                          file name : motif.c                               */
/*                   descriptive name : Motif Library                         */
/*                            Library : Motif1.2,X11R5                        */
/*                           compiler : cc                                    */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                                                                            */
/*                      creating date : 43280322                              */
/*                        update date : 43280819,1022,1030                    */
/*                        update date : 43290301                              */
/*                        update date : 43300527-0529,0705,0917,1206-1230     */
/*                        update date : 43310117-0202                         */
/*                                                                            */
/******************************************************************************/
/*
   xlsfonts
   fslsfonts
   xfd
*/
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <X11/X.h>
#include <X11/Xlib.h>

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
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/Scale.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/ScrollBar.h>
#include <Xm/DrawingA.h>
#include <Xm/FileSB.h>
#include <Xm/SelectioB.h>
#include <Xm/MessageB.h>

#if defined(_UNIXC_)
#include <varargs.h>
#endif

#include "motif.h"

static Widget buildArrowButtonText();
static Widget buildColorOMButton();
static Widget buildStippleOMButton();
static Widget buildColorPMButton();

static struct _MOTIFFUNC {
   MMWIDGETYPE type; 
   Widget (*func)();
} my_motif[]= {
   {MM_MainWindow,          XmCreateMainWindow},
   {MM_Form,                XmCreateForm},
   {MM_BulletinBoard,       XmCreateBulletinBoard},
   {MM_RowColumn,           XmCreateRowColumn},
   {MM_ScrolledWindow,      XmCreateScrolledWindow},
   {MM_Frame,               XmCreateFrame},
   {MM_SeparatorG,          XmCreateSeparatorGadget},
   {MM_CascadeButtonG,      XmCreateCascadeButtonGadget},
   {MM_PushButton,          XmCreatePushButton},
   {MM_PushButtonG,         XmCreatePushButtonGadget},
   {MM_ToggleButtonG,       XmCreateToggleButtonGadget},
   {MM_ArrowButton,         XmCreateArrowButton},
   {MM_ArrowButtonG,        XmCreateArrowButtonGadget},
   {MM_Label,               XmCreateLabel},
   {MM_LabelG,              XmCreateLabelGadget},
   {MM_Scale,               XmCreateScale},
   {MM_ScrollBar,           XmCreateScrollBar},
   {MM_MenuBar,             XmCreateMenuBar},
   {MM_PulldownMenu,        XmCreatePulldownMenu},
   {MM_OptionMenu,          XmCreateOptionMenu},
   {MM_PopupMenu,           XmCreatePopupMenu},
   {MM_RadioBox,            XmCreateRadioBox},
   {MM_ErrorDialog,         XmCreateErrorDialog},
   {MM_FileSelectionDialog, XmCreateFileSelectionDialog},
   {MM_InformationDialog,   XmCreateInformationDialog},
   {MM_PromptDialog,        XmCreatePromptDialog},
   {MM_QuestionDialog,      XmCreateQuestionDialog},
   {MM_SelectionDialog,     NULL},
   {MM_WarningDialog,       XmCreateWarningDialog},
   {MM_WorkingDialog,       XmCreateWorkingDialog},
   {MM_BulletinBoardDialog, XmCreateBulletinBoardDialog},
   {MM_FormDialog,          XmCreateFormDialog},
   {MM_List,                XmCreateList},
   {MM_ScrolledList,        XmCreateScrolledList},
   {MM_Text,                XmCreateText},
   {MM_ScrolledText,        XmCreateScrolledText},
   {MM_ArrowButtonText,     buildArrowButtonText},
   {MM_ColorOMButton,       buildColorOMButton},
   {MM_StippleOMButton,     buildStippleOMButton},
   {MM_ColorPMButton,       buildColorPMButton},
   NULL
};

static Arg al[32];
static int ac=0;

#define MIN(x,y) (((x)<(y)) ? (x):(y))
#define MAX(x,y) (((x)>(y)) ? (x):(y))
#define noof(obj) (sizeof(obj)/sizeof((obj)[0]))

static Display *MMdisplay;
static Screen *MMscreen;
static int MMdepth;

/******************************************************************************/

void MMopen( container )
   Widget container;
{
   MMdisplay=XtDisplay(container);
   MMscreen=XtScreen(container);
   MMdepth=XDefaultDepthOfScreen(MMscreen);
}

void MMclose()
{
}

unsigned long MMcolor( colorName )
   char *colorName;
{
   Colormap cmap;
   XColor px,exact;

   cmap=DefaultColormap(MMdisplay,0);
   XAllocNamedColor(MMdisplay,cmap,colorName,&px,&exact);
   return px.pixel;
}

int MMsetArgument( index,name,value )
   int index;
   String name;
   XtArgVal value;
{
   if (index>=noof(al))
      fprintf(stderr,"Warning, ... <%s:%d> in MMsetArgument()\n",name,index);
   else
      XtSetArg(al[index],name,value);
}

int MMsetString( widget,name,char_set,text )
   Widget widget;
   char *name,*char_set,*text;
{
   Arg MyArgs[1];
   XmString comp;

   XtSetArg(MyArgs[0],name,&comp);
   XtGetValues(widget,MyArgs,1);
   if (!XmStringEmpty(comp)) XmStringFree(comp);
/*
   comp=XmStringSegmentCreate(text,char_set,
       XmSTRING_DIRECTION_L_TO_R,True);
*/
   comp=XmStringCreateLtoR(text,char_set);
   XtSetArg(MyArgs[0],name,comp);
   XtSetValues(widget,MyArgs,1);
}

int MMgetString( widget,name,char_set,text )
   Widget widget;
   char *name,*char_set,**text;
{
   XtArgVal value;

   XtVaGetValues(widget,name,&value,NULL);
   XmStringGetLtoR(value,char_set,text);
   if (!XmStringEmpty(value)) XmStringFree(value);
}

Widget MMaddWidget( va_alist )
   va_dcl
{
   va_list ap;
   Widget parent,widget,child;
   MMWIDGETYPE type;
   char *widget_name;
   String name;
   XtArgVal value;
   XmString string[10];
   int stringCount;
   Arg afterWork[10];
   int afterWorkCount;
   int unmanageWidget=0;
   int i;

#if __COMPILER__==__UNIXC__
   va_start(ap);
   parent=va_arg(ap,Widget);
   type=va_arg(ap,MMWIDGETYPE);
   widget_name=va_arg(ap,char*);
   name=va_arg(ap,String);
   ac=0;
   stringCount=0;
   afterWorkCount=0;
   while (name) {
      if (stringCount>=noof(string)) {
         fprintf(stderr,
                 "Warning, ... stringCount(%d)>=%d in MMaddWidget()\n",
                 stringCount,noof(string));
         exit(1);
      }
      if (afterWorkCount>=noof(afterWork)) {
         fprintf(stderr,
                 "Warning, ... afterWorkCount(%d)>=%d in MMaddWidget()\n",
                 afterWorkCount,noof(afterWork));
         exit(1);
      }
      if (!strcmp(name,XmNlabelString)
      || !strcmp(name,XmNacceleratorText)
      || !strcmp(name,XmNtitleString)
      || !strcmp(name,XmNselectionLabelString)
      || !strcmp(name,XmNmessageString)
      || !strcmp(name,XmNdialogTitle)) {
         value=va_arg(ap,XtArgVal); 
         string[stringCount]=XmStringCreateLtoR(value,XmFONTLIST_DEFAULT_TAG);
         MMsetArgument(ac++,name,string[stringCount++]);
      } else if (!strcmp(name,XzNunmanageChild)
      || !strcmp(name,XzNaddTabGroup)) {
         value=va_arg(ap,XtArgVal); 
         afterWork[afterWorkCount].name=name;
         afterWork[afterWorkCount].value=value;
         afterWorkCount++;
      } else if (!strcmp(name,XzNaddCallback)) {
         afterWork[afterWorkCount].name=name;
         afterWork[afterWorkCount++].value=va_arg(ap,XtArgVal); 
         afterWork[afterWorkCount].name=(char*)va_arg(ap,IPTRFN);
         afterWork[afterWorkCount++].value=va_arg(ap,XtArgVal); 
      } else if (!strcmp(name,XzNaddEventHandler)) {
         afterWork[afterWorkCount].name=name;
         afterWork[afterWorkCount++].value=va_arg(ap,EventMask); 
         afterWork[afterWorkCount].name=(char*)va_arg(ap,Boolean);
         afterWork[afterWorkCount++].value=(XtArgVal)va_arg(ap,IPTRFN); 
         afterWork[afterWorkCount].name=(char*)va_arg(ap,XtPointer);
         afterWork[afterWorkCount++].value=0;
      } else if (!strcmp(name,XzNunmanageWidget)) {
         unmanageWidget=va_arg(ap,XtArgVal); 
      } else {
         value=va_arg(ap,XtArgVal); 
         MMsetArgument(ac++,name,value);
      }
      name=va_arg(ap,String);
   }
   va_end(ap);
   i=0;
   while (my_motif[i].type) {
      if (my_motif[i].type==type) {
         if (!(my_motif[i].func)) {
            fprintf(stderr,"Warning, no creating function .. in AddWidget()\n");
            exit(1);
         }
         widget=(*(my_motif[i].func))(parent,widget_name,al,ac);
         if (!unmanageWidget)
            XtManageChild(widget);
         break;
      } else
         i++;
   }
   if (i>=noof(my_motif)) {
      fprintf(stderr,"Error, ... unknown widget in AddWidget()\n");
      exit(1);
   }
   while (stringCount--)
      XmStringFree(string[stringCount]);
   for (i=0;i<afterWorkCount;i++) {
      if (!strcmp(afterWork[i].name,XzNunmanageChild)) {
         switch (type) {
            case MM_ErrorDialog :
            case MM_InformationDialog :
            case MM_QuestionDialog :
            case MM_SelectionDialog :
            case MM_WarningDialog :
            case MM_WorkingDialog :
                 child=XmMessageBoxGetChild(
                       widget,afterWork[i].value);
                 break;
            case MM_FileSelectionDialog :
            case MM_PromptDialog :
                 child=XmSelectionBoxGetChild(
                       widget,afterWork[i].value);
                 break;
         }
         if (child)
            XtUnmanageChild(child);
      } else if (!strcmp(afterWork[i].name,XzNaddTabGroup)) {
         if (afterWork[i].value)
            XmAddTabGroup(widget);
      } else if (!strcmp(afterWork[i].name,XzNaddCallback)) {
         XtAddCallback(widget,(String)afterWork[i].value,
            (IPTRFN)afterWork[i+1].name,(XtArgVal)afterWork[i+1].value);
         i++;
      } else if (!strcmp(afterWork[i].name,XzNaddEventHandler)) {
         XtAddEventHandler(widget,(EventMask)afterWork[i].value,
            (Boolean)afterWork[i+1].name,(IPTRFN)afterWork[i+1].value,
            (XtPointer)afterWork[i+2].name);
         i++;
      }
   }
/*
   WSpush(widget);
*/
   return widget;
#endif
#if __COMPILER__==__TURBO__ \
 || __COMPILER__==__MICROSOFT__
#endif
}

int CBactivate( widget,client_data,call_data )
   Widget widget;
   XtPointer client_data;
   XtPointer call_data;
{
   XmAnyCallbackStruct *any=(XmAnyCallbackStruct*)call_data;
   if (client_data)
      XtManageChild((Widget)client_data);
   else
      XtManageChild(widget);
}

int CBdeactivate( widget,client_data,call_data )
   Widget widget;
   XtPointer client_data;
   XtPointer call_data;
{
   XmAnyCallbackStruct *any=(XmAnyCallbackStruct*)call_data;
   if (client_data)
      XtUnmanageChild((Widget)client_data);
   else
      XtUnmanageChild(widget);
}

int MMunmanageChildren( widget )
   Widget widget;
{
   Widget *children;
   int numChildren;

   XtVaGetValues(widget,XmNnumChildren,&numChildren,NULL);
   if (numChildren) {
      XtVaGetValues(widget,XmNchildren,&children,NULL);
      XtUnmanageChildren(children,numChildren);
   }
}

int MMdestroyChildren( widget )
   Widget widget;
{
   Widget *children;
   int numChildren;

   XtVaGetValues(widget,XmNnumChildren,&numChildren,NULL);
   if (numChildren) {
      XtVaGetValues(widget,XmNchildren,&children,NULL);
      while (numChildren--)
         XtDestroyWidget(children[numChildren]);
   }
}

int CBcursorVisibleOnFocus( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   XtVaSetValues(W,XmNcursorPositionVisible,1,NULL);
}

int CBcursorInvisibleOnLosingFocus( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   XtVaSetValues(W,XmNcursorPositionVisible,0,NULL);
}

int CBscaleSnapValue( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   int i;
   extern double stepRound();

   XmScaleGetValue(W,&i);
   i=(int)stepRound((double)i,(double)(int)client_data);
   XmScaleSetValue(W,i);
}

int EVpopUpMenuPostIt( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   Widget popup=(Widget)client_data;
   XButtonPressedEvent *bevent=(XButtonPressedEvent *)call_data;

   XmMenuPosition(popup,bevent);
   XtManageChild(popup);
}

int EVpopUpMenuPostItByButton3( W,client_data,call_data )
   Widget W;
   XtPointer client_data;
   XtPointer call_data;
{
   XButtonPressedEvent *bevent=(XButtonPressedEvent *)call_data;

   if (bevent->button!=3) return;
   EVpopUpMenuPostIt(W,client_data,call_data);
}

static
int CBtextLeftArrow( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA; /* text widget 
                             should have ArrowButtonTextUserData userData */
   XtPointer CALL_DATA;
{
   ArrowButtonTextUserData *userData;
   char *str,buf256[256];
   int i;

   XtVaGetValues(CLIENT_DATA,XmNuserData,&userData,NULL);
   if (str=XmTextGetString(CLIENT_DATA)) {
      i=atoi(str);
      XtFree(str);
      if (i>userData->lowBoundary) {
         i-=userData->snapValue;
         if (i<userData->lowBoundary) i=userData->lowBoundary;
         sprintf(buf256,"%d",i);
         XmTextSetString(CLIENT_DATA,buf256);
      }
   }
}

static
int CBtextRightArrow( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;
   XtPointer CLIENT_DATA; /* text widget 
                             should have ArrowButtonTextUserData userData */
   XtPointer CALL_DATA;
{
   ArrowButtonTextUserData *userData;
   char *str,buf256[256];
   int i;
   XEvent event;

   XtVaGetValues(CLIENT_DATA,XmNuserData,&userData,NULL);
   if (str=XmTextGetString(CLIENT_DATA)) {
      i=atoi(str);
      XtFree(str);
      if (i<userData->uppBoundary) {
         i+=userData->snapValue;
         if (i>userData->uppBoundary) i=userData->uppBoundary;
         sprintf(buf256,"%d",i);
         XmTextSetString(CLIENT_DATA,buf256);
      }
   }
}


static
Widget buildArrowButtonText( parent,name,arglist,argcount )
   Widget parent;
   String name;
   ArgList arglist;
   Cardinal argcount;
{
   Widget FORM,TEXT,w1,w2;

/*
   FORM generation ...
*/
   TEXT=XmCreateText(parent,name,arglist,argcount);
   XtVaSetValues(TEXT,
      XmNcursorPositionVisible,0,
      XzNaddCallback,XmNfocusCallback,CBcursorVisibleOnFocus,0,
      XzNaddCallback,XmNlosingFocusCallback,CBcursorInvisibleOnLosingFocus,0,
      NULL);
   w1=MMaddWidget(parent,MM_ArrowButtonG,"",
      XmNshadowThickness,1,
      XmNarrowDirection,XmARROW_LEFT,
      XzNaddCallback,XmNactivateCallback,CBtextLeftArrow,TEXT,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNtopWidget,TEXT,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNleftWidget,TEXT,
      NULL);
   w2=MMaddWidget(parent,MM_ArrowButton,"",
      XmNshadowThickness,1,
      XmNarrowDirection,XmARROW_RIGHT,
/*
      XzNaddCallback,XmNactivateCallback,CBtextRightArrow,TEXT,
*/
      XzNaddEventHandler,ButtonPressMask,FALSE,CBtextRightArrow,TEXT,
      XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,
      XmNtopWidget,w1,
      XmNleftAttachment,XmATTACH_WIDGET,
      XmNleftWidget,w1,
      NULL); 
   return TEXT;
}

#define MMAddColorButton(RC,colorName)                                         \
   MMaddWidget((RC),MM_PushButton,"",                                          \
      XmNbackground,MMcolor(colorName),                                        \
      XmNuserData,colorName,                                                   \
      XmNrecomputeSize,0,                                                      \
      XmNwidth,20,                                                             \
      XmNheight,20,                                                            \
      NULL);

static
Widget buildColorOMButton( parent,name,arglist,argcount )
   Widget parent;
   String name;
   ArgList arglist;
   Cardinal argcount;
{
   Widget PM,optionMenu;
   static char *colorName[]={
      "white","black","DimGray","red","gold",
      "green","yellow","blue","magenta","cyan1",
      "DarkSlateGray1","aquamarine1","DarkSeaGreen1","SeaGreen1","PaleGreen1",
      "SpringGreen1","green1","chartreuse1"
   };
#ifndef noof
#define noof(obj) (sizeof(obj)/sizeof((obj)[0]))
#endif
   Window window;
   GC gcBackground;
   Pixmap pixmap;
   XGCValues values;
   unsigned long valueMask=0L;
   int total,i,width=25,height=25;

   optionMenu=XmCreateOptionMenu(parent,name,arglist,argcount);
   PM=MMaddWidget(parent,MM_PulldownMenu,"",
      XmNorientation,XmVERTICAL,
      XmNpacking,XmPACK_COLUMN,
      XmNnumColumns,5,
      XzNunmanageWidget,1,
      NULL);
   window=RootWindow(MMdisplay,0);
   gcBackground=XCreateGC(MMdisplay,window,0,0);
   valueMask=GCFunction|GCForeground;
   values.function=GXcopy;
   total=noof(colorName);
   for (i=0;i<total;i++) {
      pixmap=XCreatePixmap(MMdisplay,window,width,height,MMdepth);
      values.foreground=MMcolor(colorName[i]);
      XChangeGC(MMdisplay,gcBackground,valueMask,&values);
      XFillRectangle(MMdisplay,pixmap,gcBackground,0,0,width,height);
      MMaddWidget(PM,MM_PushButton,"",
         XmNuserData,colorName[i],
         XmNlabelType,XmPIXMAP,
         XmNlabelPixmap,pixmap,
         XmNborderWidth,0,
         XmNmarginWidth,1,
         XmNmarginHeight,1,
         NULL);
   }
   XtVaSetValues(optionMenu,
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      NULL);
   return optionMenu;
}

static
Widget buildStippleOMButton( parent,name,arglist,argcount )
   Widget parent;
   String name;
   ArgList arglist;
   Cardinal argcount;
{
   extern char *GEgetMyStipple8x8();
   Window window;
   Widget PM,optionMenu;
   GC gcBackground,gc;
static Pixmap pixmap[32];
   XGCValues values;
   unsigned long valueMask=0L;
   int total=32,width=25,height=25,i;

   optionMenu=XmCreateOptionMenu(parent,name,arglist,argcount);
   PM=MMaddWidget(parent,MM_PulldownMenu,"",
      XmNorientation,XmVERTICAL,
      XmNpacking,XmPACK_COLUMN,
      XmNnumColumns,5,
      XzNunmanageWidget,1,
      NULL);
   window=RootWindow(MMdisplay,0);
   gcBackground=XCreateGC(MMdisplay,window,0,0);
   valueMask=GCFunction|GCForeground;
   values.function=GXcopy;
   values.foreground=MMcolor("black");
   XChangeGC(MMdisplay,gcBackground,valueMask,&values);
   valueMask=GCFunction|GCForeground|GCFillStyle|GCStipple;
   values.function=GXcopy;
   values.foreground=MMcolor("white");
   values.fill_style=FillStippled;
   gc=XCreateGC(MMdisplay,window,0,0);
   for (i=0;i<total;i++) {
      pixmap[i]=XCreatePixmap(MMdisplay,window,width,height,MMdepth);
      XFillRectangle(MMdisplay,pixmap[i],gcBackground,0,0,width,height);
      values.stipple=XCreateBitmapFromData(
         MMdisplay,window,GEgetMyStipple8x8(i),8,8);
      XChangeGC(MMdisplay,gc,valueMask,&values);
      XFillRectangle(MMdisplay,pixmap[i],gc,0,0,width,height);
      XFreePixmap(MMdisplay,values.stipple);
      MMaddWidget(PM,MM_PushButton,"",
         XmNuserData,i,
         XmNlabelType,XmPIXMAP,
         XmNlabelPixmap,pixmap[i],
         XmNborderWidth,0,
         NULL);
   }
   XtVaSetValues(optionMenu,
      XmNsubMenuId,PM,
      XmNmarginWidth,0,
      XmNmarginHeight,1,
      NULL);
   XFreeGC(MMdisplay,gcBackground);
   XFreeGC(MMdisplay,gc);
   return optionMenu;
}

static
int EVsetPulldownMenuUserData( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;         /* PushButton */
   XtPointer CLIENT_DATA; /* PulldownMenu */
   XtPointer CALL_DATA;
{
   XtVaSetValues(CLIENT_DATA,XmNuserData,WIDGET,NULL);
}

static
int CBactivateColorButton( WIDGET,CLIENT_DATA,CALL_DATA )
   Widget WIDGET;         /* Color PushButton */
   XtPointer CLIENT_DATA; /* PopUpMenu */
   XtPointer CALL_DATA;
{
   Widget button;
   unsigned long color,foreground;
   char *colorName,*ud;

   XtVaGetValues(WIDGET,
      XmNbackground,&color,
      XmNuserData,&colorName,
      NULL);
   XtVaGetValues(CLIENT_DATA,XmNuserData,&button,NULL);

   foreground=MMcolor("black");
   foreground^=color;
   XtVaGetValues(WIDGET,XmNuserData,&colorName,NULL);
   XtVaGetValues(button,XmNuserData,&ud,NULL);
   if (ud) XtFree(ud);
   XtVaSetValues(button,
      XmNforeground,foreground,
      XmNbackground,color,
      XmNuserData,XtNewString(colorName),
      NULL);
}

#define MMAddcolorbutton(RC,colorName)                                         \
   MMaddWidget((RC),MM_PushButton,"",                                          \
      XmNbackground,MMcolor(colorName),                                        \
      XmNuserData,colorName,                                                   \
      XmNrecomputeSize,0,                                                      \
      XmNwidth,20,                                                             \
      XmNheight,20,                                                            \
      XzNaddCallback,XmNactivateCallback,CBactivateColorButton,(RC),           \
      NULL);

static
Widget buildColorPMButton( parent,name,arglist,argcount )
   Widget parent;
   String name;
   ArgList arglist;
   Cardinal argcount;
{
   Widget button,PM;

   button=XmCreatePushButton(parent,name,arglist,argcount);
   PM=MMaddWidget(parent,MM_PopupMenu,"",
      XmNorientation,XmVERTICAL,
      XmNpacking,XmPACK_COLUMN,
      XmNnumColumns,5,
      XzNunmanageWidget,1,
      NULL);
   MMAddcolorbutton(PM,"white");
   MMAddcolorbutton(PM,"black");
   MMAddcolorbutton(PM,"DimGray");
   MMAddcolorbutton(PM,"red");
   MMAddcolorbutton(PM,"gold");
   MMAddcolorbutton(PM,"green");
   MMAddcolorbutton(PM,"yellow");
   MMAddcolorbutton(PM,"blue");
   MMAddcolorbutton(PM,"magenta");
   MMAddcolorbutton(PM,"cyan1");
   MMAddcolorbutton(PM,"DarkSlateGray1");
   MMAddcolorbutton(PM,"aquamarine1");
   MMAddcolorbutton(PM,"DarkSeaGreen1");
   MMAddcolorbutton(PM,"SeaGreen1");
   MMAddcolorbutton(PM,"PaleGreen1");
   MMAddcolorbutton(PM,"SpringGreen1");
   MMAddcolorbutton(PM,"green1");
   MMAddcolorbutton(PM,"chartreuse1");
   XtAddEventHandler(button,
      EnterWindowMask,False,EVsetPulldownMenuUserData,PM);
   XtAddEventHandler(button,
      ButtonReleaseMask,False,EVpopUpMenuPostIt,PM);
/*
      ButtonPressMask,False,EVpopUpMenuPostIt,PM);
*/
   return button;
}

int MMsetColorPMButton( widget,colorName )
   Widget widget;
   char *colorName;
{
   unsigned long color,foreground;
   char *ud;

   color=MMcolor(colorName);
   foreground=MMcolor("black");
   foreground^=color;
   XtVaGetValues(widget,XmNuserData,&ud,NULL);
   if (ud) XtFree(ud);
   XtVaSetValues(widget,
      XmNforeground,foreground,
      XmNbackground,color,
      XmNuserData,XtNewString(colorName),
      NULL);
   return 1;
}

/******************************************************************************/
/* end of motif.c */

