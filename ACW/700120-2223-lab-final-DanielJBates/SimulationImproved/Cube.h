#pragma once
#include "Model.h"

class Cube final : public Model
{
public:
	Cube(DirectX::XMVECTOR& pPosistion, Texture& pTexture) : Model(pPosistion, pTexture) {};
	Cube(DirectX::XMVECTOR& pPosition, DirectX::XMVECTOR& pScale, DirectX::XMVECTOR& pRotation, Texture& pTexture) : Model(pPosition, pScale, pRotation, pTexture) {};
	
	void Draw(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader, const Camera& pCamera, const Light& pSun, const Light& pMoon) override final;
};

