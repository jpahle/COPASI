/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 18:18:51 $
   End CVS Header */

#ifndef OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include <map>

#include "utilities/COutputHandler.h"

class COutputDefinitionVector;
class PlotWindow;

/**
 *  This is used to call the plotting routines from the tasks
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class COutputHandlerPlot : public COutputHandler
  {
  public:
    /**
     * Default constructor
     */
    COutputHandlerPlot();

    /**
     * Destructor
     */
    virtual ~COutputHandlerPlot();

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer (default: empty list)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           std::vector< CCopasiContainer * >());

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */ 
    // virtual void output(const Activity & activity);

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */ 
    // virtual void separate(const Activity & activity);

    /**
     * Finsh the output
     */ 
    // virtual void finish();

    void setOutputDefinitionVector(COutputDefinitionVector * pDefinitionVector);

  private:
    /**
     * The plot definitiona
     */
    COutputDefinitionVector * mpDefinitionVector;

    /**
     * This maps the key of a plot spec to a plot window
     */
    std::map<std::string, PlotWindow*> mPlotMap;
  };

#endif
