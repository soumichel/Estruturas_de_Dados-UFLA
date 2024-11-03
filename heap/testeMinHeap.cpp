/* 
 * 
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;

class MinHeap {
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();   //heapify
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
    public:
        MinHeap(int cap);
        MinHeap(dado vet[], int tam);
        ~MinHeap();
        void imprime();  //APENAS PARA FINALIDADES DIDÁTICAS
        dado espiaRaiz();
        dado retiraRaiz();
        void insere(dado d);
};

MinHeap::MinHeap(int cap) {
    capacidade = cap;
    heap = new dado[cap];
    tamanho = 0;
}

MinHeap::MinHeap(dado vet[], int tam) {
    capacidade = tam;
    heap = new dado[capacidade];
    
    // Utilizado para realizar a cópia de uma maneira mais rápida
    // sendo mais eficiente que a estrutura de repetição for
    memcpy(heap, vet, tam * sizeof(dado));
    
    tamanho = tam;
    arruma();
}

MinHeap::~MinHeap() {
    delete[] heap;
}

void MinHeap::arruma() {  // Iniciando alocação de dados no heap na posição 0
    for (int i = (tamanho / 2 - 1); i >= 0; i--) {
        corrigeDescendo(i);
    }
}

int MinHeap::pai(int i) {
    return (i - 1) / 2;
}

int MinHeap::esquerdo(int i) {
    return 2 * i + 1;
}

int MinHeap::direito(int i) {
    return 2 * i + 2;
}

void MinHeap::corrigeDescendo(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    int menor = i;
    
    if ((esq < tamanho) && (heap[esq] < heap[menor])) {
        menor = esq;
    }
    
    if ((dir < tamanho) && (heap[dir] < heap[menor])) {
        menor = dir;
    }
    
    if (menor != i) {
        swap(heap[i], heap[menor]);
        corrigeDescendo(menor);
    }
}

void MinHeap::corrigeSubindo(int i) {
    int p = pai(i);
    
    if (heap[i] < heap[p]) {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

void MinHeap::imprime() {  // Imprime todos os dados
    for (int i = 0; i < capacidade; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

dado MinHeap::espiaRaiz() {
    return heap[0];
}

dado MinHeap::retiraRaiz() {
    if (tamanho == 0) {
        cerr << "Erro ao retirar raiz" << endl;
        exit(EXIT_FAILURE);
    }
    
    dado aux = heap[0];
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

void MinHeap::insere(dado d) {
    if (tamanho == capacidade) {
        cerr << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

int main() {
    int tam = 13;
    dado vet[] = {50, 2, 90, 20, 230, 43, 8, 34, 66, 100, 110, 3, 13};
    
    MinHeap *h = new MinHeap(vet, tam);
    
    for (int i = 0; i < tam; i++) {
        cout << h->retiraRaiz() << " : ";
        h->imprime();
    }
    cout << endl;
    
    for (int i = 0; i < tam; i++) {
        h->insere(vet[i]);
    }
    
    // Feita após o uso de inserção
    cout << "Feita apos o uso de insercao" << endl;
    for (int i = 0; i < tam; i++) {
        cout << h->retiraRaiz() << " : ";
        h->imprime();
    }
    cout << endl;
    
    delete h;
    
    return 0;
}
