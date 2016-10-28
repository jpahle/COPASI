// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CTaskFactory
#define COPASI_CTaskFactory

#include "copasi/utilities/CTaskEnum.h"

class CCopasiTask;
class CCopasiContainer;

class CTaskFactory
{
public:
  static CCopasiTask * createTask(const CTaskEnum::Task & type, const CCopasiContainer * pParent);
};

#endif //COPASI_CTaskFactory
