#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class CompteBancaire {
private:
    string titulaire;
    double solde;
    string* historique;
    size_t capacite;
    size_t nbOps;
    
void agrandirHistorique() {
    size_t nouvelleCap = capacite * 2;

    string* nouveau = new string[nouvelleCap];

    copy(historique, historique + nbOps, nouveau);

    delete[] historique;
    historique = nouveau;
    capacite = nouvelleCap;
}

void ajouterOperation(const string& operation) {
    if (nbOps == capacite) {
        agrandirHistorique();
    }

    historique[nbOps++] = operation;
}


public:
    
    // Constructeur par defaut
    CompteBancaire()
        : titulaire("Inconnu"),
          solde(0.0),
          historique(new string[2]),
          capacite(2),
          nbOps(0) {
    }

    // Constructeur parametre
    CompteBancaire(string nom, double montant)
        : titulaire(nom),
          solde(montant),
          historique(new string[2]),
          capacite(2),
          nbOps(0) {
    }

    // Constructeur par copie
    CompteBancaire(const CompteBancaire& autre)
        : titulaire(autre.titulaire),
          solde(autre.solde),
          historique(new string[autre.capacite]),
          capacite(autre.capacite),
          nbOps(autre.nbOps) {
        copy(autre.historique,
             autre.historique + autre.nbOps,
             historique);
    }

    // Constructeur par deplacement
    CompteBancaire(CompteBancaire&& autre) noexcept
        : titulaire(move(autre.titulaire)),
          solde(autre.solde),
          historique(autre.historique),
          capacite(autre.capacite),
          nbOps(autre.nbOps) {

        autre.solde = 0.0;
        autre.historique = nullptr;
        autre.capacite = 0;
        autre.nbOps = 0;
    }

    // Destructeur
    ~CompteBancaire() {
        cout << "Destruction du compte de "
             << titulaire << endl;
    }

    // Deposer de l'argent
    void deposer(double montant) {
        if (montant > 0) {
            solde += montant;
            cout << "Depot de " << montant << " DH effectue." << endl;
        } else {
            cout << "Montant invalide !" << endl;
        }
    }

    // Retirer de l'argent
    void retirer(double montant) {
        if (montant <= 0) {
            cout << "Montant invalide !" << endl;
        } else if (montant > solde) {
            cout << "Solde insuffisant !" << endl;
        } else {
            solde -= montant;
            cout << "Retrait de " << montant << " DH effectue." << endl;
        }
    }

};

int main() {
    CompteBancaire compte1;
    CompteBancaire compte2("Sara", 1500.0);
    CompteBancaire compte4(std::move(compte2));

cout << "--- Compte 4 ---" << endl;
compte4.afficher();

cout << "--- Compte 2 apres deplacement ---" << endl;
compte2.afficher();

    // Creation d'une copie
    CompteBancaire compte3(compte2);

    cout << "--- Compte 1 ---" << endl;
    compte1.afficher();

    cout << "\n--- Compte 2 ---" << endl;
    compte2.afficher();

    cout << "\n--- Compte 3 (copie de compte2) ---" << endl;
    compte3.afficher();
compte4.deposer(500);
compte4.retirer(200);
compte4.retirer(5000);

cout << "\n--- Solde final ---" << endl;
compte4.afficher();
    return 0;
}
