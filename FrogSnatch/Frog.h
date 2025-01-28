#ifndef FROG_H
#define FROG_H

#include "GameObject.h"

#define TONGUE_FAST_SPEED 45
#define TONGUE_NORMAL_SPEED 30
#define TONGUE_SLOW_SPEED 15
#define TONGUE_DRAWBACK_TIME 0.1 * 60

class Frog : public GameObject
{
private:

    // Frog Variables
    Texture2D m_FrogTexture;

    // Tongue Tip Variables
    Texture2D m_TongueTexture;
    Vector2 m_TongueSize;
    Vector2 m_TonguePosition;
    float m_TongueSpeed;
    bool m_TongueActive;

    float m_TongueExtendTimer;
    float m_CalculatedTongueTime;
    Vector2 m_NormDirection;
    int m_FlipDirection;

    // Tongue Length
    Vector2 m_TLStart;
    Vector2 m_TLEnd;
    Color m_TongueColour = PINK;

    bool m_HasPlayedTongue = false;
    Sound m_TongueSound;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Frog(ObjectType tag, Vector2 position, Vector2 size, float rotation, const char* texture);

    /// @brief Default Destructor for Class
    ~Frog();



    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // GETTER FUNCTION(s)
    inline Rectangle GetTongueRectangle() { return Rectangle{m_TonguePosition.x, m_TonguePosition.y, m_TongueSize.x, m_TongueSize.y}; }
    
    inline Vector2 GetTonguePosition() { return m_TonguePosition; }
    inline Vector2 GetTongueSize() { return m_TongueSize; }

    // SETTER FUNCTION(s)
    inline void SetTongueSpeed(float speed) { this->m_TongueSpeed = speed; }
    inline void SetTongueColour(Color colour) { this->m_TongueColour = colour; }

};

#endif