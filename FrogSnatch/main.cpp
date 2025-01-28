#include "Constants.h"
#include "Struct.h"
#include "Frog.h"
#include "Fly.h"
#include "PickUp.h"
#include "Button.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FrogSnatch");
    InitAudioDevice();
    
    // Main Game Variables
    int m_Score = DEFAULT_SCORE;
    int m_Wave = DEFAULT_WAVE;
    int m_FlyCount = DEFAULT_WAVE;
    int m_TotalFlyKilled = DEFAULT_TOTAL_KILLS;
    float m_Health = DEFAULT_HEALTH;
    bool m_Activate = true;
    bool m_LevelStart = false;
    bool m_PauseGame = false;

    // Timer Game Variables
    float m_EnemySpawnTimer = DEFAULT_ENEMY_TIMER;
    float m_DebuffSpawnTimer = DEFAULT_DEBUFF_TIMER;
    float m_BuffSpawnTimer = DEFAULT_BUFF_TIMER;

    float m_EnemySpawnOffset = DEFAULT_ENEMY_SPAWN_TIME;
    float m_DebuffSpawnOffset = DEFAULT_DEBUFF_SPAWN_TIME;
    float m_BuffSpawnOffset = DEFAULT_BUFF_SPAWN_TIME;

    float m_WaveUpdateTimer = DEFAULT_WAVE_UPDATE_TIME;
    float m_WaveTransitionTimer = DEFAULT_WAVE_TRANSITION_TIME;

    float m_WaveUpdateOffset = WAVE_TIME * 60;
    float m_WaveTransitionOffset = WAVE_TRANSITION_TIME * 60;

    /////////////////////////////////////////////////////////////////

    // Base Load Variables
    Frog* m_Frog = new Frog(ObjectType::PLAYER, Vector2{300, 600}, Vector2{100, 100}, 0,"Images/Frog.png");
    
    Texture2D m_FrogEgg = LoadTexture("Images/FrogEgg.png");
    m_FrogEgg.width = 30;
    m_FrogEgg.height = 30;

    std::vector<SimpleObject> m_FrogSpawn;
    for (int i = 0; i < m_Health; ++i)
    {
        float RandomVariable = GetRandomValue(-5, 5);
        float Spacing = WINDOW_WIDTH / m_Health;
        SimpleObject temp(m_FrogEgg, Vector2{(float)(i * Spacing), WINDOW_HEIGHT - 15 + (RandomVariable)}, 30);
        m_FrogSpawn.push_back(temp);
    }

    std::vector<GameObject*> m_GameObjects;

    // Extra Load Variables
    Font m_TextFont = LoadFont("Font/UIFont.ttf");
    Texture2D m_Title = LoadTexture("Images/FrogSnatch.png");
    Texture2D m_Background = LoadTexture("Images/FrogBackground.png");

    Texture2D m_NormalFly = LoadTexture("Images/Fly.png");
    Texture2D m_FireFly = LoadTexture("Images/FireFly.png");
    Texture2D m_IceFly = LoadTexture("Images/IceFly.png");


    Sound m_ClickSound = LoadSound("Sound/ClickSound.wav");
    Sound m_FireFlySound = LoadSound("Sound/FireFly.wav");
    Sound m_FlyDeathSound = LoadSound("Sound/FlyDeath.wav");
    Sound m_FlySpawnSound = LoadSound("Sound/FlySpawn.wav");

    bool m_HasPlayedGameover = false;
    Sound m_GameOverSound = LoadSound("Sound/GameOver.wav");
    Sound m_IceFlySound = LoadSound("Sound/IceFly.wav");
    Sound m_GameSoundTrackMusic = LoadSound("Sound/GameSoundtrack.wav");
    Sound m_MainMenuSoundTrack = LoadSound("Sound/MainMenuSoundtrack.wav");

    // TODO: Wave Clear Sound

    SetSoundVolume(m_ClickSound, 1.0f);
    SetSoundVolume(m_FireFlySound, 1.0f);
    SetSoundVolume(m_FlyDeathSound, 0.2f);
    SetSoundVolume(m_FlySpawnSound, 0.5f);

    SetSoundVolume(m_GameOverSound, 1.0f);
    SetSoundVolume(m_IceFlySound, 1.0f);

    SetSoundVolume(m_GameSoundTrackMusic, 0.2f);
    SetSoundVolume(m_MainMenuSoundTrack, 0.1f);

    m_Background.width = WINDOW_WIDTH;
    m_Background.height = WINDOW_HEIGHT;

    /////////////////////////////////////////////////////////////////

    // Button Variables
    Button* m_ExitButton = new Button(ObjectType::BUTTON, Vector2{WINDOW_WIDTH / 2 - (150 / 2), (WINDOW_HEIGHT / 2 - (75 / 2)) + 80}, Vector2{150, 75}, 0, "Exit");
    m_ExitButton->SetButtonFontSize(25);
    m_ExitButton->SetButtonPadding(Vector2{50, 10});

    Button* m_RestartButton = new Button(ObjectType::BUTTON, Vector2{WINDOW_WIDTH / 2 - (150 / 2), WINDOW_HEIGHT / 2 - (75 / 2)}, Vector2{150, 74}, 0, "Restart");
    m_RestartButton->SetButtonFontSize(15);
    m_RestartButton->SetButtonPadding(Vector2{55, 10});

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float DeltaTime = GetFrameTime();

        // UPDATE

        // Button or Mouse Interactions
        if (IsMouseButtonPressed(3)) 
        { 
            PauseSound(m_MainMenuSoundTrack);
            m_LevelStart = true; 
        }

        if (IsKeyPressed(KEY_P) && m_PauseGame == false) { m_PauseGame = true; }
        else if (IsKeyPressed(KEY_P) && m_PauseGame == true) { m_PauseGame = false; }

        // Updating Game 
        if (m_PauseGame == false) 
        { 
            m_Frog->Update(DeltaTime);
        }
        
        if (m_PauseGame == true || m_Health <= 0)
        {
            m_ExitButton->Update(DeltaTime);
            m_RestartButton->Update(DeltaTime);

            if (m_ExitButton->GetPressed() == true) 
            { 
                PlaySound(m_ClickSound);
                break; 
            }

            if (m_RestartButton->GetPressed() == true)
            {   
                PlaySound(m_ClickSound);

                m_Score = DEFAULT_SCORE;
                m_Wave = DEFAULT_WAVE;
                m_FlyCount = DEFAULT_WAVE;
                m_TotalFlyKilled = DEFAULT_TOTAL_KILLS;
                m_Health = DEFAULT_HEALTH;

                m_EnemySpawnTimer = DEFAULT_ENEMY_TIMER;
                m_DebuffSpawnTimer = DEFAULT_DEBUFF_TIMER;
                m_BuffSpawnTimer = DEFAULT_BUFF_TIMER;

                m_EnemySpawnOffset = DEFAULT_ENEMY_SPAWN_TIME;
                m_DebuffSpawnOffset = DEFAULT_DEBUFF_SPAWN_TIME;
                m_BuffSpawnOffset = DEFAULT_BUFF_SPAWN_TIME;

                m_WaveUpdateTimer = DEFAULT_WAVE_UPDATE_TIME;
                m_WaveTransitionTimer = DEFAULT_WAVE_TRANSITION_TIME;

                m_HasPlayedGameover = false;

                std::vector<GameObject*>::iterator GameObjectItr;
                for (GameObjectItr = m_GameObjects.begin(); GameObjectItr != m_GameObjects.end(); ++GameObjectItr) { delete *GameObjectItr; }
                m_GameObjects.clear();
                m_PauseGame = false;
            }
        }

        if (m_LevelStart == true)
        {
            if (m_Health > 0)
            {
                if (m_PauseGame == false)
                {
                    // Game Object Updates
                    if (m_Activate == true) 
                    {
                        // Update Game Objects
                        for (auto& v : m_GameObjects) { v->Update(DeltaTime); }
                        for (size_t i = 0; i < m_GameObjects.size(); ++i)
                        {
                            if (!m_GameObjects.empty())
                            {
                                if (CheckCollisionRecs(m_Frog->GetTongueRectangle(), m_GameObjects[i]->GetRectangle()))
                                {
                                    switch (m_GameObjects[i]->GetTag())
                                    {
                                        case ObjectType::BUFF:
                                        case ObjectType::DEBUFF:
                                        case ObjectType::ENEMY:
                                        {
                                            m_GameObjects[i]->SetPosition(Vector2{m_Frog->GetTonguePosition().x + (m_Frog->GetTongueSize().x / 4), m_Frog->GetTonguePosition().y + (m_Frog->GetTongueSize().y / 4)});
                                        }
                                        break;

                                        default: break;
                                    }
                                }

                                if (CheckCollisionRecs(m_Frog->GetRectangle(), m_GameObjects[i]->GetRectangle()))
                                {
                                    switch (m_GameObjects[i]->GetTag())
                                    {
                                        case ObjectType::BUFF:
                                        {
                                            delete m_GameObjects[i];
                                            m_GameObjects.erase(m_GameObjects.begin() + i);
                                            PlaySound(m_FireFlySound);
                                            m_Frog->SetTongueSpeed(TONGUE_FAST_SPEED);
                                            m_Frog->SetTongueColour(RED);
                                            ++m_FlyCount;
                                            ++m_Score;
                                        }
                                        break;

                                        case ObjectType::DEBUFF:
                                        {
                                            delete m_GameObjects[i];
                                            m_GameObjects.erase(m_GameObjects.begin() + i);
                                            PlaySound(m_IceFlySound);
                                            m_Frog->SetTongueSpeed(TONGUE_SLOW_SPEED);
                                            m_Frog->SetTongueColour(BLUE);
                                            ++m_FlyCount;
                                            ++m_Score;
                                        }
                                        break;

                                        case ObjectType::ENEMY:
                                        {
                                            delete m_GameObjects[i];
                                            m_GameObjects.erase(m_GameObjects.begin() + i);
                                            PlaySound(m_FlyDeathSound);
                                            ++m_FlyCount;
                                            ++m_Score;
                                        }
                                        break;

                                        default: break;
                                    }
                                }
                                
                                // Handle GameObjects out of the Screen
                                if (m_GameObjects[i]->GetPosition().y > WINDOW_HEIGHT)
                                {
                                    m_Health -= 1.0f; 
                                    delete m_GameObjects[i];
                                    m_GameObjects.erase(m_GameObjects.begin() + i);
                                }
                            }
                        }

                        // Wave Update Code
                        m_WaveUpdateTimer += 60.0f * DeltaTime;
                        if (m_WaveUpdateTimer < m_WaveUpdateOffset)
                        {
                            // Fly Spawn
                            m_EnemySpawnTimer += 60.0f * DeltaTime;
                            if (m_EnemySpawnTimer >= GetFPS() * Clamp(m_EnemySpawnOffset, 0.1, m_EnemySpawnOffset))
                            {
                                if (!IsSoundPlaying(m_FlySpawnSound)) { PlaySound(m_FlySpawnSound); }

                                float RandomX = GetRandomValue(40, WINDOW_WIDTH - 40);
                                Fly* temp = new Fly(ObjectType::ENEMY, Vector2{RandomX, -40}, Vector2{40, 40}, 0, m_NormalFly, m_Wave);
                                m_GameObjects.push_back(temp);
                                m_EnemySpawnTimer = 0.0f;
                            }

                            // Pick Up Spawn
                            m_DebuffSpawnTimer += 60.0f * DeltaTime;
                            if (m_DebuffSpawnTimer >= 60.0f * Clamp(m_DebuffSpawnOffset, 0.1, m_DebuffSpawnOffset))
                            {
                                if (!IsSoundPlaying(m_FlySpawnSound)) { PlaySound(m_FlySpawnSound); }
                                float RandomX = GetRandomValue(40, WINDOW_WIDTH - 40);
                                Fly* temp = new Fly(ObjectType::DEBUFF, Vector2{RandomX, -40}, Vector2{40, 40}, 0, m_IceFly, m_Wave);
                                m_GameObjects.push_back(temp);
                                m_DebuffSpawnTimer = 0.0f;
                            }

                            m_BuffSpawnTimer += 60.0f * DeltaTime;
                            if (m_BuffSpawnTimer >= 60.0f * Clamp(m_BuffSpawnOffset, 0.1, m_BuffSpawnOffset))
                            {
                                if (!IsSoundPlaying(m_FlySpawnSound)) { PlaySound(m_FlySpawnSound); }
                                float RandomX = GetRandomValue(40, WINDOW_WIDTH - 40);
                                Fly* temp = new Fly(ObjectType::BUFF, Vector2{RandomX, -40}, Vector2{40, 40}, 0, m_FireFly, m_Wave);
                                m_GameObjects.push_back(temp);
                                m_BuffSpawnTimer = 0.0f;
                            }
                        }
                        else if (m_WaveUpdateTimer >= WAVE_TIME && m_GameObjects.empty())
                        {
                            // Reset Wave Update Variables
                            m_WaveUpdateTimer = 0.0f;
                            m_TotalFlyKilled += m_FlyCount;
                            m_FlyCount = 0;
                            m_Activate = false;
                        }
                    }

                    // Wave Transition Code
                    if (m_Activate == false)
                    {
                        m_WaveTransitionTimer += 60.0f * DeltaTime;
                        if (m_WaveTransitionTimer >= m_WaveTransitionOffset)
                        {
                            ++m_Wave;
                            m_EnemySpawnOffset -= 0.1;
                            m_WaveTransitionTimer = 0.0f;
                            m_Activate = true;
                        }
                    }
                }
            }
        }

        // DRAW
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(m_Background, 0, 0, WHITE);

        if (m_LevelStart == true)
        {
            m_Frog->Draw();

            if (m_PauseGame == true) { DrawTextEx(m_TextFont, TextFormat("Paused"), Vector2{WINDOW_WIDTH - 190, 5}, 30, 1, WHITE); }

            if (m_PauseGame == true || m_Health <= 0)
            {
                m_ExitButton->Draw();
                m_RestartButton->Draw();
            }

            if (m_Health > 0)
            {
                if (!IsSoundPlaying(m_GameSoundTrackMusic))
                {
                    PlaySound(m_GameSoundTrackMusic);
                }

                DrawTextEx(m_TextFont, TextFormat("Score:%d", m_Score), Vector2{5, 5}, 30, 1, WHITE);
                DrawTextEx(m_TextFont, TextFormat("Wave:%d", m_Wave), Vector2{280, 5}, 30, 1, WHITE);

                if (!m_GameObjects.empty()) { for (auto& v : m_GameObjects) { v->Draw(); } }
                for (int i = 0; i < m_Health; ++i) { DrawTextureV(m_FrogSpawn[i].texture, m_FrogSpawn[i].position, WHITE); }
            }
            else
            {
                if (!IsSoundPlaying(m_GameOverSound) && m_HasPlayedGameover == false)
                {
                    PlaySound(m_GameOverSound);
                    m_HasPlayedGameover = true;
                }

                PauseSound(m_GameSoundTrackMusic);
                DrawTextEx(m_TextFont, TextFormat("Total Score:%d", m_TotalFlyKilled), Vector2{WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 120}, 30, 1, WHITE);
                DrawTextEx(m_TextFont, TextFormat("Wave Reached:%d", m_Wave), Vector2{WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 80}, 30, 1, WHITE);
            }
        }
        else 
        {
            if (!IsSoundPlaying(m_MainMenuSoundTrack)) { PlaySound(m_MainMenuSoundTrack); }

            static float SinWave;
            SinWave += 0.2;
            if (SinWave == 100) { SinWave = 0; }
            DrawTexture(m_Title, 100, 150 + (sinf(SinWave) * 10), WHITE);
        }
        
        EndDrawing();
    }

    m_FrogSpawn.clear();
    
    delete m_Frog;
    m_Frog = nullptr;

    delete m_ExitButton;
    m_ExitButton = nullptr;

    delete m_RestartButton;
    m_RestartButton = nullptr;

    std::vector<GameObject*>::iterator GameObjectItr;
    for (GameObjectItr = m_GameObjects.begin(); GameObjectItr != m_GameObjects.end(); ++GameObjectItr) { delete *GameObjectItr; *GameObjectItr = nullptr; }


    // Texture Unloading
    UnloadTexture(m_Background);
    UnloadTexture(m_Title);
    UnloadTexture(m_NormalFly);
    UnloadTexture(m_IceFly);
    UnloadTexture(m_FireFly);
    UnloadTexture(m_FrogEgg);


    // Sound Unloading
    UnloadSound(m_ClickSound);
    UnloadSound(m_FireFlySound);
    UnloadSound(m_FlyDeathSound);
    UnloadSound(m_FlySpawnSound);

    UnloadSound(m_GameOverSound);
    UnloadSound(m_IceFlySound);


    // Font Unloading
    UnloadFont(m_TextFont);


    CloseAudioDevice();
    CloseWindow();

    return 0;
}