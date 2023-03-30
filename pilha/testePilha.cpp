/* 
 * 
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 
 */

#include <iostream>
using namespace std;

class noh {
    friend class pilha;  //apenas para acessar os campos privados
    private:
        int mValor;
        noh* mProximo;  //apontando para o próximo valor
    public:
        noh(int valor);
};

noh::noh(int valor){   //nós sendo construídos apontando para ninguém
    mValor = valor;
    mProximo = NULL;
    //cout << "no criado: " << this << endl;
}


class pilha {
    private:
        noh* mTopo;  //apontando para o topo da pilha
        unsigned mTamanho;
    public:
        pilha();
        ~pilha();
        unsigned tamanho();
        void empilha(int valor);
        int desempilha();
        void limpaPilha();
        bool vazia();
};

pilha::pilha() {
    mTopo = NULL;
    mTamanho = 0;
}

pilha::~pilha() {
    limpaPilha();
};

void pilha::limpaPilha() {  //limpa todos os nós
    while (mTamanho > 0){
        desempilha();
    };
}

unsigned pilha::tamanho() {  //retorna o tamanho da pilha
    return mTamanho;
}

bool pilha::vazia() {
    return (mTamanho == 0);
}

void pilha::empilha(int valor) {
    //cout << "topo (antes): " << mTopo << endl;
    noh* novo = new noh(valor);
    novo->mProximo = mTopo;
    mTopo = novo;
    mTamanho++;
    //cout << "topo (depois): " << mTopo << endl;
    //cout << "proximo do topo: " <<mTopo->mProximo << endl;
}

int pilha::desempilha() {
    int valor = mTopo->mValor;
    noh* temp = mTopo;
    mTopo = mTopo->mProximo;
    delete temp;
    mTamanho--;
    return valor;
    
}


int main() {
    pilha p1;
    int num;
    cout << "Digite um numero negativo para interromper o programa" << endl;
    cin >> num;
    

    while ( num >= 0){
        p1.empilha(num);
        cin >> num;
    }
    
    cout << "tamanho: " << p1.tamanho() << endl;
    cout << "elementos: ";
    
    while (not p1.vazia()){
        cout << p1.desempilha() << " ";
    }
    cout << endl;
    
    return 0;
}
