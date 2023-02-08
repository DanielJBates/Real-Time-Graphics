#pragma once
// Simulation template, based on the Microsoft DX11 tutorial 04

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <atlbase.h>
#include <fstream>
#include <vector>

#include <DirectX SDK/D3DX11.h>

#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Rocket.h"

using namespace DirectX;

#define COMPILE_CSO

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Norm;
	XMFLOAT2 TexCoord;
};

class D3DFramework final {

	HINSTANCE _hInst = nullptr;
	HWND _hWnd = nullptr;
	D3D_DRIVER_TYPE _driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL _featureLevel = D3D_FEATURE_LEVEL_11_1;
	CComPtr <ID3D11Device> _pd3dDevice;
	CComPtr <ID3D11Device1> _pd3dDevice1;
	CComPtr <ID3D11DeviceContext> _pImmediateContext;
	CComPtr <ID3D11DeviceContext1> _pImmediateContext1;
	CComPtr <IDXGISwapChain1> _swapChain;
	CComPtr <IDXGISwapChain1> _swapChain1;
	CComPtr <ID3D11RenderTargetView> _pRenderTargetView;
	CComPtr <ID3D11Texture2D> _pDepthStencil;
	CComPtr <ID3D11DepthStencilView> _pDepthStencilView;
	CComPtr <ID3D11VertexShader> _pVertexShader;
	CComPtr <ID3D11PixelShader> _pPixelShader;
	CComPtr <ID3D11InputLayout> _pVertexLayout;
	CComPtr <ID3D11Buffer> _pVertexBuffer;
	CComPtr <ID3D11Buffer> _pIndexBuffer;
	CComPtr <ID3D11Buffer> _pConstantBuffer;

	std::unique_ptr <Texture> _pRocks;
	std::unique_ptr <Texture> _pLavaRock;
	std::unique_ptr <Texture> _pRocketMetal;
	std::unique_ptr <Texture> _pRustedMetal;

	std::unique_ptr<Camera> _pCamera;

	std::vector< std::unique_ptr<Cube> > _pTerrain;

	std::unique_ptr<Cylinder> _pLauncher;

	std::unique_ptr<Rocket> _pRocket;

	std::unique_ptr<Light> _pLights[2];
	
	static std::unique_ptr<D3DFramework> _instance;
public:

	D3DFramework() = default;
	D3DFramework(D3DFramework&) = delete;
	D3DFramework(D3DFramework&&) = delete;
	D3DFramework& operator=(const D3DFramework&) = delete;
	D3DFramework& operator=(const D3DFramework&&) = delete;
	~D3DFramework();
	
	static D3DFramework& getInstance() { return *_instance; }

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT initWindow(HINSTANCE hInstance, int nCmdShow);
	static HRESULT compileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT initDevice();
	void render();

	void loadOBJ(const std::string& pFilename, std::vector<SimpleVertex>& pVertices, std::vector<WORD>& pIndices) const;
};