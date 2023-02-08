#include "D3DFramework.h"
#include <directxcolors.h>
#include <vector>
#include "Resource.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Rocket.h"
#include "Cube.h"

std::unique_ptr<D3DFramework> D3DFramework::_instance = std::make_unique<D3DFramework>();

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK D3DFramework::wndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam) {
	PAINTSTRUCT ps;
	std::string msg;
	const auto& app = D3DFramework::getInstance();
	
	switch (message) {
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case 'W':
			app._pCamera->rotate(XMVectorSet(0.0174533f, 0.0f, 0.0f, 0.0f));
			break;
		case 'A':
			app._pCamera->rotate(XMVectorSet(0.0f, 0.0174533f, 0.0f, 0.0f));
			break;
		case 'S':
			app._pCamera->rotate(XMVectorSet(-0.0174533f, 0.0f, 0.0f, 0.0f));
			break;
		case 'D':
			app._pCamera->rotate(XMVectorSet(0.0f, -0.0174533f, 0.0f, 0.0f));
			break;
		case 'I':
			app._pCamera->pan(XMVectorSet(0.0f, 0.0174533f, 0.0f, 0.0f));
			break;
		case 'J':
			app._pCamera->pan(XMVectorSet(-0.0174533f, 0.0f, 0.0f, 0.0f));
			break;
		case 'K':
			app._pCamera->pan(XMVectorSet(0.0f, -0.0174533f, 0.0f, 0.0f));
			break;
		case 'L':
			app._pCamera->pan(XMVectorSet(0.0174533f, 0.0f, 0.0f, 0.0f));
			break;		
		case VK_UP:
			if (GetKeyState(VK_CONTROL) < 0) {
				app._pCamera->pan(XMVectorSet(0.0f, 0.0174533f, 0.0f, 0.0f));
			}
			else {
				app._pCamera->rotate(XMVectorSet(0.0174533f, 0.0f, 0.0f, 0.0f));
			}
			break;
		case VK_LEFT:
			if (GetKeyState(VK_CONTROL) < 0) {
				app._pCamera->pan(XMVectorSet(-0.0174533f, 0.0f, 0.0f, 0.0f));
			}
			else {
				app._pCamera->rotate(XMVectorSet(0.0f, 0.0174533f, 0.0f, 0.0f));
			}
			break;		
		case VK_DOWN:
			if (GetKeyState(VK_CONTROL) < 0) {
				app._pCamera->pan(XMVectorSet(0.0f, -0.0174533f, 0.0f, 0.0f));
			}
			else {
				app._pCamera->rotate(XMVectorSet(-0.0174533f, 0.0f, 0.0f, 0.0f));
			}
			break;
		case VK_RIGHT:
			if (GetKeyState(VK_CONTROL) < 0) {
				app._pCamera->pan(XMVectorSet(0.0174533f, 0.0f, 0.0f, 0.0f));
			}
			else {
				app._pCamera->rotate(XMVectorSet(0.0f, -0.0174533f, 0.0f, 0.0f));
			}
			break;
		case 'T':
			if (GetKeyState(VK_SHIFT) < 0)
			{
				//increase time speed
				app._pRocket->increaseSpeed();
			}
			else
			{
				//decrease time speed
				app._pRocket->decreaseSpeed();
			}
			break;
		case 'R':
			app._pLauncher->reset();
			app._pRocket->reset();

			for (int i = 0; i < 2; i++)
			{
				app._pLights[i]->reset();
			}
			break;
		case 188:
			app._pLauncher->rotate(XMVectorSet(0.0f, 0.0f, 0.0174533f, 0.0f));
			app._pRocket->rotate(XMVectorSet(0.0f, 0.0f, 0.0174533f, 0.0f));
			app._pRocket->setInitialRotation(app._pRocket->getCurrentRotation());
			//decrease launcher pitch
			break;
		case 190:
			app._pLauncher->rotate(XMVectorSet(0.0f, 0.0f, -0.0174533f, 0.0f));
			app._pRocket->rotate(XMVectorSet(0.0f, 0.0f, -0.0174533f, 0.0f));
			app._pRocket->setInitialRotation(app._pRocket->getCurrentRotation());
			//increase launcher pitch
			break;
		case 'N':
			app._pLauncher->rotate(XMVectorSet(0.0f, 0.0f, 0.0174533f, 0.0f));
			app._pRocket->rotate(XMVectorSet(0.0f, 0.0f, 0.0174533f, 0.0f));
			app._pRocket->setInitialRotation(app._pRocket->getCurrentRotation());
			//decrease launcher pitch
			break;
		case 'M':
			app._pLauncher->rotate(XMVectorSet(0.0f, 0.0f, -0.0174533f, 0.0f));
			app._pRocket->rotate(XMVectorSet(0.0f, 0.0f, -0.0174533f, 0.0f));
			app._pRocket->setInitialRotation(app._pRocket->getCurrentRotation());
			//increase launcher pitch
			break;
		case VK_F1:
			app._pCamera->setEye(XMVectorSet(-6.0f, 2.0f, -3.0f, 0.0f));
			app._pCamera->setAt(app._pLauncher->getCurrentPosition());
			break;
		case VK_F2:
			app._pCamera->setEye(XMVectorSet(0.0f, 2.0f, -8.0f, 0.0f));
			app._pCamera->setAt(XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f));
			break;
		case VK_F3:
			app._pCamera->setEye(XMVectorSet(-7.0f, 2.0f, -3.0f, 0.0f));	
			app._pCamera->setAt(app._pRocket->getCurrentPosition());
			break;
		case VK_F4:
			msg = "F4 pressed";
			break;
		case VK_F5:
			app._pCamera->setEye(XMVectorSet(-7.0f, 2.0f, -2.0f, 0.0f));
			app._pCamera->setAt(app._pRocket->getCurrentPosition());
			break;
		case VK_F6:
			msg = "F6 pressed";
			break;
		case VK_F11:
			app._pRocket->launch();
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;

	case WM_KEYUP:
		switch (wParam) {
		case 'A':
			msg = "A released";
			break;
		case '1':
			msg = "1 released";
			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT D3DFramework::initWindow(const HINSTANCE hInstance, const int nCmdShow) {
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, reinterpret_cast<LPCTSTR>(IDI_SIMULATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"Starter Template";
	wcex.hIconSm = LoadIcon(wcex.hInstance, reinterpret_cast<LPCTSTR>(IDI_SIMULATION));
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	_hInst = hInstance;
	RECT rc = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	_hWnd = CreateWindow(L"Starter Template", L"Direct3D 11 Simulation",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!_hWnd)
		return E_FAIL;

	ShowWindow(_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT D3DFramework::compileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	auto dwShaderFlags = static_cast<DWORD>(D3DCOMPILE_ENABLE_STRICTNESS);
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	CComPtr <ID3DBlob> pErrorBlob;
	const auto hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr)) {
		if (pErrorBlob)
			OutputDebugStringA(static_cast<const char*>(pErrorBlob->GetBufferPointer()));
		return hr;
	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT D3DFramework::initDevice()
{
	auto hr = S_OK;

	RECT rc;
	GetClientRect(_hWnd, &rc);
	const UINT width = rc.right - rc.left;
	const UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	const auto numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	const auto numFeatureLevels = static_cast<UINT>(ARRAYSIZE(featureLevels));

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);

		if (hr == E_INVALIDARG)
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1, D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	CComPtr <IDXGIFactory1> dxgiFactory;
	{
		CComPtr <IDXGIDevice> dxgiDevice;
		hr = _pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr)) {
			CComPtr <IDXGIAdapter> adapter;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr)) {
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
			}
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	CComPtr <IDXGIFactory2> dxgiFactory2;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));

	// DirectX 11.1 or later
	hr = _pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&_pd3dDevice1));
	if (SUCCEEDED(hr)) {
		(void)_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&_pImmediateContext1));
	}

	DXGI_SWAP_CHAIN_DESC1 sd{};
	sd.Width = width;
	sd.Height = height;
	sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;

	hr = dxgiFactory2->CreateSwapChainForHwnd(_pd3dDevice, _hWnd, &sd, nullptr, nullptr, &_swapChain1);
	if (SUCCEEDED(hr)) {
		hr = _swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&_swapChain));
	}

	// Note this tutorial doesn't handle full-screen swap chains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(_hWnd, DXGI_MWA_NO_ALT_ENTER);

	if (FAILED(hr))
		return hr;

	// Create a render target view
	CComPtr <ID3D11Texture2D> pBackBuffer;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
	if (FAILED(hr))
		return hr;

	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView.p, nullptr);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_pImmediateContext->RSSetViewports(1, &vp);

	//Create depth stencil texture
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	hr = _pd3dDevice->CreateTexture2D(&depthDesc, nullptr, &_pDepthStencil);
	if (FAILED(hr))
		return hr;

	//Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = dsvDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = _pd3dDevice->CreateDepthStencilView(_pDepthStencil, &dsvDesc, &_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView.p, _pDepthStencilView.p);

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	const auto numElements = static_cast<UINT>(ARRAYSIZE(layout));

