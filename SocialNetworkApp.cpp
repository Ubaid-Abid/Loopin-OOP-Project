
#include "SocialNetworkApp.h"
#include <raylib.h>
#include<cstring>
#include"UI.h"
void SocialNetworkApp::point_to_owner(page* p) {
    owner = p;
}

void SocialNetworkApp::loadfromfile() {
    //loading users
    string name, id;
    user::user_record = new user * [1];
    ifstream in("User.txt");
    while (getline(in, name) && getline(in, id)) {

        if (user::total_users == 0)
        {
            user::user_record[0] = new user;
            user::user_record[user::total_users]->set_person(name, stoi(id));
            user::total_users++;
        }
        else {
            user::total_users++;
            user** temp = new user * [user::total_users];
            for (int i = 0; i < user::total_users - 1; i++)
                temp[i] = user::user_record[i];
            delete[] user::user_record;
            temp[user::total_users - 1] = new user;
            temp[user::total_users - 1]->set_person(name, stoi(id));
            user::user_record = temp;

        }
    }
    in.close();

    //loading pages
    ifstream input("Page.txt");
    
    string title, fullId;
    while (std::getline(input, title) && std::getline(input, fullId)) {
        auto dashPos = fullId.find('-');
        if (dashPos == string::npos) continue;

        int ownerId = std::stoi(fullId.substr(0, dashPos));
        for (int i = 0; i < user::total_users; ++i) {
            if (user::user_record[i]->get_id() == ownerId) {
                page* P = new page;
                P->set_page(fullId, title, user::user_record[i]);
                user::user_record[i]->appendOwnedPage(P);
                break;
            }
        }
    }
    input.close();
}

