#ifndef VIX_TRANSFORM_H
#define VIX_TRANSFORM_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_quaternion.h>
#include <vix_vector3.h>

namespace Vixen {

	class VIX_API Transform
	{
	protected:
		/*Rotation of transformation*/
		Quaternion  Rotation;

		/*Translation of transformation*/
		Vector3     Translation;

		/*3D scale of object (always applied in local space) as vector*/
		Vector3     Scale;

	public:
		inline Transform()
			:	Rotation(0, 0, 0, 0),
				Translation(0, 0, 0),
				Scale(1, 1, 1)
		{
			
		}

		/**
		* The identity transfor
		* (Rotation = Quaternion::Identity,
		*  Translation = Vector3::Zero,
		*  Scale = Vector3::One)
		*/
		static const Transform Identity;
	};

}

#endif