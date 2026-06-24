#------------------------------------------------------------------------------#
#--- (c)shik ------------------------------------------------------------------#
#--- 43280323,1022 ------------------------------------------------------------#
#--- 43290118,0301,0320,0424,0518,0521 ----------------------------------------#
#--- 43300423,0531,0920 -------------------------------------------------------#
#--- 43310117,0126 ------------------------------------------------------------#
#--- 433110713 ----------------------------------------------------------------#
#------------------------------------------------------------------------------#

TARGET : grxSUN motif.o grm af

#------------------------------------------------------------------------------#

BIN = /bin
LIBS = -L$(SHIK_XLIB) -L$(SHIK_MLIB) -lXm -lXt -lX11 -lm
INCLUDES = -I/usr/include -I$(SHIK_XINC) -I$(SHIK_MINC)
UIL = $(BIN)/X11/uil
CC = cc -g

#------------------------------------------------------------------------------#

.c.o:
	$(CC) $(INCLUDES) -DCOMPILER=__UNIXC__ -c $<

myFiles=*.[ch] Makefile shikEnv gr gr_include demo?.gr shik.??? *.rs

b :
	$(BIN)/cp $(myFiles) ../bak
tar :
	tar cvf ../gr4.11-980916.tar -C /user/mospdt/shik/c/code $(myFiles)
t :
	$(BIN)/touch *.c *.h;rm -f core
c :
	$(BIN)/rm -f *.o core
r :
	\rcp gr_include demo?.gr gr grxHP grxSUN g[RS] mospdt@mipu7:~/.bin
	\rcp gr_include demo?.gr gr grxHP grxSUN g[RS] csp7et@tdu5:~/.bin
	@echo "... remote-release finished !"
 
#==============================================================================#
CORE_H = system.h typedef.h keydef.h any.h blob.h wrappers.h str.h clock.h     \
         mtrx.h number.h parser.h tools.h recipe.h nr.h
CORE_O = any.o blob.o wrappers.o str.o clock.o                                 \
         mtrx.o parser.o tools.o recipe.o nr.o 
GRCORE_H = gecore.h gegraph.h geprint.h geplot.h sunview.h xwindow.h           \
           gecolor.h gewindow.h geresource.h                                   \
           getext.h stroke.h xform.h                                           \
           plot.h plotcv.h plotio.h usrfunc.h macrodef.h skeleton.h strsymb.h
GRCORE_O = gecore.o gegraph.o geprint.o geplot.o sunview.o xwindow.o           \
           gecolor.o gewindow.o geresource.o                                   \
           getext.o stroke.o xform.o                                           \
           plot.o plotcv.o plotio.o usrfunc.o macrodef.o skeleton.o strsymb.o

grxHP : $(CORE_O) $(GRCORE_O) g.o gR.o gS.o
	$(CC) $(CORE_O) $(GRCORE_O) g.o -o grxHP $(LIBS)
	$(CC) $(CORE_O) $(GRCORE_O) gR.o -o gRHP $(LIBS)
	$(CC) $(CORE_O) $(GRCORE_O) gS.o -o gSHP $(LIBS)
grxSUN : $(CORE_O) $(GRCORE_O) g.o gR.o gS.o
	$(CC) $(CORE_O) $(GRCORE_O) g.o -o grxSUN $(LIBS)
	$(CC) $(CORE_O) $(GRCORE_O) gR.o -o gRSUN $(LIBS)
	$(CC) $(CORE_O) $(GRCORE_O) gS.o -o gSSUN $(LIBS)

#==============================================================================#
GRM_h =       motif.h plotse.h geresource.h
GRM_c = grm.c motif.c plotse.c geresource.h
GRM_o = grm.o motif.o plotse.o geresource.o $(CORE_O)
grm : $(GRM_o) $(GRM_c) $(GRM_h)
	$(CC) $(GRM_o) $(LIBS) -o $@
# ==============================================================================#
AF_h = anyfind.h
AF_c = anyfind.c af.c
AF_o = anyfind.o af.o $(CORE_O)
af : $(AF_o) $(AF_c) $(AF_h)
	$(CC) $(AF_o) $(LIBS) -o $@
# ==============================================================================#
