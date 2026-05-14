#include "User.h"
#include "post.h"
#include <raylib.h>
//#include"SocialNetworkApp.h"
class UIManager 
{
public:
    enum class ScreenState { MAIN, ADD_FRIEND, VIEW_FRIEND, MAKE_POST, VIEW_POST, LIKE_POST, VIEW_PEOPLE_LIKE_POST, SHARE_POST, MAKE_COMMENT,SWITCH_USER
    , SWITCH_DATE,   VIEW_USER_PROFILE,
    };
    int viewPostStage;
    UIManager(user* u, const Date& date)
        : person(u)
        , viewPostStage(0)
         , viewLikeStage(0)
        , viewPeopleStage(0)          // ? init
        , currentScreen(ScreenState::MAIN)
        , inMakePost(false)
        , foundIndex(-1)
        , inputPos(0)
        , message(nullptr)
        , messageColor(WHITE)
        , messageTime(0)
        , currentDate(date)
        , viewShareStage(0)
        , viewCommentStage(0)
        ,viewPageStage(0),pageIsLogin(false), pageInputPos(0), createIdPos(0), createTitlePos(0),viewSwitchStage(0)
        {
        InitButtons();
    }
public:
    ~UIManager() {
        delete[] buttons;
    }

    void InitButtons()
    {
        const Vector2 btnSize = { 400,80 };
        const int pad = 20, cols = 3;
        const int total = 11;
        screenWidth = 1900; screenHeight = 930;
        buttons = new Rectangle[total];
        float startX = (screenWidth - (cols * btnSize.x + (cols - 1) * pad)) / 2;
        float x = startX, y = 100;
        for (int i = 0; i < total; i++) {
            buttons[i] = { x, y, btnSize.x, btnSize.y };
            x += btnSize.x + pad;
            if ((i + 1) % cols == 0) { y += btnSize.y + pad; x = startX; }
        }
    }

    void ProcessInput() {
        Vector2 mouse = GetMousePosition();
        if ( IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_DELETE)) {
            ResetToMain();
        }
        if (currentScreen == ScreenState::MAIN && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 11; i++) {
                if (CheckCollisionPointRec(mouse, buttons[i])) {
                    SwitchScreen(i);
                    break;
                }
            }
        }
        // per-screen input
        switch (currentScreen) {
        case ScreenState::ADD_FRIEND: HandleAddFriendInput(); break;
        case ScreenState::VIEW_POST: HandleViewPostInput(); break;
        case ScreenState::LIKE_POST : HandleLikePostInput(); break;
        case ScreenState::VIEW_PEOPLE_LIKE_POST: HandleViewPeopleInput(); break;
        case ScreenState::SHARE_POST: HandleSharePostInput(); break;
        case ScreenState::MAKE_COMMENT:         HandleMakeCommentInput();   break;
        case ScreenState::SWITCH_USER:   HandleSwitchUserInput();   break;
        case ScreenState::SWITCH_DATE:
            HandleSwitchDateInput();
            break;
        default: break;
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 mouse = GetMousePosition();
        switch (currentScreen) {
        case ScreenState::MAIN: DrawMain(mouse); break;
        case ScreenState::ADD_FRIEND: DrawAddFriend(); break;
        case ScreenState::VIEW_FRIEND: DrawViewFriend(); break;
        case ScreenState::MAKE_POST: DrawMakePost(); break;
        case ScreenState::VIEW_POST: DrawViewPost(); break;
        case ScreenState::LIKE_POST: DrawLikePost(); break;
        case ScreenState::VIEW_PEOPLE_LIKE_POST: DrawViewPeople();break;
        case ScreenState::SHARE_POST:           DrawSharePost(); break;
        case ScreenState::MAKE_COMMENT:         DrawMakeComment();          break;
        case ScreenState::SWITCH_DATE: DrawSwitchDate(); break;
        case ScreenState::VIEW_USER_PROFILE: DrawViewUserProfile();  break;
        case ScreenState::SWITCH_USER: DrawSwitchUser();break;
        }
       
        EndDrawing();
    }

