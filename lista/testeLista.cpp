/* 
 * 
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 
 */

#include <iostream>
#include <cstdlib>
using namespace std;

/* Para facilitar a troca de int para outro tipo
 * estamos criando um apelido para int chamado Dado
 * - com isso, destaca-se que a lista pode ser uma
 * lista de qualquer objeto, não apenas de inteiros...
 * ou seja: é uma lista de dados
*/

typedef int Dado;  //typedef permite criar novos tipos a partir de outros

class noh {
    friend class lista;
    private:
        // dado está como constante para não permitir alteração
        const Dado dado;
        noh* proximo;
    public:
        // noh()
        noh(Dado d = 0);
};

/* Construindo dado chamando seu construtor
 * note o uso de inicialização em lista, já que dado é atributo constante
*/
noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

// Lista dinamicamente encadeada
class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        
        void removeTodos();  // remove todos os elementos da lista
        void imprimeReversoAux(noh* umNoh);  // imprime reverso a partir de um nó -> exemplo do uso de recursão
        
    public:
        // construtor e destrutor
        lista();
        lista(const lista& umaLista);
        ~lista();
        lista& operator=(const lista& umaLista);  // sobrecarga do operador de atribuição
        // inserção, remoção e procura
        inline void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(int posicao, Dado dado);
        int procura (Dado valor);  // retorna a posição do nó com va
        // métodos adicionais (impressão, vazia)
        void imprime();
        void imprimeReverso();
        inline bool vazia();
        void removeNoFim();
        void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
    
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista() {
    removeTodos();
}

void lista::removeTodos() {
    noh* aux = primeiro;
    noh* temp;
    
    while (aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    
    // redirecionando ponteiros
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista) {
    removeTodos();  // limpa a lista atual
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    insereNoFim(dado);
}

// insere no final da lista
void lista::insereNoFim(Dado dado) {
    noh* novo = new noh(dado);  // primeiro criamos um novo nó
    
    // agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos o primeiro nó
    if (vazia()){  // ou (primeiro == NULL) ou (tamanho == 0)
        primeiro = novo;
        ultimo = novo;
    } else {  // já tem elementos na lista, insere no final
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}


// insere no inicio da lista
void lista::insereNoInicio(Dado dado) {
    noh* novo = new noh(dado);  // primeiro criamos um novo nó
    
    // agora inserimos o nó na lista
    // se a lista estiver vazia, inserimos o primeiro nó
    if (vazia()){  // ou (primeiro == NULL) ou (tamanho == 0)
        primeiro = novo;
        ultimo = novo;
    } else {  // já tem elementos na lista, insere no inicio
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, Dado dado) {
    noh* novo = new noh(dado);  // primeiro criamos um novo nó
    
    // agora inserimos o nó na lista
    // verificamos antes se é possível inserir na posição
    if ((posicao <= tamanho) and (posicao >= 0)){
        if (vazia()){  // ou (primeiro == NULL) ou (tamanho == 0)
            primeiro = novo;
            ultimo = novo;
        } else if (posicao == 0){  // insere no inicio
        novo->proximo = primeiro;
        primeiro = novo;
    } else if (posicao == tamanho){  // insere no fim
        ultimo->proximo = novo;
        ultimo = novo;
    } else {  // insere no meio da lista
        noh* aux = primeiro;
        int posAux = 0;
        
        // chegando na posicao da lista
        while (posAux < (posicao - 1)){
            aux = aux->proximo;
            posAux++;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
    tamanho++;
    } else {
    cerr << "Posicao Inexistente!" << endl;
    exit(EXIT_FAILURE);
}
}
int lista::procura(Dado valor) {
    noh* aux = primeiro;
    int posAux = 0;
    
    while ((aux != NULL) and (aux->dado != valor)){
        posAux++;
        aux = aux->proximo;
    }
    
    if (aux == NULL){
        posAux = -1;
    }
    return posAux;
}

// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    noh* aux = primeiro;
    
    while (aux != NULL){
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
     cout << endl;
}

// usamos recursão (pilha de recursão) para imprimir reverso
// para isso precisa de função auxiliar
void lista::imprimeReverso() {
    imprimeReversoAux(primeiro);
    cout << endl;
}

void lista::imprimeReversoAux(noh* umNoh) {
    if (umNoh != NULL){
        imprimeReversoAux(umNoh->proximo);
        cout << umNoh->dado << " ";
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}


void lista::removeNoFim() {
    if (vazia()){
        cerr << "Remocao em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    } 
    
    noh* aux = primeiro;
    noh* anterior;
    
    while (aux->proximo != NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    
    // para no penúltimo
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    
    // verificação feita sendo se o primeiro for nulo
    if (vazia()){
        primeiro = NULL;
    }
    tamanho--;
    
    /* CASO A VERIFICAÇÃO FOSSE FEITA PELO TAMANHO

    tamanho--;
    if (tamanho == 0){
        primeiro = NULL;
    }

    */
}

void lista::removeNoInicio() {
    if (vazia()){
        cerr << "Remocao em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    } 
    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    
    // verificação feita sendo se o ultimo for nulo
    if (vazia()){
        ultimo = NULL;
    }
    tamanho--;
    
    /* CASO A VERIFICAÇÃO FOSSE FEITA PELO TAMANHO
     
    tamanho--;
    if (vazia()){
        ultimo = NULL;
    }
    
    */
}


int main() {
    lista minhaLista;
    
    cout << " === Teste da Lista === " << endl;
    cout << "Quantidade de valores a inserir" << endl;
    
    int valor;
    int num;
    cin >> num;
    
    for (int i=0; i<num; i++){
        cin >> valor;
        minhaLista.insere(valor);
    }
    minhaLista.imprime();
    
    minhaLista.insereNoInicio(18);
    minhaLista.insereNaPosicao(3,25);
    minhaLista.imprime();
    minhaLista.imprimeReverso();
    
    cout << endl;
    cout << "Posicao na lista: " << minhaLista.procura(0) << endl;
    cout << "Posicao na lista: " << minhaLista.procura(50) << endl;
    cout << "Posicao na lista: " << minhaLista.procura(12) << endl;
    
    cout << endl;
    //construtor de cópia
    cout << "Sobrecarga do construtor de copia" << endl;
    lista outraLista(minhaLista);
    outraLista.imprime();
    outraLista.imprimeReverso();
    cout << endl;
    
    //sobrecarga de operador de atribuição
    cout << "Sobrecarga do operador de atribuicao" << endl;
    lista maisUmaLista;
    maisUmaLista = outraLista;
    
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();
    
    cout << endl;
    cout << "Apos duas remocoes no fim" << endl;
    maisUmaLista.removeNoFim();
    maisUmaLista.removeNoFim();
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();
    
    cout << endl;
    cout << "Apos duas remocoes no inicio" << endl;
    maisUmaLista.removeNoInicio();
    maisUmaLista.removeNoInicio();
    maisUmaLista.imprime();
    maisUmaLista.imprimeReverso();

    return 0;
}
