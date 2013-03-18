/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013 by LazyFox Studios
*	Created: 2012-07-28 by Taylor Snead
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

// External

// Internal
#include <lfant/Mesh.h>
#include <lfant/Material.h>

namespace lfant
{
/** @addtogroup Game
 *	 @{
 */
/** @addtogroup Rendering
 *	 @{
 */

/**
 *	Sprite renders a textured material on a plane.
 *		Also, it uses SpriteAnimation instances to animate itself. These animations
 *		change the texture to a different part of the sprite-sheet assigned to the
 *		playing animation.
 *	@todo
 *		Have animations
 */
class Sprite : public Mesh
{
public:
//	DECLARE_COMP(Sprite)

	/**
	 *	Supported animation play modes.
	 */
	enum AnimPlayMode
	{
		Once, Loop, Bounce, Default = Loop
	};

	/**
	 *	An animation that consists of a single texture as a sprite-sheet.
	 *	@details
	 *		A SpriteAnimation has one material of one texture, and for each frame,
	 *		it moves by frameSize, at frameRate times per second. playMode determines
	 *		what the animation will do when it reaches its end. It can either stop,
	 *		loop, or reverse to play forward when it reaches its beginning.
	 */
	class Animation
	{
	public:
		string name = "Animation";
		Material material;
		uint16_t rows = 5;
		uint16_t columns = 10;
		AnimPlayMode playMode = Loop;
		byte frameRate = 5;
	};

	friend class Renderer;
public:
	Sprite();
	virtual ~Sprite();

	// Loop functions
//	virtual void Init();
	virtual void Update();
//	virtual void OnDestroy();

	void BeginRender();
	void Render();
	void EndRender();

	void PlayAnim(string name, AnimPlayMode mode = Default, bool reverse = false);
	void PlayLastAnim();
	void PauseAnim();
	void ResumeAnim();
	void StopAnim();

	void AddAnim(Animation& anim);
	void RemoveAnim(string name);
	Animation& GetAnim(string name);

	/// The sprite animations to be used.
	forward_list<Animation> animations;

protected:
	/// The currently playing animation.
	Animation* currentAnim = nullptr;

	vec2 currentFrame = vec2(0.0f, 0.0f);

	double currentTime = 0.0f;

	bool playingAnim = false;
	bool playingReverseAnim = false;

	AnimPlayMode animMode = Default;
	AnimPlayMode currAnimMode = Default;

private:
};

/** @} */
/** @} */
}