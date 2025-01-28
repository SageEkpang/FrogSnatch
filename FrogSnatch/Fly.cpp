#include "Fly.h"

Fly::Fly(ObjectType tag, Vector2 position, Vector2 size, float rotation, Texture2D texture, int waveOffset)
: GameObject(tag, position, size, rotation)
{
    m_FlyTexture = texture;
    m_FlyTexture.width = m_Size.x;
    m_FlyTexture.height = m_Size.y;

    m_RotationSpeedOffset = (float)(GetRandomValue(1, 10)) / 10;
    m_PositionDirectionOffset = (float)GetRandomValue(1, 10);

    m_WaveBasedOffset = waveOffset * 0.5;
    float Temp = Clamp(m_WaveBasedOffset, 0, 4);
    m_FlyYSpeed = (float)GetRandomValue(50 * Temp, 80 * Temp);
}

Fly::~Fly() 
{
    
}

void Fly::Update(float deltaTime) 
{
    // Fly Rotation Code
    m_TurningRate += ROTATION_SPEED * m_RotationSpeedOffset * deltaTime;
    m_Rotation = (cosf(m_TurningRate) * ROTATION_DEGREE) + (sinf(m_TurningRate) * ROTATION_DEGREE) * deltaTime;
    if (m_TurningRate == 100) m_TurningRate = 0;

    // Fly Falling Code
    m_SwipeRate += SWIPE_SPEED * m_PositionDirectionOffset * deltaTime;
    m_Position.y += m_FlyYSpeed * deltaTime;
    m_Position.x += sinf(m_SwipeRate);
    if (m_SwipeRate == 100) m_SwipeRate = 0;
}

void Fly::Draw() 
{
    DrawTexturePro
    (
        m_FlyTexture,
        Rectangle{0, 0, m_Size.x, m_Size.y},
        Rectangle{m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Size.x, m_Size.y},
        Vector2{m_Size.x / 2, m_Size.y / 2},
        m_Rotation,
        WHITE
    );
}
