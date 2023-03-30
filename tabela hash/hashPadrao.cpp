/* 
 * 
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 
 */

#include <iostream>

using namespace std;

class Noh{
    private:
        int chave;
        Noh* proximo;
    public:
        Noh(int chave){
            this->chave = chave;
            this->proximo = NULL;
        }
        int getChave(){
            return this->chave;
        }
        Noh* getProximo(){
            return this->proximo;
        }
        void setProximo(Noh* noh){
            this->proximo = noh;
        }
};

class Hash{
    private:
        Noh** tabela;
        int tamanho;
        int qtdElementos;
    public:
        Hash(int tamanho){
            this->tamanho = tamanho;
            this->tabela = new Noh*[tamanho];
            for(int i = 0; i < tamanho; i++){
                this->tabela[i] = NULL;
            }
            this->qtdElementos = 0;
        }
        int getTamanho(){
            return this->tamanho;
        }
        int getQtdElementos(){
            return this->qtdElementos;
        }
        void inserir(int chave){
            int posicao = chave % this->tamanho;
            Noh* noh = new Noh(chave);
            if(this->tabela[posicao] == NULL){
                this->tabela[posicao] = noh;
            }else{
                Noh* aux = this->tabela[posicao];
                while(aux->getProximo() != NULL){
                    aux = aux->getProximo();
                }
                aux->setProximo(noh);
            }
            this->qtdElementos++;
        }
        void remover(int chave){
            int posicao = chave % this->tamanho;
            if(this->tabela[posicao] != NULL){
                Noh* aux = this->tabela[posicao];
                if(aux->getChave() == chave){
                    this->tabela[posicao] = aux->getProximo();
                    delete aux;
                    this->qtdElementos--;
                }else{
                    while(aux->getProximo() != NULL){
                        if(aux->getProximo()->getChave() == chave){
                            Noh* aux2 = aux->getProximo();
                            aux->setProximo(aux2->getProximo());
                            delete aux2;
                            this->qtdElementos--;
                            break;
                        }
                        aux = aux->getProximo();
                    }
                }
            }
        }
        void imprimir(){
            for(int i = 0; i < this->tamanho; i++){
                if(this->tabela[i] != NULL){
                    Noh* aux = this->tabela[i];
                    while(aux != NULL){
                        cout << aux->getChave() << " ";
                        aux = aux->getProximo();
                    }
                    cout << endl;
                }
            }
        }
};

int main(){

    

    return 0;
}
