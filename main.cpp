#include "main.h"

int main(void)
{
    SetConsoleSize(100, 50);
    LockConsoleResize();
    struct Player_List Gamers;
    struct Player Selected_Player;
    struct Player Enemy_Player;
    int select_num = 0;
    int answer = 0;
    int error_num = 0;
    bool winner = 0;

    // Select Start
    Start(&answer);
    do
    {
        if (answer == 1)
        {
            End();
            return 0;
        }
        else if (answer != 0)
        {
            Wrong(&error_num);
        }
        else
        {
            cout << "\t\t\t\t\t    ようこそ！" << endl;
            cout << "\t\t\t\t　　メニューを選択してください！\n" << endl;
            line();
            break;
        }
        cin >> answer;
    } while (1);

    // Select Menu
select:
    Select_menu(&answer);
    do
    {
        error_num = 0;
        if (answer == 2)
        {
            End();
            return 0;
        }
        else if (answer == 1)
        {
            Select_character(&Gamers, &Selected_Player, &error_num, &select_num);
            switch (error_num)
            {
            case 1:
                goto select;
                break;
            case 3:
                Wrong(&error_num);
                goto select;
            case 5:
                Wrong(&error_num);
                goto select;
            }
            break;
        }
        else if (answer == 0)
        {
            Create_character(&Gamers, &error_num);
            switch (error_num)
            {
            case 2:
                Wrong(&error_num);
                break;
            case 4:
                Wrong(&error_num);
                break;
            case 5:
                Wrong(&error_num);
                break;
            case 6:
                Wrong(&error_num);
                break;
            }
            goto select;
        }
        else
        {
            Wrong(&error_num);
            goto select;
        }
    } while (1);

    // Make Tournament
    int All_Players = Gamers.player_count;
    Tournament(&Gamers, All_Players, select_num);
    int Ranking_Round = Gamers.players[select_num - 1].player_rank;

    // Play;
    int Round = 0;
    while (1)
    {
        Round++;
        Get_Ready();
        Select_Enemy(Gamers, &Enemy_Player, Round, select_num);
        Enemy_Info(Enemy_Player, Round);
        Lets_Play(&Gamers, &Selected_Player, &Enemy_Player, Round);

        // Player Win
        if (Round == Gamers.players[Selected_Player.player_number].player_rank - 1)
        {
            winner = true;
            break;
        }
        // CPU Win
        else if (Round == Gamers.players[Selected_Player.player_number].player_rank)
        {
            winner = false;
            CPU_Tournament(&Gamers, All_Players, select_num, Round + 1);
            break;
        }
    }

    Ranking(Gamers, Ranking_Round, select_num);
    Game_Over(winner);

    cin.ignore();
    cin.get();
    return 0;
}

void line(void)
{
    for (int i = 0; i < 100; i++)
    {
        cout << "-";
    }
    cout << endl;
}
/* void ClearScreen(void)
{
    system("cls");
} */

