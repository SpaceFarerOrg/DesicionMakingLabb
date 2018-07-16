#pragma once
#include <SFML\System\Vector2.hpp>
#include <math.h>
#include <stdlib.h>

namespace Math
{
	static float Length(const sf::Vector2f& aVector)
	{
		float l2 = aVector.x * aVector.x + aVector.y * aVector.y;

		return sqrtf(l2);

	}

	static float Length2(const sf::Vector2f& aVector)
	{
		return aVector.x * aVector.x + aVector.y * aVector.y;
	}

	static void Normalize(sf::Vector2f& aVectorToNorm)
	{
		if (Length2(aVectorToNorm) == 0)
			return;

		float lenght = Length(aVectorToNorm);
		aVectorToNorm.x /= lenght;
		aVectorToNorm.y /= lenght;
	}

	static sf::Vector2f Normalized(const sf::Vector2f& aVectorToNorm)
	{
		sf::Vector2f vector = aVectorToNorm;
		Normalize(vector);
		return vector;
	}

	template<typename T>
	static T Clamp(T aValue, T aMin, T aMax)
	{
		return aValue < aMin ? aMin : (aValue > aMax ? aMax : aValue);
	}

	static float Random()
	{
		float returnValue = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
		return returnValue;
	}
}