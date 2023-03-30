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

// para facilitar a troca de int para outro tipo
// estamos criando um apelido para int chamado dado
// com issso, destaca-se que a lista pode ser uma lista
// de qualquer objeto, não apenas inteiros...
// ou seja, é uma lista de dados.
typedef int Dado; //typedef permite criar novos tipos a partir de outros

class noh{
	friend class listadup;
	private:
		// dado está como constante para não permitir alteração//
		const Dado dado; // poderia ser outro tipo de variável
		noh* proximo;
		noh* anterior;
	public:
		//noh();
		noh(Dado d = 0);
};

// construindo dado chamando seu construtor
noh::noh(Dado d) : dado(d){
	//dado = d;
	proximo = NULL;
	anterior = NULL;
}

// lista dinamicamente encadeada
class listadup{
private:
	noh* primeiro;
	noh* ultimo;
	int tamanho;
	void removeTodos();// remove todos os elementos da lista
public:
	// construtores e destrutores
	listadup();
	listadup(const listadup& umaLista);
	~listadup();
	// sobrecarga do operador de atribuição
	listadup& operator=(const listadup& umaLista);
	// inserção, remoção e procura
	inline void insere(Dado dado);
	void insereNoFim(Dado dado);
	void insereNoInicio(Dado dado);
	void insereNaPosicao(int posicao, Dado dado);
	int procura (Dado valor); // retorna a posição
	// métodos adicionais (impressão, vazia)
	void imprime();
	inline bool vazia();
	void removeNoInicio();
	void removeNoFim();
	void removeValor(Dado valor);
};

// constrói uma lista inicialmente vazia
listadup::listadup(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// construtor de copia
listadup::listadup(const listadup& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

	// percorre a lista recebida como parâmetro, copian do os dados
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}

// destrutor da lista (chama a função privada aux)
listadup::~listadup(){
	removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos(){
	noh* aux = primeiro;
	noh* temp;
	
	while(aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	// redirecionado ponteiros
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// sobrecarga do operador de atruibuição
listadup& listadup::operator =(const listadup& umaLista){
	// limpa a lista atual
	removeTodos();
	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
	return *this;
}

// insere por padrão no final da lista
void listadup::insere(Dado dado){
	insereNoFim(dado);
}

// insere no final da lista 
void listadup::insereNoFim(Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// * agora inserioms o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	}
	else{ // já tem elementos na lista, insere no final
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// * agora inserioms o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	}
	else{ // já tem elementos na lista, insere no início
		novo->proximo = primeiro;
		primeiro->anterior = novo;
		primeiro = novo;
	}
	tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if( (posicao <= tamanho) and (posicao >= 0) ){
		if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
			primeiro = novo;
			ultimo = novo;
		}
		else if(posicao == 0){ // insere no início
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}
		else if( posicao == tamanho){ // insere no fim
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}
		else{ // insere no meio da lista
			noh* aux = primeiro;
			int posaux = 0;
			
			// chegando na posição da lista
			while( posaux < (posicao-1) ){
				aux = aux->proximo;
				posaux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
		tamanho++;
	}
	else{
		cerr << "Posicao inexistente!" << endl;
		exit(EXIT_FAILURE);
	}
}

int listadup::procura(Dado valor){
	noh* aux = primeiro;
	int posAux = 0;
	
	while((aux != NULL) and (aux->dado != valor)){
		posAux++;
		aux = aux->proximo;
	}
	if(aux == NULL){
		posAux = -1;
	}
	return posAux;
}

// método básico que percorre uma lista, imprimindo seus elementos
void listadup::imprime(){
	noh* aux = primeiro;
	
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
	
	// imprime reverso(para mostrar o duplo encadeamento)
	aux = ultimo;
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}

// verifica SE ESTÁ VAZIA
inline bool listadup::vazia(){
	return (tamanho == 0);
}

void listadup::removeNoInicio(){
	if ( vazia() ){
		cerr << "Remoção em lista vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	noh* removido = primeiro;
	primeiro = primeiro->proximo;
	if(primeiro != NULL) primeiro->anterior = NULL;
	delete removido;
	
	tamanho--;
	if( vazia() )ultimo = NULL;
}

void listadup::removeNoFim(){
	if ( vazia() ){
		cerr << "Remoção em lista vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	noh* removido = ultimo;
	ultimo = ultimo->anterior;
	if(ultimo != NULL) ultimo->proximo = NULL;
	delete removido;
	
	tamanho--;
	if( vazia() )ultimo = NULL;
}

void listadup::removeValor(Dado valor){
	noh* aux = primeiro;
	
	while((aux != NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	if(aux == NULL){
		cerr << "Erro: remoção de valor não encontrado!" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		noh* anterior = aux->anterior;
		noh* proximo = aux->proximo;
		if(anterior != NULL) anterior->proximo = proximo;
		else primeiro = aux->proximo;
		if(proximo != NULL) proximo->anterior = anterior;
		else ultimo = aux->anterior;
		delete aux;
	}
	tamanho--;
	if( vazia() ){
		ultimo = NULL;
		primeiro = NULL;
	}
}

int main (){
	listadup minhaLista;
	
	cout <<" == Teste da lista == "<< endl;
	
	minhaLista.insere(5);
	minhaLista.insere(3);
	minhaLista.insere(1);
	minhaLista.insere(0);
	minhaLista.insere(6);
	minhaLista.insereNoInicio(18);
	minhaLista.insereNaPosicao(3,25);
	minhaLista.imprime();
	
	cout << minhaLista.procura(3) << endl;
	cout << minhaLista.procura(50) << endl;
	cout << minhaLista.procura(6) << endl;
	
	// construtor de cópia
	cout << "Sobrecarga do construtor de cópia" << endl;
	listadup outraLista(minhaLista);
	outraLista.insereNoInicio(99);
	outraLista.insereNoFim(10);
	
	// sobrecarga de operador de atribuição
	cout << "Sobrecarga do operador de atribuição" << endl;
	listadup maisUmaLista;
	maisUmaLista = outraLista;
	maisUmaLista.insereNoInicio(31);
	maisUmaLista.insereNoFim(13);
	
	cout << endl;
	minhaLista.imprime();
	cout << endl;
	outraLista.imprime();
	cout << endl;
	maisUmaLista.imprime();
	cout << endl;
	
	cout << "Após remover:" << endl;
	minhaLista.removeNoFim();
	minhaLista.removeNoInicio();
	minhaLista.removeNoFim();
	minhaLista.removeNoInicio();
	minhaLista.removeNoFim();
	minhaLista.removeNoInicio();
	minhaLista.imprime();
	cout << endl;
	
	cout <<"25 removido." << endl;
	minhaLista.removeValor(25);
	minhaLista.imprime();
	cout << endl;
	
	outraLista.removeValor(10);
	outraLista.imprime();
	cout << endl;
	
	maisUmaLista.removeValor(31);
	maisUmaLista.removeValor(25);
	maisUmaLista.imprime();
	cout << endl;
	
	minhaLista.insere(0);
	minhaLista.imprime();
	minhaLista.insereNoInicio(12);
	minhaLista.imprime();
	
	return 0;
}
