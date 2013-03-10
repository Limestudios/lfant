/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013 by LazyFox Studios
*	Created: 2012-07-17 by Taylor Snead
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

// Internal
#include <lfant/Texture.h>
#include <lfant/Shader.h>

// External

namespace lfant
{
/** @addtogroup Game
 *	 @{
 */
/** @addtogroup Rendering
 *	 @{
 */

/**
 *
 */
class Material
{
public:
	// Path and name for the texture file.
	Texture texture;
	uint32_t textureUnif;
	Shader shader;
	vec2 tiling { 1, 1 };
	vec2 offset { 0, 0 };
	rgba color { 255, 255, 255, 255 };

	Material()
	{
	}

	Material(Texture texture, Shader shader) :
		texture(texture), shader(shader)
	{
	}

	Material& operator()(Texture texture, Shader shader)
	{
		this->texture = texture;
		this->shader = shader;
		return *this;
	}
};

/// @}
/// @}
}
