#ifndef MENU_H
#define MENU_H

#include <iostream>

// simple menu class

class menu
{
public:
	void ShowMenu();
	int GetMenuChoice();

private:
    int choice = 0;
};

inline void menu::ShowMenu()
{
    std::cout <<
        "\n"
        "________________________________________________________\n\n"
        "1. Load and compress lyrics from a file\n"
        "2. Display the compressed form\n"
        "3. (Bonus) Switch between available encoding methods\n"
        "4. Quit the program\n"
        "________________________________________________________\n";
}

inline int menu::GetMenuChoice()
{
    std::cout << "Choose an option: " << std::endl;
    std::cin >> choice;
    if (std::cin.fail())
    {
        std::cin.clear(); // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Invalid input. Please enter a number.\n";
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}
#endif
