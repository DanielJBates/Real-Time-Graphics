#include "Rocket.h"

void Rocket::launch()
{
	_mLaunch = true;

	float angle = DirectX::XMVectorGetZ(getInitialRotation());

	float vy = sqrtf(2 * 9.8f * 7.5f);

	float timeToPeak = vy / 9.8f;

	float xDistance = 2 * vy * sinf(-angle) * timeToPeak;
	float vx = xDistance / timeToPeak;

	_mInitialVelocity = DirectX::XMVectorSet(vx, vy, 0.0f, 0.0f);
	_mCurrentVelocity = _mInitialVelocity;
}

void Rocket::Draw(const CComPtr<ID3D11DeviceContext>& const pContext, const CComPtr <ID3D11Buffer>& const pConstantBuffer, const CComPtr<ID3D11VertexShader>& const pVertexShader, const CComPtr<ID3D11PixelShader>& const pPixelShader, const Camera& pCamera, const Light& pSun, const Light& pMoon)
{
	updateCB(pContext, pConstantBuffer, pCamera, pSun, pMoon);

	pContext->VSSetShader(pVertexShader, nullptr, 0);
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer.p);
	pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer.p);
	pContext->PSSetShader(pPixelShader, nullptr, 0);
	pContext->PSSetShaderResources(0, 1, &getTexture().getSRV().p);
	pContext->PSSetSamplers(0, 1, &getTexture().getSampler().p);
	pContext->DrawIndexed(210, 960, 648);
}

void Rocket::update(double pDeltaTime)
{
	if (_mLaunch)
	{
		const float vx = DirectX::XMVectorGetX(_mCurrentVelocity);
		float vy = DirectX::XMVectorGetY(_mCurrentVelocity);

		float x = DirectX::XMVectorGetX(getCurrentPosition());
		float y = DirectX::XMVectorGetY(getCurrentPosition());
		const float z = DirectX::XMVectorGetZ(getCurrentPosition());

		x += vx * pDeltaTime;
		y += vy * pDeltaTime - 0.5f * 9.8f * pDeltaTime * pDeltaTime;

		vy -= 9.8f * pDeltaTime;

		_mCurrentVelocity = DirectX::XMVectorSet(vx, vy, 0.0f, 0.0f);

		setCurrentPosition(DirectX::XMVectorSet(x, y, z, 0.0f));

		float c2 = (vx * vx) + (vy * vy);
		float angle = -cosf(vx / c2 );

        rotate(DirectX::XMVectorSet(0.0f, 0.0f, angle * pDeltaTime, 0.0f));

		if (y <= 0.0f)
		{
			reset();
			_mLaunch = false;
			_mCurrentVelocity = _mInitialVelocity;
		}
	}
}
