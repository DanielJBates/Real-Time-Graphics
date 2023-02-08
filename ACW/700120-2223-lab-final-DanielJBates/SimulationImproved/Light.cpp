#include "Light.h"

void Light::rotate(const DirectX::XMVECTOR& pRotation)
{
	const DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(pRotation);
	const DirectX::XMVECTOR newPos = DirectX::XMVector4Transform(getCurrentPosition(), rotationMatrix);
	setCurrentPosition(newPos);
}