void Start(int* answer)
{
    cout << "\n\t\t\t\t\t＿人人人人人人人＿" << endl;
    cout << "\t\t\t\t\t＞ ネームバトル ＜" << endl;
    cout << "\t\t\t\t\t＞    ゲーム    ＜" << endl;
    cout << "\t\t\t\t\t￣Y^Y^Y^Y^Y^Y^Y￣" << endl;
    cout << "\n\t\t\t\t\t 始めましょうか？" << endl;
    cout << "\n\t\t\t\t\t[0] YES // [1] NO\n" << endl;
    line();
    cin >> *answer;
}
void End(void)
{
    cout << "\t\t\t\t    分かりました！終了します！" << endl;
    cout << "\t\t\t\t      また、遊びましょう！" << endl;
    cout << "\t\t\t\t       See you next time!\n" << endl;
    line();
}
void Wrong(int* num)
{
    switch (*num)
    {
    case 2:
        cout << "\t\t\t\t   もうキャラクターが一杯です！" << endl;
        break;
    case 3:
        cout << "\t\t\t\t   存在しないキャラクターです！" << endl;
        break;
    case 4:
        cout << "\t\t\t\t\t記号が入ってます！" << endl;
        break;
    case 5:
        cout << "\t\t\t\t\t空白が入ってます！" << endl;
        break;
    case 6:
        cout << "\t\t\t\t\tお名前が長いです。" << endl;
        cout << "\t\t\t\t  25文字以下で入力してください。" << endl;
        break;
    default:
        cout << "\t\t\t\t\t  間違い入力です！" << endl;
        break;
    }
    cout << "\t\t\t\t      入力を直してください！\n" << endl;
    line();
}
void No_Char(void)
{
    cout << "\t\t\t\t     キャラクターがありません！" << endl;
    cout << "\t\t\t\t  キャラクターを生成してください！\n" << endl;
    line();
}
void Select_menu(int* answer)
{

    cout << "\n\t\t\t\t      [0] キャラクター生成" << endl;
    cout << "\t\t\t\t      [1] キャラクター選択" << endl;
    cout << "\t\t\t\t\t  [2] ゲーム終了\n" << endl;
    line();
    cin >> *answer;
}
void Get_Ready(void)
{
    cout << "\n\t\t\t\t\t    GET READY" << endl;
    cout << "\t\t\t\t\t     FOR THE" << endl;
    cout << "\t\t\t\t\t   NEXT BATTLE\n" << endl;
    line();
}
void Enemy_Info(struct Player enemy, int Round)
{
    cout << "\n\t\t\t\t   ＞＞　ＲＯＵＮＤ " << Round << "　＜＜\n" << endl;
    cout << "\n\t\t\t\t    ＞＞　相手の情報　＜＜\n" << endl;
    cout << "\t\t\t\t\t名前 : " << enemy.player_name << '\n' << endl;
    cout << "\t\t\t\t\t戦力 : " << enemy.player_power << endl;
    cout << "\t\t\t\t\tATK  : " << enemy.player_ATK << endl;
    cout << "\t\t\t\t\tDEF  : " << enemy.player_DEF << endl;
    cout << "\t\t\t\t\t能力 : " << enemy.player_skill_name << '\n' << endl;
    line();
}
void Todo_List(void)
{
    cout << "\t\t\t\t\t何をしますか？" << endl;
    line();

    cout << "\t    [1] : " << left << setw(24) << "攻撃"
        << "[2] : " << left << setw(24) << "防御"
        << "[3] : " << left << setw(24) << "能力使用" << endl;
    line();
}
void Game_Over(int winner)
{
    // True(1) = Player Win / False(0) = CPU Win
    switch (winner)
    {
    case 0:
        cout << "\n\t\t\t  頑張って次は勝ってみましょう！ お疲れ様でした！\n" << endl;
        line();
        break;
    case 1:
        cout << "\n\t\t\t      最終勝利！！ おめでとうございます！\n" << endl;
        line();
        break;
    }
    cout << "\n\t\t\t\tゲームが終了しました。" << endl;
    cout << "\t\t\t\tプレイありがとうございました！\n" << endl;
}

