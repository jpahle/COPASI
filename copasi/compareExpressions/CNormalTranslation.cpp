// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalTranslation.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/11 20:55:55 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "copasi.h"

#include "CNormalBase.h"
#include "ConvertToCEvaluationNode.h"
#include "CNormalTranslation.h"
#include "CNormalFraction.h"
#include "CNormalSum.h"
#include "CNormalProduct.h"
#include "CNormalLogical.h"

#include "function/CEvaluationTree.h"

/**
 * Simplify an evaluation tree given by the root node by creating a new simplified tree from the original one.
 * The tree itself is actually not created!
 * @return CEvaluationNode*, pointer to root node of the newly created tree.
 */
CEvaluationNode* CNormalTranslation::simplifyTree(const CEvaluationNode* node)
{
  //std::cout << "simplifyTree called." << std::endl;
  const CEvaluationNode * child = dynamic_cast<const CEvaluationNode*>(node->getChild());
  CEvaluationNode * newchild = NULL;
  std::vector<CEvaluationNode*> children;
  while (child != NULL)
    {
      newchild = simplifyTree(child);
      child = dynamic_cast<const CEvaluationNode*>(child->getSibling());
      children.push_back(newchild);
    }
  CEvaluationNode* newnode = node->simplifyNode(children);
  return newnode;
}

/**
 * Creating a simplified tree by calling simplifyTree repeatedly until it cannot be simplified further.
 * The tree itself is actually not created!
 * @return CEvaluationNode*, pointer to root node of the newly created tree.
 */
CEvaluationNode * CNormalTranslation::simplifyTreeReptdly(const CEvaluationNode* root0)
{
  //std::cout << "<p>simplifyTreeReptly called.</p>" << std::endl;
  CEvaluationNode * root1 = simplifyTree(root0);
  //std::cout << "<p>" << root1->getInfix() << "</p>" << std::endl;
  //std::cout << "<p>";
  //root1->printRecursively(std::cout);
  //std::cout << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //root1->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //std::cout << "</math></p>" << std::endl;
  //root1->printRecursively(std::cout,0);

  if (root1->getInfix() != root0->getInfix())
    {
      CEvaluationNode * root2 = simplifyTreeReptdly(root1);
      delete root1;
      return root2;
    }
  else
    {
      return root1;
    }
}

/**
 * Translate and simplify a tree given by the root node into CNormal structure
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplify(const CEvaluationNode* root0)
{
  //std::cout << "<p>normAndSimplyfy called.</p>" << std::endl;
  CEvaluationNode * root1 = simplifyTreeReptdly(root0);

  CNormalFraction* base = createNormalRepresentation(root1);
  /*
  std::set<const CNormalLogical*> logicals=base->findLogicals();
  std::set<const CNormalLogical*>::iterator it=logicals.begin();
  std::set<const CNormalLogical*>::iterator endit=logicals.end();
  std::cout << "Found " << logicals.size() << " logicals: " << std::endl;
  while(it!=endit)
  {
      std::cout << (*it)->debug();
    ++it;
  }
  */
  //std::cout << "<p>Created Normal Repr.: " << base->toString() << "</p>" << std::endl;
  base->simplify();
  /*
  logicals=base->findLogicals();
  it=logicals.begin();
  endit=logicals.end();
  std::cout << "Found " << logicals.size() << " logicals: " << std::endl;
  while(it!=endit)
  {
      std::cout << (*it)->debug();
    ++it;
  }
  */
  delete root1;

  return base;
}

/**
 * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplifyReptdly(const CEvaluationTree* tree0)
{
  //std::cout << "<p>normAndSimplifyReptdly called.</p>" << std::endl;
  const CEvaluationNode* root0 = tree0->getRoot();
  CNormalFraction * base0 = normAndSimplify(root0);

  std::stringstream tmp;
  tmp << base0->toString();
  //std::cout << "<p>Normal Repr.: " << base0->toString() << "</p>" << std::endl;

  CEvaluationTree * tree1 = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);

  tree1->setInfix(tmp.str());
  //std::cout << "<p>Infix: " << tree1->getRoot()->getInfix() << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //tree1->getRoot()->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //std::cout << "</math></p>" << std::endl;
  if (tree1->getInfix() != tree0->getInfix())
    {
      CNormalFraction * base1 = normAndSimplifyReptdly(tree1);
      delete tree1;
      delete base0;
      return base1;
    }
  else
    {
      delete tree1;
      return base0;
    }
}

/**
 * Translate and simplify a tree by calling normAndSimplify repeatedly until it cannot be simplified further
 * @return CNormalFraction*
 */
CNormalFraction* CNormalTranslation::normAndSimplifyReptdly(const CEvaluationNode* root0)
{
  //std::cout << "<p>normAndSimplifyReptdly called.</p>" << std::endl;
  //const CEvaluationNode* root0=tree0->getRoot();
  CNormalFraction * base0 = normAndSimplify(root0);

  std::stringstream tmp;
  //tmp << base0->toString();

  //CEvaluationTree * tree1 = new CEvaluationTree("second tree", NULL, CEvaluationTree::Function);
  //std::cout << "<p>Normal Repr.: " << base0->toString() <<"</p>" << std::endl;
  CEvaluationNode* pTmpNode = convertToCEvaluationNode(*base0);
  //std::cout << "<p>Infix: " << pTmpNode->getInfix() << "</p>" << std::endl;
  //std::cout << "<p><math xmlns=\"&mathml;\">" << std::endl;
  //pTmpNode->writeMathML(std::cout,std::vector<std::vector<std::string> >());
  //tree1->setInfix(tmp.str());
  //std::cout << "</math></p>" << std::endl;
  CNormalFraction* pFraction = dynamic_cast<CNormalFraction*>(base0);
  assert(pFraction != NULL);

  //if (pTmpNode->getInfix() != root0->getInfix())
  if ((pFraction->getNumerator().getFractions().size() != 0) || (pFraction->getDenominator().getFractions().size() != 0))
    {
      CNormalFraction * base1 = normAndSimplifyReptdly(pTmpNode);
      delete pTmpNode;
      delete base0;
      return base1;
    }
  else
    {
      delete pTmpNode;
      return base0;
    }
}
