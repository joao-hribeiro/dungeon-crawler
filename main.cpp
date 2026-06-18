#include <bits/stdc++.h>
#include "lib/input.cpp"

#define MAX 100

using namespace std;

struct Jogo {
    int linhas, colunas, vida, dano, pocao, pontosTesouro, maxTurnos;
    int vidaAtual, turnos, tesouros, monstrosVivos; // vida atual, n_movimentos, n_tesouros, n_monstrosVivos (permitir que o jogador finalize o jogo apenas quando todos os monstros estejam mortos)
    int pX, pY; // Posicao do jogador (linha, coluna)
};

// Funcao para exibição dos status do jogo apos um movimento
void exibirStatus(char mapa[MAX][MAX], Jogo j) {
    cout << "Vida: " << j.vidaAtual << endl;
    cout << "Pontuacao: " << (j.tesouros * j.pontosTesouro) << endl;
    cout << "Turnos: " << j.turnos << "/" << j.maxTurnos << endl;
    cout << "Tesouros coletados: " << j.tesouros << endl;
    for (int i = 0; i < j.linhas; i++) {
        for (int k = 0; k < j.colunas; k++) {
            cout << mapa[i][k];             // carrega mapa
        }
        cout << endl;
    }
}

int loadConfig(Jogo &j, char mapa[MAX][MAX]){
    ifstream arqConfig("config.txt");
    if (!arqConfig){
        cout << "Erro ao abrir config.txt" << endl;
        return 0; // encerra o programa
    }
    arqConfig >> j.linhas >> j.colunas >> j.vida >> j.dano >> j.pocao >> j.pontosTesouro >> j.maxTurnos;
    j.vidaAtual = j.vida; // Recebendo os parametros
    // Leitura do arquivo com o mapa 
    ifstream arqMapa("mapa.txt");
    if (!arqMapa){
        cout << "Erro ao abrir mapa.txt" << endl;
        return 0; // encerra o programa
    }
    for (int i = 0; i < j.linhas; i++) {
        for (int k = 0; k < j.colunas; k++) {
            arqMapa >> mapa[i][k]; // recebe o mapa
            if (mapa[i][k] == '@') { // encontra o jogador
                j.pX = i; // armazena a posicao da linha do jogador
                j.pY = k; // armazena a posicao da coluna do jogador
            } else if (mapa[i][k] == 'M') j.monstrosVivos++; // armazena o numero de monstros vivos para controle
        }
    }
    return 1;
}

void game(Jogo &j, char mapa[MAX][MAX]){
    char comando;
    while (j.vidaAtual > 0 && j.turnos < j.maxTurnos) {
        exibirStatus(mapa, j);
        char comando = _getch();
        
        if (comando == 'q') break; // comando para sair do jogo
        int nextX = j.pX, nextY = j.pY; // inicializa a direcao do deslocamento
        if (comando == 'w') nextX--; // [61-64] -> acrescenta aos deslocamentos pelo eixo a direcao do movimento
        else if (comando == 's') nextX++;
        else if (comando == 'a') nextY--;
        else if (comando == 'd') nextY++;
        else { 
            cout << "Comando invalido!" << endl;
            continue;
        }
        
        // Validação de limites e paredes (verifica se o jogador pode realizar o movimento ou nao)
        if (nextX < 0 || nextX >= j.linhas || nextY < 0 || nextY >= j.colunas || mapa[nextX][nextY] == '#') {
            cout << "Movimento invalido!" << endl;
            continue;
        }
        // Lógica de interações
        char destino = mapa[nextX][nextY];
        if (destino == 'S') { // verifica se eh a saida
            if (j.monstrosVivos > 0) { // o jogo so finaliza se nao houver mais monstros vivos
                cout << "Existem monstros!" << endl;
            } else {
                cout << "Vitoria! Pontuacao: " << (j.tesouros * j.pontosTesouro) + (j.vidaAtual * 10) - j.turnos << endl;
                return; // jogo finaliza como indicado 
            }
        } else {
            if (destino == 'T') j.tesouros++; // verifica se eh um tesouro
            else if (destino == 'P') j.vidaAtual += j.pocao; // verifica se eh uma pocao
            else if (destino == 'M') {  // verifica se eh um monstro
                j.vidaAtual -= j.dano; // sendo um monstro, o jogador sofre um dano
                j.monstrosVivos--;  // um monstro morre
            }
            mapa[j.pX][j.pY] = '.'; // substitui por '.' pois foi coletado o bem ou morto (no caso do monstro)
            j.pX = nextX;
            j.pY = nextY;
            mapa[j.pX][j.pY] = '@'; // substitui por '@' pois o jogo avancouo
            j.turnos++;
        }
    }
    // jogo finalizado -> so finaliza com a pontuacao zerada. Entao: pontuacao = 0
    cout << "Fim de jogo. Pontuacao: 0" << endl;
}

int main() {
    Jogo j;
    char mapa[MAX][MAX];
    j.turnos = 0; j.tesouros = 0; j.monstrosVivos = 0;

    // Leitura do arquivo de configuração (nLinhas, nColunas, vida...)
    if(!loadConfig(j, mapa)) return 1;
    
    // Loop principal de jogo - recarrega o mapa e recebe o comando
    game(j, mapa);

    return 0;
}