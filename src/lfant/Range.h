/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013 by LazyFox Studios
*	Created: 2012-09-30 by Taylor Snead
*
*	Licensed under the Apache License, Version 2.0 (the "License");
*	you may not use this file except in compliance with the License.
*	You may obtain a copy of the License at
*
*		http://www.apache.org/licenses/LICENSE-2.0
*
*	Unless required by applicable law or agreed to in writing, software
*	distributed under the License is distributed on an "AS IS" BASIS,
*	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*	See the License for the specific language governing permissions and
*	limitations under the License.
*
******************************************************************************/
#pragma once

#include <lfant/stdafx.h>

// External

// Internal

namespace lfant
{
/** @addtogroup Game
 *	@{
 */
/** @addtogroup Utilities
 *	@{
 */

template<typename T = float>
class Range
{
public:
	union
	{
		T min, start, major;
	};

	union
	{
		T max, end, minor;
	};

	Range(T min, T max) :
		min(min), max(max)
	{
	}

	Range(T both) :
		min(both), max(both)
	{
	}

	Range(const Range<T>& other) :
		min(other.min), max(other.max)
	{
	}

	Range<T>& operator=(const Range<T>& other)
	{
		min = other.min;
		max = other.max;
		return *this;
	}

	Range() {}
};

/// @}
/// @}

} /* namespace lfant */
