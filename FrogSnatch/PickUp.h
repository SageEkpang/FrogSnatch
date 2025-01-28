#ifndef PICK_UP_H
#define PICK_UP_H

#include "GameObject.h"

#define FALL_SPEED 100

class PickUp : public GameObject
{
private:

    Texture2D m_Texture;
    float m_EffectSpeed;

public:

    // CLASS FUNCTION(s)
    PickUp(ObjectType tag, Vector2 position, Vector2 size, float rotation, const char* texture);

    ~PickUp();


    // BASE FUNCTION(s)
    void Update(float deltaTime) override;

    void Draw() override;


    // GETTER FUNCTION(s)
    inline float GetSpeed() { return m_EffectSpeed; }

    // SETTER FUNCTION(s)
    inline void SetSpeed(float speed) { this->m_EffectSpeed = speed; }

};

#endif