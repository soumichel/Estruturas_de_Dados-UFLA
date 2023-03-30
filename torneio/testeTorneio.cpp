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
const int INVALIDO = -1;  //geraria problemas caso a implementação utilizasse valores negativos

class torneio {
    private:
        dado* heap;
        int capacidade;
        int tamanho;
        int inicioDados;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();
        void copiaMaior(int i);
        void copiaSubindo(int i);
    public:
        torneio(dado vet[], int tam);
        torneio(int numFolhas);
        ~torneio();
        void imprime();  //APENAS PARA FINALIDADES DIDÁTICAS
        void insere(dado d);
};


torneio::torneio(dado vet[], int tam) {
    /* Determinando capacidade
     * número de possíveis pais é uma potência de 2 menos 1
     * capacidade é possíveis pais mais tamanho do vetor
     * começamos com 1 pai e vamos dobrando a cada caso
     */
    capacidade = 1;
    while (capacidade < tam){
        capacidade *= 2;
    }
    
    // potência de 2 menos 1 + tamanho do vetor
    capacidade = capacidade - 1 + tam;
    
    heap = new dado[capacidade];
    inicioDados = capacidade - tam;
    
    cout << "inicioDados: " << inicioDados << endl;
    cout << "capacidade: " << capacidade << endl;
    
    memcpy(&heap[inicioDados], vet, tam * sizeof(dado));
    
    tamanho = tam;
    arruma();
}

torneio::torneio(int numFolhas) {
    /* Determinando capacidade
     * número de possíveis pais é uma potência de 2 menos 1
     * capacidade é possíveis pais mais numFolhas
     * começamos com 1 pai e vamos dobrando a cada caso
     */
     capacidade = 1;
     while (capacidade < numFolhas){
         capacidade *= 2;
     }
     
     // potência de 2 menos 1 + tamanho do vetor
     capacidade = capacidade - 1 + numFolhas;
     heap = new dado[capacidade];
     inicioDados = capacidade - numFolhas;
     
     cout << "inicioDados: " << inicioDados << endl;
     cout << "capacidade: " << capacidade << endl;
     
     for (int i=0; i<capacidade; i++){
         heap[i] = INVALIDO;
     }
}

torneio::~torneio() {
    delete[] heap;
}

void torneio::arruma() {  // Aplica recebeMaior na primeira metade dos elementos
    cout << "arruma: " << inicioDados - 1 << endl;
    for (int i=inicioDados - 1; i>=0; i--){
        copiaMaior(i);
    }
}

int torneio::pai(int i) {
    return (i-1)/2;
}

int torneio::esquerdo(int i) {
    return 2 * i+1;
}

int torneio::direito(int i) {
    return 2 * i+2;
}

void torneio::copiaMaior(int i) {
    int esq = esquerdo(i);
    int dir = direito(i);
    cout << "i: " << i << " esq: " << esq << " dir: " << dir << endl;
    
    int maior = INVALIDO;
    
    if (esq < capacidade){
        if ((dir < capacidade) and (heap[dir] > heap[esq])){
            maior = dir;
        } else {
            maior = esq;
        }
        heap[i] = heap[maior];
    } else {
        heap[i] = INVALIDO;
    }
}

void torneio::copiaSubindo(int i) {
    int p = pai(i);
    
    if (heap[i] > heap[p]){
        heap[p] = heap[i];
        copiaSubindo(p);
    }
}

/*void torneio::imprime() {  //Imprime até o tamanho e não até a capacidade
    for (int i=0; i<tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}*/

void torneio::imprime() {  //Imprime todos os dados
    for (int i=0; i<capacidade; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void torneio::insere(dado d) {
    if (tamanho == capacidade){
        cerr << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    heap[tamanho+inicioDados] = d;
    copiaSubindo(tamanho+inicioDados);
    tamanho++;
}


int main() {
    /* 9 é um bom tamanho de teste já que é 1 mais o dobro
     * fica uma folha solta no último nível
     */
    int tam = 9;
    dado vet1[] = {50, 2, 90, 20, 230, 43, 8, 34, 66};
    
    torneio *h = new torneio(vet1, tam);
    h->imprime();
    delete h;
    
    tam = 13;
    dado vet2[] = {50, 2, 90, 20, 230, 43, 8, 34, 66, 100, 110, 3, 13};
    
    h = new torneio(vet2, tam);
    h->imprime();
    delete h;
    
    tam = 9;
    h = new torneio(9);
    
    for (int i=0; i<tam; i++){
        h->insere(vet1[i]);
        h->imprime();
    }
    delete h;
    
    return 0;
}
