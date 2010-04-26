# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/odepack++.pro,v $ 
#   $Revision: 1.7.2.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/04/26 17:40:55 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# Automatically generated by qmake (1.07a) Thu Feb 9 17:15:16 2006
######################################################################

LIB = odepack++

# Input
HEADERS += common.h
SOURCES += common.cpp

# Main routines
HEADERS += CLSODA.h
SOURCES += CLSODA.cpp
HEADERS += CLSODAR.h
SOURCES += CLSODAR.cpp

# These files represent the code for the class CInternalSolver
HEADERS += CInternalSolver.h
SOURCES += dintdy.cpp
SOURCES += dprja.cpp
SOURCES += drcheck.cpp
SOURCES += dsolsy.cpp
SOURCES += dstoda.cpp

# Support routines
HEADERS += dbnorm.h
HEADERS += dcfode.h
HEADERS += dewset.h
HEADERS += dfnorm.h
HEADERS += dgbfa.h   # wrapper for dgbtrf
HEADERS += dgbsl.h   # wrapper for dgbtrs
HEADERS += dgefa.h   # wrapper for dgetrf
HEADERS += dgesl.h   # wrapper for dgetrs
HEADERS += dmnorm.h

SOURCES += dbnorm.cpp
SOURCES += dcfode.cpp
SOURCES += dewset.cpp
SOURCES += dfnorm.cpp
SOURCES += dmnorm.cpp

# Error reporting
HEADERS += Cxerrwd.h
SOURCES += Cxerrwd.cpp

include(../lib.pri)
include(../common.pri)
