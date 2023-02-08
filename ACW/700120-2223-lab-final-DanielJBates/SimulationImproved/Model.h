#pragma once
#include "GraphicalObject.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;

	DirectX::XMVECTOR mLightPosition[2];
	DirectX::XMVECTOR mLightColour[2];
	DirectX::XMVECTOR mEyePosition;
};

class Model : public GraphicalObject
{
	ConstantBuffer _mCB;
	DirectX::XMMATRIX _mWorld = DirectX::XMMatrixIdentity();

	DirectX::XMVECTOR _mInitialScale = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR _mInitialRotation = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	DirectX::XMVECTOR _mCurrentScale;
	DirectX::XMVECTOR _mCurrentRotation;

	Texture& _mTexture; 

	void copy(const Model& pModel)
	{
		_mCB = pModel._mCB;
		_mWorld = pModel._mWorld;
		setInitalPosition(pModel.getInitalPosition());
		_mInitialScale = pModel._mInitialScale;
		_mInitialRotation = pModel._mInitialRotation;
		setCurrentPosition(pModel.getCurrentPosition());
		_mCurrentScale = pModel._mCurrentScale;
		_mCurrentRotation = pModel._mCurrentRotation;
		_mTexture = pModel._mTexture;
	}

public:
	Model(const DirectX::XMVECTOR& pPosition, Texture& pTexture) : GraphicalObject(pPosition), _mTexture(pTexture) { Model::reset(); };

	Model(const DirectX::XMVECTOR& pPosition, const DirectX::XMVECTOR& pScale, const DirectX::XMVECTOR& pRotation, Texture& pTexture) : GraphicalObject(pPosition), _mInitialScale(pScale), _mInitialRotation(pRotation),  _mTexture(pTexture) { Model::reset(); };

	Model& operator= (const Model& pModel)
	{
		copy(pModel);
		return *this;
	}
	virtual ~Model();

	const ConstantBuffer& getCB() const
	{
		return _mCB;
	}

	const Texture& getTexture() const
	{
		return _mTexture;
	}

	void setInitialRotation(const DirectX::XMVECTOR& pRotation)
	{
		_mInitialRotation = pRotation;
	}

	void setCurrentRotation(const DirectX::XMVECTOR& pRotation)
	{
		_mCurrentRotation = pRotation;
	}

	const DirectX::XMVECTOR& getCurrentRotation() const
	{
		return _mCurrentRotation;
	}

	void rotate(const DirectX::XMVECTOR& pRotation)
	{
		const DirectX::XMVECTOR newRotation = DirectX::XMVectorSet(DirectX::XMVectorGetX(pRotation) + DirectX::XMVectorGetX(_mCurrentRotation), DirectX::XMVectorGetY(pRotation) + DirectX::XMVectorGetY(_mCurrentRotation), DirectX::XMVectorGetZ(pRotation) + DirectX::XMVectorGetZ(_mCurrentRotation), 0.0f);
		_mCurrentRotation = newRotation;
	}

	void updateCB(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const Camera& pCamera, const Light& pSun, const Light& pMoon);

	void updateWorld();

	void reset() override;

	//void applyShader(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader) const;
	//void applyTexture(const CComPtr <ID3D11DeviceContext>& const pContext) const;

	void virtual Draw(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader, const Camera& pCamera, const Light& pSun, const Light& pMoon) = 0;
};

