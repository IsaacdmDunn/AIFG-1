#include "Car.h"


HRESULT	Car::initMesh(ID3D11Device* pd3dDevice, wstring path)
{
	m_scale = XMFLOAT3(30, 20, 1);
	setTextureName(L"Resources\\" + path + L".dds");

	HRESULT hr = DrawableGameObject::initMesh(pd3dDevice);

	m_maxSpeed = MAX_SPEED2;
	m_currentSpeed = m_maxSpeed;
	setVehiclePosition(Vector2D(0, 0));

	m_lastPosition = Vector2D(0, 0);

	return hr;
}

void Car::update(const float deltaTime)
{
	// consider replacing with force based acceleration / velocity calculations
	Vector2D vecTo = m_positionTo - m_currentPosition;
	float velocity = deltaTime * m_currentSpeed;

	/*setVehiclePosition(Vector2D(m_currentPosition.x + 0.05, m_currentPosition.y + 0.05));
	if (m_currentPosition.x > 512)
	{
		setVehiclePosition(Vector2D(-512, m_currentPosition.y));
	}
	else if (m_currentPosition.x < -512)
	{
		setVehiclePosition(Vector2D(512, m_currentPosition.y));
	}
	else if (m_currentPosition.y > 396)
	{
		setVehiclePosition(Vector2D(m_currentPosition.x, -396));
	}
	else if (m_currentPosition.y < -396)
	{
		setVehiclePosition(Vector2D(m_currentPosition.x, 396));

	}*/


	float length = (float)vecTo.Length();
	// if the distance to the end point is less than the car would move, then only move that distance. 
	if (length > 0) {
		vecTo.Normalize();
		if (length > velocity)
			vecTo *= velocity;
		else
			vecTo *= length;

		m_currentPosition += vecTo;
	}

	// rotate the object based on its last & current position
	Vector2D diff = m_currentPosition - m_lastPosition;
	if (diff.Length() > 0) { // if zero then don't update rotation
		diff.Normalize();
		m_radianRotation = atan2f(diff.y, diff.x); // this is used by DrawableGameObject to set the rotation
	}
	m_lastPosition = m_currentPosition;

	// set the current poistion for the drawablegameobject
	setPosition(XMFLOAT3((float)m_currentPosition.x, (float)m_currentPosition.y, 0));

	DrawableGameObject::update(deltaTime);
}

// a ratio: a value between 0 and 1 (1 being max speed)
void Car::setCurrentSpeed(const float speed)
{
	m_currentSpeed = m_maxSpeed * speed;
	m_currentSpeed = max(0, m_currentSpeed);
	m_currentSpeed = min(1, m_currentSpeed);
}

// a position to move to
void Car::setPositionTo(Vector2D position)
{
	m_startPosition = m_currentPosition;
	m_positionTo = position;
}

// the current position
void Car::setVehiclePosition(Vector2D position)
{
	m_currentPosition = position;
	m_positionTo = position;
	m_startPosition = position;
	setPosition(XMFLOAT3((float)position.x, (float)position.y, 0));
}
