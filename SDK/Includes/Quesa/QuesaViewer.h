/*! @header QuesaViewer.h
        Declares the Quesa viewer library.
 */
/*  NAME:
        QuesaViewer.h

    DESCRIPTION:
        Quesa public header.

    COPYRIGHT:
        Quesa Copyright � 1999-2001, Quesa Developers.
        
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
#ifndef QUESA_VIEWER_HDR
#define QUESA_VIEWER_HDR
//=============================================================================
//      Include files
//-----------------------------------------------------------------------------
#include "Quesa.h"
#include "QuesaGroup.h"

// Disable QD3D header
#if defined(__QD3DVIEWER__) || defined(__QD3DWINVIEWER__)
#error
#endif

#define __QD3DVIEWER__
#define __QD3DWINVIEWER__





//=============================================================================
//		C++ preamble
//-----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif





//=============================================================================
//      Constants
//-----------------------------------------------------------------------------
// Viewer state flags (Q3ViewerGetState/Q3WinViewerGetState)
enum {
	kQ3ViewerEmpty								= 0,
	kQ3ViewerHasModel							= (1 << 0),
	kQ3ViewerHasUndo							= (1 << 1)
};


// Viewer cameras
typedef enum {
	kQ3ViewerCameraRestore						= 0,
	kQ3ViewerCameraFit							= 1,
	kQ3ViewerCameraFront						= 2,
	kQ3ViewerCameraBack							= 3,
	kQ3ViewerCameraLeft							= 4,
	kQ3ViewerCameraRight						= 5,
	kQ3ViewerCameraTop							= 6,
	kQ3ViewerCameraBottom						= 7
} TQ3ViewerCameraView;





//=============================================================================
//      Mac OS constants
//-----------------------------------------------------------------------------
#if QUESA_OS_MACINTOSH

// Viewer flags (Q3ViewerNew)
enum {
	kQ3ViewerShowBadge							= (1 << 0),
	kQ3ViewerActive								= (1 << 1),
	kQ3ViewerControllerVisible					= (1 << 2),
	kQ3ViewerDrawFrame							= (1 << 3),
	kQ3ViewerDraggingOff						= (1 << 4),
	kQ3ViewerButtonCamera						= (1 << 5),
	kQ3ViewerButtonTruck						= (1 << 6),
	kQ3ViewerButtonOrbit						= (1 << 7),
	kQ3ViewerButtonZoom							= (1 << 8),
	kQ3ViewerButtonDolly						= (1 << 9),
	kQ3ViewerButtonReset						= (1 << 10),
	kQ3ViewerOutputTextMode						= (1 << 11),
	kQ3ViewerDragMode							= (1 << 12),
	kQ3ViewerDrawGrowBox						= (1 << 13),
	kQ3ViewerDrawDragBorder						= (1 << 14),
	kQ3ViewerDraggingInOff						= (1 << 15),
	kQ3ViewerDraggingOutOff						= (1 << 16),
	kQ3ViewerButtonOptions						= (1 << 17),
	kQ3ViewerPaneGrowBox						= (1 << 18),
	kQ3ViewerDefault							= (1 << 31)
};

#endif // QUESA_OS_MACINTOSH





//=============================================================================
//      Windows constants
//-----------------------------------------------------------------------------
#if QUESA_OS_WIN32

// Viewer flags (Q3WinViewerNew)
enum {
	kQ3ViewerShowBadge							= (1 << 0),
	kQ3ViewerActive								= (1 << 1),
	kQ3ViewerControllerVisibile					= (1 << 2),
	kQ3ViewerButtonCamera						= (1 << 3),
	kQ3ViewerButtonTruck						= (1 << 4),
	kQ3ViewerButtonOrbit						= (1 << 5),
	kQ3ViewerButtonZoom							= (1 << 6),
	kQ3ViewerButtonDolly						= (1 << 7),
	kQ3ViewerButtonReset						= (1 << 8),
	kQ3ViewerButtonNone							= (1 << 9),
	kQ3ViewerOutputTextMode						= (1 << 10),
	kQ3ViewerDraggingInOff						= (1 << 11),
	kQ3ViewerButtonOptions						= (1 << 12),
	kQ3ViewerPaneGrowBox						= (1 << 13),
	kQ3ViewerDefault							= (1 << 15)
};


// WM_NOTIFY messages
#define Q3VNM_DROPFILES							0x5000
#define Q3VNM_CANUNDO							0x5001
#define Q3VNM_DRAWCOMPLETE						0x5002
#define Q3VNM_SETVIEW							0x5003
#define Q3VNM_SETVIEWNUMBER						0x5004
#define Q3VNM_BUTTONSET							0x5005
#define Q3VNM_BADGEHIT							0x5006


// Window class name (can be passed to CreateWindow/CreateWindowEx)
#define kQ3ViewerClassName						"QD3DViewerWindow"


// Clipboard type
#define kQ3ViewerClipboardFormat				"QuickDraw 3D Metafile"

#endif // QUESA_OS_WIN32





//=============================================================================
//      Types
//-----------------------------------------------------------------------------
// The Viewer object is opaque
typedef void *TQ3ViewerObject;


// Viewer callbacks
typedef CALLBACK_API_C(TQ3Status,			TQ3ViewerWindowResizeCallbackMethod)(
							TQ3ViewerObject		theViewer,
							const void			*userData);

typedef CALLBACK_API_C(TQ3Status,			TQ3ViewerPaneResizeNotifyCallbackMethod)(
							TQ3ViewerObject		theViewer,
							const void			*userData);





//=============================================================================
//      Mac OS types
//-----------------------------------------------------------------------------
#if QUESA_OS_MACINTOSH

// Viewer callbacks
typedef CALLBACK_API_C(OSErr,				TQ3ViewerDrawingCallbackMethod)(
							TQ3ViewerObject		theViewer,
							const void			*userData);


#endif // QUESA_OS_MACINTOSH





//=============================================================================
//      Windows types
//-----------------------------------------------------------------------------
#if QUESA_OS_WIN32

// Viewer callbacks
typedef CALLBACK_API_C(TQ3Status,			TQ3ViewerDrawingCallbackMethod)(
							TQ3ViewerObject		theViewer,
							const void			*userData);


// Viewer types
typedef struct {
	NMHDR							nmhdr;
	HANDLE							hDrop;
} TQ3ViewerDropFiles;

typedef struct {
	NMHDR							nmhdr;
	TQ3ViewerCameraView				view;
} TQ3ViewerSetView;

typedef struct {
	NMHDR							nmhdr;
	TQ3Uns32						number;
} TQ3ViewerSetViewNumber;

typedef struct {
	NMHDR							nmhdr;
	TQ3Uns32						button;
} TQ3ViewerButtonSet;


#endif // QUESA_OS_WIN32





//=============================================================================
//      Mac OS function prototypes
//-----------------------------------------------------------------------------
#if QUESA_OS_MACINTOSH

/*
 *	Q3ViewerGetVersion
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetVersion (
	unsigned long                 *majorRevision,
	unsigned long                 *minorRevision
);


/*
 *	Q3ViewerGetReleaseVersion
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetReleaseVersion (
	unsigned long                 *releaseRevision
);


/*
 *	Q3ViewerNew
 *		Description of function
 */
