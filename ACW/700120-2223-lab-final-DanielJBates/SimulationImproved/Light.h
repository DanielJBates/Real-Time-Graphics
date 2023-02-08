#pragma once
#include "GraphicalObject.h"
class Light final : public GraphicalObject
{
	DirectX::XMVECTOR _mColour;

public:
	explicit Light(const DirectX::XMVECTOR& pPosition, const DirectX::XMVECTOR& pColour) : GraphicalObject(pPosition), _mColour(pColour) {};

	const DirectX::XMVECTOR& getColour() const
	{
		return _mColour;
	}

	void rotate(const DirectX::XMVECTOR& pRotation);
};