int ascii_sum(const char* str)
{
    int sum = 0;
    while (*str)
    {
        sum += (int)*str;
        str++;
    }

    return sum;
}
int Create_character(struct Player_List* List, int* num)
{
    Player_List* List_copy = List;
    int PCount = 0;
    string name;
    int power = 0;

    if (List->player_count == 100)
    {
        *num = 2;
        return 0;
    }

    cout << "\t\t\t\t    戦場に新たな光が生まれた...\n" << endl;
    line();
    PCount = List->player_count;

    do
    {
        cout << "\n\t\t\t\t     名前を入力してください！" << endl;
        cout << "\t\t\t       [英語と数字だけで入力してください。]" << endl;
        cout << "\t\t\t       ＞＞空白を入れないでください！！＜＜\n" << endl;
        line();
        cin.ignore();
        getline(cin, name);

        bool result = true;
        if (name.length() > 26)
        {
            *num = 6;
            return 0;
        }
        else if (name.find(' ') != string::npos)
        {
            *num = 5;
            return 0;
        }
        for (int i = 0; name.c_str()[i] != '\0'; i++)
        {
            if (!isalnum(name.c_str()[i]))
            {
                result = false;
                *num = 4;
                return 0;
            }
        }
        break;
    } while (1);

    List->players[PCount].player_name = name;
    List->player_count++;
    line();

    Character_Stat(List_copy, PCount, &power);

    cout << "\n\t\t\t\t    新しい選手が登場しました！" << endl;
    cout << "\t\t\t\t\t番号 : " << List->player_count << endl;
    cout << "\t\t\t\t\t名前 : " << List->players[PCount].player_name << '\n' << endl;
    cout << "\t\t\t\t\t戦力 : " << List->players[PCount].player_power << endl;
    cout << "\t\t\t\t\tATK  : " << List->players[PCount].player_ATK << endl;
    cout << "\t\t\t\t\tDEF  : " << List->players[PCount].player_DEF << endl;
    cout << "\t\t\t\t\t能力 : ";
    switch (power)
    {
    case 1:
        cout << List->players[PCount].player_skill_name << endl;
        cout << "\t\t\t\t\t       一定確率で攻撃力４倍\n" << endl;
        break;
    case 2:
        cout << List->players[PCount].player_skill_name << endl;
        cout << "\t\t\t\t\t       低確率で防御無視攻撃\n" << endl;
        break;
    case 3:
        cout << List->players[PCount].player_skill_name << endl;
        cout << "\t\t\t\t\t       一定確率で防御力４倍\n" << endl;
        break;
    case 4:
        cout << List->players[PCount].player_skill_name << endl;
        cout << "\t\t\t\t\t       一定確率で最大HPの２０％回復\n" << endl;
        break;
    case 5:
        cout << List->players[PCount].player_skill_name << endl;
        cout << "\t\t\t\t\t       非常に低い確率で相手のターンスキップ\n" << endl;
        break;
    }

    line();
    return 0;
}
int Select_character(struct Player_List* List, struct Player* select, int* num, int* player)
{
    Player_List* L_Copy = List;
    int Char_Count = 0;
    int answer = 0;

    Char_Count = List->player_count;

    if (Char_Count == 1)
    {
        cout << "\t\t\t      少なくても二つ以上のお名前が必要です！\n" << endl;
        *num = 1;

        return 0;
    }
    else if (Char_Count != 0)
    {
        cout << "\t\t\t\tキャラクターを選択してください！" << endl;
        line();

        for (int i = 0; i < List->player_count; i++)
        {
            cout << "\t[" << i + 1 << ']' << '\t' << left << setw(32) << List->players[i].player_name;
            cout << "戦力 : " << List->players[i].player_power;
            cout << "\t能力 : " << List->players[i].player_skill_name << endl;
        }
        line();

        cin >> answer;
        if (answer < 1 || answer > List->player_count)
        {
            *num = 3;
            return 0;
        }
        *select = List->players[answer - 1];
        *player = answer;

        cout << "\n\t\t\t\t      ＿人人人人人人人＿" << endl;
        cout << "\t\t\t\t      ＞ トーナメントが ＜" << endl;
        cout << "\t\t\t\t      ＞   始まります！ ＜" << endl;
        cout << "\t\t\t\t      ￣Y^Y^Y^Y^Y^Y^Y^Y￣" << endl;
        cout << "\n\t\t\t        ＞＞　あなたのキャラクター　＜＜\n" << endl;
        cout << "\t\t\t\t\t名前 : " << select->player_name << '\n' << endl;
        cout << "\t\t\t\t\tATK  : " << select->player_ATK << endl;
        cout << "\t\t\t\t\tDEF  : " << select->player_DEF << endl;
        cout << "\t\t\t\t\t能力 : " << select->player_skill_name << '\n' << endl;
        line();

        return 0;
    }
    No_Char();
    *num = 1;

    return 0;
}
void Character_Stat(struct Player_List* List, int count, int* skill)
{
    int Player_count = count;
    int Length = List->players[Player_count].player_name.length();
    int atkPoint = 0;
    int defPoint = 0;
    int power = ascii_sum(List->players[Player_count].player_name.c_str());

    if (Length >= 20)
    {
        srand((Length * power) * 15);
        atkPoint = rand() % (500 - 300 + 1) + 300;
        srand(rand() % (Length * power) + atkPoint);
        defPoint = rand() % (100 - 50 + 1) + 50;
    }
    else if (Length >= 15)
    {
        srand((Length * power) * 15);
        atkPoint = rand() % (500 - 200 + 1) + 200;
        srand(rand() % (Length * power) + atkPoint);
        defPoint = rand() % (100 - 40 + 1) + 40;
    }
    else if (Length >= 10)
    {
        srand((Length * power) * 10);
        atkPoint = rand() % (500 - 100 + 1) + 100;
        srand(rand() % (Length * power) + atkPoint);
        defPoint = rand() % (100 - 30 + 1) + 30;
    }
    else if (Length >= 5)
    {
        srand((Length * power) * 5);
        atkPoint = rand() % (500 - 75 + 1) + 75;
        srand(rand() % (Length * power) + atkPoint);
        defPoint = rand() % (100 - 20 + 1) + 20;
    }
    else
    {
        srand(Length * power);
        atkPoint = rand() % (500 - 50 + 1) + 50;
        srand(rand() % (Length * power) + atkPoint);
        defPoint = rand() % (100 - 10 + 1) + 10;
    }

    List->players[Player_count].player_ATK = atkPoint;
    List->players[Player_count].player_DEF = defPoint;
    List->players[Player_count].player_power = ((atkPoint + defPoint) * power / 100);
    List->players[Player_count].player_HP = 100 * ((List->players[Player_count].player_power) / 100);
    List->players[Player_count].player_number = Player_count;

    srand(atkPoint + defPoint);
    *skill = rand() % 5 + 1;
    List->players[Player_count].player_skill_num = *skill;

    switch (*skill)
    {
    case 1:
        List->players[Player_count].player_skill_name = "ダブルチャンス";
        break;
    case 2:
        List->players[Player_count].player_skill_name = "ジャクシャ・ヒツメツ";
        break;
    case 3:
        List->players[Player_count].player_skill_name = "アイアンウィル";
        break;
    case 4:
        List->players[Player_count].player_skill_name = "一杯の余裕";
        break;
    case 5:
        List->players[Player_count].player_skill_name = "タイム・リワインダー";
        List->players[Player_count].Skill_Count = 2;
        break;
    }
}

