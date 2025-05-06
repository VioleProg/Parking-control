#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
private:
    std::string iLogin;
    std::string iPassword;
    int cMenu;

public:
    Menu();
    ~Menu();
    void OnCreate();
    void MenuList();
    void CheckExpired();
};

#endif