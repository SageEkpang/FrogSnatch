#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

class Button : public GameObject
{
private:

    std::string m_Text;
    Texture m_Texture;
    Rectangle m_ButtonRec;
    Sound m_ButtonSound;
    bool m_ButtonPressed;
    Color m_ButtonColour;
    Font m_TextFont;
    Vector2 m_ButtonPadding;
    int m_ButtonFontSize;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Button(ObjectType tag, Vector2 position, Vector2 size, float rotation, std::string text);

    /// @brief Default Destructor for Class
    ~Button();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime) override;

    /// @brief Default draw function for Class
    void Draw() override;


    // GETTER FUNCTION(s)
    inline bool GetPressed() { return m_ButtonPressed; }


    // SETTER FUNCTION(s)
    inline void SetButtonPadding(Vector2 buttonPadding) { this->m_ButtonPadding = buttonPadding; }
    inline void SetButtonFontSize(int fontSize) { this->m_ButtonFontSize = fontSize; }

};

#endif