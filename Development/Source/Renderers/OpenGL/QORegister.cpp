/*  NAME:
       QORegister.cpp

    DESCRIPTION:
        Source for Quesa OpenGL renderer class.
		    
    COPYRIGHT:
        Copyright (c) 2007, Quesa Developers. All rights reserved.

        For the current release of Quesa, please see:

            <http://quesa.sourceforge.net/>
        
        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions
        are met:
        
            o Redistributions of source code must retain the above copyright
              notice, this list of conditions and the following disclaimer.
        
            o Redistributions in binary form must reproduce the above
              copyright notice, this list of conditions and the following
              disclaimer in the documentation and/or other materials provided
              with the distribution.
        
            o Neither the name of Quesa nor the names of its contributors
              may be used to endorse or promote products derived from this
              software without specific prior written permission.
        
        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
        OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
        SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
        TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
        PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
        LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
        NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
        SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    ___________________________________________________________________________
*/

//=============================================================================
//      Include files
//-----------------------------------------------------------------------------
#include "QORegister.h"

#include "E3Prefix.h"
#include "E3Compatibility.h"
#include "QORenderer.h"
#include "QOStatics.h"


//=============================================================================
//      Internal constants
//-----------------------------------------------------------------------------
#define kRendererClassName							"Quesa:Shared:Renderer:OpenGL"




//=============================================================================
//      External Functions
//-----------------------------------------------------------------------------


TQ3Status			QORenderer_Register(void)
{
	// Register the class
	//
	// Note that we use the undocumented registration routine, since we
	// need to request a specific class type (since the type for this
	// renderer is documented) rather than receiving the next available.
	TQ3XObjectClass theClass = EiObjectHierarchy_RegisterClassByType(
											kQ3SharedTypeRenderer,
											kQ3RendererTypeOpenGL,
											kRendererClassName,
											&QORenderer::Statics::MetaHandler,
											NULL,
											0,
											sizeof(QORenderer::Renderer*));

	return(theClass == NULL ? kQ3Failure : kQ3Success);
}


void				QORenderer_Unregister(void)
{
	// Find the renderer class
	TQ3XObjectClass theClass = Q3XObjectHierarchy_FindClassByType(
		kQ3RendererTypeOpenGL );
	
	if (theClass != NULL)
	{
		// Unregister the class
		Q3XObjectHierarchy_UnregisterClass( theClass );
	}
}
