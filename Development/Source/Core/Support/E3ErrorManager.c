/*  NAME:
        E3ErrorManager.c

    DESCRIPTION:
        Quesa error manager.
        
        The error manager maintains a set of callbacks to receive notification
        of errors, warnings, notices, and platform specific errors as they are
        generated by Quesa.

    COPYRIGHT:
        Quesa Copyright � 1999-2002, Quesa Developers.
        
        For the list of Quesa Developers, and contact details, see:
        
            Documentation/contributors.html

        For the current version of Quesa, see:

        	<http://www.quesa.org/>

		This library is free software; you can redistribute it and/or
		modify it under the terms of the GNU Lesser General Public
		License as published by the Free Software Foundation; either
		version 2 of the License, or (at your option) any later version.

		This library is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
		Lesser General Public License for more details.

		You should have received a copy of the GNU Lesser General Public
		License along with this library; if not, write to the Free Software
		Foundation Inc, 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
    ___________________________________________________________________________
*/
//=============================================================================
//      Include files
//-----------------------------------------------------------------------------
#include "E3Prefix.h"
#include "E3ErrorManager.h"





//=============================================================================
//      Public functions
//-----------------------------------------------------------------------------
//      E3ErrorManager_PostError : Post an error.
//-----------------------------------------------------------------------------
void
E3ErrorManager_PostError(TQ3Error theError, TQ3Boolean isFatal)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Update our state
	if (theGlobals->errMgrOldestError == kQ3ErrorNone)
		theGlobals->errMgrOldestError = theError;
	
	theGlobals->errMgrIsFatalError = isFatal;
	theGlobals->errMgrLatestError  = theError;



	// Call the handler
	if (theGlobals->errMgrHandlerFuncError != NULL)
		theGlobals->errMgrHandlerFuncError(theGlobals->errMgrHandlerDataError,
										   theGlobals->errMgrOldestError,
										   theGlobals->errMgrLatestError);
}





//=============================================================================
//      E3ErrorManager_PostWarning : Post a warning.
//-----------------------------------------------------------------------------
void
E3ErrorManager_PostWarning(TQ3Warning theWarning)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Update our state
	if (theGlobals->errMgrOldestWarning == kQ3WarningNone)
		theGlobals->errMgrOldestWarning = theWarning;
	
	theGlobals->errMgrLatestWarning = theWarning;



	// Call the handler
	if (theGlobals->errMgrHandlerFuncWarning != NULL)
		theGlobals->errMgrHandlerFuncWarning(theGlobals->errMgrHandlerDataWarning,
											 theGlobals->errMgrOldestWarning,
											 theGlobals->errMgrLatestWarning);
}





//=============================================================================
//      E3ErrorManager_PostNotice : Post a notice.
//-----------------------------------------------------------------------------
void
E3ErrorManager_PostNotice(TQ3Notice theNotice)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Update our state
	if (theGlobals->errMgrOldestNotice == kQ3NoticeNone)
		theGlobals->errMgrOldestNotice = theNotice;
	
	theGlobals->errMgrLatestNotice = theNotice;



	// Call the handler in debug builds (notices are not posted in release builds)
	#if Q3_DEBUG
	if (theGlobals->errMgrHandlerFuncNotice != NULL)
		theGlobals->errMgrHandlerFuncNotice(theGlobals->errMgrHandlerDataNotice,
											theGlobals->errMgrOldestNotice,
											theGlobals->errMgrLatestNotice);
	#endif
}





