#include <algorithm>
#include <iostream>
class Buffer {
private:
    char* data;
    std::size_t taille;
public:
    // Constructeur par défaut (buffer vide)
    Buffer() : data(nullptr), taille(0) {}
    // Constructeur paramétré
    explicit Buffer(std::size_t t) : data(new char[t]), taille(t) {
        std::fill_n(data, taille, 0);
        std::cout << "Buffer de " << taille << " octets créé" << std::endl;
    }
    // Constructeur de copie
    Buffer(const Buffer& other) : data(new char[other.taille]), taille(other.taille) {
        std::copy(other.data, other.data + taille, data);
        std::cout << "Constructeur de copie du buffer" << std::endl;
    }
    // Constructeur de déplacement
    Buffer(Buffer&& other) noexcept : data(other.data), taille(other.taille) {
        other.data = nullptr;
        other.taille = 0;
        std::cout << "Constructeur de déplacement du buffer" << std::endl;
    }
    // Opérateur d'assignation de copie
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            taille = other.taille;
            data = new char[taille];
            std::copy(other.data, other.data + taille, data);
        }
        return *this;
    }
    // Opérateur d'assignation de déplacement
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            taille = other.taille;
            other.data = nullptr;
            other.taille = 0;
        }
        return *this;
    }
    // Destructeur
    ~Buffer() {
        delete[] data;
        std::cout << "Destruction du buffer" << std::endl;
    }
    // Méthode d'accès simple
    char* getData() const { return data; }
    std::size_t getTaille() const { return taille; }
};

int main() {
    Buffer b1(128);               // allocation
    Buffer b2 = b1;               // copie
    Buffer b3 = std::move(b1);    // déplacement
    b2 = b3;                      // assignation copie
    b3 = Buffer(64);              // assignation déplacement via rvalue
    return 0;
}