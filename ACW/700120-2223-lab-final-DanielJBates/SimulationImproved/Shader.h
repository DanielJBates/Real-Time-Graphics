#pragma once
#include "D3DFramework.h"

class Shader final
{
	CComPtr <ID3DBlob> _mVSBlob;
	CComPtr <ID3DBlob> _mPSBlob;
	CComPtr <ID3D11VertexShader> _mVertexShader;
	CComPtr <ID3D11PixelShader> _mPixelShader;
	const WCHAR* _mFileName;

	void copy(const Shader& pShader)
	{
		_mVSBlob = pShader._mVSBlob;
		_mPSBlob = pShader._mPSBlob;
		_mFileName = pShader._mFileName;
		_mVertexShader = pShader._mVertexShader;
		_mPixelShader = pShader._mPixelShader;
	}

public:
	explicit Shader(const WCHAR* const pFileName) : _mFileName(pFileName) {}

	Shader(const WCHAR* const pFileName, const CComPtr <ID3D11Device>& const pDevice) : _mFileName(pFileName)
	{
		createResources(pDevice);
	}

	Shader(const Shader& pShader)
	{
		copy(pShader);
	}

	Shader& operator=(const Shader& pShader)
	{
		copy(pShader);
		return *this;
	}

	void createResources(const CComPtr <ID3D11Device>& const pDevice);

	const CComPtr <ID3DBlob>& getVSBlob() const
	{
		return _mVSBlob;
	}

	const CComPtr <ID3DBlob>& getPSBlob() const
	{
		return _mPSBlob;
	}

	const CComPtr <ID3D11VertexShader>& getVertexShader() const
	{
		return _mVertexShader;
	}

	const CComPtr <ID3D11PixelShader>& getPixelShader() const
	{
		return _mPixelShader;
	}
};

