/******************************************************************************/
/*                          file name : motif.h                               */
/*                   descriptive name : Motif Library                         */
/*                            Library : X11R5,Motif1.2                        */
/*                           compiler : cc                                    */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                      creating date : 43280322                              */
/*                        update date : 43280819,1022                         */
/*                        update date : 43290301                              */
/*                        update date : 43300527-0529,0705,0917,1207-1230     */
/*                        update date : 43310117-0202                         */
/*                                                                            */
/*                                 MM : My Motif                              */
/*                                                                            */
/******************************************************************************/

#ifndef motif_header_INSTALLED
#define motif_header_INSTALLED 1

/******************************************************************************/

#ifndef __VPTRFN
#define __VPTRFN 1
typedef void   (*VPTRFN)();
#endif
#ifndef __IPTRFN
#define __IPTRFN 1
typedef int    (*IPTRFN)();
#endif

typedef enum {
   MM_Null=0,
/* Containers */
   MM_MainWindow=1,MM_Form,MM_BulletinBoard,MM_RowColumn,MM_ScrolledWindow,
   MM_Frame,
/* Controls */
   MM_SeparatorG,MM_CascadeButtonG,MM_PushButton,MM_PushButtonG,
   MM_ToggleButtonG,MM_ArrowButton,MM_ArrowButtonG,
   MM_Label,MM_LabelG,MM_Scale,MM_ScrollBar,
/* Menus */
   MM_MenuBar,MM_PulldownMenu,MM_OptionMenu,MM_PopupMenu,MM_RadioBox,
/* Dialogs */
   MM_ErrorDialog,MM_FileSelectionDialog,MM_InformationDialog,
   MM_PromptDialog,MM_QuestionDialog,MM_SelectionDialog,MM_WarningDialog,
   MM_WorkingDialog,MM_BulletinBoardDialog,MM_FormDialog,
/* List */
   MM_List,MM_ScrolledList,
/* Text and Text Field */
   MM_Text,MM_ScrolledText,
/* made by shik*/
   MM_ArrowButtonText,
   MM_ColorOMButton,MM_StippleOMButton,
   MM_ColorPMButton
} MMWIDGETYPE;

typedef struct {
   int lowBoundary,uppBoundary,snapValue;
} ArrowButtonTextUserData;

#define XzNunmanageWidget       "unmanageWidget"
#define XzNunmanageChild        "unmanageChild"
#define XzNaddTabGroup          "addTabGroup"
#define XzNaddCallback          "addCallback" /* it takes four arguments */
#define XzNaddEventHandler      "addEventHandler" /* it takes five arguments */

#define MMformPosition(left,right,top,bottom)                                  \
   XmNleftAttachment,XmATTACH_POSITION,                                        \
   XmNrightAttachment,XmATTACH_POSITION,                                       \
   XmNtopAttachment,XmATTACH_POSITION,                                         \
   XmNbottomAttachment,XmATTACH_POSITION,                                      \
   XmNfractionBase,100,                                                        \
   XmNleftPosition,(left),                                                     \
   XmNrightPosition,(right),                                                   \
   XmNtopPosition,(top),                                                       \
   XmNbottomPosition,(bottom)
#define MMbulletinBoardPosition(x,y,width,height)                              \
   XmNx,(int)(x),                                                              \
   XmNy,(int)(y),                                                              \
   XmNwidth,(int)(width),                                                      \
   XmNheight,(int)(height)
#define MMbulletinBoardXY(x,y)                                                 \
   XmNx,(int)(x),                                                              \
   XmNy,(int)(y)

#define MMformTopAttach(widget)                                                \
   XmNtopWidget,(widget),                                                      \
   XmNtopAttachment,XmATTACH_WIDGET,                                           \
   XmNleftWidget,(widget),                                                     \
   XmNleftAttachment,XmATTACH_OPPOSITE_WIDGET
#define MMformLeftAttach(widget)                                               \
   XmNtopWidget,(widget),                                                      \
   XmNtopAttachment,XmATTACH_OPPOSITE_WIDGET,                                  \
   XmNleftWidget,(widget),                                                     \
   XmNleftAttachment,XmATTACH_WIDGET


/******************************************************************************/

void MMopen();
void MMclose();
unsigned long MMcolor();

int MMsetArgument();
int MMsetString();
int MMgetString();
Widget MMaddWidget();

int CBactivate();
int CBdeactivate();
int CBunmanageChildren();
int CBdestroyChildren();

int CBcursorVisibleOnFocus();
int CBcursorInvisibleOnLosingFocus();
int CBscaleSnapValue();

int EVpopUpMenuPostIt();
int EVpopUpMenuPostItByButton3();

/******************************************************************************/
#endif  /* motif.h */

