#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstring>


#pragma comment(lib, "winmm.lib")

using namespace std;

const int WIDTH = 30; const int HEIGHT = 30; const int NUMBEREVIL = 20, NUMBERESTUS = 10, NUMBERLOOT = 3;

int hard = 1;
int needExp = 100;
double discount = 0;
int backpackCount = 0;

struct coordinates { int x, y; bool visible; } position, dealerPosition, estusPosition[NUMBERESTUS];
struct loot { int power, protection, exp; coordinates position; } helmet[NUMBERLOOT], armor[NUMBERLOOT], sword[NUMBERLOOT];
struct shop { int rarity, price; char name[20];};
struct storage {shop thing; loot ammunition;} backpack[50];
struct attribute { int hp, estus, money, maxHp, exp, level; double power, protection; } hero;
struct characteristics { int hp, power, protection, exp; shop stuff; coordinates position; bool life; } evil[NUMBEREVIL], boss;


void reading(string);
int startig_menu();
int difficulty();
void beggining();
void map(int, int);
void inventory();
void openBackpack(int);
void dealer();
bool checker(bool*);
int roll_dice();
void random();
bool battle(characteristics&);

int main()
{
    position.x = 15; position.y = 15;
    hero.hp = 100; hero.maxHp = 100;  hero.estus = 0; hero.money = 0; hero.power = 1;  hero.protection = 1; hero.level = 1; hero.exp = 0;
    setlocale(LC_ALL, "Russian");

    if(!startig_menu()) return 0;
    srand(time(0));
    random();
    beggining();

    char exit = ' ';
    bool life = 1;
    needExp *= hard;
    while (exit != 0x1B)
    {
        if (!checker(&life)) break;
        map(position.x, position.y);

        exit = _getch();

        switch (exit)
        {
        case 'w': if (position.y > 1) position.y--; break;
        case 's': if (position.y < HEIGHT - 2) position.y++; break;
        case 'a': if (position.x > 1) position.x--; break;
        case 'd': if (position.x < WIDTH - 2) position.x++; break;
        case 'i': inventory(); break;
        case 0x1B: system("cls"); reading("goodbye");
        }
    }
    
}