void Tournament(struct Player_List* List, int player, int select_player)
{
    int wave = 2;
    int player_count = player;

    while (true)
    {
        vector<int> survivors;

        List->players[select_player - 1].player_rank++;

        for (int i = 0; i < player; i++)
        {
            if (List->players[i].player_rank == wave - 1 && i != select_player - 1)
                survivors.push_back(i);
        }

        if (survivors.size() <= 1)
            break;

        random_device rd;
        mt19937 g(rd());
        shuffle(survivors.begin(), survivors.end(), g);

        for (int i = 0; i + 1 < survivors.size(); i += 2)
        {
            // 6       //         0           // 6               3
            int winner = (rand() % 2 == 0) ? survivors[i] : survivors[i + 1];
            List->players[winner].player_rank = wave;
        }

        wave++;
    }
}
void CPU_Tournament(struct Player_List* List, int player, int select_player, int wave)
{
    int PLayer_Count = player;
    int select = select_player - 1;

    while (true)
    {
        vector<int> CPU;

        for (int i = 0; i < player; i++)
        {
            if (List->players[i].player_rank == wave && i != select)
                CPU.push_back(i);
        }

        if (CPU.size() == 0)
            break;

        random_device rd;
        mt19937 g(rd());
        shuffle(CPU.begin(), CPU.end(), g);

        for (int i = 0; i + 1 < CPU.size(); i += 2)
        {
            int winner = (rand() % 2 == 0) ? CPU[i] : CPU[i + 1];
            List->players[winner].player_rank = wave + 1;
        }

        wave++;
    }
}

