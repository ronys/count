#ident %W% %E% %Q%
###########################################################################
SRCROOT=	..
RULESDIR=	RULES
include		$(SRCROOT)/$(RULESDIR)/rules.top
###########################################################################

INSDIR=		include
TARGET=		avoffset.h
TARGETC=	avoffset
CPPOPTS +=	-DUSE_SCANSTACK
CFILES=		avoffset.c getfp.c

###########################################################################
include		$(SRCROOT)/$(RULESDIR)/rules.inc
###########################################################################