private:
   
    const char* buttonLabels[11] = {
        "add_friend","view friend","makepost",
        "view_post","like_post","viewpeoplelikepost",
        "sharepost","makecomment","switch user",
        "switch date",
       "viewuser profile" };
    user* person;
    ScreenState currentScreen;
    bool inMakePost;
    int screenWidth, screenHeight;
    Rectangle* buttons;
    int inputPos;
    char idInput[32] = { 0 };
    const char* message;
    Color messageColor;
    double messageTime;
    int foundIndex;
    Date currentDate;
    int viewLikeStage;
    int viewPeopleStage;
    int viewShareStage;
    int viewCommentStage;
    int   viewSwitchStage;    // 0 = choose Login/Create, 1 = enter text
    bool  switchIsLogin;      // true = login flow, false = create?account
    char  switchInput[32];    // text buffer for ID or username
    int   switchInputPos;
    char dateInputs[3][5];       // buffers for day, month, year
    int dateInputPos[3];         // current lengths
    int activeDateField;         // 0=day,1=month,2=year
    bool showDateError;
    int found_user;
    int viewPageStage; // 0: choose login/create, 1: enter inputs
    bool pageIsLogin;
    char pageInput[32];      // for existing page id
    int pageInputPos;
    char createId[32];
    int createIdPos;
    char createTitle[64];
    int createTitlePos;
    int pageMenuStage = 0;               // 0 = read ID, 1 = read comment/text
    static const int MAX_COMMENT = 256;
    char commentBuf[MAX_COMMENT];
    int  commentPos = 0;

    page* currentPage = nullptr;
    int      pageMenuSelection;
    int user_index;
        // track which sub?step we’re on in the SWITCH_PAGE screen

    void ResetToMain() {
        currentScreen = ScreenState::MAIN;
        inMakePost = false;
        viewPostStage = 0;
        message = nullptr;
        inputPos = 0;
        memset(idInput, 0, sizeof(idInput));
        foundIndex = -1;
        viewLikeStage = 0;
        viewCommentStage = 0;
        viewShareStage = 0;
        viewPeopleStage = 0;
        viewSwitchStage = 0;
        currentPage = nullptr;
        viewPageStage = 0;
        currentScreen = ScreenState::MAIN;                   
        currentPage = nullptr;                            
        viewPageStage = 0;                                   
             
        pageInputPos = 0;                                
        pageInput[0] = '\0';                                
        createIdPos = 0;                                  
        createTitlePos = 0;                                   
        createId[0] = '\0';                                
        createTitle[0] = '\0';                                
        message = nullptr;                             
        messageTime = 0;
        messageColor = WHITE;
    }

    void SwitchScreen(int idx) {
        message = nullptr;
        user* newUser = nullptr;
        inputPos = 0; memset(idInput, 0, sizeof(idInput));
        foundIndex = -1;
        switch (idx)
        {
        case 0: currentScreen = ScreenState::ADD_FRIEND; break;
        case 1: currentScreen = ScreenState::VIEW_FRIEND; break;
        case 2: currentScreen = ScreenState::MAKE_POST; break;
        case 3: currentScreen = ScreenState::VIEW_POST; break;
        case 4:
            currentScreen = ScreenState::LIKE_POST;
            break;
        case 5:
            currentScreen = ScreenState::VIEW_PEOPLE_LIKE_POST;
            inputPos = 0; memset(idInput, 0, sizeof(idInput)); message = nullptr;
            break;
        case 6:
            currentScreen = ScreenState::SHARE_POST;
            inputPos = 0; memset(idInput, 0, sizeof(idInput)); message = nullptr;
            break;
        case 7:
            currentScreen = ScreenState::MAKE_COMMENT;
            inputPos = 0; memset(idInput, 0, sizeof(idInput));
            commentBuf[0] = '\0'; commentPos = 0;
            message = nullptr;
            break;

        case 8: { 
            currentScreen = ScreenState::SWITCH_USER;
            viewSwitchStage = 0;
            switchInputPos = 0;
            memset(switchInput, 0, sizeof(switchInput));
            break;
        }
        case 9: 
            currentScreen = ScreenState::SWITCH_DATE;
            // reset date input fields
            for (int i = 0; i < 3; ++i) {
                dateInputPos[i] = 0;
                dateInputs[i][0] = '\0';
            }
            activeDateField = 0;
            showDateError = false;
            break;
       
        case 10:
            currentScreen = ScreenState::VIEW_USER_PROFILE;
            break;
           default: currentScreen = ScreenState::MAIN; break;
        }
    }

    // Input handlers
    void HandleAddFriendInput() {
        int key = GetCharPressed();
        while (key > 0 && inputPos < 31) { 
            if (key >= '0' && key <= '9')
                idInput[inputPos++] = (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0)
            idInput[--inputPos] = '\0';
        if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
            int fid = atoi(idInput);
            bool ok = person->add_friend(fid);
            message = ok ? "Friend added!" : "Invalid ID or already friends";
            messageColor = ok ? GREEN : RED;
            messageTime = GetTime();
        }
    }
    void HandleSwitchDateInput() {
       
        if (IsKeyPressed(KEY_TAB)) {
            activeDateField = (activeDateField + 1) % 3;
        }
      
        if (IsKeyPressed(KEY_BACKSPACE) && dateInputPos[activeDateField] > 0) {
            dateInputs[activeDateField][--dateInputPos[activeDateField]] = '\0';
        }
      
        int maxLen[3] = { 2,2,4 };
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= '0' && key <= '9' && dateInputPos[activeDateField] < maxLen[activeDateField]) {
                dateInputs[activeDateField][dateInputPos[activeDateField]++] = (char)key;
                dateInputs[activeDateField][dateInputPos[activeDateField]] = '\0';
            }
            key = GetCharPressed();
        }
       
        if (IsKeyPressed(KEY_ENTER)) {
            int d = atoi(dateInputs[0]);
            int m = atoi(dateInputs[1]);
            int y = atoi(dateInputs[2]);
            bool bd = (d < 1 || d > 30);
            bool bm = (m < 1 || m > 12);
            bool by = (y < 2000);
            showDateError = bd || bm || by;
            if (!showDateError) {
                currentDate.set_Date(d, m, y);           
                currentScreen = ScreenState::MAIN;
            }
        }
    }
    void HandleViewPostInput() { 
        if (viewPostStage == 0) {
            int key = GetCharPressed();
            while (key > 0 && inputPos < 31) 
            { 
                if (key >= '0' && key <= '9')
                    idInput[inputPos++] = (char)key; 
                key = GetCharPressed(); 
            }
            if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0) 
                idInput[--inputPos] = '\0';
            if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
                int pid = atoi(idInput);
                foundIndex = -1;

                for (int i = 0; i < user::total_users; i++) {
                    for (int j = 0; j < user::user_record[i]->get_post_count(); j++) {
                        if (user::user_record[i]->get_specific_post(j)->get_id() == pid)
                        {
                            foundIndex = j;
                            user_index = i;
                            break;
                        }
                    }
                }
                if (foundIndex >= 0) 
                    viewPostStage = 1;
                else
                {
                    message = "Enter correct ID";
                    messageColor = RED;
                    messageTime = GetTime(); 
                }
            }
        }
    }

    void HandleLikePostInput() {
      
        const int MAX_DIGITS = 6;
        int key = GetCharPressed();
        while (key > 0 && inputPos < MAX_DIGITS) {
            if (key >= '0' && key <= '9')
                idInput[inputPos++] = char(key);
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0) {
            idInput[--inputPos] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
            int pid = atoi(idInput);
            foundIndex = -1;

         
            
            for (int i = 0; i < user::total_users; i++) {
                for (int j = 0; j < user::user_record[i]->get_post_count(); j++)
                {
                    if (user::user_record[i]->get_specific_post(j)->get_id() == pid) {
                        foundIndex = i;
                        user::user_record[i]->get_specific_post(j)->like_increase(person);
                        message = "Post liked!";
                        messageColor = GREEN;
                        messageTime = GetTime();
                        return;
                    }
                }              
            }

           
            for (int u = 0; u < user::total_users; u++) {
                user* uu = user::user_record[u];
                // pages they own
                for (int p = 0; p < uu->get_ownercount(); p++) {
                    page* pg = uu->get_pages_own(p);
                    for (int k = 0; k < pg->get_numberofpost(); k++) {
                        post* pst = pg->get_specific_post(k);
                        if (pst->get_id() == pid) {
                            pst->like_increase(pg);
                            message = "Post liked on page!";
                            messageColor = GREEN;
                            messageTime = GetTime();
                            return;
                        }
                    }
                }
            }      
            message = "Invalid Post ID";
            messageColor = RED;
            messageTime = GetTime();
        }
    }

    void HandleViewPeopleInput() {
        if (viewPeopleStage == 0) {
                    
                int key = GetCharPressed();
           while (key > 0 && inputPos < 8) {
                if (key >= '0' && key <= '9')
                     idInput[inputPos++] = char(key);
                key = GetCharPressed();
                
            }
             if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0)
                 idInput[--inputPos] = '\0';
            
                           
                if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
                int pid = atoi(idInput);
                foundIndex = -1;
                                                 
                    for (int i = 0; i < person->get_post_count(); i++) 
                    {
                    if (person->get_specific_post(i)->get_id() == pid) 
                    {
                        foundIndex = i;
                        break;                       
                    }
                    
                    }
                
                                   
                    if (foundIndex < 0) {
                        for (int u = 0; u < user::total_users && foundIndex < 0; u++)
                        {
                            user* uu = user::user_record[u];
                            for (int p = 0; p < uu->get_ownercount(); p++) {
                                page* pg = uu->get_pages_own(p);
                                for (int k = 0; k < pg->get_numberofpost(); k++) {
                                    post* pst = pg->get_specific_post(k);
                                    if (pst->get_id() == pid) {
                                        foundIndex = -2;
                                        break;
                                    }
                                }
                                if (foundIndex < 0) continue;
                                break;

                            }

                        }

                    }
                    if (foundIndex >= 0 || foundIndex == -2)
                    {
                        viewPeopleStage = 1;
                        messageTime = GetTime();
                    }
                    else {
                    message = "Invalid Post ID";
                    messageColor = RED;
                    messageTime = GetTime();
                    
                    } 
                }
        }
        
    }
    void HandleSharePostInput() {
        if (viewShareStage == 0) {
            
            int key = GetCharPressed();
            while (key > 0 && inputPos < 8) {
                if (key >= '0' && key <= '9')
                    idInput[inputPos++] = char(key);
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0)
                idInput[--inputPos] = '\0';

           
            if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
                int pid = atoi(idInput);
                           
                    inputPos = 0; 
                    idInput[0] = '\0';

                bool ok = person->share_post(pid);
                if (ok) {
                    message = "Post shared successfully";
                    messageColor = GREEN;
                }
                else {
                    message = "Enter correct ID";
                    messageColor = RED;
                }
                messageTime = GetTime();
                viewShareStage = 1;
            }
        }
    }
    void HandleMakeCommentInput() {
        
        if (viewCommentStage == 0) {
            
            int key = GetCharPressed();
            while (key > 0 && inputPos < 8) {
                if (key >= '0' && key <= '9')
                    idInput[inputPos++] = char(key);
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && inputPos > 0)
                idInput[--inputPos] = '\0';

         
            if (IsKeyPressed(KEY_ENTER) && inputPos > 0) {
                int pid = atoi(idInput);
                foundIndex = -1;

               
                for (int i = 0; i < user::total_users; i++) {
                    for(int j=0;j<user::user_record[i]->get_post_count();j++)
                    if (user::user_record[i]->get_specific_post(j)->get_id() == pid) {
                        foundIndex = j;
                        found_user = i;
                        break;
                    }
                }
              
                if (foundIndex < 0) {
                    for (int u = 0; u < user::total_users && foundIndex < 0; u++) {
                        user* uu = user::user_record[u];
                        for (int p = 0; p < uu->get_ownercount() && foundIndex < 0; p++) {
                            page* pg = uu->get_pages_own(p);
                            for (int k = 0; k < pg->getpostcount(); k++) {
                                if (pg->get_specific_post(k)->get_id() == pid) {
                                    foundIndex = -2; 
                                    message = (const char*)pg->get_specific_post(k);
                                    break;
                                }
                            }
                        }
                    }
                }

                if (found_user >= 0 || foundIndex == -2) {
                    
                    viewCommentStage = 1;
                    
                    commentPos = 0;
                    commentBuf[0] = '\0';
                }
                else {
                    message = "Invalid Post ID";
                    messageColor = RED;
                    messageTime = GetTime();
                }
            }
        }
        else if (viewCommentStage == 1) {
           
            int k = GetCharPressed();
            while (k > 0 && commentPos < 256 - 1) {
                if (k >= 32 && k < 127)   
                    commentBuf[commentPos++] = char(k);
                k = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && commentPos > 0)
                commentBuf[--commentPos] = '\0';

           
            if (IsKeyPressed(KEY_ENTER) && commentPos > 0) {
                post* target = nullptr;
                if (foundIndex >= 0) {
                    target = user::user_record[found_user]->get_specific_post(foundIndex);
                }
                else { 
                    target = (post*)message;
                }

                target->add_comment(person->get_name().c_str(), commentBuf);

                message = "Comment added!";
                messageColor = GREEN;
                messageTime = GetTime();

             
                viewCommentStage = 2;
            }
        }
    }
   
    void DrawSwitchDate() {
        ClearBackground(BLACK);
        const char* labels[3] = { "Day", "Month", "Year" };
        int screenW = screenWidth, screenH = screenHeight;
        int boxW = 80, boxH = 40, gap = 20;
        int totalW = 3 * boxW + 2 * gap;
        int startX = (screenW - totalW) / 2;
        int startY = (screenH - boxH) / 2;
       
        DrawText("Switch Date (DD MM YYYY)", screenW / 2 - MeasureText("Switch Date (DD MM YYYY)", 24) / 2, startY - 60, 24, WHITE);
        // Draw fields
        for (int i = 0; i < 3; ++i) {
            int x = startX + i * (boxW + gap);
            bool error = false;
            if (showDateError) {
                if (i == 0) error = (atoi(dateInputs[0]) < 1 || atoi(dateInputs[0]) > 30);
                if (i == 1) error = (atoi(dateInputs[1]) < 1 || atoi(dateInputs[1]) > 12);
                if (i == 2) error = (atoi(dateInputs[2]) < 2000);
            }
            DrawRectangleLines(x, startY, boxW, boxH, error ? RED : (activeDateField == i ? BLUE : GRAY));
            DrawText(labels[i], x + 5, startY - 30, 20, WHITE);
            DrawText(dateInputs[i], x + 5, startY + 5, 20, WHITE);
        }
        if (showDateError) {
            const char* err = "Enter valid: 1<=D<=30,1<=M<=12,Year>=2000";
            DrawText(err, screenW / 2 - MeasureText(err, 20) / 2, startY + boxH + 20, 20, RED);
        }
        DrawText("TAB to switch field, ENTER to set date", screenW / 2 - MeasureText("TAB to switch field, ENTER to set date", 18) / 2, screenH - 40, 18, LIGHTGRAY);
    }
    void DrawMain(const Vector2 mouse) {
        DrawText(person->get_name().c_str(), 20, 20, 30, DARKBLUE);
        std::string idTxt = TextFormat("ID: %d", person->get_id());
        DrawText(idTxt.c_str(), screenWidth - MeasureText(idTxt.c_str(), 30) - 20, 20, 30, DARKBLUE);
        for (int i = 0; i < 11; i++) {
            Color col = CheckCollisionPointRec(mouse, buttons[i]) ? GREEN : LIGHTGRAY;
            DrawRectangleRec(buttons[i], col);
            DrawRectangleLinesEx(buttons[i], 2, DARKGRAY);
            int tw = MeasureText(buttonLabels[i], 20);
            DrawText(buttonLabels[i], buttons[i].x + (400 - tw) / 2, buttons[i].y + 30, 20, DARKGRAY);
        }
    }

    void DrawAddFriend() {
        ClearBackground(BLACK);
        DrawText("Enter Friend ID:", screenWidth / 2 - 200, screenHeight / 2 - 80, 30, WHITE);
        Rectangle box = { (screenWidth / 2 - 200), (screenHeight / 2 - 30),400,60 };
        DrawRectangleRec(box, LIGHTGRAY);
        DrawRectangleLinesEx(box, 2, DARKGRAY);
        DrawText(idInput, box.x + 10, box.y + 15, 30, DARKBLUE);
        if (message && GetTime() - messageTime < 1.0) {
            int tw = MeasureText(message, 4);
            DrawText(message, screenWidth / 2 - tw / 2, screenHeight / 2 + 50, 30, messageColor);
        }
    }

    void DrawViewFriend() {
        ClearBackground(BLACK);
        int cnt = person->get_friendcount();
        if (cnt > 0) {
            float y = 100; for (int i = 0; i < cnt; i++) {
                user* f = person->get_specificfriend(i);
                string line = TextFormat("%d. %s (ID:%d)", i + 1, f->get_name().c_str(), f->get_id());
                DrawText(line.c_str(), 100, y, 25, WHITE); y += 50;
            }
        }
        else {
            const char* msg = "No friends yet";
            int tw = MeasureText(msg, 40);
            DrawText(msg, screenWidth / 2 - tw / 2, screenHeight / 2, 40, WHITE);
        }
        DrawText("Press BACKSPACE to return", 20, screenHeight - 40, 20, GRAY);
    }

    void DrawMakePost() {
      
        static int postStage = 0;        
        static int chosenCat = 0;        
        static char descBuf[256] = { 0 };  
        static int descPos = 0;
        const char* cats[4] = { "Feeling","Thinking about","Making","Celebrating" };
        const char* opts[4][3] = {
          {"Happy","Sad","Excited"},
          {"Life","Future","Meaning of life"},
          {"Money","Art","Memories"},
          {"Birthday","Halloween","Success"}
        };

        Vector2 mouse = GetMousePosition();
        ClearBackground(BLACK);
        DrawText("Press BACKSPACE to cancel", 20, screenHeight - 40, 20, GRAY);

        if (postStage == 0) {
           
            for (int i = 0; i < 4; ++i) {
                Rectangle r = { 100, 150 + i * 100, 400, 60 };
                Color col = CheckCollisionPointRec(mouse, r) ? SKYBLUE : LIGHTGRAY;
                DrawRectangleRec(r, col);
                DrawText(cats[i], r.x + 20, r.y + 15, 30, DARKBLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, r)) {
                    postStage = 1;
                    chosenCat = i;
                }
            }
        }
        else if (postStage == 1) {
          
              
            for (int j = 0; j < 3; ++j) {
                Rectangle r = { 100 + j * 450, 200, 400, 60 };
                Color col = CheckCollisionPointRec(mouse, r) ? SKYBLUE : LIGHTGRAY;
                DrawRectangleRec(r, col);
                DrawText(opts[chosenCat][j], r.x + 20, r.y + 15, 30, DARKBLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, r)) {
                    postStage = 2;
                   
                }
            }
        }
        else if (postStage == 2) {
           
            Rectangle box = { 100, 200, 800, 60 };
            DrawRectangleRec(box, LIGHTGRAY);
            DrawRectangleLinesEx(box, 2, DARKGRAY);
            DrawText("Enter description & press ENTER:", 100, 150, 25, WHITE);
            DrawText(descBuf, box.x + 10, box.y + 10, 25, DARKBLUE);

            int k = GetCharPressed();
            while (k > 0 && descPos < (int)(sizeof(descBuf) - 1)) {
                if (k >= 32 && k < 127) descBuf[descPos++] = (char)k;
                k = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && descPos > 0) {
                descBuf[--descPos] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && descPos > 0) {
              
                person->create_post_with_info(cats[chosenCat], descBuf, currentDate);
               
                postStage = 0;
                descPos = 0;
                memset(descBuf, 0, sizeof(descBuf));
                currentScreen = ScreenState::MAIN; 
            }
        }
    }
    void DrawViewPost() {
        
        if (viewPostStage == 0) {
           
            ClearBackground(BLACK);
            DrawText("Enter Post ID:", 100, 200, 30, WHITE);
            Rectangle box = { 100, 250, 300, 50 };
            DrawRectangleRec(box, LIGHTGRAY);
            DrawRectangleLinesEx(box, 2, DARKGRAY);
            DrawText(idInput, box.x + 10, box.y + 10, 30, DARKBLUE);
            if (message && GetTime() - messageTime < 1.0) {
                int tw = MeasureText(message, 25);
                DrawText(message, box.x + box.width / 2 - tw / 2, box.y + 70, 25, messageColor);
            }
        }
        else {
            
            ClearBackground(BLACK);
            post* p = user::user_record[user_index]->get_specific_post(foundIndex);
          
            string header = TextFormat("--- %s %s",
                p->get_owner().c_str(), p->get_activity().c_str());
            DrawText(header.c_str(), 50, 50, 30, WHITE);

          
            std::string body = TextFormat("\"%s\" ... (%02d/%02d/%04d)",
                p->get_description().c_str(),
                p->getDate().get_d(), user::user_record[user_index]->get_specific_post(foundIndex)->getDate().get_m(), p->getDate().get_y());
            DrawText(body.c_str(), 50, 100, 25, WHITE);

            // Comments
            int cc = p->get_comment_count();
            if (cc > 0) {
                for (int i = 0; i < cc; ++i) {
                    comment* c = p->get_comments(i);
                    std::string ctext = TextFormat("    %s wrote: \"%s\"",
                        c->get_owner().c_str(), c->get_text().c_str());
                    DrawText(ctext.c_str(), 70, 150 + i * 30, 24, GRAY);
                }
            }
            else {
                DrawText("No comments yet", 50, 150, 24, GRAY);
            }

            DrawText("Press BACKSPACE to return", 50, screenHeight - 50, 20, GRAY);
        }
    }
    void DrawLikePost() {
        ClearBackground(BLACK);
        DrawText("Enter Post ID to Like:", 100, 200, 30, WHITE);
        Rectangle box = { 100, 250, 300, 50 };
        DrawRectangleRec(box, LIGHTGRAY);
        DrawRectangleLinesEx(box, 2, DARKGRAY);
        DrawText(idInput, box.x + 10, box.y + 10, 30, DARKBLUE);

       
        if (message && (GetTime() - messageTime) < 1.0) {
            int tw = MeasureText(message, 25);
            DrawText(message, box.x + box.width / 2 - tw / 2, box.y + 70, 25, messageColor);
        }
        
    }

     void DrawViewPeople() {
        ClearBackground(BLACK);
        if (viewPeopleStage == 0) {
                       
                DrawText("Enter Post ID:", 100, 200, 30, WHITE);
            Rectangle box = { 100, 250, 300, 50 };
            DrawRectangleRec(box, LIGHTGRAY);
            DrawRectangleLinesEx(box, 2, DARKGRAY);
            DrawText(idInput, box.x + 10, box.y + 10, 30, DARKBLUE);
            if (message && (GetTime() - messageTime) < 1.0) {
                int tw = MeasureText(message, 25);
                DrawText(message, box.x + box.width / 2 - tw / 2, box.y + 70, 25, messageColor);
                
            }
            
        }
        else {
                       
                post * p = nullptr;
            if (foundIndex >= 0)
                 p = person->get_specific_post(foundIndex);
            else if (foundIndex == -2)
                 p = (post*)message; 
            
                if (!p) {
                DrawText("Error retrieving post", 100, 200, 30, RED);
                }
                else {
                    int count = p->get_no_of_likes();
                    if (count == 0) {
                        DrawText("No one has liked this post yet", 100, 200, 30, WHITE);

                    }
                    else {
                        float y = 150;
                        for (int i = 0; i < count; i++)
                        {
                            user* liker = p->get_likers()[i];
                            string line = TextFormat("%d. %s (ID:%d)",
                                i + 1,
                                liker->get_name().c_str(),
                                liker->get_id());
                            DrawText(line.c_str(), 100, y, 25, WHITE);
                            y += 40;
                        }
                    }

                }
             DrawText("Press BACKSPACE to return", 20, screenHeight - 40, 20, GRAY);
        }
        
     }
     void DrawSharePost() {
         ClearBackground(BLACK);
         if (viewShareStage == 0) {
             DrawText("Enter Post ID to Share:", 100, 200, 30, WHITE);
             Rectangle box = { 100, 250, 300, 50 };
             DrawRectangleRec(box, LIGHTGRAY);
             DrawRectangleLinesEx(box, 2, DARKGRAY);
             DrawText(idInput, box.x + 10, box.y + 10, 30, DARKBLUE);
         }
         else {
             // show the transient message
             if (message && (GetTime() - messageTime) < 1.0) {
                 int tw = MeasureText(message, 25);
                 DrawText(message, 100, 300, 25, messageColor);
             }
             DrawText("Press BACKSPACE to return", 20, screenHeight - 40, 20, GRAY);
         }
     }
     void DrawMakeComment() {
         ClearBackground(BLACK);

         if (viewCommentStage == 0) {
           
             DrawText("Enter Post ID to Comment:", 100, 200, 30, WHITE);
             Rectangle box = { 100, 250, 300, 50 };
             DrawRectangleRec(box, LIGHTGRAY);
             DrawRectangleLinesEx(box, 2, DARKGRAY);
             DrawText(idInput, box.x + 10, box.y + 10, 30, DARKBLUE);
             if (message && (GetTime() - messageTime) < 1.0) {
                 int tw = MeasureText(message, 25);
                 DrawText(message, box.x + box.width / 2 - tw / 2, box.y + 70, 25, messageColor);
             }
         }
         else if (viewCommentStage == 1) {
          
             DrawText("Enter your comment:", 100, 200, 30, WHITE);
             Rectangle box = { 100, 250, 600, 80 };
             DrawRectangleRec(box, LIGHTGRAY);
             DrawRectangleLinesEx(box, 2, DARKGRAY);
             DrawText(commentBuf, box.x + 10, box.y + 10, 24, DARKBLUE);
         }
         else {
            
             if (message && (GetTime() - messageTime) < 1.0) {
                 int tw = MeasureText(message, 25);
                 DrawText(message, 100, 300, 25, messageColor);
             }
             DrawText("Press BACKSPACE to return", 20, screenHeight - 40, 20, GRAY);
         }
     }
     
     
     void DrawViewUserProfile() {
         ClearBackground(BLACK);

        
         std::string header = TextFormat("%s (ID: %d)",
             person->get_name().c_str(),
             person->get_id());
         DrawText(header.c_str(), 50, 50, 30, WHITE);

         // 2) Posts
         int pc = person->get_post_count();
         if (pc == 0) {
             DrawText("No posts yet", 50, 100, 25, GRAY);
         }
         else {
             float y = 100;
             for (int i = 0; i < pc; ++i) {
                 post* p = person->get_specific_post(i);
               
                 string postLine = TextFormat("%d) \"%s\"  (%02d/%02d/%04d)",
                     p->get_id(),
                     p->get_description().c_str(),
                     p->getDate().get_d(),
                     p->getDate().get_m(),
                     p->getDate().get_y());
                 DrawText(postLine.c_str(), 50, y, 24, WHITE);
                 y += 30;

               
                 int cc = p->get_comment_count();
                 if (cc == 0) {
                     DrawText("   No comments", 70, y, 20, GRAY);
                     y += 25;
                 }
                 else {
                     for (int c = 0; c < cc; ++c) {
                         comment* cm = p->get_comments(c);
                         std::string cmLine = TextFormat("   %s: \"%s\"",
                             cm->get_owner().c_str(),
                             cm->get_text().c_str());
                         DrawText(cmLine.c_str(), 70, y, 20, GRAY);
                         y += 25;
                     }
                 }

                 y += 10;

               
             }
         }

       
         DrawText("Press ESC or BACKSPACE to return", 50,
             screenHeight - 40, 20, LIGHTGRAY);
     }    
   

     void DrawSwitchUser()
     {
         ClearBackground(BLACK);
         Vector2 mouse = GetMousePosition();

        
         if (viewSwitchStage == 0)
         {
             
             Rectangle loginBtn = {
                 (screenWidth - 300) * 0.5f,
                 (screenHeight - 2 * 60 - 30) * 0.5f,
                 300, 60
             };
             Rectangle createBtn = {
                 loginBtn.x,
                 loginBtn.y + 60 + 30,
                 300, 60
             };
             // Hover effect
             DrawRectangleRec(loginBtn, CheckCollisionPointRec(mouse, loginBtn) ? GRAY : RAYWHITE);
             DrawText("Login (ID)", loginBtn.x + 60, loginBtn.y + 18, 30, BLACK);
             DrawRectangleRec(createBtn, CheckCollisionPointRec(mouse, createBtn) ? GRAY : RAYWHITE);
             DrawText("Create Account", createBtn.x + 20, createBtn.y + 18, 30, BLACK);
         }
        
         else
         {
             const char* prompt = switchIsLogin ? "Enter 4-digit ID:" : "Enter Username:";
             int pw = MeasureText(prompt, 28);
             DrawText(prompt, (screenWidth - pw) * 0.5f, screenHeight * 0.3f, 28, GREEN);

             Rectangle box = {
                 (screenWidth - 400) * 0.5f,
                 screenHeight * 0.5f,
                 400, 50
             };
             DrawRectangleRec(box, LIGHTGRAY);
             DrawRectangleLinesEx(box, 2, DARKGRAY);
             DrawText(switchInput, box.x + 10, box.y + 10, 28, DARKBLUE);

             
             if (message && GetTime() - messageTime < 1.0)
             {
                 int tw = MeasureText(message, 24);
                 DrawText(message, (screenWidth - tw) * 0.5f, box.y + 70, 24, messageColor);
             }
         }
     }

     void HandleSwitchUserInput()
     {
         Vector2 mouse = GetMousePosition();

        
         if (viewSwitchStage == 0)
         {
             Rectangle loginBtn = {
                 (screenWidth - 300) * 0.5f,
                 (screenHeight - 2 * 60 - 30) * 0.5f,
                 300, 60
             };
             Rectangle createBtn = {
                 loginBtn.x,
                 loginBtn.y + 60 + 30,
                 300, 60
             };
             if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
             {
                 if (CheckCollisionPointRec(mouse, loginBtn))
                 {
                     switchIsLogin = true;
                     viewSwitchStage = 1;
                     switchInputPos = 0;
                     switchInput[0] = '\0';
                 }
                 else if (CheckCollisionPointRec(mouse, createBtn))
                 {
                     switchIsLogin = false;
                     viewSwitchStage = 1;
                     switchInputPos = 0;
                     switchInput[0] = '\0';
                 }
             }
         }
        
         else
         {
             
             static bool active = false;
             Rectangle box = {
                 (screenWidth - 400) * 0.5f,
                 screenHeight * 0.5f,
                 400, 50
             };
             if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                 active = CheckCollisionPointRec(mouse, box);

            
             if (active)
             {
                 int key = GetCharPressed();
                 while (key > 0 && switchInputPos < 31)
                 {
                     bool ok = switchIsLogin
                         ? (key >= '0' && key <= '9')
                         : ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || key == ' ');
                     if (ok) switchInput[switchInputPos++] = char(key);
                     key = GetCharPressed();
                 }
                 if (IsKeyPressed(KEY_BACKSPACE) && switchInputPos > 0)
                     switchInput[--switchInputPos] = '\0';
             }

            
             if (IsKeyPressed(KEY_ENTER) && switchInputPos > 0)
             {
                 if (switchIsLogin)
                 {
                     
                     if (switchInputPos == 4)
                     {
                         int pid = atoi(switchInput);
                         bool found = false;
                         for (int i = 0; i < user::total_users; ++i)
                         {
                             if (user::user_record[i]->get_id() == pid)
                             {
                                 person = user::user_record[i];
                                 found = true;
                                 break;
                             }
                         }
                         if (!found)
                         {
                             message = "Invalid ID!";
                             messageColor = RED;
                             messageTime = GetTime();
                         }
                         else
                         {
                            
                             ResetToMain();
                         }
                     }
                 }
                 else
                 {
                    
                     std::string name(switchInput);
                     bool exists = false;
                     for (int i = 0; i < user::total_users; ++i)
                         if (user::user_record[i]->get_name() == name)
                             exists = true;
                     if (exists)
                     {
                         message = "Username exists!";
                         messageColor = RED;
                         messageTime = GetTime();
                     }
                     else
                     {
                       
                         user::total_users++;
                         user** tmp = new user * [user::total_users];
                         for (int i = 0; i < user::total_users - 1; ++i)
                             tmp[i] = user::user_record[i];
                         tmp[user::total_users - 1] = new user;
                         tmp[user::total_users - 1]->set_person(name, 1000 + user::total_users);
                         delete[] user::user_record;
                         user::user_record = tmp;
                         person = tmp[user::total_users - 1];
                         ResetToMain();
                     }
                 }
             }
         }
     }
};