//=============================================================================
//      E3ErrorManager_PostPlatformError : Post a platform specific error.
//-----------------------------------------------------------------------------
void
E3ErrorManager_PostPlatformError(TQ3Uns32 theError)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Update our state
	if (theGlobals->errMgrOldestPlatform == 0)
		theGlobals->errMgrOldestPlatform = theError;
	
	theGlobals->errMgrLatestPlatform = theError;



	// Post the platform specific error
	//
	// At present, we don't provide a public API for registering a platform
	// error handler - instead we follow the original QD3D model, where a
	// kQ3Error<Platform>Error is posted to the generic error handler.
	//
	// In preparation for a separate channel for platform specific errors,
	// we post the error directly to a platform handler if it's registered.
	// When this API is made public, apps will be able to listen directly
	// to platform specific errors.
	if (theGlobals->errMgrHandlerFuncPlatform != NULL)
		theGlobals->errMgrHandlerFuncPlatform(theGlobals->errMgrHandlerDataPlatform,
											  (TQ3Error) theGlobals->errMgrOldestPlatform,
											  (TQ3Error) theGlobals->errMgrLatestPlatform);
	else
		E3ErrorManager_PostError(
				#if QUESA_OS_MACINTOSH
				kQ3ErrorMacintoshError,
	
				#elif QUESA_OS_WIN32
				kQ3ErrorWin32Error,
		
				#elif QUESA_OS_UNIX
				kQ3ErrorUnixError,

				#else
				kQ3ErrorPlatformError,
				#endif
				
				kQ3False);
}





//=============================================================================
//      E3ErrorManager_GetIsFatalError : Get as the last error was fatal.
//-----------------------------------------------------------------------------
TQ3Boolean
E3ErrorManager_GetIsFatalError(TQ3Error theError)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Determine if the error is fatal or not
	if (theError == kQ3ErrorInternalError || theError == kQ3ErrorNoRecovery)
		return(kQ3True);



	// If this error isn't fatal, see if we've hit one which is
	return(theGlobals->errMgrIsFatalError);
}





//=============================================================================
//      E3ErrorManager_GetError : Get the oldest and latest errors.
//-----------------------------------------------------------------------------
//		Note : Both our parameters are optional.
//-----------------------------------------------------------------------------
void
E3ErrorManager_GetError(TQ3Error *oldestError, TQ3Error *latestError)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return the requested state
	if (oldestError != NULL)
		*oldestError = theGlobals->errMgrOldestError;

	if (latestError != NULL)
		*latestError = theGlobals->errMgrLatestError;



	// Set our flags
	theGlobals->errMgrClearError = kQ3True;
}





//=============================================================================
//      E3ErrorManager_GetWarning : Get the oldest and latest warnings.
//-----------------------------------------------------------------------------
//		Note : Both our parameters are optional.
//-----------------------------------------------------------------------------
void
E3ErrorManager_GetWarning(TQ3Warning *oldestWarning, TQ3Warning *latestWarning)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return the requested state
	if (oldestWarning != NULL)
		*oldestWarning = theGlobals->errMgrOldestWarning;

	if (latestWarning != NULL)
		*latestWarning = theGlobals->errMgrLatestWarning;



	// Set our flags
	theGlobals->errMgrClearWarning = kQ3True;
}





//=============================================================================
//      E3ErrorManager_GetNotice : Get the oldest and latest notices.
//-----------------------------------------------------------------------------
//		Note : Both our parameters are optional.
//-----------------------------------------------------------------------------
void
E3ErrorManager_GetNotice(TQ3Notice *oldestNotice, TQ3Notice *latestNotice)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return the requested state
	if (oldestNotice != NULL)
		*oldestNotice = theGlobals->errMgrOldestNotice;

	if (latestNotice != NULL)
		*latestNotice = theGlobals->errMgrLatestNotice;



	// Set our flags
	theGlobals->errMgrClearNotice = kQ3True;
}





//=============================================================================
//      E3ErrorManager_GetPlatformError : Get the oldest and latest platform.
//-----------------------------------------------------------------------------
//		Note : Both our parameters are optional.
//-----------------------------------------------------------------------------
void
E3ErrorManager_GetPlatformError(TQ3Uns32 *oldestPlatform, TQ3Uns32 *latestPlatform)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return the requested state
	if (oldestPlatform != NULL)
		*oldestPlatform = theGlobals->errMgrOldestPlatform;

	if (latestPlatform != NULL)
		*latestPlatform = theGlobals->errMgrLatestPlatform;



	// Set our flags
	theGlobals->errMgrClearPlatform = kQ3True;
}





//=============================================================================
//      E3ErrorManager_ClearError : Clear the error state.
//-----------------------------------------------------------------------------
void
E3ErrorManager_ClearError(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Clear our state
	theGlobals->errMgrClearError  = kQ3False;
	theGlobals->errMgrOldestError = kQ3ErrorNone;
	theGlobals->errMgrLatestError = kQ3ErrorNone;
}





