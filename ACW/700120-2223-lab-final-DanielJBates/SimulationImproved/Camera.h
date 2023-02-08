#pragma once
#include <DirectXMath.h>

class Camera final
{
	DirectX::XMVECTOR _mEye;
	DirectX::XMVECTOR _mAt;
	DirectX::XMVECTOR _mUp;

	DirectX::XMMATRIX _mView;
	DirectX::XMMATRIX _mProjection;

public:
	explicit Camera(const DirectX::XMVECTOR& pEye, const DirectX::XMVECTOR& pAt, const DirectX::XMVECTOR& pUp) : _mEye(pEye), _mAt(pAt), _mUp(pUp) { updateView(); };

	void updateView() { _mView = DirectX::XMMatrixLookAtLH(_mEye, _mAt, _mUp); }

	void setEye(const DirectX::XMVECTOR& pEye) { _mEye = pEye; }
	void setAt(const DirectX::XMVECTOR& pAt) { _mAt = pAt; }

	void rotate(const DirectX::XMVECTOR& pRotation);
	void pan(const DirectX::XMVECTOR& pTranslation);

	void setProjection(const DirectX::XMMATRIX& pProjection) { _mProjection = pProjection; }

	const DirectX::XMVECTOR& getEye() const { return _mEye; }

	const DirectX::XMMATRIX& getView() const { return _mView; }
	const DirectX::XMMATRIX& getProjection() const { return _mProjection; }
};

