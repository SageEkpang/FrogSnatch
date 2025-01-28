#ifndef FLY_H
#define FLY_H

#include "GameObject.h"

#define ROTATION_SPEED 10
#define ROTATION_DEGREE 10
#define SWIPE_SPEED 3

class Fly : public GameObject
{
private:

    // Fly Variables
    Texture2D m_FlyTexture;

    // Rotation Variables
    float m_TurningRate;
    float m_RotationSpeedOffset;

    // Speed Variables
    float m_FlyYSpeed;

    // Offset Values
    float m_SwipeRate;
    float m_PositionDirectionOffset;
    float m_WaveBasedOffset;

    static Texture2D m_NormalFlyText;

public:

    // CLASS FUNCTION(s)

    Fly(ObjectType tag, Vector2 position, Vector2 size, float rotation, Texture2D texture, int waveOffset);

    ~Fly();

    // BASE FUNCTION(s)
    void Update(float deltaTime) override;
    void Draw() override;


    // GETTER FUNCTION(s)
    inline float GetFlySpeed() { return m_FlyYSpeed; }

    // SETTER FUNCTION(s)
    inline void SetFlySpeed(float speed) { this->m_FlyYSpeed = speed; }
};

#endif