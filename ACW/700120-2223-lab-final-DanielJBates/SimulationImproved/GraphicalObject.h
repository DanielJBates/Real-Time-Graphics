#pragma once
#include <DirectXMath.h>
class GraphicalObject
{
	DirectX::XMVECTOR _mInitialPosition;
	DirectX::XMVECTOR _mCurrentPosition;

protected:
	void setInitalPosition(const DirectX::XMVECTOR& pPosition)
		{
			_mInitialPosition = pPosition;
		}

public:
	explicit GraphicalObject(const DirectX::XMVECTOR& pPosition) : _mInitialPosition(pPosition), _mCurrentPosition(pPosition) {};

	virtual ~GraphicalObject();

	const DirectX::XMVECTOR& getInitalPosition() const
	{
		return _mInitialPosition;
	}
	void setCurrentPosition(const DirectX::XMVECTOR& pPosition)
	{
		_mCurrentPosition = pPosition;
	}
	const DirectX::XMVECTOR& getCurrentPosition() const
	{
		return _mCurrentPosition;
	}

	void virtual reset();
};

