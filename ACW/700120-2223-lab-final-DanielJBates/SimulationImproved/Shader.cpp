#include "Shader.h"

void Shader::createResources(const CComPtr<ID3D11Device>& const pDevice)
{
	D3DFramework::compileShaderFromFile(_mFileName, "VS", "vs_4_0", &_mVSBlob);
	pDevice->CreateVertexShader(_mVSBlob->GetBufferPointer(), _mVSBlob->GetBufferSize(), nullptr, &_mVertexShader);

	D3DFramework::compileShaderFromFile(_mFileName, "PS", "vs_4_0", &_mPSBlob);
	pDevice->CreatePixelShader(_mPSBlob->GetBufferPointer(), _mPSBlob->GetBufferSize(), nullptr, &_mPixelShader);
}
