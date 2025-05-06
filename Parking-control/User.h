#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string jsonFilePath;
    static const int TOTAL_SLOTS = 50;

public:
    User();
    bool RegisterUser(const std::string& name, const std::string& login, const std::string& password, const std::string& placa, int hours);
    bool Authenticate(const std::string& login, const std::string& password);
    void SearchByName(const std::string& name);
    void SearchByPlaca(const std::string& placa);
    bool CheckOut(const std::string& placa);
    int GetAvailableSlots();
    void CheckExpiredVehicles();
};

#endif