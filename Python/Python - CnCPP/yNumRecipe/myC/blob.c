/******************************************************************************/
/*                           file name : blob.c                               */
/*                    descriptive name : Binary Large OBject                  */
/*                         environment : SUN UNIX 4.0.3                       */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                       creating date : 43260416                             */
/*                         update date : 43260416-43260419                    */
/*                         update date : 43280328-43280602                    */
/*                         update date : 43320331+0706                        */
/*                         update date : 43330224+0308+1006                   */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myCore.h"
#include "any.h"
#include "tools.h"
#include "blob.h"
#include "str.h"

/******************************************************************************/

BLOBATTR BLOBTABLE[BL_TOTAL];

#define SetBlobTable(_id,_typedef)                                             \
        BLOBTABLE[(int)(_id)].type=(_id);                                      \
        BLOBTABLE[(int)(_id)].size=sizeof(_typedef);                           \
        BLOBTABLE[(int)(_id)].name="_id";                                      \
        BLOBTABLE[(int)(_id)].proc=NULL;                                       \
        BLOBTABLE[(int)(_id)].print=NULL;

int BLOpenList();
int BLCloseList();
 
int BLAlloObject();
int BLFreeObject();
int BLAddrObject(); /* !!? */
int BLHintObject(); /* !!? */

int BLSetProcedure();
int BLExecute();

int BLAddCommand();
int BLAddHeader();
int BLAdd2DMatrix();
int BLAdd3DMatrix();
int BLAddGC();
int BLAddData();
int BLAddPoint();
int BLAddLine();
int BLAddPoly();
int BLAddArc();
int BLAddFontAttr();
int BLAddText();
int BLAddClipWin();
int BLAddDataBase();
int BLAddPrint();

int BLGetStatus();
int BLFindObject();

int BLFreadList();
int BLFwriteList();

int BLDBOpen();
int BLDBClose();
int BLDBGetNode();
int BLDBPutNode();
int BLDBRead();
int BLDBWrite();
int BLDBtoPrevAddress();
int BLDBtoNextAddress();
int BLDBtoAbsPrevAddress();
int BLDBtoAbsNextAddress();

int BLDBPrint();

/******************************************************************************/

int BLOpenList( list )
   ANYLIST **list;
{
   AnyOpenLinkedObject(list,sizeof(BLOBLIST));
   /**/
   memset((char*)BLOBTABLE,0,sizeof(BLOBTABLE));
   SetBlobTable(BL_NULL,        BLOBNULL      );
   SetBlobTable(BL_COMMAND,     BLOBTEXT      );
   SetBlobTable(BL_HEADER,      BLOBHEADER    );
   SetBlobTable(BL_2DMDATA,     BLOB2DMDATA   );
   SetBlobTable(BL_3DMDATA,     BLOB3DMDATA   );
   SetBlobTable(BL_GC,          BLOBGC        );
   SetBlobTable(BL_DATA,        BLOBDATA      );
   SetBlobTable(BL_POINT,       BLOBPOINT     );
   SetBlobTable(BL_LINE,        BLOBLINE      );
   SetBlobTable(BL_POLY,        BLOBPOINT     );
   SetBlobTable(BL_ARC,         BLOBARC       );
   SetBlobTable(BL_TEXT,        BLOBPOINT     );
   SetBlobTable(BL_CLIPWIN,     BLOBCLIPWIN   );
   SetBlobTable(BL_DATABASE,    BLOBTEXT      );
   SetBlobTable(BL_PRINT,       BLOBPRINT     );
   return TRUE;
}

int BLCloseList( list )
   ANYLIST *list;
{
   if (list)
      AnyCloseLinkedObject(list,NULL);
   return TRUE;
}

int BLDuplicateList( list,ppNew )
   BLOBLIST *list,**ppNew;
{
   int nCount,nType,nTotal;
   BLOBNODE *node;

   BLOpenList(ppNew);
   nCount=0;
   for (node=list->head;node;node=node->next) {
      nType=BLNodeType(node);
      nTotal=BLNodeTotal(node);
      BLAlloObject(*ppNew,nType,nTotal,BLNodeObjAddr(node));
      nCount++;
   }
   return nCount;
}

