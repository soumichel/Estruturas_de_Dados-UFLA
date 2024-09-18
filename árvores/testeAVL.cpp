/*

 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 * 

Implementação de uma Árvore AVL com operações de inserção, busca, remoção e exibição da estrutura. 
A árvore armazena chaves inteiras e utiliza o atributo de altura nos métodos de escrita. 

Entradas:
O programa lê códigos de comandos a executar. Sempre um caractere identificando o comando, seguido dos parâmetros necessários para executar o comando, se houverem. 
Os códigos de comandos são:

i: para inserir um elemento (string / número real) à árvore, sendo que os dados são ordenados pela string;
b: para buscar um valor (número real) associado a uma chave (string);
r: para remover um elemento, seguido da chave (string) do elemento;
e: para escrever a estrutura da árvore.

Saídas:
Somente o comando para escrever produz saída no formato especificado, que já está implementado.

Exemplo de Entrada:
i andre 19
e
i antonio 29
e
i carla 28
e
i diego 52
e
i eduardo 63
e
r diego
e
r antonio
e
b eduardo
f
Exemplo de Saída:

[1:andre/19]
[] []

[2:andre/19]
[] [1:antonio/29]
[] []

[2:antonio/29]
[1:andre/19] [1:carla/28]
[] [] [] []

[3:antonio/29]
[1:andre/19] [2:carla/28]
[] [] [] [1:diego/52]
[] []

[3:antonio/29]
[1:andre/19] [2:diego/52]
[] [] [1:carla/28] [1:eduardo/63]
[] [] [] []

[3:antonio/29]
[1:andre/19] [2:eduardo/63]
[] [] [1:carla/28] []
[] []

[2:carla/28]
[1:andre/19] [1:eduardo/63]
[] [] [] []

63*/

#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <queue>
using namespace std;

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

class NohAVL;

class AVL {
public:
    AVL();
    ~AVL();
    TValor& Valor(TChave chave);
    void EscreverEmOrdem();
    void EscreverNivelANivel(std::ostream& saida);
    void Inserir(TChave chave, const TValor& valor);
    bool ConferirLigacoes();
    void Remover(TChave chave);
private:
    NohAVL* mPtRaiz;
};

class NohAVL {
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
        if (ptNoh == NULL) {
        saida << "[]";
    } else {
        saida << '['  << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    }
    return saida;
}
    friend void AVL::EscreverNivelANivel(std::ostream& saida);
public:
    NohAVL(TChave c, const TValor& v);
    ~NohAVL();
    void DesalocarFilhosRecursivo();
    NohAVL* InserirRecursivo(NohAVL* ptNoh);
    NohAVL* MenorRecursivo();
    NohAVL* RemoverRecursivo(TChave chave);
    TValor& Valor(TChave chave);
private:
    NohAVL* ArrumarBalanceamento();
    void AtualizarAltura();
    int FatorBalanceamento();
    NohAVL* Remover();
    NohAVL* RotacionarEsquerda();
    NohAVL* RotacionarDireita();
    void SubstitutirPor(NohAVL* ptNoh);
    void Transplantar(NohAVL* ptFilho);
    void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
    TChave mChave;
    TValor mValor;
    NohAVL* mPtEsq;
    NohAVL* mPtDir;
    NohAVL* mPtPai;
    unsigned int mAltura; // folhas têm altura 1
};

NohAVL::NohAVL(TChave c, const TValor& v)
    : mChave(c), mValor(v), mPtEsq(NULL), mPtDir(NULL), mPtPai(NULL), mAltura(1) {
}

NohAVL::~NohAVL() {
}

// Atualiza a altura do nó.
void NohAVL::AtualizarAltura() {
    int alturaEsq = (mPtEsq) ? mPtEsq->mAltura : 0;
    int alturaDir = (mPtDir) ? mPtDir->mAltura : 0;
    mAltura = 1 + max(alturaEsq, alturaDir);
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
    int alturaEsq = (mPtEsq) ? mPtEsq->mAltura : 0;
    int alturaDir = (mPtDir) ? mPtDir->mAltura : 0;
    return alturaEsq - alturaDir;
}

// Faz as rotações e ajustes necessários para balancear o nó.
NohAVL* NohAVL::ArrumarBalanceamento() {
    AtualizarAltura();
    int fatorBal = FatorBalanceamento();
    if (fatorBal > 1) {
        if (mPtEsq && mPtEsq->FatorBalanceamento() < 0) {
            mPtEsq = mPtEsq->RotacionarEsquerda();
        }
        return RotacionarDireita();
    }
    else if (fatorBal < -1) {
        if (mPtDir && mPtDir->FatorBalanceamento() > 0) {
            mPtDir = mPtDir->RotacionarDireita();
        }
        return RotacionarEsquerda();
    }
    return this;
}

