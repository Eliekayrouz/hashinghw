#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <openssl/sha.h>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.length(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
    int user_id = 1001;
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::string timestamp = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());

  
    std::string plain_password = password;
    std::string plain_hash = sha256(password);

    
    std::string salt = sha256(username + std::to_string(user_id) + timestamp);
    std::string salted_hash = sha256(salt + password);

 
    std::cout << "\n=== Table 1: Plain Password ===\n";
    std::cout << "ID: " << user_id << " | User: " << username << " | Pass: " << plain_password << "\n";

    
    std::cout << "\n=== Table 2: Hashed Password ===\n";
    std::cout << "ID: " << user_id << " | User: " << username << "\nHash: " << plain_hash << "\n";

   
    std::cout << "\n=== Table 3: Salted & Hashed Password ===\n";
    std::cout << "ID: " << user_id << " | User: " << username << "\nSalt: " << salt << "\nHash: " << salted_hash << "\n";

    return 0;
}