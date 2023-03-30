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
    friend class fila;  //apenas para acessar os campos privados
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


class fila {
    private:
        noh* mInicio;  
        noh* mFim;
        unsigned mTamanho;
    public:
        fila();
        ~fila();
        unsigned tamanho();
        void enfileira(int valor);
        int desenfileira();
        void limpaFila();
        bool vazia();
};

fila::fila() {
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

fila::~fila() {
    limpaFila();
};

void fila::limpaFila() {  //limpa todos os nós
    while (mTamanho > 0){
        desenfileira();
    };
}

unsigned fila::tamanho() {  //retorna o tamanho da fila
    return mTamanho;
}

bool fila::vazia() {
    return (mTamanho == 0);
}

void fila::enfileira(int valor) {
    //cout << "inicio (antes): " << mInicio << endl;
    
    
    noh* novo = new noh(valor);
    
    if (mTamanho == 0){
        mInicio = novo;
    } else {
        mFim->mProximo = novo;
    }
    
    mFim = novo;
    mTamanho++;
    
    
    //cout << "inicio (depois): " << mInicio << endl;
    //cout << "proximo do inicio: " <<mInicio->mProximo << endl;
}

int fila::desenfileira() {
    int valor = mInicio->mValor;
    noh* temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    
    if (mTamanho == 0){
        mFim = NULL;
    }
    return valor;
    
}


int main() {
    fila f1;
    int num;
    cout << "Digite um numero negativo para interromper o programa" << endl;
    cin >> num;
    
    
    while ( num >= 0){
        f1.enfileira(num);
        cin >> num;
    }
    
    cout << "tamanho: " << f1.tamanho() << endl;
    cout << "elementos: ";
    
    while (not f1.vazia()){
        cout << f1.desenfileira() << " ";
    }
    cout << endl;
    
    return 0;
}
