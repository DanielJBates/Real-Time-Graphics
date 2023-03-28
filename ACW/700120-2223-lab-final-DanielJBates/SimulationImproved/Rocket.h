#pragma once
#include "Model.h"
class Rocket final : public Model
{
	DirectX::XMVECTOR _mInitialVelocity; //= DirectX::XMVectorSet(5.0f, 10.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR _mCurrentVelocity; //= _mInitialVelocity;

	bool _mLaunch = false;

public:
	Rocket(DirectX::XMVECTOR& pPosition, Texture& pTexture) : Model(pPosition, pTexture) {};
	Rocket(DirectX::XMVECTOR& pPosition, DirectX::XMVECTOR& pScale, DirectX::XMVECTOR& pRotation, Texture& pTexture) : Model(pPosition, pScale, pRotation, pTexture) {};

	void launch();

	void Draw(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader, const Camera& pCamera, const Light& pSun, const Light& pMoon) override final;

	void update(double pDeltaTime);

};

