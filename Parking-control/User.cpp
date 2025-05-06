#include "User.h"
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

User::User() : jsonFilePath("users.json") {
    std::ifstream file(jsonFilePath);
    if (!file.good()) {
        std::ofstream out(jsonFilePath);
        out << "[]";
        out.close();
    }
    file.close();
}

bool User::RegisterUser(const std::string& name, const std::string& login, const std::string& password, const std::string& placa, int hours) {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    if (GetAvailableSlots() <= 0) {
        return false;
    }

    for (const auto& user : j) {
        if (user["login"] == login || user["placa"] == placa) {
            return false;
        }
    }

    std::time_t now = std::time(nullptr);
    char buffer[20];
#ifdef _MSC_VER
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
#else
    struct tm* timeInfo = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
#endif
    std::string entryTime = buffer;

    std::time_t exitTime = now + hours * 3600;
#ifdef _MSC_VER
    localtime_s(&timeInfo, &exitTime);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
#else
    timeInfo = std::localtime(&exitTime);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
#endif
    std::string expectedExitTime = buffer;

    json newUser = {
        {"name", name},
        {"login", login},
        {"password", password},
        {"placa", placa},
        {"entryTime", entryTime},
        {"expectedExitTime", expectedExitTime}
    };

    j.push_back(newUser);

    std::ofstream out(jsonFilePath);
    out << j.dump(4);
    out.close();
    return true;
}

bool User::Authenticate(const std::string& login, const std::string& password) {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    

    for (const auto& user : j) {
        if (user["login"] == login && user["password"] == password) {
            return true;
        }
    }
    return false;
}

void User::SearchByName(const std::string& name) {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    bool found = false;
    for (const auto& user : j) {
        if (user["name"].get<std::string>().find(name) != std::string::npos) {
            std::cout << "Nome: " << user["name"] << "\n";
            std::cout << "Placa: " << user["placa"] << "\n";
            std::cout << "Hora de Entrada: " << user["entryTime"] << "\n";
            if (user.contains("exitTime")) {
                std::cout << "Hora de Saida: " << user["exitTime"] << "\n";
            }
            std::cout << "------------------------\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Nenhum usuario encontrado com esse nome.\n";
    }
}

void User::SearchByPlaca(const std::string& placa) {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    bool found = false;
    for (const auto& user : j) {
        if (user["placa"] == placa) {
            std::cout << "Nome: " << user["name"] << "\n";
            std::cout << "Placa: " << user["placa"] << "\n";
            std::cout << "Hora de Entrada: " << user["entryTime"] << "\n";
            if (user.contains("exitTime")) {
                std::cout << "Hora de Saida: " << user["exitTime"] << "\n";
            }
            found = true;
        }
    }
    if (!found) {
        std::cout << "Nenhuma placa encontrada.\n";
    }
}

bool User::CheckOut(const std::string& placa) {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    std::time_t now = std::time(nullptr);
    char buffer[20];
#ifdef _MSC_VER
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
#else
    struct tm* timeInfo = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
#endif
    std::string exitTime = buffer;

    for (auto& user : j) {
        if (user["placa"] == placa && !user.contains("exitTime")) {
            user["exitTime"] = exitTime;
            std::ofstream out(jsonFilePath);
            out << j.dump(4);
            out.close();
            return true;
        }
    }
    return false;
}

int User::GetAvailableSlots() {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    int occupied = 0;
    for (const auto& user : j) {
        if (!user.contains("exitTime")) {
            occupied++;
        }
    }
    return TOTAL_SLOTS - occupied;
}

void User::CheckExpiredVehicles() {
    std::ifstream in(jsonFilePath);
    json j;
    in >> j;
    in.close();

    std::time_t now = std::time(nullptr);
    json updatedList;
    bool modified = false;

    for (const auto& user : j) {
        if (user.contains("expectedExitTime") && !user.contains("exitTime")) {
            std::string exitTimeStr = user["expectedExitTime"].get<std::string>();
            std::tm tm = {};
            std::istringstream ss(exitTimeStr);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            std::time_t exitTime = std::mktime(&tm);

            if (now > exitTime) {
                std::cout << "Carro com placa " << user["placa"] << " abandonado! Horario expirado.\n";
                modified = true;
                continue;
            }
        }
        updatedList.push_back(user);
    }

    if (modified) {
        std::ofstream out(jsonFilePath);
        out << updatedList.dump(4);
        out.close();
    }
}