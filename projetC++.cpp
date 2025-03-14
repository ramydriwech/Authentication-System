#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <ctime>    
#include <sstream>
#include <iomanip>
#include <functional>
#include <regex>    // Pour la validation du mot de passe

// Fonction pour générer un salt aléatoire
std::string generateSalt() {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int saltLength = 16;
    std::string salt;
    srand(time(0)); // Initialisation du générateur de nombres aléatoires

    for (int i = 0; i < saltLength; ++i) {
        salt += charset[rand() % charset.length()];
    }
    return salt;
}

// Fonction de hachage SHA-256 (alternative avec std::hash)
std::string sha256(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hashedValue = hasher(input);

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hashedValue;

    return ss.str();
}

// Fonction pour vérifier la force du mot de passe
bool isStrongPassword(const std::string& password) {
    if (password.length() < 8) return false;  // Doit contenir au moins 8 caractères

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    std::string specialChars = "@#$%^&*()-_=+[]{}|;:,.<>?/!";

    for (char ch : password) {
        if (std::isupper(ch)) hasUpper = true;
        if (std::islower(ch)) hasLower = true;
        if (std::isdigit(ch)) hasDigit = true;
        if (specialChars.find(ch) != std::string::npos) hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Classe User : Représente un utilisateur
class User {
private:
    std::string username;
    std::string hashedPassword;
    std::string salt;

public:
    User(const std::string& username, const std::string& hashedPassword, const std::string& salt)
        : username(username), hashedPassword(hashedPassword), salt(salt) {}

    std::string getUsername() const { return username; }
    std::string getHashedPassword() const { return hashedPassword; }
    std::string getSalt() const { return salt; }
};

// Classe FileManager : Gère la lecture et l'écriture des utilisateurs dans un fichier
class FileManager {
private:
    std::string filename;

public:
    FileManager(const std::string& filename) : filename(filename) {}

    void saveUser(const User& user) {
        std::ofstream file(filename, std::ios::app);
        file << user.getUsername() << "," << user.getHashedPassword() << "," << user.getSalt() << std::endl;
        file.close();
    }

    std::vector<User> loadUsers() {
        std::vector<User> users;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);

            std::string username = line.substr(0, pos1);
            std::string hashedPassword = line.substr(pos1 + 1, pos2 - (pos1 + 1));
            std::string salt = line.substr(pos2 + 1);

            users.push_back(User(username, hashedPassword, salt));
        }

        file.close();
        return users;
    }
};

// Classe AuthManager : Gère la logique d'authentification
class AuthManager {
private:
    FileManager fileManager;

public:
    AuthManager(const std::string& filename) : fileManager(filename) {}

    void registerUser() {
        std::string username, password;
        std::cout << "Entrez un nom d'utilisateur : ";
        std::cin >> username;

        do {
            std::cout << "Entrez un mot de passe (au moins 8 caracteres, une majuscule, une minuscule, un chiffre et un caractere special) : ";
            std::cin >> password;

            if (!isStrongPassword(password)) {
                std::cout << "Mot de passe trop faible ! Essayez encore.\n";
            }

        } while (!isStrongPassword(password));

        std::string salt = generateSalt();
        std::string hashedPassword = sha256(password + salt);

        User newUser(username, hashedPassword, salt);
        fileManager.saveUser(newUser);

        std::cout << "Utilisateur enregistre avec succes !" << std::endl;
    }

    void loginUser() {
        std::string inputUsername, inputPassword;
        std::cout << "Entrez votre nom d'utilisateur : ";
        std::cin >> inputUsername;
        std::cout << "Entrez votre mot de passe : ";
        std::cin >> inputPassword;

        std::vector<User> users = fileManager.loadUsers();
        for (const User& user : users) {
            if (user.getUsername() == inputUsername) {
                std::string inputHashedPassword = sha256(inputPassword + user.getSalt());

                if (inputHashedPassword == user.getHashedPassword()) {
                    std::cout << "Connexion reussie !" << std::endl;
                    return;
                }
            }
        }

        std::cout << "Nom d'utilisateur ou mot de passe incorrect." << std::endl;
    }
};

// Fonction principale
int main() {
    AuthManager authManager("users.txt");

    std::cout << "=== Système d'Authentification ===" << std::endl;
    std::cout << "1. S'inscrire\n2. Se connecter\n3. Quitter\n";

    int choice;
    while (true) {
        std::cout << "Choisissez une option : ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                authManager.registerUser();
                break;
            case 2:
                authManager.loginUser();
                break;
            case 3:
                std::cout << " Au revoir !" << std::endl;
                return 0;
            default:
                std::cout << "Option invalide. Veuillez reessayer." << std::endl;
                break;
        }
    }

    return 0;
}
