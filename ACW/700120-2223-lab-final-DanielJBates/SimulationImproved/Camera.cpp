#include "Camera.h"

void Camera::rotate(const DirectX::XMVECTOR& pRotation)
{
	const DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(pRotation);
	const DirectX::XMVECTOR newEye = DirectX::XMVector4Transform(_mEye, rotationMatrix);
	_mEye = newEye;
}

void Camera::pan(const DirectX::XMVECTOR& pTranslation)
{
	const DirectX::XMVECTOR newAt = DirectX::XMVectorSet(DirectX::XMVectorGetX(_mAt) + DirectX::XMVectorGetX(pTranslation), DirectX::XMVectorGetY(_mAt) + DirectX::XMVectorGetY(pTranslation), DirectX::XMVectorGetZ(_mAt) + DirectX::XMVectorGetZ(pTranslation), 0.0f);
	_mAt = newAt;
}