int BLAlloObject( list,type,total,objs )
   BLOBLIST *list;
   BLOBTYPE type;
   int total;
   Pointer objs;
{
   BLOBNODE *node;
   unsigned long nSize;

   if (type==BL_TEXT) {
      nSize=sizeof(BLOBNODE)+BLOBTABLE[(int)type].size+total;
      node=(BLOBNODE*)malloc(nSize);
      node->any.type=type;
      node->any.total=total;
      memcpy((Pointer)node+sizeof(BLOBNODE),objs,nSize-sizeof(BLOBNODE));
      AnyAddDLObject(list,node);      
      return TRUE;
   }
   nSize=sizeof(BLOBNODE)+BLOBTABLE[(int)type].size*total;
   node=(BLOBNODE*)malloc(nSize);
   node->any.type=type;
   node->any.total=total;
   memcpy((Pointer)node+sizeof(BLOBNODE),objs,
          BLOBTABLE[(int)type].size*total);
   AnyAddDLObject(list,node);
   return TRUE;
}

int BLFreeObject( list,node )
   BLOBLIST *list;
   BLOBNODE *node;
{
   AnyDelDLObject(list,node);
   free(node);
   return TRUE;
}

int BLAddrObject( node,index,addr )
   BLOBNODE *node;
   int index;
   Pointer *addr;
{
   BLOBTYPE type=node->any.type;

   if (index>=node->any.total) {
      *addr=NULL;
   } else {
      *addr=(char*)node+sizeof(BLOBNODE);
      *addr+=index*BLOBTABLE[(int)type].size;
   }
   return TRUE;
}

int BLHintObject( list,nNode,nSub,nTotalSize )
   BLOBLIST *list;
   int *nNode,*nSub,*nTotalSize;
{
   BLOBNODE *node;
   int NodeNo=0,SubNo=0,TotSize=0;

   node=list->head;
   while (node) {
      SubNo+=node->any.total;
      TotSize+=BLOBTABLE[(int)node->any.type].size*node->any.total;
      NodeNo++; 
      node=node->next;
   }
   *nNode=NodeNo;
   *nSub=SubNo;
   *nTotalSize=TotSize;
   return TRUE;
}

int BLSetProcedure( type,proc )
   BLOBTYPE type;
   IPTRFN proc;
{
   BLOBTABLE[(int)type].proc=proc;
   return TRUE;
}

int BLExecute( list )
   BLOBLIST *list;
{
   BLOBNODE *node;

   node=list->head;
   while (node) {
      if (BLOBTABLE[(int)node->any.type].proc)
      (*BLOBTABLE[(int)node->any.type].proc)
      ((Pointer)node+sizeof(BLOBNODE),node->any.total);
      node=node->next;
   }
   return TRUE;
}

int BLAddCommand( list,addr,total )
   BLOBLIST *list;
   BLOBTEXT *addr;
   int total;
{
   return BLAlloObject(list,BL_COMMAND,total,addr);
}

int BLAddHeader( list,addr,total )
   BLOBLIST *list;
   BLOBHEADER *addr;
   int total;
{
   return BLAlloObject(list,BL_HEADER,total,addr);
}

int BLAdd2DMatrix( list,addr,total )
   BLOBLIST *list;
   BLOB2DMDATA *addr;
   int total;
{
   return BLAlloObject(list,BL_2DMDATA,total,addr);
}

int BLAdd3DMatrix( list,addr,total )
   BLOBLIST *list;
   BLOB3DMDATA *addr;
   int total;
{
   return BLAlloObject(list,BL_3DMDATA,total,addr);
}

int BLAddGC( list,addr,total )
   BLOBLIST *list;
   BLOBGC *addr;
   int total;
{
   return BLAlloObject(list,BL_GC,total,addr);
}

int BLAddData( list,addr,total )
   BLOBLIST *list;
   BLOBDATA *addr;
   int total;
{
   return BLAlloObject(list,BL_DATA,total,addr);
}

int BLAddPoint( list,addr,total )
   BLOBLIST *list;
   BLOBPOINT *addr;
   int total;
{
   return BLAlloObject(list,BL_POINT,total,addr);
}

int BLAddLine( list,addr,total )
   BLOBLIST *list;
   BLOBLINE *addr;
   int total;
{
   return BLAlloObject(list,BL_LINE,total,addr);
}

int BLAddPoly( list,addr,total )
   BLOBLIST *list;
   BLOBPOINT *addr;
   int total;
{
   return BLAlloObject(list,BL_POLY,total,addr);
}

int BLAddArc( list,addr,total )
   BLOBLIST *list;
   BLOBARC *addr;
   int total;
{
   return BLAlloObject(list,BL_ARC,total,addr);
}

int BLAddText( list,addr,total,x,y )
   BLOBLIST *list;
   BLOBTEXT *addr;
   int total;
   double x,y;
{
   BLOBTEXT *ptr;
   char *p;

   ptr=(BLOBTEXT*)malloc(sizeof(BLOBPOINT)+sizeof(BLOBTEXT)*total);
   ((BLOBPOINT*)ptr)->x=x;
   ((BLOBPOINT*)ptr)->y=y;
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   memcpy(p,addr,sizeof(BLOBTEXT)*total);
   BLAlloObject(list,BL_TEXT,total,ptr);
   free(ptr);
   return TRUE;
}

