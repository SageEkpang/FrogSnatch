#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Constants.h"
#include "Struct.h"

struct SimpleObject
{
    Texture2D texture;
    Vector2 position;
    int scale;

    SimpleObject(Texture2D texture, Vector2 position, int scale)
    {
        this->texture = texture;
        this->position = position;
        this->scale = scale;
    }

};

enum ObjectType
{
    BUTTON,
    PLAYER,
    ENEMY,
    BUFF,
    DEBUFF
};

class GameObject
{
protected:

    ObjectType m_Tag;
    Vector2 m_Position;
    Vector2 m_Size;
    
    float m_Rotation;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameObject(ObjectType tag, Vector2 position, Vector2 size, float rotation);

    /// @brief Default Destructor for Class
    virtual ~GameObject() { };


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float deltaTime) = 0;

    /// @brief Default Draw function for Class
    virtual void Draw() = 0;


    // GETTER FUNCTION(s)
    inline Rectangle GetRectangle() { return Rectangle{m_Position.x, m_Position.y, m_Size.x, m_Size.y}; }
    inline ObjectType GetTag() { return m_Tag; }
    inline Vector2 GetPosition() { return m_Position; }
    inline Vector2 GetSize() { return m_Size; }
    inline float GetRotation() { return m_Rotation; }


    // SETTER FUNCTION(s)
    inline void SetTag(ObjectType tag) {this->m_Tag = tag; }

    inline void SetPosition(Vector2 position) { this->m_Position = position; }
    inline void SetPosition(float x, float y) { this->m_Position = Vector2{x, y}; }

    inline void SetSize(Vector2 size) { this->m_Size = size; }
    inline void SetSize(float x, float y) {this->m_Size = Vector2{x, y}; }

    inline void SetRotation(float& rotation) { this->m_Rotation = rotation; }
    
};

#endif