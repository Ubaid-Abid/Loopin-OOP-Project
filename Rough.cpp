//#include "raylib.h"
//#include <stdio.h>
//
//int main() {
//    // 1) Initialize your window
//    int screenWidth = 1000;
//    int screenHeight = 850;
//    InitWindow(screenWidth, screenHeight, "(: LOOPIN :)");
//
//    // 2) Load your background image
//    Texture2D bg = LoadTexture("C:\\Users\\ubaid_\\Downloads\\Background_image.png");
//    if (bg.id == 0) {
//        printf("ERROR: Could not load background image!\n");
//        CloseWindow();
//        return 1;
//    }
//
//    // 3) Record the start time (in seconds)
//    double startTime = GetTime();
//
//    // 4) Set your target FPS
//    SetTargetFPS(60);
//
//    // 5) Main loop
//    while (!WindowShouldClose()) {
//        double elapsed = GetTime() - startTime;
//
//        BeginDrawing();
//        if (elapsed < 3.0) {
//            // FIRST 5 SECONDS: draw your background
//            ClearBackground(BLACK);
//            DrawTexture(bg, 0, 0, WHITE);
//        }
//        else {
//            // AFTER 5 SECONDS: plain black screen
//            ClearBackground(BLACK);
//            // (nothing else)
//        }
//        EndDrawing();
//    }
//
//    // 6) Cleanup
//    UnloadTexture(bg);
//    CloseWindow();
//    return 0;
//}
//void SocialNetworkApp::general() {
//    const int screenWidth = 1900;
//    const int screenHeight = 930;
//    InitWindow(screenWidth, screenHeight, "Social Network Interface");
//    SetTargetFPS(60);
//    
//    // Button configuration
//    const Vector2 buttonSize = { 400, 80 };
//    const int padding = 20;
//    const int cols = 3;
//    const int totalButtons = 18;
//
//    // Dynamic array for button labels
//    const char** buttonLabels = new const char* [totalButtons] {
//        "add_friend", "view friend", "makepost",
//            "view_post", "like_post", "viewpeoplelikepost",
//            "sharepost", "makecomment", "switch user",
//            "switch date", "switch to page", "like page",
//            "view home", "view timeline", "viewuser profile",
//            "share memory", "view page", "view memory"
//        };
//
//    // Dynamic array for button rectangles
//    Rectangle* buttons = new Rectangle[totalButtons];
//
//    // Calculate grid positions
//    const float startX = (screenWidth - (cols * buttonSize.x + (cols - 1) * padding)) / 2;
//    float x = startX;
//    float y = 100;
//
//    for (int i = 0; i < totalButtons; ++i) {
//        buttons[i] = { x, y, buttonSize.x, buttonSize.y };
//        x += buttonSize.x + padding;
//
//        if ((i + 1) % cols == 0) {
//            y += buttonSize.y + padding;
//            x = startX;
//        }
//    }
//
//    // Interaction variables
//    char* clickedAction = nullptr;
//    const Rectangle leftPanel = { 50, 100, 400, screenHeight - 150 };
//
//    while (!WindowShouldClose()) {
//        Vector2 mousePoint = GetMousePosition();
//
//        // Update interactions
//        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//            delete[] clickedAction; // Clear previous click
//            clickedAction = nullptr;
//            if (CheckCollisionPointRec(mousePoint, buttons[0])) {
//                person->add_friend();
//            }
//           
//        }
//
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        // Draw user info
//        DrawText(person->get_name().c_str(), 20, 20, 30, DARKBLUE);
//        DrawText(TextFormat("ID: %d", person->get_id()),
//            screenWidth - MeasureText(TextFormat("ID: %d", person->get_id()), 30) - 20,
//            20, 30, DARKBLUE);
//
//        // Draw buttons
//        for (int i = 0; i < totalButtons; ++i) {
//            Color btnColor = CheckCollisionPointRec(mousePoint, buttons[i]) ?
//                Color{ 100, 200, 255, 255 } : LIGHTGRAY;
//
//            DrawRectangleRec(buttons[i], btnColor);
//            DrawRectangleLinesEx(buttons[i], 2, DARKGRAY);
//
//            // Center text in buttons
//            int textWidth = MeasureText(buttonLabels[i], 20);
//            DrawText(buttonLabels[i],
//                buttons[i].x + (buttonSize.x - textWidth) / 2,
//                buttons[i].y + (buttonSize.y - 20) / 2,
//                20, DARKGRAY);
//        }
//
//        // Draw left panel
//        DrawRectangleRec(leftPanel, LIGHTGRAY);
//        DrawRectangleLinesEx(leftPanel, 2, DARKGRAY);
//        if (clickedAction) {
//            DrawText("{ }", leftPanel.x + 20, leftPanel.y + 20, 40, DARKGRAY);
//            DrawText(TextFormat("Action: %s", clickedAction),
//                leftPanel.x + 20, leftPanel.y + 70, 20, DARKGRAY);
//        }
//
//        EndDrawing();
//    }
//
//    // Cleanup dynamic memory
//    delete[] buttonLabels;
//    delete[] buttons;
//    delete[] clickedAction;
//
//    CloseWindow();
//}
//void SocialNetworkApp::general() {
//    const int screenWidth = 1900;
//    const int screenHeight = 930;
//    InitWindow(screenWidth, screenHeight, "Social Network Interface");
//    SetTargetFPS(60);
//    bool allow = true;
//    // Button configuration
//    const Vector2 buttonSize = { 400, 80 };
//    const int padding = 20;
//    const int cols = 3;
//    const int totalButtons = 18;
//
//    // Dynamic array for button labels
//    const char** buttonLabels = new const char* [totalButtons] {
//        "add_friend", "view friend", "makepost",
//            "view_post", "like_post", "viewpeoplelikepost",
//            "sharepost", "makecomment", "switch user",
//            "switch date", "switch to page", "like page",
//            "view home", "view timeline", "viewuser profile",
//            "share memory", "view page", "view memory"
//        };
//
//    // Dynamic array for button rectangles
//    Rectangle* buttons = new Rectangle[totalButtons];
//
//    // Calculate grid positions
//    const float startX = (screenWidth - (cols * buttonSize.x + (cols - 1) * padding)) / 2;
//    float x = startX;
//    float y = 100;
//
//    for (int i = 0; i < totalButtons; ++i) {
//        buttons[i] = { x, y, buttonSize.x, buttonSize.y };
//        x += buttonSize.x + padding;
//
//        if ((i + 1) % cols == 0) {
//            y += buttonSize.y + padding;
//            x = startX;
//        }
//    }
//
//    // Add Friend state variables
//    bool isAddingFriend = false;
//    char idInput[20] = { 0 };
//    int inputPos = 0;
//    const char* message = nullptr;
//    Color messageColor = WHITE;
//    double messageTime = 0;
//    bool successState = false;
//
//    while (!WindowShouldClose()) {
//        Vector2 mousePoint = GetMousePosition();
//
//        // Handle general screen interactions
//        if (!isAddingFriend && allow) {
//            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//                // Check all buttons
//                for (int i = 0; i < totalButtons; ++i) {
//                    if (CheckCollisionPointRec(mousePoint, buttons[i])) {
//                        // Handle add_friend click
//                        if (i == 0) {
//                            isAddingFriend = true;
//                            memset(idInput, 0, sizeof(idInput));
//                            inputPos = 0;
//                            message = nullptr;
//                            successState = false;
//                        }
//                        // Handle other button clicks here...
//                    }
//                }
//            }
//        }
//        else { // Add Friend modal is active
//            // Handle numeric input
//            ClearBackground(BLACK);
//            allow = false;
//            int key = GetCharPressed();
//            while (key > 0 && inputPos < 19) {
//                if (key >= '0' && key <= '9') {
//                    idInput[inputPos++] = (char)key;
//                }
//                key = GetCharPressed();
//            }
//
//            if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0) {
//                idInput[--inputPos] = '\0';
//            }
//
//            if (IsKeyPressed(KEY_ENTER)) {
//                if (inputPos > 0) {
//                    int friendId = atoi(idInput);
//                    bool success = person->add_friend(friendId);
//
//                    if (success) {
//                        message = "Friend added successfully!";
//                        messageColor = GREEN;
//                        successState = true;
//                        allow = true;
//                    }
//                    else {
//                        message = (friendId == person->get_id())
//                            ? "Cannot add yourself!"
//                            : "Invalid ID or already friends!";
//                        messageColor = RED;
//                        successState = false;
//                    }
//                    messageTime = GetTime();
//                }
//            }
//
//            if (IsKeyPressed(KEY_ESCAPE)) {
//                isAddingFriend = false;
//                message = nullptr;
//            }
//        }
//
//        // Handle message timeout
//        if (message && GetTime() - messageTime > 1.0) {
//            if (successState) {
//                isAddingFriend = false;
//                message = nullptr;
//                successState = false;
//            }
//            else {
//                message = nullptr;
//            }
//        }
//
//        BeginDrawing();
//
//        if (isAddingFriend) {
//            // Dark overlay
//            DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 0, 0, 0, 200 });
//
//            // Draw input box
//            Rectangle inputBox = { screenWidth / 2 - 200, screenHeight / 2 - 30, 400, 60 };
//            DrawRectangleRec(inputBox, LIGHTGRAY);
//            DrawRectangleLinesEx(inputBox, 2, DARKGRAY);
//
//            // Draw text elements
//            DrawText("Enter Friend ID:", screenWidth / 2 - 120, screenHeight / 2 - 80, 30, WHITE);
//            DrawText(idInput, inputBox.x + 20, inputBox.y + 15, 30, DARKBLUE);
//
//            // Draw message if exists
//            if (message) {
//                int textWidth = MeasureText(message, 30);
//                DrawText(message, screenWidth / 2 - textWidth / 2, screenHeight / 2 + 50, 30, messageColor);
//            }
//        }
//
//        // Always draw general screen elements
//        ClearBackground(RAYWHITE);
//
//        // Draw user info
//        DrawText(person->get_name().c_str(), 20, 20, 30, DARKBLUE);
//        DrawText(TextFormat("ID: %d", person->get_id()),
//            screenWidth - MeasureText(TextFormat("ID: %d", person->get_id()), 30) - 20,
//            20, 30, DARKBLUE);
//
//        // Draw buttons
//        if (allow) {
//            for (int i = 0; i < totalButtons; ++i) {
//                Color btnColor = LIGHTGRAY;
//
//                if (!isAddingFriend) {
//                    btnColor = CheckCollisionPointRec(mousePoint, buttons[i])
//                        ? Color{ 100, 200, 255, 255 }
//                    : LIGHTGRAY;
//                }
//
//                DrawRectangleRec(buttons[i], btnColor);
//                DrawRectangleLinesEx(buttons[i], 2, DARKGRAY);
//
//                // Center text in buttons
//                int textWidth = MeasureText(buttonLabels[i], 20);
//                DrawText(buttonLabels[i],
//                    buttons[i].x + (buttonSize.x - textWidth) / 2,
//                    buttons[i].y + (buttonSize.y - 20) / 2,
//                    20, DARKGRAY);
//            }
//        }
//        EndDrawing();
//    }
//
//    // Cleanup dynamic memory
//    delete[] buttonLabels;
//    delete[] buttons;
//    CloseWindow();
//}



