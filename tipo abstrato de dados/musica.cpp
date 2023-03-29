/*
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩      
 *                   
    musica.cpp - aplicação para desenvolvimento de atividade
    de Tipo Abstrato de Dados

    Atividade de  GCC216 - Estruturas de Dados, 2020

    Solução de: MICHEL ALEXANDRINO DE SOUZA
*/

#include <iostream>

using namespace std;

struct musica {
    string nomeDoProduto;
    int diasConsiderados;
    int quantidadeDeSolicitacoes;
    musica();
};

musica::musica() {
    nomeDoProduto.clear();
    diasConsiderados = 0;
    quantidadeDeSolicitacoes = 0;
}

class radio {
    private:
        // *** AVISO: Não altere os atributos privados da classe ***
        musica* listaDeMusicas;
        int quantidadeDeItens;
        int capacidadeMaxima;
    public:
        radio(int capacidade);
        radio(const radio& copia);  //construtor de cópia
        ~radio();
        void inserirNovaMusica(const musica& ummusica);
        bool buscarradio(const string& nome, musica& ummusica);
        void redimensionarCapacidade();
        friend void verificarAsMaisPedidas(radio umradio, int dias);
};

radio::radio(int capacidade) {
    quantidadeDeItens = 0;
    capacidadeMaxima = capacidade;
    listaDeMusicas = new musica[capacidadeMaxima];
}

//construtor de cópia
radio::radio(const radio& copia) {
	quantidadeDeItens = copia.quantidadeDeItens;
	capacidadeMaxima = copia.capacidadeMaxima;
	listaDeMusicas = new musica[capacidadeMaxima];
	copy(copia.listaDeMusicas, copia.listaDeMusicas + copia.quantidadeDeItens, listaDeMusicas);
}

radio::~radio() {
    delete [] listaDeMusicas;
}

void radio::inserirNovaMusica(const musica& ummusica) {
    if (quantidadeDeItens == capacidadeMaxima) { // vetor cheio, precisa redimensionar
        redimensionarCapacidade();
    }
    listaDeMusicas[quantidadeDeItens] = ummusica;
    quantidadeDeItens++;
}

bool radio::buscarradio(const string& nome, musica& ummusica) {
    int posicaoAtual = 0;

    while (posicaoAtual < quantidadeDeItens and
           listaDeMusicas[posicaoAtual].nomeDoProduto != nome)
        posicaoAtual++;

    // se posicaoAtual não for menor que quantidade de produtos, é porque não encontrou
    if (posicaoAtual < quantidadeDeItens) {
        ummusica = listaDeMusicas[posicaoAtual];
        return true;
    }

    return false;
}

void radio::redimensionarCapacidade() {
	musica *listaAux = new musica[capacidadeMaxima + 4];
	copy(listaDeMusicas, listaDeMusicas + quantidadeDeItens, listaAux);
	delete[] listaDeMusicas;
	
	capacidadeMaxima = capacidadeMaxima + 4;
	
	listaDeMusicas = new musica[capacidadeMaxima];
	copy(listaAux, listaAux + quantidadeDeItens, listaDeMusicas);
	delete[] listaAux;
}

void verificarAsMaisPedidas(radio umradio, int dias) {
    // *** AVISO: Não altere esta função ***
    for (int i = 0; i < umradio.quantidadeDeItens; i++) {
      if (umradio.listaDeMusicas[i].diasConsiderados <= dias)
            cout << umradio.listaDeMusicas[i].nomeDoProduto << " " << umradio.listaDeMusicas[i].quantidadeDeSolicitacoes << endl;
    }
    cout << endl;
}


int main() {
    // *** AVISO: Não altere a função principal, o main() ***
    int capacidadeInicial;

    cout << "radio - Aplicativo para Rádios\n"
         << "Entre com capacidade máxima inicial: ";
    cin >> capacidadeInicial;

    radio meuradio(capacidadeInicial);

    cout << "radio - Escolha a Opção:\n"
         << "i - inserir nova musica\n"
         << "b - buscar por um dada musica a partir do nome\n"
         << "v - verificar musicas mais tocadas\n"
         << "s - para sair do programa" << endl;

    char opcaoDoMenu;
    musica ummusica;
    string nome;
    int dias;

    cin >> opcaoDoMenu;

    while (opcaoDoMenu != 's') {
        switch(opcaoDoMenu) {
            case 'i' :
                cout << "Entre com dados do musica (nome da música, dias a serem considerados na contabilização das mais pedidas, quantidade de vazes solicitadas):" << endl;
                cin >> ummusica.nomeDoProduto
                    >> ummusica.diasConsiderados
                    >> ummusica.quantidadeDeSolicitacoes;
                meuradio.inserirNovaMusica(ummusica);
                break;

            case 'b' :
                cout << "Entre com nome do musica para busca: ";
                cin >> nome;

                if (meuradio.buscarradio(nome, ummusica))
                    cout << ummusica.nomeDoProduto << " "
                         << ummusica.diasConsiderados << " "
                         << ummusica.quantidadeDeSolicitacoes << endl << endl;
                else
                    cout << "musica não encontrado!" << endl << endl;
                break;

            case 'v' :
                cout << "Entre com quantidade de dias para verificação: ";
                cin >> dias;
                verificarAsMaisPedidas(meuradio, dias);
                break;

            case 's' : // não faz nada, espera retorno ao while para sair
                break;

            default:
                cout << "Opção inválida!" << endl;
                break;

        }
        cout << "radio - Escolha a Opção:\n"
            << "i - inserir novo musica\n"
            << "b - buscar por um dado musica a partir do nome\n"
            << "v - verificar musicas mais tocadas\n"
            << "s - para sair do programa" << endl;
        cin >> opcaoDoMenu;
    }

    return 0;
}
