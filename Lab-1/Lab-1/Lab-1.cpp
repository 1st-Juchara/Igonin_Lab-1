// Lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

void Menu() {
    int number;
    std::cout << "1. Add pipe \n2. Add CS \n3. Objects \n4. Edit pipe \n5. Edit CS \n6. Save \n7. Exit \n> ";
    std::cin >> number;
}

int main()
{
    Menu();
    return 0;
}