// Rotaciona à direita a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
    NohAVL* aux = mPtEsq;
    mPtEsq = aux->mPtDir;
    if (aux->mPtDir) aux->mPtDir->mPtPai = this;
    aux->mPtPai = mPtPai;
    aux->mPtDir = this;
    mPtPai = aux;
    AtualizarAltura();
    aux->AtualizarAltura();
    return aux;
}

// Rotaciona à esquerda a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
    NohAVL* aux = mPtDir;
    mPtDir = aux->mPtEsq;
    if (aux->mPtEsq) aux->mPtEsq->mPtPai = this;
    aux->mPtPai = mPtPai;
    aux->mPtEsq = this;
    mPtPai = aux;
    AtualizarAltura();
    aux->AtualizarAltura();
    return aux;
}

// Insere um nó numa subárvore. Retorna o ponteiro para o nó que ficou no lugar do que recebeu
// a mensagem.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
    if (ptNoh->mChave < mChave) {
        if (mPtEsq == NULL) {
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        }
        else {
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    }
    else {
        if (mPtDir == NULL) {
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        }
        else {
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

// Busca o nó que tem a menor chave. Retorna o ponteiro para ele.
NohAVL* NohAVL::MenorRecursivo() {
    if (mPtEsq == NULL) return this;
    else return mPtEsq->MenorRecursivo();
}

// Remove o nó. Retorna o ponteiro para o nó que ficou no lugar dele.
NohAVL* NohAVL::Remover() {
    if (mPtEsq == NULL && mPtDir == NULL) { // Nó folha
        return NULL;
    }
    else if (mPtEsq == NULL) { // Só tem filho à direita
        mPtDir->mPtPai = mPtPai;
        return mPtDir;
    }
    else if (mPtDir == NULL) { // Só tem filho à esquerda
        mPtEsq->mPtPai = mPtPai;
        return mPtEsq;
    }
    else { // Nó tem dois filhos
        NohAVL* sucessor = mPtDir->MenorRecursivo();
        mChave = sucessor->mChave;
        mValor = sucessor->mValor;
        mPtDir = mPtDir->RemoverRecursivo(sucessor->mChave);
        return ArrumarBalanceamento();
    }
}

// Busca recursivamente um nó com dada chave e o remove. Retorna o ponteiro para o nó que ficou
// no lugar do nó que recebeu a mensagem.
NohAVL* NohAVL::RemoverRecursivo(TChave chave) {
    if (chave < mChave) {
        if (mPtEsq != NULL) mPtEsq = mPtEsq->RemoverRecursivo(chave);
    }
    else if (chave > mChave) {
        if (mPtDir != NULL) mPtDir = mPtDir->RemoverRecursivo(chave);
    }
    else {
        return Remover();
    }
    return ArrumarBalanceamento();
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
    if (mPtEsq) {
        mPtEsq->DesalocarFilhosRecursivo();
        delete mPtEsq;
    }
    if (mPtDir) {
        mPtDir->DesalocarFilhosRecursivo();
        delete mPtDir;
    }
}

// Busca recursivamente uma dada chave e retorna o valor associado a ela.
// Levanta exceção se não encontrar a chave.
TValor& NohAVL::Valor(TChave chave) {
    if (chave == mChave) return mValor;
    else if (chave < mChave) {
        if (mPtEsq == NULL) throw runtime_error("Chave não encontrada.");
        else return mPtEsq->Valor(chave);
    }
    else {
        if (mPtDir == NULL) throw runtime_error("Chave não encontrada.");
        else return mPtDir->Valor(chave);
    }
}

AVL::AVL() : mPtRaiz(NULL) {
}

AVL::~AVL() {
    if (mPtRaiz != NULL) {
        mPtRaiz->DesalocarFilhosRecursivo();
        delete mPtRaiz;
    }
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    NohAVL* novoNoh = new NohAVL(chave, valor);
    if (mPtRaiz == NULL) {
        mPtRaiz = novoNoh;
    }
    else {
        mPtRaiz = mPtRaiz->InserirRecursivo(novoNoh);
    }
}

// Remove da árvore o nó que tiver uma dada chave.
void AVL::Remover(TChave chave) {
    if (mPtRaiz == NULL)
        throw runtime_error("Tentativa de remover elemento de uma árvore vazia.");
    else
        mPtRaiz = mPtRaiz->RemoverRecursivo(chave);
}

// Retorna o valor associado a uma dada chave.
TValor& AVL::Valor(TChave chave) {
    if (mPtRaiz == NULL)
        throw runtime_error("Tentativa de buscar valor numa árvore vazia.");
    return mPtRaiz->Valor(chave);
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'r': // Remover
                try {
                    cin >> chave;
                    minhaArvore.Remover(chave);
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'b': // Buscar
                try {
                    cin >> chave;
                    valor = minhaArvore.Valor(chave);
                    cout << valor << endl;
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
