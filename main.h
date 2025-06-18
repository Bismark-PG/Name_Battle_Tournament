#include <iostream>
#include <stdlib.h>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <Windows.h>
using namespace std;

static void SetConsoleSize(int width, int height, int bufferHeight = 1000)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { (SHORT)width, (SHORT)bufferHeight };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}
static void LockConsoleResize()
{
    HWND hwnd = GetConsoleWindow();

    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE, style);
}

struct Player
{
    string player_name = {};
    int player_power = 0;
    int player_HP = 0;
    int player_ATK = 0;
    int player_DEF = 0;
    int player_skill_num = 0;
    string player_skill_name = {};
    int Skill_Count = 3;
    int player_rank = 1;
    int player_number = 0;
};
struct Player_List
{
    struct Player players[100] = {};
    int player_count = 0;
};

void line(void);
// void ClearScreen(void);

void Start(int* answer);
void End(void);
void Wrong(int* num);
void No_Char(void);
void Select_menu(int* answer);
void Get_Ready(void);
void Enemy_Info(struct Player enemy, int Round);
void Todo_List(void);
void Game_Over(int winner);

int ascii_sum(const char* str);
int Create_character(struct Player_List* List, int* num);
int Select_character(struct Player_List* List, struct Player* select, int* num, int* player);
void Character_Stat(struct Player_List* List, int count, int* skill);
void Tournament(struct Player_List* List, int player, int select_player);
void CPU_Tournament(struct Player_List* List, int player, int select_player, int wave);
void Select_Enemy(struct Player_List List, struct Player* enemy, int wave, int select_player);
void Battle_Stat(struct Player Human, struct Player CPU, int Wave, int PHP, int AHP);
void Battle(struct Player* Human, struct Player* CPU,
    int* PHP, int PATK, int PDEF, int* EHP, int EATK, int EDEF,
    int* SCount, int* FCount, int* ESCount, int* Result);
void Lets_Play(struct Player_List* List, struct Player* Human, struct Player* CPU, int Round);
void Ranking(struct Player_List List, int Round, int select_player);