#include "Frog.h"

Frog::Frog(ObjectType tag, Vector2 position, Vector2 size, float rotation, const char* texture)
    : GameObject(tag, position, size, rotation)
{

    m_TongueActive = false;

    // Frog Variables
    m_FrogTexture = LoadTexture(texture);
    m_FrogTexture.width = m_Size.x;
    m_FrogTexture.height = m_Size.y;


    // Tongue Variables
    m_TongueTexture = LoadTexture("Images/TongueTip.png");

    m_TongueSound = LoadSound("Sound/TongueNoise.wav");
    SetSoundVolume(m_TongueSound, 5.0f);

    m_TongueSize.x = m_Size.x / 2;
    m_TongueSize.y = m_Size.y / 2;

    m_TongueTexture.width = m_TongueSize.x;
    m_TongueTexture.height = m_TongueSize.y;
    
    m_TonguePosition.x = m_Position.x + (m_Size.x / 4);
    m_TonguePosition.y = m_Position.y + (m_Size.y / 4);

    m_TLStart.x = m_Position.x + (m_Size.x / 2);
    m_TLStart.y = m_Position.y + (m_Size.y / 2);

    m_TLEnd.x = m_Position.x + (m_Size.x / 2);
    m_TLEnd.y = m_Position.y + (m_Size.y / 2);

    m_FlipDirection = 1;

    m_TongueSpeed = TONGUE_NORMAL_SPEED;
}

Frog::~Frog() 
{
    UnloadTexture(m_TongueTexture);
    UnloadTexture(m_FrogTexture);
}

void Frog::Update(float deltaTime) 
{
    // Frog Rotation
    if (m_TongueActive == false) 
    { 
        Vector2 TempPosition;
        TempPosition.x = m_Position.x + (m_Size.x / 2);
        TempPosition.y = m_Position.y + (m_Size.y / 2);
        m_Rotation = Vector2Angle(TempPosition, GetMousePosition()); 
    }

    // Tongue Tip Code (New)
    if (IsMouseButtonPressed(3) && m_TongueActive == false)
    {
        // Tongue Calculations (Normalised Distance, Calculated Time)
        Vector2 FrogPos = Vector2{m_Position.x + (m_Size.x / 2) - (m_TongueSize.x / 2), m_Position.y + (m_Size.y / 2) - (m_TongueSize.y / 2)};
        Vector2 EndPos = Vector2{GetMouseX() - (m_TongueSize.x / 2), GetMouseY() - (m_TongueSize.y / 2)};
        
        m_NormDirection = Vector2Normalize(Vector2Subtract(FrogPos, EndPos));
        m_CalculatedTongueTime = Vector2Distance(FrogPos, EndPos) / TONGUE_NORMAL_SPEED;

        m_TongueActive = true;
    }

    if (m_TongueActive == true)
    {
        // Play Tongue Sound
        if (!IsSoundPlaying(m_TongueSound) && m_HasPlayedTongue == false) 
        { 
            PlaySound(m_TongueSound);
            m_HasPlayedTongue = true;
        }
        
        // Move Tongue Tip and Segment
        m_TonguePosition.x -= m_TongueSpeed * m_NormDirection.x * m_FlipDirection;
        m_TonguePosition.y -= m_TongueSpeed * m_NormDirection.y * m_FlipDirection;
        m_TLEnd.x = m_TonguePosition.x + (m_TongueSize.x / 2);
        m_TLEnd.y = m_TonguePosition.y + (m_TongueSize.y / 2);

        // Tongue Timer
        m_TongueExtendTimer += m_TongueSpeed * deltaTime;
    }

    if (m_TongueExtendTimer >= m_CalculatedTongueTime / 2)
    {
        m_FlipDirection = -1;

        if (m_TongueExtendTimer >= m_CalculatedTongueTime)
        {
            m_TonguePosition.x = m_Position.x + (m_Size.x / 4);
            m_TonguePosition.y = m_Position.y + (m_Size.y / 4);

            m_TLStart.x = m_Position.x + (m_Size.x / 2);
            m_TLStart.y = m_Position.y + (m_Size.y / 2);

            m_TLEnd.x = m_Position.x + (m_Size.x / 2);
            m_TLEnd.y = m_Position.y + (m_Size.y / 2);

            m_FlipDirection = 1;
            m_TongueActive = false;
            m_HasPlayedTongue = false;
            m_TongueExtendTimer = 0;
        }
    }

    if (m_TongueSpeed != TONGUE_NORMAL_SPEED)
    {
        m_TongueSpeed = Lerp(m_TongueSpeed, TONGUE_NORMAL_SPEED, deltaTime / 10);
        
        if ((m_TongueSpeed >= TONGUE_NORMAL_SPEED - 5 && m_TongueSpeed < TONGUE_NORMAL_SPEED)
            || (m_TongueSpeed <= TONGUE_NORMAL_SPEED + 5 && m_TongueSpeed > TONGUE_NORMAL_SPEED))
        {
            m_TongueSpeed = TONGUE_NORMAL_SPEED;
            m_TongueColour = PINK;
        }
    }
}

void Frog::Draw() 
{
    // Frog Tongue
    DrawLineEx(m_TLStart, m_TLEnd, 22, BLACK);
    DrawCircleV(Vector2{m_TonguePosition.x + (m_TongueSize.x / 2), m_TonguePosition.y + (m_TongueSize.y / 2)}, 30, BLACK);

    DrawLineEx(m_TLStart, m_TLEnd, 15, m_TongueColour);
    DrawTextureV(m_TongueTexture, m_TonguePosition, m_TongueColour);

    // Frog Body
    DrawTexturePro(
    m_FrogTexture, 
    Rectangle{0, 0, m_Size.x, m_Size.y}, 
    Rectangle{m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Size.x, m_Size.y}, 
    Vector2{m_Size.x / 2, m_Size.y / 2}, 
    m_Rotation + 90, 
    WHITE
    );
}

