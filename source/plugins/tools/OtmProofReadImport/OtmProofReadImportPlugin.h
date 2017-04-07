/*! \file
	Copyright Notice:

	Copyright (C) 1990-2017, International Business Machines
	Corporation and others. All rights reserved
*/

#ifndef _OtmProofReadImportPlugin_H_
#define _OtmProofReadImportPlugin_H_

#include <string>
#include <vector>
#include "core\pluginmanager\OtmToolPlugin.h"
#include "OtmProofReadFilter.h"

/*! \brief relative path for the filter DLLs */
const char szFilterDir[] = "OtmProofReadImport\\filter";

/*! \brief name of GetFilterInfo function */
const char szGetFilterInfoFunc[] = "getFilterInfo";

/*! \brief name of ConvertToProofReadFormat function */
const char szConvertToProofReadFormat[] = "convertToProofReadFormat";

class OtmProofReadImportPlugin: public OtmToolPlugin
/*! \brief This class implements the standard translation memory plugin (EQF) for OpenTM2.
*/

{
public:
/*! \brief Constructor
*/
	OtmProofReadImportPlugin();
/*! \brief Destructor
*/
	~OtmProofReadImportPlugin();
/*! \brief Returns the name of the plugin
*/
	const char* getName();
/*! \brief Returns a short plugin-Description
*/
	const char* getShortDescription();
/*! \brief Returns a verbose plugin-Description
*/
	const char* getLongDescription();
/*! \brief Returns the version of the plugin
*/
	const char* getVersion();
/*! \brief Returns the name of the plugin-supplier
*/
	const char* getSupplier();

/*! \brief Initialize plugin 
  This method is called when the workbench window has been created.
  The tool plugin can use the plugin manager methods addMenuItem and addSubMenu to add
  own entries to the workbench toolbar.
*/
  void init();

  /*! \brief Process an action bar command
  This method is called when a menu item created by the tool plugin is selected by the user.
	\param iCommandID Id of the command
*/
  void processCommand( int iCommandID );



/*! \brief Stops the plugin. 
	Terminating-function for the plugin, will be called directly before
	the DLL containing the plugin will be unloaded.\n
	The method should call PluginManager::deregisterPlugin() to tell the PluginManager
  that the plugin is not active anymore.
  Warning: THIS METHOD SHOULD BE CALLED BY THE PLUGINMANAGER ONLY!
	\param fForce, TRUE = force stop of the plugin even if functions are active, FALSE = only stop plugin when it is inactive
	\returns TRUE when successful */
	bool stopPlugin( bool fForce = false );

 
private:
	std::string name;
	std::string shortDesc;
	std::string longDesc;
	std::string version;
	std::string supplier;
	std::string strLastError;

/*! \brief structure for filter information  */
  typedef struct _FILTERENTRY
  {
    char szPathName[MAX_PATH];           // fully qualified name of the filter DLL
    char szDLLName[MAX_PATH];            // name of the filter DLL (w/o path)
    char szDisplayName[MAX_PATH];        // filter name as displayed for the user
    char szFileExtension[MAX_PATH];      // file extension of the files supported by this filter
  } FILTERENTRY, *PFILTERENTRY;

/*! \brief structure for filter information  */
  std::vector<FILTERENTRY> vFilterList;

  /*! \brief Fill the list of available filters
  */
  void fillFilterList();

  /*! \brief make file name for last used values profile
	  \param pszLastUsedValuesFile buffer for the file name
	  \returns TRUE if the function completed successfully
  */
  BOOL getLastUsedValuesProfileName( char *pszLastUsedValuesFile  );

  /*! \brief Get the name of the input file using the standard Windows open file dialog
	  \param strInputFile this string will contain the last used input file name and will receive the choosen input file name on return
	  \param strFilterDLL this string will contain the name of the LU filter DLL (w/o path), on return it is filled with the name of the selected filter DLL
	  \returns TRUE if the user selected successfully a input file
  */
  BOOL getImportFile( std::string &strInputFile, std::string &strFilterDLL );

  /*! \brief Get the last used values 
	  \param strInputFile this string will receive the fully qualified last used input file name 
	  \param strFilterDLL this string will receive the last used filter DLL name  (w/o path)
	  \returns TRUE if the function completed successfully
  */
  BOOL getLastUsedValues( std::string &strInputFile, std::string &strFilterDLL );

  /*! \brief Get the last used values 
	    \param strInputFile string with the last used file name
	    \param strFilterDLL string with the last used filter DLL
   	  \returns TRUE if the function completed successfully
  */
  BOOL saveLastUsedValues( std::string &strInputFile, std::string &strFilterDLL );

  /*! \brief Call a filter DLL to convert the input file into our proofread import XML format
	  \param strInputFile the input file being converted
	  \param strFilterDLL the filter DLL selected by the user
	  \param strProofReadXML the fully qualified name of the proofread import XML file to be created by the filter
	  \returns TRUE if the filter completed successfully
  */
  BOOL applyFilter( std::string strInputFile, std::string strFilterDLL, std::string strProofReadXML );

  /*! \brief Show the proofreading process window
	  \param strProofReadXML the fully qualified name of the proofread import XML file
	  \returns TRUE if the function completed successfully
  */
  BOOL showProofReadWindow( std::string strProofReadXML );



};


#endif // #ifndef _OtmProofReadImportPlugin_H_