/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013, by LazyFox Studios
*	Created: 2012-08-13 by Taylor Snead
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
#include <lfant/Subsystem.h>

struct ALCdevice_struct;
struct ALCcontext_struct;

namespace lfant
{
/**	@addtogroup Game
 *	@{
 */
/** @addtogroup Audio
 *	@{
 */

/**
 *
 */
class Audio : public Subsystem
{
	friend class AudioSource;
public:
	Audio();
	virtual ~Audio();

	virtual void Init();

	/**
	 *	Plays a 2D sound at global volume.
	 *	@param file The audio file to load and play.
	 */
//	 PlaySound(string file, bool loop = false);

	uint8_t maxChannels = 10;

protected:
	virtual void Update();
	virtual void Deinit();

	ALCdevice_struct* device;
	ALCcontext_struct* context;
private:
};

}
