#include "AIManager.h"
#include "Vehicle.h"
#include "Car.h"
#include "DrawableGameObject.h"
#include "PickupItem.h"
#include "Waypoint.h"

#include "main.h"


HRESULT AIManager::initialise(ID3D11Device* pd3dDevice)
{
    // create a pickup item ----------------------------------------------

    PickupItem* pPickup = new PickupItem();
    HRESULT hr = pPickup->initMesh(pd3dDevice);
    m_pickups.push_back(pPickup);


    // create the vehicle ------------------------------------------------
    float xPos = 0;
    float yPos = 0;

    m_pCar = new Vehicle();
    m_pCar2 = new Car();
    hr = m_pCar->initMesh(pd3dDevice, L"car_blue");
    hr = m_pCar2->initMesh(pd3dDevice, L"car_red");
    m_pCar->setPosition(XMFLOAT3(xPos, yPos, 0));
    m_pCar2->setPosition(XMFLOAT3(xPos, yPos, 0));
    if (FAILED(hr))
        return hr;

    // create the waypoints
    float xGap = SCREEN_WIDTH / WAYPOINT_RESOLUTION;
    float yGap = SCREEN_HEIGHT / WAYPOINT_RESOLUTION;
    float xStart = -(SCREEN_WIDTH / 2) + (xGap / 2);
    float yStart = -(SCREEN_HEIGHT / 2) + (yGap / 2);

    unsigned int index = 0;
    for (unsigned int j = 0; j < WAYPOINT_RESOLUTION; j++) {
        for (unsigned int i = 0; i < WAYPOINT_RESOLUTION; i++) {
            Waypoint* wp = new Waypoint();
            hr = wp->initMesh(pd3dDevice, index++);
            wp->setPosition(XMFLOAT3(xStart + (xGap * i), yStart + (yGap * j), 0));
            m_waypoints.push_back(wp);
        }
    }



    /*Waypoint* wp = new Waypoint();
    hr = wp->initMesh(pd3dDevice, 5 * WAYPOINT_RESOLUTION + 3);
    wp->setPosition(XMFLOAT3(xStart + (xGap * 3), yStart + (yGap * 5), 0));
    m_waypoints.push_back(wp);*/

    return hr;
}

void AIManager::update(const float fDeltaTime)
{
    for (unsigned int i = 0; i < m_waypoints.size(); i++) {
        m_waypoints[i]->update(fDeltaTime);
        AddItemToDrawList(m_waypoints[i]); // if you comment this in, it will display the waypoints
    }

    for (unsigned int i = 0; i < m_pickups.size(); i++) {
        m_pickups[i]->update(fDeltaTime);
        AddItemToDrawList(m_pickups[i]);
    }

    m_pCar->update(fDeltaTime);
    m_pCar2->update(fDeltaTime);

    checkForCollisions();

    AddItemToDrawList(m_pCar);
    AddItemToDrawList(m_pCar2);
}

void AIManager::mouseUp(int x, int y)
{
    m_pCar->setPositionTo(Vector2D(x, y));
    m_pCar2->setPositionTo(Vector2D(x + 25, y));
}

void AIManager::space(int x, int y)
{
    m_pCar->setPositionTo(Vector2D(x, y));
    m_pCar2->setPositionTo(Vector2D(x + 25, y));
}

void AIManager::keyPress(WPARAM param)
{
    switch (param)
    {
        case VK_NUMPAD0:
        {
            OutputDebugStringA("0 pressed \n");
            break;
        }
        case VK_NUMPAD1:
        {
            OutputDebugStringA("1 pressed \n");
            break;
        }
        case VK_NUMPAD2:
        {
            break;
        }
        case VK_SPACE:
        {
            space(0, 0);
            break;
        }
        // etc
        default:
            break;
    }
}

bool AIManager::checkForCollisions()
{
    if (m_pickups.size() == 0)
        return false;

    XMVECTOR dummy;

    // the car
    XMVECTOR carPos;
    XMVECTOR carScale;
    XMMatrixDecompose(
        &carScale,
        &dummy,
        &carPos,
        XMLoadFloat4x4(m_pCar->getTransform())
    );

    XMFLOAT3 scale;
    XMStoreFloat3(&scale, carScale);
    BoundingSphere boundingSphereCar;
    XMStoreFloat3(&boundingSphereCar.Center, carPos);
    boundingSphereCar.Radius = scale.x;

    // a pickup - !! NOTE it is only referring the first one in the list !!
    XMVECTOR puPos;
    XMVECTOR puScale;
    XMMatrixDecompose(
        &puScale,
        &dummy,
        &puPos,
        XMLoadFloat4x4(m_pickups[0]->getTransform())
    );

    XMStoreFloat3(&scale, puScale);
    BoundingSphere boundingSpherePU;
    XMStoreFloat3(&boundingSpherePU.Center, puPos);
    boundingSpherePU.Radius = scale.x;

    // test
    if (boundingSphereCar.Intersects(boundingSpherePU))
    {
        OutputDebugStringA("Collision!\n");
        return true;
    }

    return false;
}

Waypoint* AIManager::getWaypoint(const int x, const int y)
{
    Waypoint* w = m_waypoints[y * WAYPOINT_RESOLUTION + x];
    return w;
}

//Waypoint* AIManager::getWaypointNeighbours(const int x, const int y)
//{
//    /*Waypoint* w[8];
//    w[0] = m_waypoints[y-1 * WAYPOINT_RESOLUTION + x-1];
//    w[1] = m_waypoints[y-1 * WAYPOINT_RESOLUTION + x];
//    w[2] = m_waypoints[y-1 * WAYPOINT_RESOLUTION + x+1];
//
//    w[3] = m_waypoints[y * WAYPOINT_RESOLUTION + x-1];
//    w[4] = m_waypoints[y * WAYPOINT_RESOLUTION + x];
//    w[5] = m_waypoints[y * WAYPOINT_RESOLUTION + x+1];
//
//    w[6] = m_waypoints[y+1 * WAYPOINT_RESOLUTION + x-1];
//    w[7] = m_waypoints[y+1 * WAYPOINT_RESOLUTION + x];
//    w[8] = m_waypoints[y+1 * WAYPOINT_RESOLUTION + x+1];*/
//    return 
//}


