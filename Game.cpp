/* simple text based rpg game
create character and enemy classes
create functions to fight enemies
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// Character class
class Character
{
public:
    string name;
    string type;
    int health;
    int attack;
    int defense;
    int specialtyCount;

    Character(string _name, string _type)
    {
        name = _name;
        type = _type;
        specialtyCount = 1;

        if (type == "warrior")
        {
            health = 100;
            attack = 30;
            defense = 15;
        }

        if (type == "wizard")
        {
            health = 90;
            attack = 20;
            defense = 10;
        }

        if (type == "cleric")
        {
            health = 75;
            attack = 15;
            defense = 10;
        }
    }

    void useSpecialty()
    {
        if (type == "warrior")
        {
            health += 50;
            specialtyCount--;
        }
        else if (type == "wizard")
        {
            if (specialtyCount > 0)
            {
                health += 25;
                specialtyCount--;
            }
        }
        else if (type == "cleric")
        {
            if (specialtyCount > 0)
            {
                health += 40;
                specialtyCount--;
            }
        }
    }
};

// Enemy class
class Enemy
{
public:
    string name;
    int health;
    int attack;
    int defense;

    Enemy(string _name)
    {
        name = _name;
        health = 50 + rand() % 51;
        attack = 15 + rand() % 11;
        defense = rand() % 11;
    }

    void takeDamage(int damage)
    {
        health -= damage;
    }
};

// Function to simulate a battle between character and enemy
// Function to simulate a battle between character and enemy
bool battle(Character &player, Enemy &enemy)
{
    cout << "A wild " << enemy.name << " appears!" << endl;

    while (player.health > 0 && enemy.health > 0)
    {
        // Player's turn
        cout << "Your turn. Choose an action:\n";
        cout << "1. Attack\n2. Use Specialty\n";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int playerDamage = player.attack - enemy.defense;
            if (playerDamage < 0)
                playerDamage = 0;
            enemy.health -= playerDamage;
            cout << "You dealt " << playerDamage << " damage to " << enemy.name << endl;
        }
        else if (choice == 2)
        {
            player.useSpecialty();
            cout << "You used your specialty. Health increased to " << player.health << endl;
        }

        // Enemy's turn
        int enemyDamage = enemy.attack - player.defense;
        if (enemyDamage < 0)
            enemyDamage = 0;
        player.health -= enemyDamage;
        cout << enemy.name << " dealt " << enemyDamage << " damage to you" << endl;

        cout << "Your health: " << player.health << "   " << enemy.name << "'s health: " << enemy.health << endl;
    }

    if (player.health <= 0)
    {
        cout << "You were defeated by the " << enemy.name << "." << endl;
        return false;
    }
    else
    {
        cout << "You defeated the " << enemy.name << "!" << endl;
        return true;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    string playerName;
    string playerType;

    cout << "Welcome to the Console RPG!\n";
    cout << "Enter your character's name: ";
    cin >> playerName;

    cout << "Choose your character type (warrior, wizard, or cleric): ";
    cin >> playerType;
    this_thread::sleep_for(chrono::milliseconds(1000));

    Character player(playerName, playerType);
    cout << "Welcome, " << playerName << " the " << playerType << "!\n";
    this_thread::sleep_for(chrono::milliseconds(1000));

    cout << "Your journey begins now!\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "You are on a quest to reach the castle and win the game!\n";
    cout << "You have entered the wooden forest.\n";
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "There appears to be a crossroads ahead.\n";
    cout << "There are three paths to choose from. Which one do you take?\n";
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "1. Go Left.\n";
    cout << "2. Go Middle.\n";
    cout << "3. Go Right.\n";
    int pathChoice;
    cin >> pathChoice;

    if (pathChoice == 1)
    {
        // Path 1: Troll and Dragon
        Enemy troll("Troll");
        if (battle(player, troll))
        {
            Enemy dragon("Dragon (Castle Guardian)");
            if (battle(player, dragon))
            {
                cout << "Congratulations! You've reached the castle and won the game!\n";
            }
        }
    }
    else if (pathChoice == 2)
    {
        // Path 2: Clear path until Dragon
        Enemy dragon("Dragon (Castle Guardian)");
        if (battle(player, dragon))
        {
            cout << "Congratulations! You've reached the castle and won the game!\n";
        }
    }
    else if (pathChoice == 3)
    {
        // Path 3: Goblin and Dragon
        Enemy goblin("Goblin");
        if (battle(player, goblin))
        {
            Enemy dragon("Dragon (Castle Guardian)");
            if (battle(player, dragon))
            {
                cout << "Congratulations! You've reached the castle and won the game!\n";
            }
        }
    }
    else
    {
        cout << "Invalid path choice. The adventure ends.\n";
    }

    cout << "Game over. Thanks for playing!\n";

    return 0;
}