void Select_Enemy(struct Player_List List, struct Player* enemy, int wave, int select_player)
{
    vector<int> Enemy;

    for (int i = 0; i < List.player_count; i++)
    {
        if (List.players[i].player_rank == wave && i != select_player - 1)
            Enemy.push_back(i);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(Enemy.begin(), Enemy.end(), g);

    *enemy = List.players[Enemy.at(0)];
}
void Battle_Stat(struct Player Human, struct Player CPU, int Wave, int PHP, int AHP)
{
    cout << "\n\t\t\t\t\t>> Wave : " << Wave << " <<\n" << endl;

    cout << "\t[Player]  " << left << setw(32) << Human.player_name
        << "[HP] : " << left << setw(8) << PHP
        << "[ATK] : " << left << setw(8) << Human.player_ATK
        << "[DEF] : " << left << setw(8) << Human.player_DEF << endl;
    cout << "\t[能力] : " << Human.player_skill_name << "\n" << endl;

    cout << "\t[Enemy]   " << left << setw(32) << CPU.player_name
        << "[HP] : " << left << setw(8) << AHP
        << "[ATK] : " << left << setw(8) << CPU.player_ATK
        << "[DEF] : " << left << setw(8) << CPU.player_DEF << endl;
    cout << "\t[能力] : " << CPU.player_skill_name << "\n" << endl;
    line();
}
void Battle(struct Player* Human, struct Player* CPU,
    int* PHP, int PATK, int PDEF, int* EHP, int EATK, int EDEF,
    int* SCount, int* FCount, int* ESCount, int* Result)
{
    srand((unsigned)time(nullptr));

    int Todo = 0, Skill_Percent = 0, Enemy_Skill_Do = 0;
    bool Player_Turn_Skip_Count = false, CPU_Turn_Skip_Count = false, Enemy_Skill = false;

    Todo_List();
    cin >> Todo;
    line();

    //CPU Turn
    if (!(*ESCount == 0))
        Enemy_Skill_Do = rand() % 3;
    else
        Enemy_Skill_Do = rand() % 2;
    // Attack Or Defense
    switch (Enemy_Skill_Do)
    {
    case 0:
        EATK = static_cast<int>(EATK * 1.2);
        break;
    case 1:
        EDEF *= 2;
        break;
    }

    // Use Skill
    if (Enemy_Skill_Do == 2)
    {
        Enemy_Skill_Do = rand() % 100 + 1;
        switch (CPU->player_skill_num)
        {
        case 1:
            if (!(Enemy_Skill_Do >= 10 && Enemy_Skill_Do <= 60))
                break;
            Enemy_Skill = true;
            *ESCount -= 1;
            break;
        case 2:
            if (!(Enemy_Skill_Do >= 35 && Enemy_Skill_Do <= 65))
                break;
            Enemy_Skill = true;
            *ESCount -= 1;
            break;
        case 3:
            if (!(Enemy_Skill_Do >= 40 && Enemy_Skill_Do <= 90))
                break;
            Enemy_Skill = true;
            *ESCount -= 1;
            break;
        case 4:
            if (!(Enemy_Skill_Do >= 25 && Enemy_Skill_Do <= 75))
                break;
            Enemy_Skill = true;
            *ESCount -= 1;
            break;
        case 5:
            if (!(Enemy_Skill_Do >= 45 && Enemy_Skill_Do <= 55))
                break;
            Player_Turn_Skip_Count = true;
            *ESCount -= 1;
            break;
        }
    }

    //Player Turn
    if (Player_Turn_Skip_Count == true)
    {
        cout << "\n\t相手の能力「タイム・リワインド」発動！！" << endl;
        cout << "\t時間が止まって動きません！！ やられます！" << endl;
    }
    else if (Todo >= 1 && Todo <= 3)
    {
        // Attack or Defense
        switch (Todo)
        {
        case 1:
            cout << "\n\t全力攻撃！！ ATKが１．２倍になります！\n" << endl;
            PATK = static_cast<int>(PATK * 1.2);
            line();
            break;
        case 2:
            cout << "\n\t全身防御！！ DEFが２倍になります！\n" << endl;
            PDEF *= 2;
            line();
            break;
        }
        // Use Skill
        if (Todo == 3 && *SCount == 0)
            cout << "\t気力足りなくて何もできない！ もう能力発動ができません！" << endl;
        else if (Todo == 3 && *SCount != 0)
        {
            Skill_Percent = rand() % 100 + 1;
            Skill_Percent += *FCount;
            switch (Human->player_skill_num)
            {
            case 1:
                if (!(Skill_Percent >= 10 && Skill_Percent <= 60))
                {
                    cout << "\n\t集中が乱れて能力発動ができませんでした！" << endl;
                    *FCount += 10;
                    break;
                }
                cout << "\n\t\t\t\t    ＞＞＞ 能力発動！ ＜＜＜\n"
                    << "\t\t\t\t       [" << Human->player_skill_name << "]\n" << endl;
                cout << "\t攻撃力が２倍になります！ ヤッタ！" << endl;
                PATK *= 2;
                *SCount -= 1;
                *FCount = 0;
                break;
            case 2:
                if (!(Skill_Percent >= 35 && Skill_Percent <= 65))
                {
                    cout << "\n\t集中が乱れて能力発動ができませんでした！" << endl;
                    *FCount += 5;
                    break;
                }
                cout << "\n\t\t\t\t    ＞＞＞ 能力発動！ ＜＜＜\n"
                    << "\t\t\t\t    [" << Human->player_skill_name << "]\n" << endl;
                cout << "\t相手の防御力が０になります！ 「弱者必滅」だ！ " << endl;
                EDEF = 0;
                *SCount -= 1;
                *FCount = 0;
                break;
            case 3:
                if (!(Skill_Percent >= 40 && Skill_Percent <= 90))
                {
                    cout << "\n\t集中が乱れて能力発動ができませんでした！" << endl;
                    *FCount += 10;
                    break;
                }
                cout << "\n\t\t\t\t    ＞＞＞ 能力発動！ ＜＜＜\n"
                    << "\t\t\t\t       [" << Human->player_skill_name << "]\n" << endl;
                cout << "\t防御力が４倍になります！ 痛くない！" << endl;
                PDEF *= 4;
                *SCount -= 1;
                *FCount = 0;
                break;
            case 4:
                if (!(Skill_Percent >= 25 && Skill_Percent <= 75))
                {
                    cout << "\n\t集中が乱れて能力発動ができませんでした！" << endl;
                    *FCount += 10;
                    break;
                }
                cout << "\n\t\t\t\t    ＞＞＞ 能力発動！ ＜＜＜\n"
                    << "\t\t\t\t\t [" << Human->player_skill_name << "]\n" << endl;
                cout << "\t回復します！ イイ感じ！" << endl;
                *PHP += (*PHP / 100) * 20;
                *SCount -= 1;
                *FCount = 0;
                break;
            case 5:
                if (!(Skill_Percent >= 45 && Skill_Percent <= 55))
                {
                    cout << "\n\t集中が乱れて能力発動ができませんでした！" << endl;
                    *FCount += 2;
                    break;
                }
                cout << "\n\t\t\t\t    ＞＞＞ 能力発動！ ＜＜＜\n"
                    << "\t\t\t\t    [" << Human->player_skill_name << "]\n" << endl;
                CPU_Turn_Skip_Count = true;
                *SCount -= 1;
                *FCount = 0;
                break;
            }
            cout << endl;
            line();
        }
    }
    else
        cout << "\n\t間違い行動！！ 外れました！ 何もできない！" << endl;

    // CPU Turn Skip And Use Skill
    if (CPU_Turn_Skip_Count == true)
    {
        cout << "\n\t\t\t 「槍見たいな風がやわらかくなり、時間が止まってきた」\n" << endl;
        cout << "\t\t\t相手の動きを制圧しました！！ 相手はもう何もできません！" << endl;
    }
    else if (Enemy_Skill == true)
    {
        switch (CPU->player_skill_num)
        {
        case 1:
            cout << "\n\t相手が「ダブルチャンス」を発動！" << endl;
            cout << "\t相手の攻撃力が２倍になります！ 絶対痛そう..." << endl;
            EATK *= 2;
            break;
        case 2:
            cout << "\n\t相手が「ジャクシャ・ヒツメツ」を発動！" << endl;
            cout << "\t防御力が０になります！マズイ！" << endl;
            PDEF = 0;
            break;
        case 3:
            cout << "\n\t相手が「アイアンウィル」を発動！" << endl;
            cout << "\t相手の防御力が４倍になります！ 堅い！" << endl;
            EDEF *= 4;
            break;
        case 4:
            cout << "\n\t相手が「一杯の余裕」を発動！" << endl;
            *EHP += (*EHP / 100) * 20;
            cout << "\t相手が回復します！" << endl;
            break;
        }
        cout << endl;
        line();
    }

    // Show Battle Log

    // Enemy Get Damage
    if (Player_Turn_Skip_Count == false)
    {
        cout << endl;
        if (EDEF == 0)
        {
            cout << "\tスキだらけだ！！全力攻撃！！" << endl;
            cout << "\t相手に" << PATK << "ダメージ！！ どうだ！" << endl;
            *EHP -= PATK;
        }
        else if (EDEF - PATK >= 0)
        {
            cout << "\t相手に" << PATK << "ダメージで攻撃！！" << endl;
            cout << "\n\t...が、相手の完全防御！ ATKが足りません！" << endl;
        }
        else
        {
            cout << "\t相手に" << PATK << "ダメージで攻撃！！" << endl;
            cout << "\t相手が" << EDEF << "のダメージをブロックしで"
                << PATK - EDEF << "ダメージを受けた！" << endl;
            *EHP -= (PATK - EDEF);
        }
        cout << endl;
        line();
        if (*EHP <= 0)
        {
            *Result = 1;
            return;
        }
    }

    // Player Get Damage
    if (CPU_Turn_Skip_Count == false)
    {
        cout << endl;
        if (PDEF == 0)
        {
            cout << "\t相手の気に圧倒されました！ 怖い！" << endl;
            cout << "\t相手から" << EATK << "ダメージ！！" << endl;
            cout << "\tＣＲＩＴＩＣＡＬ！！死ぬほど痛い！！！" << endl;
            *PHP -= EATK;
        }
        else if (PDEF - EATK > 0)
        {
            cout << "\t相手が" << EATK << "ダメージで攻撃！！" << endl;
            cout << "\n\t...が、防御して耐えました！" << endl;
        }
        else
        {
            cout << "\t相手の反撃！" << endl;
            cout << "\t相手が" << EATK << "ダメージで攻撃！！" << endl;
            cout << '\t' << PDEF << "のダメージをブロックして"
                << EATK - PDEF << "ダメージを受けた！ 痛いなー" << endl;
            *PHP -= (EATK - PDEF);
        }
        cout << endl;
        line();
        if (*PHP <= 0)
        {
            *Result = 0;
            return;
        }
    }

}
void Lets_Play(struct Player_List* List, struct Player* Human, struct Player* CPU, int Round)
{
    int Player_ATK = Human->player_ATK, Player_DEF = Human->player_DEF, Player_HP = Human->player_HP;
    int CPU_ATK = CPU->player_ATK, CPU_DEF = CPU->player_DEF, CPU_HP = CPU->player_HP;
    int Skill_Count = Human->Skill_Count, Fail_Count = 0, Enemy_Skill_Count = CPU->Skill_Count;

    int Win = 2; // True(1) = Player Win / False(0) = CPU Win
    int Player_Num = 0, Enemy_Num = 0;

    int Wave = 1;

    while (1)
    {
        Battle_Stat(*Human, *CPU, Wave, Player_HP, CPU_HP);
        Battle(Human, CPU, &Player_HP, Player_ATK, Player_DEF,
            &CPU_HP, CPU_ATK, CPU_DEF, &Skill_Count, &Fail_Count, &Enemy_Skill_Count, &Win);
        if (Win != 2)
            break;
        Wave++;
        if (Wave > 50)
        {
            cout << "\n\t\t\t\t  ＞＞　ＴＩＭＥＯＶＥＲ　＜＜\n" << endl;
            cout << "\t\t\t\t残ったＨＰにより勝者を決まります！\n" << endl;
            cout << "\t\t[プレイヤーＨＰ] : " << left << setw(24) << Player_HP
                << "[相手のＨＰ] : " << CPU_HP << '\n' << endl;
            Win = Player_HP > CPU_HP ? true : false;
            line();
            break;
        }
    }
    switch (Win)
    {
    case 0:
        cout << "\n\t\t\t\t      体に力が入らない..." << endl;
        cout << "\t\t\t\t      ＨＰが0になりました。" << endl;
        cout << "\n\t\t\t\t      倒れた...負けました！\n" << endl;
        line();
        List->players[CPU->player_number].player_rank = Round + 1;
        List->players[Human->player_number].player_rank = Round;
        break;
    case 1:
        cout << "\n\t\t\t\t    相手が倒れた！" << endl;
        cout << "\t\t\t\t    相手ＨＰが0になりました。" << endl;
        cout << "\n\t\t\t\t    ヤッターカッター！\n" << endl;
        line();
        break;
    }
}
void Ranking(struct Player_List List, int Round, int select_player)
{
    int Rank = Round;
    int PSelect = select_player - 1, PRank = 0;
    cout << "\n\t\t\t\t  ＞＞　ＧＡＭＥＯＶＥＲ　＜＜\n" << endl;
    cout << "\t\t\t\t      「ＲＡＮＫＩＮＧ」\n" << endl;

    for (int i = 1; i <= Rank; i++)
    {
        for (int j = 0; j < List.player_count; j++)
        {
            if (List.players[j].player_rank == Round)
            {
                cout << "\t\t\tPlayer Name : " << left << setw(24) << List.players[j].player_name << "Rank " << i << endl;
                if (List.players[j].player_number == List.players[PSelect].player_number)
                    PRank = i;
            }
        }
        cout << endl;
        Round--;
    }
    line();
    cout << "\n\t\tあなたのお名前 : " << left << setw(32)
        << List.players[PSelect].player_name
        << "あなたの順位 : " << PRank << '\n' << endl;
    line();
}