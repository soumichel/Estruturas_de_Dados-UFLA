/*

 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 

Implementação de uma Árvore Binária de Busca (ABB) com operações de inserção, remoção e exibição de elementos em duas formas: em ordem e pré-ordem. 
A árvore armazena chaves inteiras, e as operações de escrita exibem a chave seguida por uma barra e o nível da árvore
onde a chave está. Ao tentar remover uma chave inexistente, o programa deve retornar "ERRO". 
A remoção de nós com dois filhos segue a estratégia de substituição pelo sucessor. 
O programa recebe comandos para inserir, remover, exibir elementos e finalizar a execução. Os comandos possíveis devem ser:

A letra i, seguida de uma chave para inserir uma chave na árvore.
A letra r, seguida de uma chave para remover uma chave da árvore.
A letra o para escrever os elementos em ordem, no formato descrito acima.
A letra p para escrever os elementos em pré-ordem, no formato descrito acima.
A letra f para finalizar a execução do programa.

Entradas:
Uma sequência de comandos, conforme especificado acima.

Saídas:
Somente os comandos para escrever produzem saída, conforme formato explicado acima.

Exemplo de Entrada:
i 3
i 4
i 2
i 5
i 1
r 3
o
p
f
Exemplo de Saída:

1/2 2/1 4/0 5/1 
4/0 2/1 1/2 5/1
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class noh {
    friend class abb;
    private:
        int chave; // Valor da chave do nó
        noh* esq;  // Ponteiro para o filho à esquerda
        noh* dir;  // Ponteiro para o filho à direita
    public:
        noh(int c) : chave(c), esq(NULL), dir(NULL) {}
};

class abb {
    private:
        noh* raiz; // Raiz da árvore
        noh* insereAux(noh* umNoh, int chave);
        noh* removeAux(noh* umNoh, int chave);
        noh* menorAux(noh* raizSub);
        noh* removeMenorAux(noh* raizSub);
        void emOrdemAux(noh* umNoh, int nivel);
        void preOrdemAux(noh* umNoh, int nivel);
        void destruirRecursivamente(noh* umNoh);
    public:
        abb() : raiz(NULL) {}
        ~abb();
        void insere(int chave);
        void remove(int chave);
        void emOrdem();
        void preOrdem();
};

abb::~abb() {
    destruirRecursivamente(raiz);
}

void abb::destruirRecursivamente(noh* umNoh) {
    if (umNoh != NULL) {
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void abb::insere(int chave) {
    raiz = insereAux(raiz, chave);
}

noh* abb::insereAux(noh* umNoh, int chave) {
    if (umNoh == NULL) {
        return new noh(chave);
    } else if (chave < umNoh->chave) {
        umNoh->esq = insereAux(umNoh->esq, chave);
    } else {
        umNoh->dir = insereAux(umNoh->dir, chave);
    }
    return umNoh;
}

void abb::remove(int chave) {
    raiz = removeAux(raiz, chave);
}

noh* abb::removeAux(noh* umNoh, int chave) {
    if (umNoh == NULL) {
        cout << "ERRO" << endl; // Chave não encontrada
        return NULL;
    } else if (chave < umNoh->chave) {
        umNoh->esq = removeAux(umNoh->esq, chave);
    } else if (chave > umNoh->chave) {
        umNoh->dir = removeAux(umNoh->dir, chave);
    } else {
        // Nó encontrado
        if (umNoh->esq == NULL) {
            noh* temp = umNoh->dir;
            delete umNoh;
            return temp;
        } else if (umNoh->dir == NULL) {
            noh* temp = umNoh->esq;
            delete umNoh;
            return temp;
        } else {
            // Nó com dois filhos: substituição pelo sucessor
            umNoh->chave = menorAux(umNoh->dir)->chave;
            umNoh->dir = removeAux(umNoh->dir, umNoh->chave);
        }
    }
    return umNoh;
}

noh* abb::menorAux(noh* raizSub) {
    while (raizSub->esq != NULL) {
        raizSub = raizSub->esq;
    }
    return raizSub;
}

void abb::emOrdem() {
    emOrdemAux(raiz, 0);
    cout << endl;
}

void abb::emOrdemAux(noh* umNoh, int nivel) {
    if (umNoh != NULL) {
        emOrdemAux(umNoh->esq, nivel + 1);
        cout << umNoh->chave << "/" << nivel << " ";
        emOrdemAux(umNoh->dir, nivel + 1);
    }
}

void abb::preOrdem() {
    preOrdemAux(raiz, 0);
    cout << endl;
}

void abb::preOrdemAux(noh* umNoh, int nivel) {
    if (umNoh != NULL) {
        cout << umNoh->chave << "/" << nivel << " ";
        preOrdemAux(umNoh->esq, nivel + 1);
        preOrdemAux(umNoh->dir, nivel + 1);
    }
}

int main() {
    abb arvore;
    char comando;
    int chave;

    do {
        cin >> comando;
        switch (comando) {
            case 'i':
                cin >> chave;
                arvore.insere(chave);
                break;
            case 'r':
                cin >> chave;
                arvore.remove(chave);
                break;
            case 'o':
                arvore.emOrdem();
                break;
            case 'p':
                arvore.preOrdem();
                break;
            case 'f':
                break;
            default:
                cout << "Comando invalido!" << endl;
        }
    } while (comando != 'f');

    return 0;
}