//void SocialNetworkApp::general() {
//    const int screenWidth = 1900;
//    const int screenHeight = 930;
//    InitWindow(screenWidth, screenHeight, "Social Network Interface");
//    SetTargetFPS(60);
//
//    // Button configuration
//    const Vector2 buttonSize = { 400, 80 };
//    const int padding = 20;
//    const int cols = 3;
//    const int totalButtons = 18;
//
//    // Dynamic array for button labels
//    const char** buttonLabels = new const char* [totalButtons] {
//        "add_friend", "view friend", "makepost",
//            "view_post", "like_post", "viewpeoplelikepost",
//            "sharepost", "makecomment", "switch user",
//            "switch date", "switch to page", "like page",
//            "view home", "view timeline", "viewuser profile",
//            "share memory", "view page", "view memory"
//        };
//
//    // Dynamic array for button rectangles
//    Rectangle* buttons = new Rectangle[totalButtons];
//
//    // Calculate grid positions
//    const float startX = (screenWidth - (cols * buttonSize.x + (cols - 1) * padding)) / 2;
//    float x = startX;
//    float y = 100;
//
//    for (int i = 0; i < totalButtons; ++i) {
//        buttons[i] = { x, y, buttonSize.x, buttonSize.y };
//        x += buttonSize.x + padding;
//
//        if ((i + 1) % cols == 0) {
//            y += buttonSize.y + padding;
//            x = startX;
//        }
//    }
//
//    // State variables
//    bool isAddingFriend = false;
//    bool isViewingFriend = false;
//    bool ismakingpost = false;
//    bool isviewpost = false;
//    char idInput[20] = { 0 };
//    int inputPos = 0;
//    const char* message = nullptr;
//    Color messageColor = WHITE;
//    double messageTime = 0;
//
//    while (!WindowShouldClose()) {
//        Vector2 mousePoint = GetMousePosition();
//
//        // Handle general screen interactions
//        if (!isAddingFriend && !isViewingFriend && !ismakingpost && isviewpost) {
//            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//                for (int i = 0; i < totalButtons; ++i) {
//                    if (CheckCollisionPointRec(mousePoint, buttons[i])) {
//                        if (i == 0) { // add_friend button
//                            isAddingFriend = true;
//                            memset(idInput, 0, sizeof(idInput));
//                            inputPos = 0;
//                            message = nullptr;
//                        }
//                        else if (i == 1) { // view friend button
//                            isViewingFriend = true;
//                            message = nullptr;
//                        }
//                        else if (i == 2)
//                        {
//                            ismakingpost = true;
//                            message = nullptr;
//                        }
//                        else if (i == 3) {
//                            isviewpost = true;
//                            message = nullptr;
//                        }
//                    }
//                }
//            }
//        }
//        else if (isAddingFriend)
//        { // Add Friend mode
//            // Handle input
//            int key = GetCharPressed();
//            while (key > 0 && inputPos < 19) {
//                if (key >= '0' && key <= '9') {
//                    idInput[inputPos++] = (char)key;
//                }
//                key = GetCharPressed();
//            }
//
//            if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0) {
//                idInput[--inputPos] = '\0';
//            }
//
//            if (IsKeyPressed(KEY_ENTER)) {
//                if (inputPos > 0) {
//                    int friendId = atoi(idInput);
//                    bool success = person->add_friend(friendId);
//
//                    if (success) {
//                        message = "Friend added successfully!";
//                        messageColor = GREEN;
//                    }
//                    else {
//                        message = (friendId == person->get_id())
//                            ? "Cannot add yourself!"
//                            : "Invalid ID or already friends!";
//                        messageColor = RED;
//                    }
//                    messageTime = GetTime();
//                }
//            }
//
//            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_DELETE)) {
//                isAddingFriend = false;
//                message = nullptr;
//            }
//        }
//        else if (isViewingFriend)
//        { // View Friends mode
//            if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE)) {
//                isViewingFriend = false;
//                message = nullptr;
//            }
//        }
//        else if (ismakingpost)
//        {
//            if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_ESCAPE)) {
//                ismakingpost = false;
//                message = nullptr;
//            }
//        }
//        else if (isviewpost)
//            if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_ESCAPE))
//            {
//                ismakingpost = false;
//                message = nullptr;
//            }
//        // Handle message timeout
//        if (message && GetTime() - messageTime > 1.0) {
//            if (messageColor.r == GREEN.r) {
//                isAddingFriend = false;
//            }
//            message = nullptr;
//        }
//
//        BeginDrawing();
//
//        if (isAddingFriend)
//        {
//            // Add friend screen
//            ClearBackground(BLACK);
//
//            // Draw input box
//            Rectangle inputBox = { screenWidth / 2 - 200, screenHeight / 2 - 30, 400, 60 };
//            DrawRectangleRec(inputBox, LIGHTGRAY);
//            DrawRectangleLinesEx(inputBox, 2, DARKGRAY);
//
//            // Draw text
//            DrawText("Enter Friend ID:", screenWidth / 2 - 120, screenHeight / 2 - 80, 30, WHITE);
//            DrawText(idInput, inputBox.x + 20, inputBox.y + 15, 30, DARKBLUE);
//
//            // Draw message
//            if (message) {
//                int textWidth = MeasureText(message, 30);
//                DrawText(message, screenWidth / 2 - textWidth / 2, screenHeight / 2 + 50, 30, messageColor);
//            }
//        }
//        else if (isViewingFriend)
//        {
//            // View Friends screen
//            ClearBackground(BLACK);
//
//            int count = person->get_friendcount();
//            if (count > 0) {
//                // List each friend
//                float startY = 100;
//                for (int i = 0; i < count; ++i) {
//                    user* f = person->get_specificfriend(i);
//                    string line1 = TextFormat("%d. Name: %s", i + 1, f->get_name().c_str());
//                    std::string line2 = TextFormat("   ID: %d", f->get_id());
//                    DrawText(line1.c_str(), 100, startY, 25, WHITE);
//                    DrawText(line2.c_str(), 100, startY + 30, 25, WHITE);
//                    startY += 80;
//                }
//                DrawText("Press BACKSPACE to return", screenWidth / 2 - 150, screenHeight - 60, 20, GRAY);
//            }
//            else {
//                // No friends
//                const char* noMsg = "No friends yet";
//                int tw = MeasureText(noMsg, 40);
//                DrawText(noMsg, screenWidth / 2 - tw / 2, screenHeight / 2 - 20, 40, WHITE);
//                DrawText("Press BACKSPACE to return", screenWidth / 2 - 150, screenHeight / 2 + 40, 20, GRAY);
//            }
//        }
//
//        else if (ismakingpost) {
//
//            static int postStage = 0;        // 0: pick category, 1: pick option, 2: enter text
//            static int chosenCat = 0;        // 0–3 which top-level category
//            static char descBuf[256] = { 0 };  // description buffer
//            static int descPos = 0;
//            // labels:
//            const char* cats[4] = { "Feeling","Thinking about","Making","Celebrating" };
//            const char* opts[4][3] = {
//              {"Happy","Sad","Excited"},
//              {"Life","Future","Meaning of life"},
//              {"Money","Art","Memories"},
//              {"Birthday","Halloween","Success"}
//            };
//
//            ClearBackground(BLACK);
//            DrawText("Press BACKSPACE to cancel", 20, screenHeight - 40, 20, GRAY);
//
//            if (postStage == 0) {
//                // draw 4 category buttons vertically
//                for (int i = 0; i < 4; ++i) {
//                    Rectangle r = { 100, 150 + i * 100, 400, 60 };
//                    Color col = CheckCollisionPointRec(mousePoint, r) ? SKYBLUE : LIGHTGRAY;
//                    DrawRectangleRec(r, col);
//                    DrawText(cats[i], r.x + 20, r.y + 15, 30, DARKBLUE);
//                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, r)) {
//                        postStage = 1;
//                        chosenCat = i;
//                    }
//                }
//            }
//            else if (postStage == 1) {
//                // draw 3 option buttons horizontally
//                for (int j = 0; j < 3; ++j) {
//                    Rectangle r = { 100 + j * 450, 200, 400, 60 };
//                    Color col = CheckCollisionPointRec(mousePoint, r) ? SKYBLUE : LIGHTGRAY;
//                    DrawRectangleRec(r, col);
//                    DrawText(opts[chosenCat][j], r.x + 20, r.y + 15, 30, DARKBLUE);
//                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, r)) {
//                        postStage = 2;
//                        // store opts[chosenCat][j] if you need it later
//                    }
//                }
//            }
//            else if (postStage == 2) {
//                // text input box
//                Rectangle box = { 100,200,800,60 };
//                DrawRectangleRec(box, LIGHTGRAY);
//                DrawRectangleLinesEx(box, 2, DARKGRAY);
//                DrawText("Enter description & press ENTER:", 100, 150, 25, WHITE);
//                DrawText(descBuf, box.x + 10, box.y + 10, 25, DARKBLUE);
//
//                // capture text
//                int k = GetCharPressed();
//                while (k > 0 && descPos < sizeof(descBuf) - 1) {
//                    if (k >= 32 && k < 127) descBuf[descPos++] = (char)k;
//                    k = GetCharPressed();
//                }
//                if (IsKeyPressed(KEY_BACKSPACE) && descPos > 0) {
//                    descBuf[--descPos] = '\0';
//                }
//                if (IsKeyPressed(KEY_ENTER) && descPos > 0) {
//                    // commit new post:
//                    person->create_post_with_info(cats[chosenCat], descBuf, date);
//                    // reset
//                    postStage = 0;
//                    descPos = 0;
//                    memset(descBuf, 0, sizeof(descBuf));
//                    ismakingpost = false;
//                }
//            }
//
//            // cancel back to main
//            if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE)) {
//                ismakingpost = false;
//                // also reset postStage & buffer if mid-flow:
//                postStage = 0;
//                descPos = 0;
//                memset(descBuf, 0, sizeof(descBuf));
//            }
//        }
//        else if (isviewpost) {
//
//        }
//
//
//
//        else {
//            // Normal general screen
//            ClearBackground(RAYWHITE);
//
//            // Draw user info
//            DrawText(person->get_name().c_str(), 20, 20, 30, DARKBLUE);
//            DrawText(TextFormat("ID: %d", person->get_id()),
//                screenWidth - MeasureText(TextFormat("ID: %d", person->get_id()), 30) - 20,
//                20, 30, DARKBLUE);
//
//            // Draw buttons
//            for (int i = 0; i < totalButtons; ++i) {
//                Color btnColor = CheckCollisionPointRec(mousePoint, buttons[i])
//                    ? Color{ 100, 200, 255, 255 }
//                : LIGHTGRAY;
//
//                DrawRectangleRec(buttons[i], btnColor);
//                DrawRectangleLinesEx(buttons[i], 2, DARKGRAY);
//
//                int textWidth = MeasureText(buttonLabels[i], 20);
//                DrawText(buttonLabels[i],
//                    buttons[i].x + (buttonSize.x - textWidth) / 2,
//                    buttons[i].y + (buttonSize.y - 20) / 2,
//                    20, DARKGRAY);
//            }
//        }
//
//        EndDrawing();
//    }
//
//    // Cleanup
//    delete[] buttonLabels;
//    delete[] buttons;
//    CloseWindow();
//}