int BLAddClipWin( list,addr,total )
   BLOBLIST *list;
   BLOBCLIPWIN *addr;
   int total;
{
   return BLAlloObject(list,BL_CLIPWIN,total,addr);
}

int BLAddDataBase( list,addr,total )
   BLOBLIST *list;
   BLOBTEXT *addr;
   int total;
{
   return BLAlloObject(list,BL_DATABASE,total,addr);
}

int BLAddPrint( list,addr,total )
   BLOBLIST *list;
   BLOBPRINT *addr;
   int total;
{
   return BLAlloObject(list,BL_PRINT,total,addr);
}

int BLGetStatus( list,size )
   BLOBLIST *list;
   int *size;
{
   BLOBNODE *node;
   int tot;

   node=list->head;
   tot=0;
   *size=0;
   while (node) {
      tot++;
      *size+=sizeof(BLOBNODE)+
             BLOBTABLE[(int)node->any.type].size*node->any.total;
      node=node->next;
   }
   return tot;
}

int BLFindObject( list,ppNode,nBlobType,nKey )
   BLOBLIST *list;
   BLOBNODE **ppNode;
   int nBlobType,nKey;
/*
 * nKey : 'H','L','h','l'
 */
{
   BLOBNODE *pTracer;

   if (!*ppNode) return 0;

   pTracer=*ppNode;
   *ppNode=(BLOBNODE *)0;
   switch (nKey) {
   case 'H' :
      if (BLNodeType(list->head)==nBlobType) {
         *ppNode=list->head;
         return 1;
      } else {
         pTracer=list->head;
         while (pTracer!=list->tail->next) {
            if (BLNodeType(pTracer)==nBlobType) {
               *ppNode=pTracer;
               return 1;
            }
            pTracer=pTracer->next;
         }
      }
      return 0;
   case 'L' :
      if (BLNodeType(list->tail)==nBlobType) {
         *ppNode=list->tail;
         return 1;
      } else {
         pTracer=list->tail;
         while (pTracer!=list->head->prev) {
            if (BLNodeType(pTracer)==nBlobType) {
               *ppNode=pTracer;
               return 1;
            }
            pTracer=pTracer->prev;
         }
      }
      return 0;
   case 'h' :
      if (pTracer!=list->head)
         pTracer=pTracer->prev;
      while (pTracer!=list->head->prev) {
         if (BLNodeType(pTracer)==nBlobType) {
            *ppNode=pTracer;
            return 1;
         }
         pTracer=pTracer->prev;
      }
      if (BLNodeType(pTracer)==nBlobType) {
         *ppNode=pTracer;
         return 1;
      }
      return 0;
   case 'l' : /* 2000.0310+1006 */
      while (pTracer!=list->tail->next) {
         if (BLNodeType(pTracer)==nBlobType) {
            *ppNode=pTracer;
            return 1;
         }
         pTracer=pTracer->next;
      }
      return 0;
   }
   return TRUE;
}

int BLFreadList( name,list )
   char *name;
   BLOBLIST *list;
{
   FILE *f;
   BLOBNODE any;
   char *buf;
   int size;

   if (!(f=fopen(name,"r+b")))
      return FALSE;
   do {
      if (!fread(&any,sizeof(char),sizeof(BLOBNODE),f))
         break;
      size=BLOBTABLE[(int)(any.any.type)].size*(any.any.total);

      buf=(char*)malloc(sizeof(char)*size);
      if (!fread(buf,sizeof(char),size,f))
         break;
      BLAlloObject(list,any.any.type,any.any.total,buf);
      free(buf);
   } while (1);
   fclose(f);
   return TRUE;
}

int BLFwriteList( list,name )
   BLOBLIST *list;
   char *name;
{
   FILE *f;
   BLOBNODE *node;

   if (!(f=fopen(name,"w+b")))
      return FALSE;
   node=list->head;
   while (node) {
      fwrite((char*)node,
             sizeof(char),
             sizeof(BLOBNODE)+
             BLOBTABLE[(int)node->any.type].size*node->any.total,
             f);
      node=node->next;
   }
   fclose(f);
   return TRUE;
}

int BLDBOpen( name,handle )
   char *name;
   int *handle;
{
   if (strlen(name)>0) {
      myOpen(name,handle);
   } else {
      fprintf(stderr,"Error, ... null name in MYDBOpen()\n");
      exit(1);
   }
   return TRUE;
}

