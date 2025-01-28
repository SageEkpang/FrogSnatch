#include "GameObject.h"

GameObject::GameObject(ObjectType tag, Vector2 position, Vector2 size, float rotation) 
: m_Tag(tag), m_Position(position), m_Size(size), m_Rotation(rotation)
{
}