void reading(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        cout << text[i];
        Sleep(40);
        if (GetAsyncKeyState('\r'))
        {
            _getch();
            for (int j = i; j < text.length(); j++)
                cout << text[j];
            break;
        }
    }
    Sleep(250);
}
void menu()
{
    system("cls");

    cout << R"(


                                                 _____   _____     ___     _____    _____    _   _
                                                |  _  | |  _  |   / _ \   |  ___|  |  _  |  | \ | |
                                                | | | | | | | |  / /_\ \  |  _ \   | | | |  | \ \ |
                                                | | | | | |_| |  |  _  |  | | | |  | | | |  | | | |
                                                | |/ /  |    /   | | | |  | |_| |  | |_| |  | |\  |
                                                |___/   |_| \_\  \_| |_/  |_____|  |_____|  |_| \_|
)";
    cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  S - START                     |
                                                |                                                |
                                                --------------------------------------------------
)";
    cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                D - DIFFICULTY                  |
                                                |                                                |
                                                --------------------------------------------------
)";
    cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                    ESC - EXIT                  |
                                                |                                                |
                                                --------------------------------------------------
)";
}
int startig_menu()
{
    mciSendString(L"open \"phone.mp3\" type mpegvideo alias phone", NULL, 0, NULL);
    //mciSendString(L"open \"evil_laugh.mp3\" type mpegvideo alias evil_laugh", NULL, 0, NULL);
    mciSendString(L"play phone", NULL, 0, NULL);
    menu();
    char menu = ' ';
    while (menu != 's')
    {
        menu = _getch();

        switch (menu)
        {
        case 's': return 1;
        case 'd': hard = difficulty(); break;
        case 0x1B: system("cls"); reading("Goodbye"); return 0; break;
        }
    }
}
int difficulty()
{

    system("cls");

    cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  1 - ИВАН ЗОЛО                 |
                                                |                                                |
                                                --------------------------------------------------
)";   cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  2 - ЛОШОК                     |
                                                |                                                |
                                                --------------------------------------------------
)";   cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  3 - МАЛЬЧИК                   |
                                                |                                                |
                                                --------------------------------------------------
)";   cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  4 - СИЛАЧ                     |
                                                |                                                |
                                                --------------------------------------------------
)";   cout << R"(

                                                --------------------------------------------------
                                                |                                                |
                                                |                  5 - БЕЛАРУС                   |
                                                |                                                |
                                                --------------------------------------------------
)";

    int difficulty = 1;
    while (true)
    {

        difficulty = _getch();

        switch (difficulty)
        {
        case '1': menu(); return 1; break;
        case '2': menu(); return 2; break;
        case '3': menu(); return 3; break;
        case '4': menu(); return 4; break;
        case '5': menu(); return 5; break;
        }
    }
}
void beggining() 
{
  system("cls");
  reading("Когда-то этот мир дышал в такт биению драконьих сердец — величественных и древних, как само время. Их крылья держали небесный свод, а пламя, бьющееся в их груди, согревало землю. Люди строили города у подножия их тронов, молясь о капле их милости. Но алчность разъедала души, как ржавчина — сталь.\n\nАркмаги, провозгласившие себя новыми богами, начали эксперименты. Они вскрывали драконов живьем, вплетали их сущность в механизмы, в плоть, в камни. Первая Драконья Клеть заработала в столице, ее черные трубы изрыгали дым, затмевающий солнце. Потом появились десятки, сотни... Мир захлебнулся в искусственном пламени.\n\nИ тогда Бездна ответила...");
  Sleep(1000);
}
void map(int px, int py) {
    system("cls"); // Очищаем консоль

    for (int y = 0; y < HEIGHT; y++) {
        cout << "\t\t\t\t";
        for (int x = 0; x < WIDTH; x++) {
            // Проверка границ
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                cout << "#";
                continue;
            }

            // Проверка игрока (наивысший приоритет)
            if (x == px && y == py) {
                cout << "P";
                continue;
            }

            // Проверка босса (второй по приоритету)
            if (!boss.life && x == boss.position.x && y == boss.position.y) {
                cout << "B";
                continue;
            }

            // Проверка торговца (третий по приоритету)
            if (dealerPosition.visible && x == dealerPosition.x && y == dealerPosition.y) {
                cout << "D";
                continue;
            }

            // Проверка обычных врагов
            bool isEnemy = false;
            for (int i = 0; i < NUMBEREVIL; i++) {
                if (!evil[i].life && x == evil[i].position.x && y == evil[i].position.y) {
                    cout << "X";
                    isEnemy = true;
                    break;
                }
            }
            if (isEnemy) continue;

            // Проверка лута
            bool isLoot = false;
            for (int i = 0; i < NUMBERLOOT; i++) {
                if ((helmet[i].position.visible && x == helmet[i].position.x && y == helmet[i].position.y) ||
                    (armor[i].position.visible && x == armor[i].position.x && y == armor[i].position.y) ||
                    (sword[i].position.visible && x == sword[i].position.x && y == sword[i].position.y)) {
                    cout << "L";
                    isLoot = true;
                    break;
                }
            }
            if (isLoot) continue;

            // Проверка эстуса
            bool isEstus = false;
            for (int i = 0; i < NUMBERESTUS; i++) {
                if (estusPosition[i].visible && x == estusPosition[i].x && y == estusPosition[i].y) {
                    cout << "E";
                    isEstus = true;
                    break;
                }
            }
            if (isEstus) continue;

            // Пустое пространство
            cout << " ";
        }
        cout << endl;
    }

    cout << "\n\n\t\t\twasd - Движение / i - Инвентарь / esc - Выход";
}
void inventory()
{
    char end = ' ';
    while (end != 0x1B)
    {
        system("cls");
        cout << "\n\n\n-------------------------------------------------------------------------------------\n\t\t\tИНВЕНТАРЬ"
            << "\n\nВаш Уровень : " << hero.level << "\n\nВаше ХП : " << hero.hp << " / " << hero.maxHp
            << "\n\nВаша сила : " << hero.power << "\n\nВаша защита : " << hero.protection
            << "\n\nКОЛ - ВО Эстуса : " << hero.estus << "\n\nКОЛ - ВО Вещей в рюкзаке : " << backpackCount
            << "\n\nКОЛ - ВО опыта : " << hero.exp << " / " << needExp << "\n\n------------------------------------------------------------------------------------- "
            << "\n\nh - heal / b - backpack / esc - выход \n\n------------------------------------------------------------------------------------- ";
        end = _getch();

        switch (end)
        {
        case 'h': if (hero.estus > 0) { hero.hp += 50; hero.estus--; if (hero.hp > hero.maxHp) hero.hp = hero.maxHp; } break;
        case 'b': openBackpack(backpackCount); break;
        }
    }
};
void openBackpack(int backpackCount) 
{
    system("cls");

    char exit = ' ';
    while (exit != 0x1B)
    {
        for (int i = 0; i < backpackCount; i++)
        {
            cout << "\n[ " << i + 1 <<" ] " << backpack[i].thing.name;
            cout << "\tРедкость: " << backpack[i].thing.rarity;
            cout << "\tЦена: " << backpack[i].thing.price << "\n";
        }
        cout << "\nesc - Выход";
        exit = _getch();
    }
}
bool checker(bool* life)
{

    if(hero.exp > needExp)
    {
        hero.level++; hero.exp -= needExp; hero.maxHp += 50; discount += 0.05; hero.hp = hero.maxHp; hero.power++; hero.protection++; needExp *= hero.level * hard;
        system("cls");
        reading("\n\nПоздравляю герой, пройдя такой долгий путь вы достигли "); cout << hero.level; reading("-го уровня. Слава о вас расходится всё дальше и дальше.\n\nВаши характеристики были изменены");
    }

    if (position.x == boss.position.x && position.y == boss.position.y && boss.life == 1)
    {
        system("cls");
        reading("\n\nВы чувствуете в этой местности что-то загадочное. Вы уверены, что хотите продолжить обыскивать эту местность?\n\nY - Да / N - Нет");
        char exit = ' ';
        exit = _getch();
        if (exit == 'y') *life = battle(boss);
    }

    for (int i = 0; i < NUMBEREVIL; i++)
        if (position.x == evil[i].position.x && position.y == evil[i].position.y && evil[i].life == 1)
            *life = battle(evil[i]);


    for (int i = 0; i < NUMBERESTUS; i++)
        if (position.x == estusPosition[i].x && position.y == estusPosition[i].y) {
            system("cls"); reading("\n\nВами обнаружен бутэль эстуса\n\n"); hero.estus++; estusPosition[i].x = 0; estusPosition[i].y = 0;
        }

    for (int i = 0; i < NUMBERLOOT; i++)
        if (position.x == helmet[i].position.x && position.y == helmet[i].position.y) {
            system("cls"); 
            mciSendString(L"open \"loot.mp3\" type mpegvideo alias loot", NULL, 0, NULL);
            mciSendString(L"play loot", NULL, 0, NULL);
            reading("\n\nСреди руин древнего храма, в лунном свете, мерцает забытая реликвия — Древний Шлем Агонии.\n\nПолучено "); cout << helmet[i].exp; reading(" опыта\n\nВаши характеристики изменились\n\n"); hero.power += helmet[i].power; hero.protection += helmet[i].protection; hero.exp += helmet[i].exp; helmet[i].position.x = 0; helmet[i].position.y = 0;
            mciSendString(L"close loot", NULL, 0, NULL);
        }

    for (int i = 0; i < NUMBERLOOT; i++)
        if (position.x == armor[i].position.x && position.y == armor[i].position.y) {
            system("cls");
            mciSendString(L"open \"loot.mp3\" type mpegvideo alias loot", NULL, 0, NULL);
            mciSendString(L"play loot", NULL, 0, NULL);
            reading("\n\nВ глубине проклятого склепа, под слоями пыли и паутины, лежит Древняя Броня. \n\nПолучено "); cout << armor[i].exp; reading(" опыта\n\nВаши характеристики изменились\n\n"); hero.power += armor[i].power; hero.protection += armor[i].protection; hero.exp += armor[i].exp; armor[i].position.x = 0; armor[i].position.y = 0;
            mciSendString(L"close loot", NULL, 0, NULL);
        }

    for (int i = 0; i < NUMBERLOOT; i++)
        if (position.x == sword[i].position.x && position.y == sword[i].position.y) {
            system("cls"); 
            mciSendString(L"open \"loot.mp3\" type mpegvideo alias loot", NULL, 0, NULL);
            mciSendString(L"play loot", NULL, 0, NULL);
            reading("\n\nСреди обломков древнего алтаря, пронзая каменную плиту, торчит Клинок Вечной Песни.\n\nПолучено "); cout << sword[i].exp; reading(" опыта\n\nВаши характеристики изменились\n\n"); hero.power += sword[i].power; hero.protection += sword[i].protection; hero.exp += sword[i].exp; sword[i].position.x = 0; sword[i].position.y = 0;
            mciSendString(L"close loot", NULL, 0, NULL);
        }

    if (position.x == dealerPosition.x && position.y == dealerPosition.y)
    {
        dealerPosition.visible = 1;
        dealer();
    }
    
    if (!boss.life)
    {
        reading("\n\nПоследний удар меча - и исполинское тело рушится на землю, сотрясая камни под вашими ногами. Кровь, густая и темная, как расплавленный обсидиан, медленно растекается между трещин в камнях. Его крылья, еще недавно затмевавшие солнце, теперь представляют лишь жалкое зрелище - переломанные кости, покрытые порванной кожей.\n\nВы тяжело дышите, ощущая, как адреналин постепенно покидает ваше тело. Дождь из пепла начинает падать с неба, покрывая все вокруг серым саваном. Кажется, сам мир оплакивает падение этого величественного существа.");
        return 0;
    }
    return *life;
};
void draw_dice(int value) 
{
    switch (value) 
    {
    case 1:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            |       |
                            |   *   |
                            |       |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    case 2:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            | *     |
                            |       |
                            |     * |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    case 3:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            | *     |
                            |   *   |
                            |     * |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    case 4:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            | *   * |
                            |       |
                            | *   * |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    case 5:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            | *   * |
                            |   *   |
                            | *   * |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    case 6:
        cout << R"(
-----------------------------------------------------------------------------------------------------------------------------------------------------


                            |-------|
                            | *   * |
                            | *   * |
                            | *   * |
                            |-------|


-----------------------------------------------------------------------------------------------------------------------------------------------------
)";
        break;
    }
}
void draw_evil(int value)
{
    switch (value)
    {
    case 1: // Классический гоблин
        cout << R"(
                                ,-----,
                               / .   . \
                              |    ▽    | 
                              \  '---'  /
                               \_______/
                                /     \
                               /       \
)";
        break;

    case 2:
        cout << R"(
                               /\____/\
                              /   <>   \
                             |  \____/  |
                              \   ||   /
                               \__||__/
                                  **
                                 /__\
)";
        break;

    case 3:
        cout << R"(
                               .-./'-'\.-.
                              /   \   /   \
                              |  (o) (o)  |
                               \    "    /
                                \__==__/
                                 _/  \_
                                /      \
)";
        break;

    case 4: // Раненый гоблин
        cout << R"(
                                o   o
                               / \_/ \
                              |       |
                              |  X X  |
                               \ \_/ /
                                \___/
)";
        break;

    case 5: // Гоблин-лучник
        cout << R"(
                                 __
                                /  \
                               | () |
                                \__/
                                 /|
                               _/ |_
                              /   / \
)";
        break;

    case 6: // Гоблин-лучник
        cout << R"(
                                ~~~~~~~
                               ~  o o  ~
                              ~   ~~~   ~ 
                               ~  \_/  ~
                                ~_____~
)";
        break;

    case 7: // босс
        cout << R"(
                                   ______________
                            ,===:'.,            `-._
                                 `:.`---.__         `-._
                                   `:.     `--.         `.
                                     \.        `.         `.
                             (,,(,    \.         `.   ____,-`.,
                          (,'     `/   \.   ,--.___`.'
                      ,  ,'  ,--.  `,   \.;'         `
                       `{D, {    \  :    \;
                         V,,'    /  /    //
                         j;;    /  ,' ,-//.    ,---.      ,
                         \;'   /  ,' /  _  \  /  _  \   ,'/
                               \   `'  / \  `'  / \  `.' /
                                `.___,'   `.__,'   `.__,'  
)";
        break;
    }
}
void draw_dealer()
{
    system("cls");
    cout << "Ваша СКИДКА: " << discount * 100 << "%\t\t";
    cout << R"(
                      ____      
                   .-'    `-.                          1. Купить товар
                 .'          `.                        2. Продать товар
                /   O      O   \                       3. Купить информацию
               :           `    :
               |     _______    |                      ESC - Выход
               :   .'       `.  ;  
                \_/  $$$$$$  \_/   
                / \__________/ \   
               /               \  
              / /|           |\ \ 
             /_/ |___________| \_\
             \_\_|           |_/ /
              \__\___________/__/    
   ____________(_)__________(_)__________________________________________________      
         _______|___________|_______
        |                             |
        |  "Добро пожаловать, герой!  |
        |  Всё по справедливой цене!" |
        |_____________________________|       

)";
}
void dealer()
{
    char exit = ' ';
    while (exit != 0x1B)
    {
        draw_dealer();
        exit = _getch();

        switch (exit)
        {
        case '1': break;
        case '2': break; 
        case '3': break;
        }

    }
}
int roll_dice() 
{
    srand(time(0));
    for (int i = 0; i < 10; i++) 
    {
        system("cls"); 
        draw_dice(rand() % 6 + 1); 
        Sleep(100); 
    }
    int result = rand() % 6 + 1;
    system("cls");
    draw_dice(result);
    Sleep(1000);

    return result;
}
void random() 
{
    boss.position.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
    boss.position.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
    boss.hp = 200 * hard;
    boss.power = 5 * hard;
    boss.protection = 5 * hard;
    boss.exp = 500 * hard;
    boss.stuff.rarity = 10;
    boss.life = 1;

    for (int i = 0; i < NUMBEREVIL; i++)
    {
        evil[i].position.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
        evil[i].position.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
        evil[i].position.visible = 0;
        evil[i].hp = (rand() % (50 - 10 + 1) + 10) * hard;
        evil[i].power = (rand() % (3 - 1 + 1) + 1) * hard;
        evil[i].protection = (rand() % (3 - 1 + 1) + 1) * hard;
        evil[i].exp = 10 * evil[i].power * evil[i].protection * hard;
        evil[i].stuff.rarity = evil[i].power * evil[i].protection / hard / hard;
        evil[i].stuff.price = 100+(evil[i].hp * evil[i].stuff.rarity);
        evil[i].life = 1;
    }

    strcpy(evil[1].stuff.name, "Счастливая лапка");
    strcpy(evil[2].stuff.name, "Широкая шкура");
    strcpy(evil[3].stuff.name, "Хрусталь глаза");
    strcpy(evil[4].stuff.name, "Осколки черепа");
    strcpy(evil[5].stuff.name, "Кусок плоти");
    strcpy(evil[6].stuff.name, "Счастливая лапка");
    strcpy(evil[7].stuff.name, "Широкая шкура");
    strcpy(evil[8].stuff.name, "Хрусталь глаза");
    strcpy(evil[9].stuff.name, "Осколки черепа");
    strcpy(evil[10].stuff.name, "Кусок плоти");
    strcpy(evil[11].stuff.name, "Счастливая лапка");
    strcpy(evil[12].stuff.name, "Кусок плоти");
    strcpy(evil[13].stuff.name, "Широкая шкура");
    strcpy(evil[14].stuff.name, "Хрусталь глаза");
    strcpy(evil[15].stuff.name, "Осколки черепа");
    strcpy(evil[16].stuff.name, "Счастливая лапка");
    strcpy(evil[17].stuff.name, "Счастливая лапка");
    strcpy(evil[18].stuff.name, "Широкая шкура");
    strcpy(evil[19].stuff.name, "Хрусталь глаза");
    strcpy(evil[20].stuff.name, "Осколки черепа");


    dealerPosition.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
    dealerPosition.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
    dealerPosition.visible = 0;

    for (int i = 0; i < NUMBERESTUS; i++)
    {
        estusPosition[i].x = rand() % (WIDTH - 2 - 1 + 1) + 1;
        estusPosition[i].y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
        estusPosition[i].visible = 0;
    }
    for (int i = 0; i < NUMBERLOOT; i++)
    {
        helmet[i].position.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
        helmet[i].position.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
        helmet[i].position.visible = 0;
        helmet[i].power = rand() % 1;
        helmet[i].protection = rand() % 3;
        helmet[i].exp = (rand() % 40+10) * hard;
    }

    for (int i = 0; i < NUMBERLOOT; i++)
    {
        armor[i].position.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
        armor[i].position.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
        armor[i].position.visible = 0;
        armor[i].power = rand() % 1;
        armor[i].protection = rand() % 3;
        armor[i].exp = (rand() % 40 + 10) * hard;
    }

    for (int i = 0; i < NUMBERLOOT; i++)
    {
        sword[i].position.x = rand() % (WIDTH - 2 - 1 + 1) + 1;
        sword[i].position.y = rand() % (HEIGHT - 2 - 1 + 1) + 1;
        sword[i].position.visible = 0;
        sword[i].power = rand() % 3;
        sword[i].protection = rand() % 1;
        sword[i].exp = (rand() % 40 + 10) * hard;
    }
}
void attack(int power, int protection, int& hp)
{
    mciSendString(L"open \"goodHit.mp3\" type mpegvideo alias goodHit", NULL, 0, NULL);
    mciSendString(L"open \"badHit.mp3\" type mpegvideo alias badHit", NULL, 0, NULL);

    char battle = ' ';
    int damage = 0, defense = (rand() % (10 - 0 + 1) + 0)*protection;
    battle = _getch();
    switch (battle)
    {
    case 'f': damage = (roll_dice() + 6) * hero.power; if (damage > defense) { mciSendString(L"play goodHit", NULL, 0, NULL); damage -= defense; hp -= damage; reading("\n\n\t\t\tВы нанесли "); cout << damage; reading(" урона\n\n"); }
            else { mciSendString(L"play badHit", NULL, 0, NULL); reading("\n\n\t\t\tВы не попали\n\n"); } break;
    case 'l': damage = (roll_dice() + roll_dice() + roll_dice()) * hero.power; if (damage > defense) { mciSendString(L"play goodHit", NULL, 0, NULL); damage -= defense; hp -= damage; reading("\n\n\t\t\tВы нанесли "); cout << damage; reading(" урона\n\n"); }
            else { mciSendString(L"play badHit", NULL, 0, NULL); reading("\n\n\t\t\tВы не попали\n\n");} break;
    case 'h': if (hero.estus > 0) { hero.hp += 50; hero.estus--; if (hero.hp > hero.maxHp) hero.hp = hero.maxHp; }
            else { reading("\nНе хватает флясок\n"); } break;
    }

    mciSendString(L"close goodHit", NULL, 0, NULL);
    mciSendString(L"close badHit", NULL, 0, NULL);
}
void evil_attack(int power, int protection, int& hp)
{

    mciSendString(L"open \"goodHit.mp3\" type mpegvideo alias goodHit", NULL, 0, NULL);
    mciSendString(L"open \"badHit.mp3\" type mpegvideo alias badHit", NULL, 0, NULL);

    char battle = ' ';
    int damage = (rand() % (10 - 0 + 1) + 0) * power, defense = (rand() % (10 - 0 + 1) + 0) * protection;
    if (damage > defense) { mciSendString(L"play goodHit", NULL, 0, NULL); damage -= defense; reading("\n\n\t\t\tВам нанесли "); cout << damage;  reading(" урона\n\n"); hp -= damage; }
    else { mciSendString(L"play badHit", NULL, 0, NULL); reading("\n\n\t\t\tПо вам промохнулись\n\n"); }

    mciSendString(L"close goodHit", NULL, 0, NULL);
    mciSendString(L"close badHit", NULL, 0, NULL);
}
bool battle(characteristics& evil)
{
    system("cls");
    mciSendString(L"stop phone", NULL, 0, NULL);
    mciSendString(L"open \"boss_phone.mp3\" type mpegvideo alias boss_phone", NULL, 0, NULL);
    mciSendString(L"open \"evil_phone.mp3\" type mpegvideo alias evil_phone", NULL, 0, NULL);

    int typeEvil;
    if (evil.position.x == boss.position.x && evil.position.y == boss.position.y) 
    {mciSendString(L"play boss_phone", NULL, 0, NULL); 
    typeEvil = 7; 
    reading("Темные облака сгущаются над разрушенным замком, и ветер воет, будто предупреждая об опасности. Воздух пропитан запахом серы и пепла. Вы ступаете по обугленным камням, и внезапно...\n\nГРОМКИЙ РЫК разрывает тишину.\n\nИз глубины разверстых врат выползает исполинская тень. Чешуя, чернее ночи, отливает кровавым багрянцем в свете угасающего солнца. Глаза, как расплавленное золото, пылают ненавистью. \n\n«Смертный...» — его голос гудит, как подземный гром.\n\nВы чувствуете дрожь в коленях, но меч уже в вашей руке."); }
    
    else 
    {mciSendString(L"play evil_phone", NULL, 0, NULL); 
    typeEvil = rand() % 6 + 1; 
    reading("\n\nВы встретили врага\n\n"); 
    }

    while (true)
    {
        cout << "\n\n___________________________________________________________________________________________________\n"
            << "\n\tХП: " << hero.hp << " / " << hero.maxHp << "\t\t ХП врага: " << evil.hp << "\t\t КОЛ - ВО Бутлей: " << hero.estus
            << "\n___________________________________________________________________________________________________\n\n";
        draw_evil(typeEvil);
        cout << "\n\n___________________________________________________________________________________________________\n"
             << "\n\nВыберите желаемое действие (f - fast / l - long / h - heal\n\n";

        attack(hero.power, evil.protection, evil.hp);

        if (evil.hp < 1) 
        { 
        mciSendString(L"close evil_phone", NULL, 0, NULL); mciSendString(L"close \"boss_phone.mp3\" type mpegvideo alias boss_phone", NULL, 0, NULL); mciSendString(L"open \"evil_death.mp3\" type mpegvideo alias evil_death", NULL, 0, NULL); mciSendString(L"play evil_death", NULL, 0, NULL); 
        reading("\n\nВы победили врага\n\nПолучено "); cout << evil.exp; reading(" опыта");
        reading("\n\nВы нашли "); cout << evil.stuff.name;
        backpack[backpackCount].thing = evil.stuff; backpackCount++;
        hero.exp += evil.exp; evil.life = 0; 
        Sleep(350);
        mciSendString(L"close evil_death", NULL, 0, NULL); mciSendString(L"play phone", NULL, 0, NULL); return 1 ; }
        
        evil_attack(evil.power, hero.protection, hero.hp);
        
        if (hero.hp < 1) { mciSendString(L"open \"hero_death.mp3\" type mpegvideo alias hero_death", NULL, 0, NULL); mciSendString(L"play hero_death", NULL, 0, NULL); system("cls"); reading("Вы погибли как лох"); return 0; }
        system("cls");
    }
}