int BLDBClose( handle )
   int handle;
{
   myClose(handle);
   return TRUE;
}

static
int BLDBGetNode( handle,node,buffer )
   int handle;
   BLOBNODE *node; /* static memory */
   char **buffer;  /* dynamic memory */
{
   long current;

   current=tell(handle);
   if (read(handle,node,BLNodeSelfSize(node))) {
      if (BLNodeType(node)>=BL_TOTAL) {
         *buffer=NULL;
         return FALSE;
      }
      *buffer=salloc(char,BLNodeDataSize(node));
      if (read(handle,*buffer,BLNodeDataSize(node)))
         return TRUE;
      else {
         free(*buffer);
         *buffer=NULL;
      }
   }
   lseek(handle,current,0);
   return FALSE;
}

int BLDBPutNode( handle,node )
   int handle;
   BLOBNODE *node;
{
   long current;
   BLOBNODE *buffer;

   buffer=(BLOBNODE*)salloc(char,BLNodeTotalSize(node));
   memcpy(buffer,(char*)node,BLNodeTotalSize(node));
   buffer->prev=buffer->next=0; 

   current=tell(handle);
   if (write(handle,(char*)buffer,BLNodeTotalSize(node))) {
      return TRUE;
   } else {
      lseek(handle,current,0);
      free(buffer);
      return FALSE;
   }
   return TRUE;
}

int BLDBRead( name,list )
   char *name;
   BLOBLIST **list;
{
   int handle;
   BLOBNODE node;
   char *buffer;
   int type;

   BLOpenList(list);
   if (!BLDBOpen(name,&handle)) {
      BLCloseList(*list);
      *list=NULL;
      fprintf(stderr,"Warning, ... <%s> not found in BLDBRead()\n",name);
      return FALSE;
   }
   while (BLDBGetNode(handle,&node,&buffer)) {
      type=BLNodeType(&node);
      if (type>=BL_TOTAL) {
         BLCloseList(*list);
         *list=NULL;
         fprintf(stderr,"Warning, file \"%s\" is invalid in BLDBRead()\n",name);
         return FALSE;
      }
      BLAlloObject(*list,BLNodeType(&node),BLNodeTotal(&node),buffer);
      free(buffer);
   }
   BLDBClose(handle);
   return TRUE;
}

int BLDBWrite( name,list )
   char *name;
   BLOBLIST *list;
{
   int handle;
   BLOBNODE *node;

   BLDBOpen(name,&handle);
   node=list->head;
   while (node) {
      if (!BLDBPutNode(handle,node))
         return FALSE;
      node=node->next;
   }
   BLDBClose(handle);
   return TRUE;
}

int BLDBtoPrevAddress( handle,type )
   int handle;
   BLOBTYPE type;
{
   long current;
   BLOBNODE node;

   current=tell(handle);
   while (BLDBtoAbsPrevAddress(handle)) {
      if (read(handle,&node,BLNodeSelfSize(&node))
      && type==BLNodeType(&node)) {
         lseek(handle,-1L*(long)sizeof(BLOBNODE),1);
         return TRUE;
      }
      lseek(handle,-1L*(long)sizeof(BLOBNODE),1);
   }
   lseek(handle,current,0);
   return FALSE;
}

int BLDBtoNextAddress( handle,type )
   int handle;
   BLOBTYPE type;
{
   long current;
   BLOBNODE node;

   current=tell(handle);
   while (BLDBtoAbsNextAddress(handle)) {
      if (read(handle,&node,BLNodeSelfSize(&node))
      && type==BLNodeType(&node)) {
         lseek(handle,-1L*(long)sizeof(BLOBNODE),1);
         return TRUE;
      }
      lseek(handle,-1L*(long)sizeof(BLOBNODE),1);
   }
   lseek(handle,current,0);
   return FALSE;
}

int BLDBtoAbsPrevAddress( handle )
   int handle;
{
   BLOBNODE node;

   if (read(handle,&node,BLNodeSelfSize(&node))
   && node.prev) {
      lseek(handle,(long)node.prev,0);
      return TRUE;
   } else
      return FALSE;
}

int BLDBtoAbsNextAddress( handle )
   int handle;
{
   BLOBNODE node;

   if (read(handle,&node,BLNodeSelfSize(&node))
   && node.next) {
      lseek(handle,(long)node.next,0);
      return TRUE;
   } else
      return FALSE;
}

int BLDBPrint( list )
   BLOBLIST *list;
{
   return TRUE;
}

/******************************************************************************/
/* blob.c */