EXTERN_API_C ( TQ3ViewerObject )
Q3ViewerNew(
	CGrafPtr                      port,
	Rect                          *rect,
	unsigned long                 flags
);


/*
 *	Q3ViewerDispose
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerDispose (
	TQ3ViewerObject               theViewer
);


/*
 *	Q3ViewerUseFile
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerUseFile (
	TQ3ViewerObject                theViewer,
	long                           refNum
);


/*
 *	Q3ViewerUseData
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerUseData (
	TQ3ViewerObject                theViewer,
	void                           *data,
	long                           size
);


/*
 *	Q3ViewerWriteFile
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerWriteFile (
	TQ3ViewerObject                theViewer,
	long                           refNum
);


/*
 *	Q3ViewerWriteData
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3ViewerWriteData (
	TQ3ViewerObject                theViewer,
	Handle                         data
);


/*
 *	Q3ViewerDraw
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerDraw (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerDrawContent
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerDrawContent (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerDrawControlStrip
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerDrawControlStrip (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerEvent
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerEvent (
	TQ3ViewerObject                theViewer,
	EventRecord                    *evt
);


/*
 *	Q3ViewerGetPict
 *		Description of function
 */
EXTERN_API_C ( PicHandle )
Q3ViewerGetPict (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerGetButtonRect
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetButtonRect (
	TQ3ViewerObject                theViewer,
	unsigned long                  button,
	Rect                           *rect
);


/*
 *	Q3ViewerGetCurrentButton
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3ViewerGetCurrentButton (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerSetCurrentButton
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetCurrentButton (
	TQ3ViewerObject                theViewer,
	unsigned long                  button
);


/*
 *	Q3ViewerUseGroup
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerUseGroup (
	TQ3ViewerObject                theViewer,
	TQ3GroupObject                 group
);


/*
 *	Q3ViewerGetGroup
 *		Description of function
 */
EXTERN_API_C ( TQ3GroupObject )
Q3ViewerGetGroup (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerSetBackgroundColor
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetBackgroundColor (
	TQ3ViewerObject                theViewer,
	TQ3ColorARGB                   *color
);


/*
 *	Q3ViewerGetBackgroundColor
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetBackgroundColor (
	TQ3ViewerObject                theViewer,
	TQ3ColorARGB                   *color
);


/*
 *	Q3ViewerGetView
 *		Description of function
 */
EXTERN_API_C ( TQ3ViewObject )
Q3ViewerGetView (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerRestoreView
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerRestoreView (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerSetFlags
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetFlags (
	TQ3ViewerObject                theViewer,
	unsigned long                  flags
);


/*
 *	Q3ViewerGetFlags
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3ViewerGetFlags (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerSetBounds
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetBounds (
	TQ3ViewerObject                theViewer,
	Rect                           *bounds
);


/*
 *	Q3ViewerGetBounds
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetBounds (
	TQ3ViewerObject                theViewer,
	Rect                           *bounds
);


/*
 *	Q3ViewerSetDimension
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetDimension (
	TQ3ViewerObject                theViewer,
	unsigned long                  width,
	unsigned long                  height
);


/*
 *	Q3ViewerGetDimension
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetDimension (
	TQ3ViewerObject                theViewer,
	unsigned long                  *width,
	unsigned long                  *height
);


/*
 *	Q3ViewerGetMinimumDimension
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetMinimumDimension (
	TQ3ViewerObject                theViewer,
	unsigned long                  *width,
	unsigned long                  *height
);


/*
 *	Q3ViewerSetPort
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetPort (
	TQ3ViewerObject                theViewer,
	CGrafPtr                       port
);


/*
 *	Q3ViewerGetPort
 *		Description of function
 */
EXTERN_API_C ( CGrafPtr )
Q3ViewerGetPort (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerAdjustCursor
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerAdjustCursor (
	TQ3ViewerObject                theViewer,
	Point                          *pt
);


/*
 *	Q3ViewerCursorChanged
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerCursorChanged (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerGetState
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3ViewerGetState (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerClear
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerClear (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerCut
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerCut (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerCopy
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerCopy (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerPaste
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerPaste (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerMouseDown
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerMouseDown (
	TQ3ViewerObject                theViewer,
	long                           x,
	long                           y
);


/*
 *	Q3ViewerContinueTracking
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerContinueTracking (
	TQ3ViewerObject                theViewer,
	long                           x,
	long                           y
);


/*
 *	Q3ViewerMouseUp
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerMouseUp (
	TQ3ViewerObject                theViewer,
	long                           x,
	long                           y
);


/*
 *	Q3ViewerHandleKeyEvent
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerHandleKeyEvent (
	TQ3ViewerObject                theViewer,
	EventRecord                    *evt
);


/*
 *	Q3ViewerSetDrawingCallbackMethod
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetDrawingCallbackMethod (
	TQ3ViewerObject                theViewer,
	TQ3ViewerDrawingCallbackMethod callbackMethod,
	const void                     *data
);


/*
 *	Q3ViewerSetWindowResizeCallback
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetWindowResizeCallback (
	TQ3ViewerObject                theViewer,
	TQ3ViewerWindowResizeCallbackMethod windowResizeCallbackMethod,
	const void                     *data
);


/*
 *	Q3ViewerSetPaneResizeNotifyCallback
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetPaneResizeNotifyCallback (
	TQ3ViewerObject                theViewer,
	TQ3ViewerPaneResizeNotifyCallbackMethod paneResizeNotifyCallbackMethod,
	const void                     *data
);


/*
 *	Q3ViewerUndo
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerUndo (
	TQ3ViewerObject                theViewer
);


/*
 *	Q3ViewerGetUndoString
 *		Description of function
 */
EXTERN_API_C ( Boolean )
Q3ViewerGetUndoString (
	TQ3ViewerObject                theViewer,
	char                           *str,
	unsigned long                  *cnt
);


/*
 *	Q3ViewerGetCameraCount
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetCameraCount (
	TQ3ViewerObject                theViewer,
	unsigned long                  *cnt
);


/*
 *	Q3ViewerSetCameraByNumber
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetCameraByNumber (
	TQ3ViewerObject                theViewer,
	unsigned long                  cameraNo
);


/*
 *	Q3ViewerSetCameraByView
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetCameraByView (
	TQ3ViewerObject                theViewer,
	TQ3ViewerCameraView            viewType
);


/*
 *	Q3ViewerSetRendererType
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetRendererType (
	TQ3ViewerObject                theViewer,
	TQ3ObjectType                  rendererType
);


/*
 *	Q3ViewerGetRendererType
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetRendererType (
	TQ3ViewerObject                theViewer,
	TQ3ObjectType                  *rendererType
);


/*
 *	Q3ViewerChangeBrightness
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerChangeBrightness (
	TQ3ViewerObject                theViewer,
	float                          brightness
);


/*
 *	Q3ViewerSetRemoveBackfaces
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetRemoveBackfaces (
	TQ3ViewerObject                theViewer,
	TQ3Boolean                     remove
);


/*
 *	Q3ViewerGetRemoveBackfaces
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetRemoveBackfaces (
	TQ3ViewerObject                theViewer,
	TQ3Boolean                     *remove
);


/*
 *	Q3ViewerSetPhongShading
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerSetPhongShading (
	TQ3ViewerObject                theViewer,
	TQ3Boolean                     phong
);


/*
 *	Q3ViewerGetPhongShading
 *		Description of function
 */
EXTERN_API_C ( OSErr )
Q3ViewerGetPhongShading (
	TQ3ViewerObject                theViewer,
	TQ3Boolean                     *phong
);

#endif // QUESA_OS_MACINTOSH





//=============================================================================
//      Windows function prototypes
//-----------------------------------------------------------------------------
#if QUESA_OS_WIN32

/*
 *	Q3WinViewerGetVersion
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetVersion (
	unsigned long                  *majorRevision,
	unsigned long                  *minorRevision
);


/*
 *	Q3WinViewerGetReleaseVersion
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetReleaseVersion (
	unsigned long                  *releaseRevision
);


/*
 *	Q3WinViewerNew
 *		Description of function
 */
EXTERN_API_C ( TQ3ViewerObject )
Q3WinViewerNew (
	HWND                           window,
	const RECT                     *rect,
	unsigned long                  flags
);


/*
 *	Q3WinViewerDispose
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerDispose (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerUseFile
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerUseFile (
	TQ3ViewerObject                viewer,
	HANDLE                         fileHandle
);


/*
 *	Q3WinViewerUseData
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerUseData (
	TQ3ViewerObject                viewer,
	void                           *data,
	unsigned long                  size
);


/*
 *	Q3WinViewerWriteFile
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerWriteFile (
	TQ3ViewerObject                viewer,
	HANDLE                         fileHandle
);


/*
 *	Q3WinViewerWriteData
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerWriteData (
	TQ3ViewerObject                viewer,
	void                           *data,
	unsigned long                  dataSize,
	unsigned long                  *actualDataSize
);


/*
 *	Q3WinViewerDraw
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerDraw (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerDrawContent
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerDrawContent (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerDrawControlStrip
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerDrawControlStrip (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerMouseDown
 *		Description of function
 */
EXTERN_API_C ( BOOL )
Q3WinViewerMouseDown (
	TQ3ViewerObject                viewer,
	long                           x,
	long                           y
);


/*
 *	Q3WinViewerContinueTracking
 *		Description of function
 */
EXTERN_API_C ( BOOL )
Q3WinViewerContinueTracking (
	TQ3ViewerObject                viewer,
	long                           x,
	long                           y
);


/*
 *	Q3WinViewerMouseUp
 *		Description of function
 */
EXTERN_API_C ( BOOL )
Q3WinViewerMouseUp (
	TQ3ViewerObject                viewer,
	long                           x,
	long                           y
);


/*
 *	Q3WinViewerGetBitmap
 *		Description of function
 */
EXTERN_API_C ( HBITMAP )
Q3WinViewerGetBitmap (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerGetButtonRect
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetButtonRect (
	TQ3ViewerObject                viewer,
	unsigned long                  button,
	RECT                           *rectangle
);


/*
 *	Q3WinViewerGetCurrentButton
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3WinViewerGetCurrentButton (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerSetCurrentButton
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetCurrentButton (
	TQ3ViewerObject                viewer,
	unsigned long                  button
);


/*
 *	Q3WinViewerUseGroup
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerUseGroup (
	TQ3ViewerObject                viewer,
	TQ3GroupObject                 group
);


/*
 *	Q3WinViewerGetGroup
 *		Description of function
 */
EXTERN_API_C ( TQ3GroupObject )
Q3WinViewerGetGroup (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerSetBackgroundColor
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetBackgroundColor (
	TQ3ViewerObject                viewer,
	TQ3ColorARGB                   *color
);


/*
 *	Q3WinViewerGetBackgroundColor
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetBackgroundColor (
	TQ3ViewerObject                viewer,
	TQ3ColorARGB                   *color
);


/*
 *	Q3WinViewerGetView
 *		Description of function
 */
EXTERN_API_C ( TQ3ViewObject )
Q3WinViewerGetView (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerRestoreView
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerRestoreView (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerSetFlags
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetFlags (
	TQ3ViewerObject                viewer,
	unsigned long                  flags
);


/*
 *	Q3WinViewerGetFlags
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3WinViewerGetFlags (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerSetBounds
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetBounds (
	TQ3ViewerObject                viewer,
	RECT                           *bounds
);


/*
 *	Q3WinViewerGetBounds
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetBounds (
	TQ3ViewerObject                viewer,
	RECT                           *bounds
);


/*
 *	Q3WinViewerSetDimension
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetDimension (
	TQ3ViewerObject                viewer,
	unsigned long                  width,
	unsigned long                  height
);


/*
 *	Q3WinViewerGetDimension
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetDimension (
	TQ3ViewerObject                viewer,
	unsigned long                  *width,
	unsigned long                  *height
);


/*
 *	Q3WinViewerGetMinimumDimension
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetMinimumDimension (
	TQ3ViewerObject                viewer,
	unsigned long                  *width,
	unsigned long                  *height
);


/*
 *	Q3WinViewerSetWindow
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetWindow (
	TQ3ViewerObject                viewer,
	HWND                           window
);


/*
 *	Q3WinViewerGetWindow
 *		Description of function
 */
EXTERN_API_C ( HWND )
Q3WinViewerGetWindow (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerGetViewer
 *		Description of function
 */
EXTERN_API_C ( TQ3ViewerObject )
Q3WinViewerGetViewer (
	HWND                           theWindow
);


/*
 *	Q3WinViewerGetControlStrip
 *		Description of function
 */
EXTERN_API_C ( HWND )
Q3WinViewerGetControlStrip (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerAdjustCursor
 *		Description of function
 */
EXTERN_API_C ( TQ3Boolean )
Q3WinViewerAdjustCursor (
	TQ3ViewerObject                viewer,
	long                           x,
	long                           y
);


/*
 *	Q3WinViewerCursorChanged
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerCursorChanged (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerGetState
 *		Description of function
 */
EXTERN_API_C ( unsigned long )
Q3WinViewerGetState (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerClear
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerClear (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerCut
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerCut (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerCopy
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerCopy (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerPaste
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerPaste (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerUndo
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerUndo (
	TQ3ViewerObject                viewer
);


/*
 *	Q3WinViewerGetUndoString
 *		Description of function
 */
EXTERN_API_C ( TQ3Boolean )
Q3WinViewerGetUndoString (
	TQ3ViewerObject                viewer,
	char                           *theString,
	unsigned long                  stringSize,
	unsigned long                  *actualSize
);


/*
 *	Q3WinViewerGetCameraCount
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerGetCameraCount (
	TQ3ViewerObject                viewer,
	unsigned long                  *count
);


/*
 *	Q3WinViewerSetCameraNumber
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetCameraNumber (
	TQ3ViewerObject                viewer,
	unsigned long                  cameraNo
);


/*
 *	Q3WinViewerSetCameraView
 *		Description of function
 */
EXTERN_API_C ( TQ3Status )
Q3WinViewerSetCameraView (
	TQ3ViewerObject                viewer,
	TQ3ViewerCameraView            viewType
);

#endif // QUESA_OS_WIN32





//=============================================================================
//		C++ postamble
//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif

