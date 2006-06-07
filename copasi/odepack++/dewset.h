/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/dewset.h,v $
   $Revision: 1.2.2.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/07 00:07:28 $
   End CVS Header */

// Copyright � 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.
//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#ifndef ODEPACK_dewset
#define ODEPACK_dewset

C_INT dewset_(C_INT *n, C_INT *itol, double *rtol,
              double *atol, double *ycur, double *ewt);

#endif // ODEPACK_dewset
