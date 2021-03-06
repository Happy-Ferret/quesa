/*
 *  GeneralPolygonHint.cpp
 *  Textify3DMF
 *
 *  Created by James Walker on 4/15/12.
 *  Copyright (c) 2012 James W. Walker.
 *
 *  This software is provided 'as-is', without any express or implied warranty.
 *  In no event will the authors be held liable for any damages arising from the
 *  use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "GeneralPolygonHint.h"

namespace
{
	const char* kHintName[] = { "Complex", "Concave", "Convex" };
}

GeneralPolygonHint::GeneralPolygonHint()
	: TypeHandler( 'gplh', "GeneralPolygonHint" )
{
}

void	GeneralPolygonHint::Process( uint32_t inStartOffset,
										uint32_t inEndOffset )
{
	if (inEndOffset != inStartOffset + 4)
	{
		throw DataLengthException( Name(), inStartOffset, inEndOffset, 4 );
	}
	
	uint32_t	capsEnum = FetchUInt32( inStartOffset );
	
	if (capsEnum > 2)
	{
		throw FormatException( Name(), inStartOffset );
	}
	
	Out() << Indent() << Name() << " ( " <<
		kHintName[ capsEnum ] << " )\n";
}
