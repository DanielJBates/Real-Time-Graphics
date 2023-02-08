#include "Texture.h"

void Texture::createResources(CComPtr<ID3D11Device>& pDevice, const D3D11_SAMPLER_DESC& pSampDesc)
{
    D3DX11CreateShaderResourceViewFromFile(pDevice, _mTextureFile, nullptr, nullptr, &_mTextureSRV, nullptr);
    pDevice->CreateSamplerState(&pSampDesc, &_mTextureSampler);
}
