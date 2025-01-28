#include "Button.h"

Button::Button(ObjectType tag, Vector2 position, Vector2 size, float rotation, std::string text) 
    : GameObject(tag, position, size, rotation)
{
    m_Text = text;
    m_TextFont = LoadFont("Font/UIFont.ttf");
    m_Texture = LoadTexture("Images/FrogButton.png");
    m_Texture.width = m_Size.x;
    m_Texture.height = m_Size.y;

    m_ButtonColour = WHITE;
}

Button::~Button() 
{
    UnloadTexture(m_Texture);
    UnloadFont(m_TextFont);
    // UnloadSound(m_ButtonSound);
}

void Button::Update(float deltaTime) 
{
    if (!CheckCollisionRecs(Rectangle{m_Position.x, m_Position.y, m_Size.x, m_Size.y}, 
    Rectangle{(float)GetMouseX(), (float)GetMouseY(), 1, 1})) { m_ButtonPressed = false; return; } 

    if (IsMouseButtonPressed(3)) { m_ButtonColour = GRAY; m_ButtonPressed = true; }
    else if (IsMouseButtonUp(3)) { m_ButtonColour = WHITE; m_ButtonPressed = false; }
}

void Button::Draw() 
{
    DrawTexturePro(
    m_Texture, 
    Rectangle{0, 0, m_Size.x, m_Size.y}, 
    Rectangle{m_Position.x + (m_Size.x / 2), m_Position.y + (m_Size.y / 2), m_Size.x, m_Size.y}, 
    Vector2{m_Size.x / 2, m_Size.y / 2}, 
    m_Rotation,
    m_ButtonColour
    );

    // TODO: Fix how the text is created on the screen
    DrawTextEx(m_TextFont, m_Text.c_str(), Vector2{m_Position.x + (m_Size.x / 2) - m_ButtonPadding.x, m_Position.y + (m_Size.y / 2) - m_ButtonPadding.y}, m_ButtonFontSize, 1, WHITE);

}
