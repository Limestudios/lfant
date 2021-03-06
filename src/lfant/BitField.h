/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013 by LazyFox Studios
*	Created: 2012-07-16 by Taylor Snead
*
*	Licensed under the Apache License, Version 2.0 (the "License");
*	you may not use this file except in compliance with the License.
*	You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
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
 *	 @{
 */
/** @addtogroup Utilities
 *	 @{
 */

/**
 *
 */
template<typename TEnum, typename TType = byte>
class BitField
{
public:
	BitField()
	{
	}
	~BitField()
	{
	}

	void set(const TEnum& flag)
	{
		value = flag;
	}

	void add(const TEnum& flag)
	{
		value |= flag;
	}

	bool check(const TEnum& flag)
	{
		return value & flag;
	}

	void remove(const TEnum& flag)
	{
		value &= ~flag;
	}

	void clear()
	{
		value = 0;
	}

	TType& operator=(const TEnum& flag)
	{
		set(flag);
	}

	void operator+=(const TEnum& flag)
	{
		add(flag);
	}

	void operator-=(const TEnum& flag)
	{
		remove(flag);
	}

	bool operator==(const TEnum& flag)
	{
		return check(flag);
	}

private:
	TType value;
};

/** @} */
/** @} */
}
