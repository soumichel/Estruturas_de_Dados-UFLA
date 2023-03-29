/*
========================================================================
 * ╦ ╦╔═╗╦  ╔═╗                          
 * ║ ║╠╣ ║  ╠═╣  *
 * ╚═╝╚  ╩═╝╩ ╩                        
 * 
 * Nome: Michel Alexandrino de Souza
 * Turma: 14B
 * Professores: Joaquim Uchôa, Renato Ramos - GAC108 (2022/1)
 * 
 * Enunciado 8
 * 
 * EXPLICAÇÃO PASSO A PASSO:
 * 
 *  - TODOS OS PROCEDIMENTOS FEITOS NA CLASSE POKEDEX -
 *  Entrada de valores (cadastro dos Pokemons e Treinadores com tamanho
 *  de vetor definido em 100)
 *  Procedimento que realiza a verificação do tipo do pokemon e o exibe.
 *  Procedimento que compara a variavel melhorContra (entrada no
 *  cadastro do treinador) com a variavel tipo (entrada no
 *  cadastro pokemon) e também compara o nome do treinador
 *  com o argumento indicado.
 * 
 *  - MAIN -
 *  Entrada de valores pelo usuário, alocação da memória, e chamada das
 *  funções.
========================================================================
 */

#include <iostream>
#include <string>
using namespace std;

//Entidade Documento
struct Pokemon{
    string nome;
    string tipo;
    int posicaoPokedex;
    float velocidade;
    float ataque;
    float defesa;
    float ataqueEsp;
    float defesaEsp;
};

//Entidade Artista
struct Treinador{
    string nome;
    string nomeGinasio;
    string tipoPreferido;
    string melhorContra;
};

//Método utilizado para os procedimentos necessários (Registros e Listagem)
class Pokedex{
    private:
        Pokemon cadastro[100];
        Treinador cadastroT[100];
        
    public:
        int numPoke;
        int numTreinador;
        
        void registrarCadastroPoke(){
            cout << " =========================== | Ola Treinador, bem vindo! | ===========================" << endl << endl;
            cout << "Quantos Pokemons serao cadastrados? (O programa tem um limite de cadastro de 100 pokemons!)" << endl;
            cin >> numPoke;
            cout << endl;
            
            for (int i=0; i<numPoke; i++){
                cout << "     ====================     " << endl;
                cout << "=== | CADASTRO POKEMON " << i+1 << " | ===" << endl;
                cout << "     ====================     " << endl << endl;
                
                cout << "Insira o nome do Pokemon: ";
                getline(cin >> ws, cadastro[i].nome);
                
                cout << "Insira o tipo do Pokemon: ";
                getline(cin >> ws, cadastro[i].tipo);
                
                cout << "Posicao na Pokedex: ";
                cadastro[i].posicaoPokedex = rand() % 100;
                cout << cadastro[i].posicaoPokedex << endl;
                
                cout << "Insira a velocidade: ";
                cin >> cadastro[i].velocidade;
                
                cout << "Insira o ataque: ";
                cin >> cadastro[i].ataque;
                
                cout << "Insira a defesa: ";
                cin >> cadastro[i].defesa;
                
                cout << "Insira o ataque especial: ";
                cin >> cadastro[i].ataqueEsp;
                
                cout << "Insira a defesa especial: ";
                cin >> cadastro[i].defesaEsp;
                
                cout << endl;
            }
        }
        
        void registrarCadastroTreinador(){
            cout << endl;
            cout << "Quantos Treinadores serao cadastrados? (O programa tem um limite de cadastro de 100 treinadores!)" << endl;
            cin >> numTreinador;
            cout << endl;
            
            for (int i=0; i<numTreinador; i++){
                cout << "  ======================     " << endl;
                cout << " | CADASTRO TREINADOR " << i+1 << " |" << endl;
                cout << "  ======================     " << endl << endl;
                
                cout << "Insira o nome do treinador: ";
                getline(cin >> ws, cadastroT[i].nome);
                
                cout << "Insira o nome do ginasio: ";
                getline(cin >> ws, cadastroT[i].nomeGinasio);
                
                cout << "Insira o tipo preferido do treinador: ";
                getline(cin >> ws, cadastroT[i].tipoPreferido);
                
                cout << "Insira o melhor tipo de pokemon para se usar contra: ";
                getline(cin >> ws, cadastroT[i].melhorContra);
            }
            cout << " =========================== | CADASTROS FINALIZADOS COM SUCESSO! | ===========================" << endl;
            cout << endl;
        }
        
        //Realizar a verificação do tipo e exibir os pokemons
        void listarPokemonsMesmoTipo(string tipo) {
            cout << "=== POKEMONS CADASTRADOS DO MESMO TIPO ===" << endl << endl;
            
            for (int i=0; i<numPoke; i++){
                if (tipo == cadastro[i].tipo){
                    cout << cadastro[i].nome << endl;
                } else{
                    cout << "NAO HA POKEMONS REGISTRADOS DESTE TIPO!" << endl;;
                }
            }
            cout << endl;
        }
        
        //Mostrar o melhor tipo pra se usar contra o treinador
        void listarMelhorContra(string nomeTreinador) {
            cout << endl;
            cout << " === POKEMONS INDICADOS PARA SE USAR CONTRA O TREINADOR ===" << endl << endl;
            
            for (int i=0; i<numTreinador; i++){
                for (int j=0; j<numPoke; j++){
                    if (cadastroT[i].melhorContra == cadastro[j].tipo and cadastroT[i].nome == nomeTreinador){
                        cout << cadastro[j].nome << endl;
                    } else{
                        cout << "VOCE NAO HA POKEMONS EFICAZES CONTRA ESTE TREINADOR!" << endl;
                    }
                }
            }
            cout << endl;
        }
};

int main() {
    Pokedex *exibir = new Pokedex();
    exibir->registrarCadastroPoke();
    exibir->registrarCadastroTreinador();
    
    cout << "Qual Treinador voce gostaria de visualizar?" << endl;
    string treinador;
    cin >> treinador;
    exibir->listarMelhorContra(treinador);
    
    cout << "Qual o tipo do pokemon que voce deseja listar?" << endl;
    string tipo;
    cin >> tipo;
    cout << endl;
    exibir->listarPokemonsMesmoTipo(tipo);
    return 0;
}
