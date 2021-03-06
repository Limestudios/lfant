/******************************************************************************
*
*	LFANT Source
*	Copyright (C) 2012-2013 by LazyFox Studios
*	Created: 2012-11-01 by Taylor Snead
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

#include <lfant/Component.h>

class btCollisionShape;

namespace lfant
{
class Rigidbody;

/** @addtogroup Game
 *	 @{
 */
/** @addtogroup Physics
 *	 @{
 */

class Collider : public Component
{
	friend class Rigidbody;
public:
	bool trigger;
	//SurfaceMaterial* material;
	vec3 center;

protected:
	Collider()
	{
	}
	virtual ~Collider()
	{
	}

	void Save(Properties* prop);
	void Load(Properties* prop);

	virtual void Init();
	virtual void OnSetScale(vec3 scale);

	virtual btCollisionShape* GetShape() = 0;

	virtual vec3 GetSize() { return size; }
	virtual void SetSize(vec3 size) { this->size = size; }

	Rigidbody* rigidbody;
	vec3 size = vec3(1);

private:

};

/** @} */
/** @} */
}
