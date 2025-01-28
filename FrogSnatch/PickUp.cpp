#include "PickUp.h"

PickUp::PickUp(ObjectType tag, Vector2 position, Vector2 size, float rotation, const char* texture) 
: GameObject(tag, position, size, rotation)
{
    m_Texture = LoadTexture(texture);
    m_Texture.width = m_Size.x;
    m_Texture.height = m_Size.y;
}

PickUp::~PickUp() 
{
    UnloadTexture(m_Texture);
}

void PickUp::Update(float deltaTime) 
{
    m_Position.y += FALL_SPEED * deltaTime;
}

void PickUp::Draw() 
{
    DrawTexturePro
    (
        m_Texture,
        Rectangle{0, 0, m_Size.x, m_Size.y},
        Rectangle{m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Size.x, m_Size.y},
        Vector2{m_Size.x / 2, m_Size.y / 2 },
        m_Rotation,
        WHITE
    );
}
