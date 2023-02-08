#pragma once
#include <atlbase.h>
#include <d3d11.h>
#include <DirectX SDK/D3DX11.h>

class Texture final
{
	_In_  LPCTSTR _mTextureFile;
	CComPtr <ID3D11ShaderResourceView> _mTextureSRV;
	CComPtr <ID3D11SamplerState> _mTextureSampler;

	void copy(const Texture& pTexture)
	{
		_mTextureFile = pTexture._mTextureFile;
		_mTextureSRV = pTexture._mTextureSRV;
		_mTextureSampler = pTexture._mTextureSampler;
	};

public:
	explicit Texture(const _In_  LPCTSTR pTextureFile) : _mTextureFile(pTextureFile) {}

	Texture(const _In_  LPCTSTR pTextureFile, CComPtr <ID3D11Device> &pDevice, const D3D11_SAMPLER_DESC &pSampDesc) : _mTextureFile(pTextureFile)
	{
		createResources(pDevice, pSampDesc);//NEED TO CONSIDER WHAT HAPPENS IF THIS FAILS
	}

	~Texture() = default;

	Texture(const Texture& pTexture)
	{
		copy(pTexture);
	}

	Texture& operator=(const Texture& pTexture)
	{
		copy(pTexture);
		return *this;
	};

	const CComPtr <ID3D11ShaderResourceView>& getSRV() const
	{
		return _mTextureSRV;
	};

	const CComPtr <ID3D11SamplerState>& getSampler() const
	{
		return _mTextureSampler;
	};
	
	void createResources(CComPtr <ID3D11Device>& pDevice, const D3D11_SAMPLER_DESC& pSampDesc);
};