void SocialNetworkApp::set_date() {
    const int screenW = 1900, screenH = 930;
    InitWindow(screenW, screenH, "(:      LOOPIN        :)");
    SetTargetFPS(30);

    std::string inputs[3] = { "", "", "" };
    int maxLen[3] = { 2, 2, 4 };
    int activeField = 0;
    bool submitted = false;
    bool errorFields[3] = { false, false, false };
    bool showErrorMsg = false;
    const char* errMsg = "Please enter: 1<=day<=30, 1<=mon<=12, year>=2000";

   
    int boxW = 80, boxH = 40, gap = 20;
    int totalW = 3 * boxW + 2 * gap;
    int startX = (screenW - totalW) / 2;
    int startY = (screenH - boxH) / 2;

    while (!WindowShouldClose() && !submitted) {
       
        if (IsKeyPressed(KEY_BACKSPACE) && !inputs[activeField].empty()) {
            inputs[activeField].pop_back();
        }
        if (IsKeyPressed(KEY_TAB)) {
            activeField = (activeField + 1) % 3;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            
            int d = inputs[0].empty() ? 0 : std::stoi(inputs[0]);
            int m = inputs[1].empty() ? 0 : std::stoi(inputs[1]);
            int y = inputs[2].empty() ? 0 : std::stoi(inputs[2]);
            errorFields[0] = (d < 1 || d > 30);
            errorFields[1] = (m < 1 || m > 12);
            errorFields[2] = (y < 2000);
            showErrorMsg = errorFields[0] || errorFields[1] || errorFields[2];
            if (!showErrorMsg) {
                date.set_Date(d, m, y);
                submitted = true;
            }
        }
       
        int chr;
        while ((chr = GetCharPressed()) != 0) {
            if (chr >= '0' && chr <= '9'
                && (int)inputs[activeField].size() < maxLen[activeField]) {
                inputs[activeField].push_back((char)chr);
            }
        }

       
        BeginDrawing();
        ClearBackground(RAYWHITE);

       
        const char* prompt = "Enter date:";
        int pw = MeasureText(prompt, 24);
        DrawText(prompt, (screenW - pw) / 2, startY - 60, 24, DARKGRAY);

        
        const char* labels[3] = { "Day", "Month", "Year" };
        for (int i = 0; i < 3; ++i) {
            int x = startX + i * (boxW + gap);

          
            int lw = MeasureText(labels[i], 20);
            DrawText(labels[i], x + (boxW - lw) / 2, startY - 30, 20, BLACK);

           
            Color edge = errorFields[i]
                ? RED
                : (activeField == i ? BLUE : GRAY);
            DrawRectangleLines(x, startY, boxW, boxH, edge);

            
            DrawText(inputs[i].c_str(),
                x + 5,
                startY + (boxH / 2 - 10),
                20,
                BLACK);
        }

        
        if (showErrorMsg) {
            int ew = MeasureText(errMsg, 20);
            DrawText(errMsg,
                (screenW - ew) / 2,
                startY + boxH + 20,
                20,
                RED);
        }

        
        const char* instr = "TAB to switch  ENTER to submit  BACKSPACE to delete";
        int iw = MeasureText(instr, 18);
        DrawText(instr,
            (screenW - iw) / 2,
            screenH - 40,
            18,
            DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void SocialNetworkApp::login() {
const int screenWidth = 1900;
const int screenHeight = 930;
InitWindow(screenWidth, screenHeight, "LOOPIN");
SetTargetFPS(60);

// Main menu buttons
Rectangle loginBtn, createBtn;
const int buttonWidth = 300, buttonHeight = 60, buttonSpacing = 30;
loginBtn = { (screenWidth - buttonWidth) / 2.0f,
            (screenHeight - buttonHeight * 2 - buttonSpacing) / 2.0f,
            buttonWidth, buttonHeight };
createBtn = { loginBtn.x,
             loginBtn.y + buttonHeight + buttonSpacing,
             buttonWidth, buttonHeight };


Rectangle inputBox;
const int inputWidth = 400, inputHeight = 50;
  inputBox = { (screenWidth - inputWidth) / 2.0f,
            (screenHeight - inputHeight) / 2.0f + 50,
            inputWidth, inputHeight };

bool showLogin = false, showCreate = false;
bool inputActive = false, success = false;
std::string inputText, errorMessage;
double errorTime = 0;

while (!WindowShouldClose() && !success) {
    Vector2 mousePos = GetMousePosition();

   
    if (!showLogin && !showCreate) {
        if (CheckCollisionPointRec(mousePos, loginBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showLogin = true; inputText.clear();
        }
        else if (CheckCollisionPointRec(mousePos, createBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showCreate = true; inputText.clear();
        }
    }
   
    else {
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            inputActive = CheckCollisionPointRec(mousePos, inputBox);

     
        if (inputActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if (showLogin) {
                    if (key >= '0' && key <= '9' && inputText.size() < 4)
                        inputText.push_back((char)key);
                }
                else {
                    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == ' ')
                        inputText.push_back((char)key);
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty())
                inputText.pop_back();
        }

        
        if (IsKeyPressed(KEY_ENTER)) {
         
            if (showLogin) {
                if (inputText.size() == 4) {
                    for (int i = 0; i < user::total_users; ++i) {
                        if (std::stoi(inputText) == user::user_record[i]->get_id()) {
                            person = user::user_record[i];
                           
                            success = true;
                            break;
                        }
                    }
                    if (!success) {
                        errorMessage = "Invalid ID!";
                        errorTime = GetTime();
                    }
                }
            }
           
            else {
                if (!inputText.empty()) {
                    bool exists = false;
                    for (int i = 0; i < user::total_users; ++i) {
                        if (user::user_record[i]->get_name() == inputText) {
                            exists = true; break;
                        }
                    }
                    if (!exists) {
                     
                        user::total_users++;
                        user** temp = new user * [user::total_users];
                        for (int i = 0; i < user::total_users - 1; ++i)
                            temp[i] = user::user_record[i];
                        temp[user::total_users - 1] = new user;
                        temp[user::total_users - 1]->set_person(inputText, 1000 + user::total_users);
                        delete[] user::user_record;
                        user::user_record = temp;

                        
                        ofstream out("User.txt", std::ios::app);
                        out << inputText << "\n" << (1000 + user::total_users) << "\n";
                        out.close();

                       person = temp[user::total_users - 1];
                       
                        success = true;
                    }
                    else {
                        errorMessage = "Username exists!";
                        errorTime = GetTime();
                    }
                }
            }
        }
    }

  
    BeginDrawing();
    ClearBackground(BLACK);

    if (!showLogin && !showCreate) {
        DrawRectangleRec(loginBtn, CheckCollisionPointRec(mousePos, loginBtn) ? GRAY : RAYWHITE);
        DrawText("Login to User", (int)loginBtn.x + 20, (int)loginBtn.y + 15, 24, BLACK);
        DrawRectangleRec(createBtn, CheckCollisionPointRec(mousePos, createBtn) ? GRAY : RAYWHITE);
        DrawText("Create Account", (int)createBtn.x + 20, (int)createBtn.y + 15, 24, BLACK);
    }
    else {
        const char* prompt = showLogin ? "Enter ID (4 digits):" : "Enter Username:";
        int pw = MeasureText(prompt, 32);
        DrawText(prompt, (screenWidth - pw) / 2, inputBox.y - 70, 32, GREEN);

        DrawRectangleRec(inputBox, inputActive ? LIGHTGRAY : WHITE);
        DrawRectangleLinesEx(inputBox, 2, inputActive ? BLUE : DARKGRAY);
        if (!inputText.empty()) {
            int tw = MeasureText(inputText.c_str(), 30);
            DrawText(inputText.c_str(), inputBox.x + (inputWidth - tw) / 2,
                inputBox.y + (inputHeight - 30) / 2, 30, BLACK);
        }
        if (errorTime > 0 && GetTime() - errorTime < 3.0) {
            int ew = MeasureText(errorMessage.c_str(), 24);
            DrawText(errorMessage.c_str(), (screenWidth - ew) / 2,
                inputBox.y + inputHeight + 20, 24, RED);
        }
    }

    EndDrawing();

    if (success) {
        CloseWindow();
        return;
    }
}
CloseWindow();
}
void SocialNetworkApp::welcome() {

    int W = 1900, H = 930;
    InitWindow(W, H, "(: LOOPIN :)");
    Texture2D bg = LoadTexture("C:\\Users\\ubaid_\\Downloads\\Background_image.png");

    double start = GetTime();
    SetTargetFPS(60);
   
    bool t = true;
    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            if (GetTime() - start > 2.2)
                t = false;
            if (t) {

                DrawTexture(bg, 300, 0, WHITE);
            }
            else if (!t)
            {
                if (GetTime() - start < 3.5) {
                    ClearBackground(BLACK);
                    DrawText("Loading Please wait!", 500, 450, 60, WHITE);
                }
                else
                    break;
            }
        }
        EndDrawing();
    }
    UnloadTexture(bg);
    CloseWindow();
}
void SocialNetworkApp::general( ) {
    
    UIManager ui(person,this->get_date());
    while (!WindowShouldClose()) {
        ui.ProcessInput();
        ui.Draw();
    }
}
bool SocialNetworkApp::Run() {
   
    welcome();
    set_date();
    loadfromfile();
    login();
    general();
    return true;
}
