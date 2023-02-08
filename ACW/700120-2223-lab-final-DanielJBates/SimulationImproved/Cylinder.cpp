#include "Cylinder.h"

void Cylinder::Draw(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader, const Camera& pCamera, const Light& pSun, const Light& pMoon)
{
	updateCB(pContext, pConstantBuffer, pCamera, pSun, pMoon);

	pContext->VSSetShader(pVertexShader, nullptr, 0);
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer.p);
	pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer.p);
	pContext->PSSetShader(pPixelShader, nullptr, 0);
	pContext->PSSetShaderResources(0, 1, &getTexture().getSRV().p);
	pContext->PSSetSamplers(0, 1, &getTexture().getSampler().p);
	pContext->DrawIndexed(132, 36, 24);
}
