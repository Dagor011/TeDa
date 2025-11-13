#ifndef USER_H
#define USER_H

#include <string>
#include <chrono>

class User {
private:
    std::string username;
    std::string password;
    std::string email;
    std::chrono::system_clock::time_point last_login;

public:

    User() : username(""), password(""), email(""), last_login(std::chrono::system_clock::now()) {}


    User(const std::string& username, const std::string& password, const std::string& email)
        : username(username), password(password), email(email), last_login(std::chrono::system_clock::now()) {}


    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getEmail() const { return email; }
    std::chrono::system_clock::time_point getLastLogin() const { return last_login; }

    void setLastLogin(const std::chrono::system_clock::time_point& time) { last_login = time; }
};

#endif