//=============================================================================
//      E3ErrorManager_ClearWarning : Clear the warning state.
//-----------------------------------------------------------------------------
void
E3ErrorManager_ClearWarning(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Clear our state
	theGlobals->errMgrClearWarning  = kQ3False;
	theGlobals->errMgrOldestWarning = kQ3WarningNone;
	theGlobals->errMgrLatestWarning = kQ3WarningNone;
}





//=============================================================================
//      E3ErrorManager_ClearNotice : Clear the notice state.
//-----------------------------------------------------------------------------
void
E3ErrorManager_ClearNotice(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Clear our state
	theGlobals->errMgrClearNotice  = kQ3False;
	theGlobals->errMgrOldestNotice = kQ3NoticeNone;
	theGlobals->errMgrLatestNotice = kQ3NoticeNone;
}





//=============================================================================
//      E3ErrorManager_ClearPlatformError : Clear the platform error state.
//-----------------------------------------------------------------------------
void
E3ErrorManager_ClearPlatformError(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Clear our state
	theGlobals->errMgrClearPlatform  = kQ3False;
	theGlobals->errMgrOldestPlatform = 0;
	theGlobals->errMgrLatestPlatform = 0;
}





//=============================================================================
//      E3ErrorManager_GetCallback_Error : Get the error handler.
//-----------------------------------------------------------------------------
TQ3ErrorMethod
E3ErrorManager_GetCallback_Error(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return our callback
	return(theGlobals->errMgrHandlerFuncError);
}





//=============================================================================
//      E3ErrorManager_GetCallback_Warning : Get the warning handler.
//-----------------------------------------------------------------------------
TQ3WarningMethod
E3ErrorManager_GetCallback_Warning(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return our callback
	return(theGlobals->errMgrHandlerFuncWarning);
}





//=============================================================================
//      E3ErrorManager_GetCallback_Notice : Get the notice handler.
//-----------------------------------------------------------------------------
TQ3NoticeMethod
E3ErrorManager_GetCallback_Notice(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return our callback
	return(theGlobals->errMgrHandlerFuncNotice);
}





//=============================================================================
//      E3ErrorManager_GetCallback_PlatformError : Get the platform handler.
//-----------------------------------------------------------------------------
TQ3ErrorMethod
E3ErrorManager_GetCallback_PlatformError(void)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Return our callback
	return(theGlobals->errMgrHandlerFuncPlatform);
}





//=============================================================================
//      E3ErrorManager_SetCallback_Error : Set the error handler.
//-----------------------------------------------------------------------------
void
E3ErrorManager_SetCallback_Error(TQ3ErrorMethod theCallback, TQ3Uns32 theData)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Set our callback
	theGlobals->errMgrHandlerFuncError = theCallback;
	theGlobals->errMgrHandlerDataError = theData;
}





//=============================================================================
//      E3ErrorManager_SetCallback_Warning : Set the warning handler.
//-----------------------------------------------------------------------------
void
E3ErrorManager_SetCallback_Warning(TQ3WarningMethod theCallback, TQ3Uns32 theData)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Set our callback
	theGlobals->errMgrHandlerFuncWarning = theCallback;
	theGlobals->errMgrHandlerDataWarning = theData;
}





//=============================================================================
//      E3ErrorManager_SetCallback_Notice : Set the notice handler.
//-----------------------------------------------------------------------------
void
E3ErrorManager_SetCallback_Notice(TQ3NoticeMethod theCallback, TQ3Uns32 theData)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Set our callback
	theGlobals->errMgrHandlerFuncNotice = theCallback;
	theGlobals->errMgrHandlerDataNotice = theData;
}





//=============================================================================
//      E3ErrorManager_SetCallback_PlatformError : Set the platform handler.
//-----------------------------------------------------------------------------
void
E3ErrorManager_SetCallback_PlatformError(TQ3ErrorMethod theCallback, TQ3Uns32 theData)
{	E3GlobalsPtr	theGlobals = E3Globals_Get();



	// Set our callback
	theGlobals->errMgrHandlerFuncPlatform = theCallback;
	theGlobals->errMgrHandlerDataPlatform = theData;
}

