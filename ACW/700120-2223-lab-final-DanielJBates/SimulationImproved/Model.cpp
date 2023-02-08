#include "Model.h"

Model::~Model() = default;

void Model::updateCB(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const Camera& pCamera, const Light& pSun, const Light & pMoon)
{
	updateWorld();

	_mCB.mView = DirectX::XMMatrixTranspose(pCamera.getView());
	_mCB.mProjection = DirectX::XMMatrixTranspose(pCamera.getProjection());
	_mCB.mWorld = DirectX::XMMatrixTranspose(_mWorld);

	DirectX::XMVECTOR sunPosVector = pSun.getCurrentPosition();
	const DirectX::XMFLOAT4 sunPosFloat(DirectX::XMVectorGetX(sunPosVector), DirectX::XMVectorGetY(sunPosVector), DirectX::XMVectorGetZ(sunPosVector), 1.0f);
	_mCB.mLightPosition[0] = DirectX::XMLoadFloat4(&sunPosFloat);

	DirectX::XMVECTOR sunColVector = pSun.getColour();
	const DirectX::XMFLOAT4 sunColFloat(DirectX::XMVectorGetX(sunColVector), DirectX::XMVectorGetY(sunColVector), DirectX::XMVectorGetZ(sunColVector), 1.0f);
	_mCB.mLightColour[0] = DirectX::XMLoadFloat4(&sunColFloat);

	DirectX::XMVECTOR moonPosVector = pMoon.getCurrentPosition();
	const DirectX::XMFLOAT4 moonPosFloat(DirectX::XMVectorGetX(moonPosVector), DirectX::XMVectorGetY(moonPosVector), DirectX::XMVectorGetZ(moonPosVector), 1.0f);
	_mCB.mLightPosition[1] = DirectX::XMLoadFloat4(&moonPosFloat);

	DirectX::XMVECTOR moonColVector = pMoon.getColour();
	const DirectX::XMFLOAT4 moonColFloat(DirectX::XMVectorGetX(moonColVector), DirectX::XMVectorGetY(moonColVector), DirectX::XMVectorGetZ(moonColVector), 1.0f);
	_mCB.mLightColour[1] = DirectX::XMLoadFloat4(&moonColFloat);

	DirectX::XMVECTOR eyePosVector = pCamera.getEye();
	const DirectX::XMFLOAT3 eyePosFloat(DirectX::XMVectorGetX(eyePosVector), DirectX::XMVectorGetY(eyePosVector), DirectX::XMVectorGetZ(eyePosVector));
	_mCB.mEyePosition = DirectX::XMLoadFloat3(&eyePosFloat);

	pContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &_mCB, 0, 0);
}

void Model::updateWorld()
{
	_mWorld = DirectX::XMMatrixScalingFromVector(_mCurrentScale) * DirectX::XMMatrixRotationRollPitchYawFromVector(_mCurrentRotation) * DirectX::XMMatrixTranslationFromVector(getCurrentPosition());
}

void Model::reset()
{
	setCurrentPosition(getInitalPosition());
	_mCurrentScale = _mInitialScale;
	_mCurrentRotation = _mInitialRotation;
	updateWorld();
}

//void Model::applyShader(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader) const
//{
//	pContext->VSSetShader(pVertexShader, nullptr, 0);
//	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer.p);
//	pContext->PSSetShader(pPixelShader, nullptr, 0);
//}
//
//void Model::applyTexture(const CComPtr<ID3D11DeviceContext>& const pContext) const
//{
//	pContext->PSSetShaderResources(0, 1, &_mTexture.getSRV().p);
//	pContext->PSSetSamplers(0, 1, &_mTexture.getSampler().p);
//}
