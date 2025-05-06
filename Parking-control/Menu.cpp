#include "Menu.h"
#include "User.h"
#include <iostream>
#include <limits>
#include <cstdlib>

Menu::Menu() : cMenu(0) {}

Menu::~Menu() {}

void Menu::OnCreate() {
    User userManager;
    std::cout << "=== Sistema de Estacionamento ===\n";
    MenuList();
}

void Menu::MenuList() {
    User userManager;

    do {
        system("cls");
        std::cout << "MENU DO ESTACIONAMENTO\n";
        std::cout << "Vagas disponiveis: " << userManager.GetAvailableSlots() << "\n";
        std::cout << "1 - Cadastrar Novo Usuario\n";
        std::cout << "2 - Login\n";
        std::cout << "3 - Buscar por Nome\n";
        std::cout << "4 - Buscar por Placa\n";
        std::cout << "5 - Registrar Saida\n";
        std::cout << "6 - Sair\n";
        std::cout << "Escolha uma opcao: ";

        if (!(std::cin >> cMenu)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Pressione Enter para continuar...";
            std::cin.get();
            continue;
        }
        std::cin.ignore();

        switch (cMenu) {
        case 1: {
            std::string name, login, password, placa;
            int hours;
            std::cout << "Nome: ";
            std::getline(std::cin, name);
            std::cout << "Login: ";
            std::getline(std::cin, login);
            std::cout << "Senha: ";
            std::getline(std::cin, password);
            std::cout << "Placa: ";
            std::getline(std::cin, placa);
            std::cout << "Horas de permanencia: ";
            std::cin >> hours;
            std::cin.ignore();

            if (userManager.RegisterUser(name, login, password, placa, hours)) {
                std::cout << "Usuario cadastrado com sucesso! Horario registrado.\n";
                std::cout << "Vagas restantes: " << userManager.GetAvailableSlots() << "\n";
            }
            else {
                std::cout << "Erro: Login ja existe ou sem vagas disponiveis.\n";
            }
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 2: {
            std::cout << "Login: ";
            std::getline(std::cin, iLogin);
            std::cout << "Senha: ";
            std::getline(std::cin, iPassword);

            if (userManager.Authenticate(iLogin, iPassword)) {
                std::cout << "Login bem-sucedido!\n";
            }
            else {
                std::cout << "Login ou senha incorretos.\n";
            }
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 3: {
            std::string name;
            std::cout << "Digite o nome para busca: ";
            std::getline(std::cin, name);
            userManager.SearchByName(name);
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 4: {
            std::string placa;
            std::cout << "Digite a placa para busca: ";
            std::getline(std::cin, placa);
            userManager.SearchByPlaca(placa);
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 5: {
            std::string placa;
            std::cout << "Digite a placa para registrar saida: ";
            std::getline(std::cin, placa);
            if (userManager.CheckOut(placa)) {
                std::cout << "Saida registrada com sucesso! Vagas restantes: " << userManager.GetAvailableSlots() << "\n";
            }
            else {
                std::cout << "Placa nao encontrada.\n";
            }
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 6:
            std::cout << "Saindo...\n";
            break;
        default:
            std::cout << "Opcao invalida.\n";
            std::cout << "Pressione Enter para continuar...";
            std::cin.get();
            break;
        }
        userManager.CheckExpiredVehicles();
    } while (cMenu != 6);
}

void Menu::CheckExpired() {
    User userManager;
    userManager.CheckExpiredVehicles();
}