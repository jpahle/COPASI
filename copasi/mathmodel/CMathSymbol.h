/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mathmodel/Attic/CMathSymbol.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/05/31 09:30:19 $
   End CVS Header */

/**
 *  CMathSymbol class.
 *  The class CMathSymbol associates a symbol with a CCopasiObject assuring
 *  that the symbol name is unique.
 *  Symbols are used to enhance redability of mathematical expresions.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CMathSymbol
#define COPASI_CMathSymbol

#include <string>
#include <map>

#include "report/CCopasiObjectName.h"
#include "report/CCopasiContainer.h"

/** @dia:pos -53.7866,-25.6956 */
class CMathSymbol
  {
    //  Attributes
  protected:
    /**
     * The symbols name
     */
    std::string mName;

    /**
     * The common name of the object
     */
    CCopasiObjectName mCN;

    /**
     * A pointer to the object
     */
    CCopasiObject * mpObject;

  private:
    /**
     * A list of symbols to ensure uniqueness
     */
    static std::map< std::string, CMathSymbol * > mList;

    // Operations
  protected:
    /**
     * The default constructor is protected to ensure that every symbol
     * has a name.
     */
    CMathSymbol();

    /**
     * Specific constructor
     * @param std::string & name
     */
    CMathSymbol(std::string & name);

    /**
     * Copy constructor. 
     * The name of the copied symbol is alternateName("copy of " + src.mName)
     * @param const CMathSymbol & src
     */
    CMathSymbol(const CMathSymbol & src);

    /**
     * A function to find an alternate name for a symbol in case the name is 
     * not unique. The alternate name is constructed by appending _n, where n
     * is the lowest positive integer generating a unique name.
     * Note: on return name is the found unique name
     * @param std::string & name
     * @return std::string & name
     */
    static std::string & alternateName(std::string & name);

  public:
    /**
     * Attempt to locate an object within the list of symbols.
     * When unsuccessfull the method returns NULL.
     * @return CMathSymbol *
     */
    static CMathSymbol * find(const CCopasiObject * pObject);

    static CMathSymbol * find(const std::string & key);

    /**
     * Specific constructor
     * @param const CCopasiObject * pObject
     */
    CMathSymbol(const CCopasiObject * pObject);

    /**
     * Destructor
     */
    ~CMathSymbol();

    /**
     * Set the name of a symbol
     * Note: on return name contains the unique name generated by alternateName.
     * If the return value is false the given name has not been unique and was
     * automatically changed.
     * @param std::string & name
     * @return bool (indicating whether the original name was unique)
     */
    bool setName(std::string & name);

    /**
     * Retreive the name of a symbol.
     * @return const std::string & name
     */
    const std::string & getName() const;

    /**
     * Set the common name of the symbol. This method also attempts to find 
     * the object relativly to the given container.
     * @param const CCopasiObjectName & cn
     * @param const CCopasiContainer * pContainer (default: RootContainer)
     * @return bool (indicating whether the object was found)
     */
    bool setCN(const CCopasiObjectName & cn,
               const CCopasiContainer * pContainer = & RootContainer);

    /**
     * Retrieve the common name of the symbol.
     * @return const CCopasiObjectName & cn
     */
    const CCopasiObjectName & getCN() const;

    /**
     * Set the object of the symbol.
     * @param CCopasiObject * pObject
     * @return bool (currently always true)
     */
    bool setObject(CCopasiObject * pObject);

    /**
     * Retrieve the object of the symbol.
     * @return const CCopasiObject * pObject
     */
    const CCopasiObject * getObject() const;

    /**
     * Retrieve the object of the symbol.
     * @return CCopasiObject * pObject
     */
    CCopasiObject * getObject();
  };

#endif // COPASI_CMathSymbol