#ifdef COMPILE_CSO
	// Compile the vertex shader
	CComPtr <ID3DBlob> pVSBlob;
	hr = compileShaderFromFile(L"Simulation.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);
	if (FAILED(hr)) {
		return hr;
	}

	// Create the input layout
	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &_pVertexLayout);
	if (FAILED(hr))
		return hr;
#else
	{
		const std::string fileName{ "..\\Debug\\Simulation_VS.cso" };
		std::ifstream fin(fileName, std::ios::binary);
		if (!fin) {
			MessageBox(nullptr, L"The CSO file cannot be found.", L"Error", MB_OK);
			return E_FAIL;
		}
		std::vector<unsigned char> byteCode(std::istreambuf_iterator<char>(fin), {});

		hr = _pd3dDevice->CreateVertexShader(&byteCode[0], byteCode.size(), nullptr, &_pVertexShader);
		if (FAILED(hr)) {
			return hr;
		}

		// Create the input layout
		hr = _pd3dDevice->CreateInputLayout(layout, numElements, &byteCode[0], byteCode.size(), &_pVertexLayout);
		if (FAILED(hr))
			return hr;
	}
#endif

	// Set the input layout
	_pImmediateContext->IASetInputLayout(_pVertexLayout);

#ifdef COMPILE_CSO
	// Compile the pixel shader
	CComPtr <ID3DBlob> pPSBlob;
	hr = compileShaderFromFile(L"Simulation.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
	if (FAILED(hr))
		return hr;

#else
	{
		const std::string fileName{ "..\\Debug\\Simulation_PS.cso" };
		std::ifstream fin(fileName, std::ios::binary);
		if (!fin) {
			MessageBox(nullptr, L"The CSO file cannot be found.", L"Error", MB_OK);
			return E_FAIL;
		}
		std::vector<unsigned char> byteCode(std::istreambuf_iterator<char>(fin), {});

		hr = _pd3dDevice->CreatePixelShader(&byteCode[0], byteCode.size(), nullptr, &_pPixelShader);
		if (FAILED(hr)) {
			return hr;
		}
	}
#endif		

	// Create buffers

	std::vector<SimpleVertex> vertices;
	std::vector<WORD> indices;

	loadOBJ("Models\\cube.obj", vertices, indices);
	loadOBJ("Models\\cylinder.obj", vertices, indices);
	loadOBJ("Models\\sphere.obj", vertices, indices);
	loadOBJ("Models\\rocket.obj", vertices, indices);

	// Create vertex buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = vertices.data();
	hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	// Create index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices.data();

	hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Set vertex buffer
	const auto stride = static_cast<UINT>(sizeof(SimpleVertex));
	const auto offset = static_cast<UINT>(0);
	_pImmediateContext->IASetVertexBuffers(0, 1, &_pVertexBuffer.p, &stride, &offset);

	// Set index buffer
	_pImmediateContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);
	if (FAILED(hr))
		return hr;

	// Create sampler description
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create texture resources

	_pRocks = std::make_unique<Texture>(L"Textures/rocks.dds", _pd3dDevice, sampDesc);//new Texture(L"Textures/rocks.dds", _pd3dDevice, sampDesc);
	_pLavaRock = std::make_unique<Texture>(L"Textures/lavaRock.dds", _pd3dDevice, sampDesc); //new Texture(L"Textures/lavaRock.dds", _pd3dDevice, sampDesc);
	_pRocketMetal = std::make_unique<Texture>(L"Textures/rocketMetal.dds", _pd3dDevice, sampDesc);
	_pRustedMetal = std::make_unique<Texture>(L"Textures/rustedMetal.dds", _pd3dDevice, sampDesc);

	//_pLights[1] = Light(XMVectorSet(0.0f, -10.0f, 10.0f, 0.0f), XMVectorSet(0.941f, 0.986f, 0.990f, 1.0f)); //Moon

	// Create Terrain
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 20; z++)
			{
				XMVECTOR cubePos = XMVectorSet(-10.0f + 0.5f * x, -5.0f + 0.5f * y, -5.0f + 0.5f * z, 0.0f);
				XMVECTOR cubeScale = XMVectorSet(0.25f, 0.25f, 0.25f, 0.0f);
				XMVECTOR cubeRotation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				_pTerrain.push_back(std::make_unique<Cube>(cubePos, cubeScale, cubeRotation, *_pRocks));
			}
		}
	}

	// Create Launcher
	XMVECTOR launcherPos = XMVectorSet(-6.0f, 0.0f, 0.0f, 0.0f);//XMVectorSet(4.0f, 5.0f, 5.0f, 0.0f);
	XMVECTOR launcherScale = XMVectorSet(0.5f, 1.0f, 0.5f, 0.0f);
	XMVECTOR launcherRotation = XMVectorSet(0.0f, 0.0f, -0.261799f, 0.0f);
	_pLauncher = std::make_unique<Cylinder>(launcherPos, launcherScale, launcherRotation, *_pRustedMetal);

	// Create Rocket
	XMVECTOR rocketPos = XMVectorSet(-7.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR rocketScale = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
	XMVECTOR rocketRotation = XMVectorSet(0.0f, 0.0f, -0.261799f, 0.0f);
	_pRocket = std::make_unique<Rocket>(rocketPos, rocketScale, rocketRotation, *_pRocketMetal);

	// Create Lights
	_pLights[0] = std::make_unique<Light>(XMVectorSet(0.0f, 10.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.68f, 0.13f, 1.0f));
	_pLights[1] = std::make_unique<Light>(XMVectorSet(0.0f, -10.0f, 0.0f, 0.0f), XMVectorSet(0.578f, 0.672f, 0.980f, 1.0f));


	// Initialize the view matrix
	XMVECTOR eye = XMVectorSet(0.0f, 2.0f, -8.0f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	_pCamera = std::make_unique<Camera>(eye, at, up);
	_pCamera->updateView();

	// Initialize the projection matrix
	_pCamera->setProjection(XMMatrixPerspectiveFovLH(XM_PIDIV2, width / static_cast<FLOAT>(height), 0.01f, 100.0f));

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
D3DFramework::~D3DFramework() {
	try {
		if(_pImmediateContext) _pImmediateContext->ClearState();
		_pRocks.release();
		if (_pRocks) _pRocks.release();
		if (_pLavaRock) _pLavaRock.release();
		if (_pRocketMetal) _pRocketMetal.release();
		if (_pRustedMetal) _pRustedMetal.release();
		if (_pCamera) _pCamera.release();
		if (_pLauncher) _pLauncher.release();
	}
	catch (...) {

	}
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void D3DFramework::render() {
	//
	// Animate
	//

	_pRocket->setInitialRotation(_pLauncher->getCurrentRotation());
	_pRocket->update();

	_pCamera->updateView();

	for (int i = 0; i < 2; i++)
	{
		_pLights[i]->rotate(XMVectorSet(0.005f, 0.0f, 0.0f, 0.0f));
	}

	//
	// Clear the back buffer
	//
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, Colors::MidnightBlue);

	_pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Update variables
	//

	//
	// Renders a triangle
	//

	for (int i = 0; i < _pTerrain.size(); i++)
	{
		_pTerrain[i]->Draw(_pImmediateContext, _pConstantBuffer, _pVertexShader, _pPixelShader, *_pCamera, *_pLights[0], *_pLights[1]);
	}

	_pLauncher->Draw(_pImmediateContext, _pConstantBuffer, _pVertexShader, _pPixelShader, *_pCamera, *_pLights[0], *_pLights[1]);
	_pRocket->Draw(_pImmediateContext, _pConstantBuffer, _pVertexShader, _pPixelShader, *_pCamera, *_pLights[0], *_pLights[1]);

	//
	// Present our back buffer to our front buffer
	//
	_swapChain->Present(0, 0);
}


void D3DFramework::loadOBJ(const std::string& pFilename, std::vector<SimpleVertex>& pVertices, std::vector<WORD>& pIndices) const
{
	Assimp::Importer importer;
	const aiScene* const scene = importer.ReadFile(pFilename, aiProcess_Triangulate);

	aiMesh* const modelMesh = scene->mMeshes[0];

	for (UINT i = 0; i < modelMesh->mNumVertices; i++)
	{
		SimpleVertex vertex;

		vertex.Pos.x = modelMesh->mVertices[i].x;
		vertex.Pos.y = modelMesh->mVertices[i].y;
		vertex.Pos.z = modelMesh->mVertices[i].z;

		vertex.Norm.x = modelMesh->mNormals[i].x;
		vertex.Norm.y = modelMesh->mNormals[i].y;
		vertex.Norm.z = modelMesh->mNormals[i].z;

		vertex.TexCoord.x = static_cast<float>(modelMesh->mTextureCoords[0][i].x);
		vertex.TexCoord.y = static_cast<float>(modelMesh->mTextureCoords[0][i].y);

		pVertices.push_back(vertex);
	}

	for (UINT i = 0; i < modelMesh->mNumFaces; i++)
	{
		const aiFace face = modelMesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			pIndices.push_back(face.mIndices[j]);
		}
	}
}