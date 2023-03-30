/* 
 * 
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 
 */
 
#include <iostream>
using namespace std;

class filaCircular {
    private:
        int mInicio;
        int mFim;
        int* mDados;
        unsigned mCapacidade;
        unsigned mTamanho;
    public:
        filaCircular(int capacidade = 10);
        ~filaCircular();
        unsigned tamanho();
        void enfileira(int valor);
        int desenfileira();
        bool vazia();
        
        // QUEBRA DE ESTRUTURA PARA FINS DIDÁTICOS
        //void depura();
};

filaCircular::filaCircular(int capacidade) {
    mInicio = -1;
    mFim = -1;
    mCapacidade = capacidade;
    mDados = new int[mCapacidade];
    mTamanho = 0;
}

filaCircular::~filaCircular() {
    delete[] mDados;
};

/*void fila::limpaFila() {  //limpa todos os nós
    while (mTamanho > 0){
        desenfileira();
    };
}*/

unsigned filaCircular::tamanho() {  //retorna o tamanho da fila
    return mTamanho;
}

bool filaCircular::vazia() {
    return (mTamanho == 0);
}

void filaCircular::enfileira(int valor) {
    if (mTamanho <= mCapacidade){
        mFim++;
        mFim = mFim % mCapacidade;
        mDados[mFim] = valor;
        if (mTamanho == 0){
            mInicio++;
        }
        mTamanho++;
    } else {
        cerr << "Fila cheia" << endl;
    }
    
    
}

int filaCircular::desenfileira() {
    if (mTamanho > 0){
        int valor = mDados[mInicio];
        mTamanho--;
        if (mTamanho > 0){
            mInicio++;
            mInicio = mInicio % mCapacidade;
        } else{
            mInicio = -1;
            mFim = -1;
        }
        
        return valor;
    } else {
        cerr << "Fila vazia!" << endl;
        return -1;
    }
}


// IMPLEMENTAÇÃO DESTE PROCEDIMENTO APENAS PARA FINS DIDÁTICOS
/*void filaCircular::depura() {
    cout << "inicio na posicao: " << mInicio << endl;
    cout << "fim na posicao: " << mFim << endl;
    cout << "vetor de dados: ";
    for (unsigned i=0; i<mCapacidade; i++){
        cout << mDados[i] << " ";
    }
    cout << endl;
}*/


int main() {
    filaCircular f1(12);
    int num;
    
    cout << "A fila so suporta ate 8 numeros" << endl;
    
    for (int i=0; i < 8; i++){
        cin >> num;
        f1.enfileira(num);
    }
    
    cout << "tamanho: " << f1.tamanho() << endl;
    cout << "5 elementos: ";
    
    
    for (int i=0; i < 5; i++){
        cout << f1.desenfileira() << " ";
    }
    cout << endl;
    
    
    for (int i=0; i < 8; i++){
        cin >> num;
        f1.enfileira(num);
    }
    
    cout << "tamanho: " << f1.tamanho() << endl;
    cout << "5 elementos: ";
    
    
    for (int i=0; i < 5; i++){
        cout << f1.desenfileira() << " ";
    }
    cout << endl;
    
    
    // SOMENTE PARA FINS DIDÁTICOS
    // NUNCA REALIZAR SUA IMPLEMENTAÇÃO EM TRABALHOS!!!!!!!!!
    
    //f1.depura();
    
    return 0;
}
