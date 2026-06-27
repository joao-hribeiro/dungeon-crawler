#include <bits/stdc++.h>
#include "lib/input.cpp"

#define MAX 100

using namespace std;

struct Jogo {
    int linhas, colunas, vida, dano, pocao, pontosTesouro, maxTurnos;
    int vidaAtual, turnos, tesouros, monstrosVivos; // vida atual, n_movimentos, n_tesouros, n_monstrosVivos (permitir que o jogador finalize o jogo apenas quando todos os monstros estejam mortos)
    int pX, pY; // Posicao do jogador (linha, coluna)
    int diaAtual; // é quantos dias que o jogador esta dentro da caverna
};

// Funcao para exibição dos status do jogo apos um movimento
void exibirStatus(char mapa[MAX][MAX], Jogo j) {
    cout << "\033[2J\033[H"; // limpa o terminal e joga o cursor pro topo
    cout << "=== DIA " << j.diaAtual << " ===" << endl; // mostra o dia em que o jogador esta dentro da caverna
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

// tive q tirar do loadConfig a lida do mapa, visto que toda vez que aumentasse os dias os atributos do jogador iriam resetar
int carregarMapaAleatorio(Jogo &j, char mapa[MAX][MAX]) {
    j.monstrosVivos = 0; // precisa zerar a contagem de monstros do mapa anterior
    j.turnos = 0;        // reseta os turnos para o jogador ter tempo de explorar o novo mapa

    int n = rand() % 10 + 1; // sorteia um numero aleatorio 

    string caminhoArquivo = "mapas/mapa" + to_string(n) + ".txt";// o caminhoArquivo armazena o mapa q foi sorteado 

    ifstream arqMapa(caminhoArquivo);// ve qual mapa foi sorteado 
    if (!arqMapa) {
        cout << "Erro ao abrir " << caminhoArquivo << endl;
        return 0;
    }

    for (int i = 0; i < j.linhas; i++) {// le o mapa sorteado 
        for (int k = 0; k < j.colunas; k++) {
            arqMapa >> mapa[i][k];
            if (mapa[i][k] == '@') {
                j.pX = i;
                j.pY = k;
            } else if (mapa[i][k] == 'M') {
                j.monstrosVivos++;
            }
        }
    }

    // Sistema de reconpensa progressiva
    // Percorre a matriz adicionando itens extras baseados no dia atual 

    int chanceItemExtra = j.diaAtual * 2; // +2% de chance por dia
    int contador_porcaoExtra = 0, contador_tesouroExtra = 0; // serve para limitar o tanto de porcao e tesouro extra

    for (int i = 0; i < j.linhas; i++) {

        for (int k = 0; k < j.colunas; k++) {
            // Se for chão vazio, i e j pares, tem uma chance de acontecer essas coisas
            if (mapa[i][k] == '.'&& (i%2==0&&k%2==0)) { 
                // Gera um numero entre 0 e 199, serve para gerar uma chane de o jogador ganhar uma porcao ou tesouro no espaco vazio
                int chance = rand() % 200;
                if (chance < chanceItemExtra) {
                    // Decide aleatoriamente se será Poção ou Tesouro
                    if (rand() % 2 == 0 && contador_porcaoExtra<3) {
                        mapa[i][k] = 'P';
                        contador_porcaoExtra++;

                    } else if(contador_tesouroExtra < 3) {
                        mapa[i][k] = 'T';
                        contador_tesouroExtra++;
                    }
                }
            }
        }
    }

    // Sistema de colocar monstors aleatorios com um limite de 8 monstros
    // Adiciona 1 monstro extra a cada 5 dias completos
    int monstrosExtras = j.diaAtual / 5; 
    
    // Teto de monstros extras: garante que nunca passe de 10
    if (monstrosExtras > 10) {
        monstrosExtras = 10;
    }
    
    for (int m = 0; m < monstrosExtras; m++) {
        bool posicaoEncontrada = false; // se der uma posicao que tenha como colocar o monstro ela vira true
        int tentativas = 0;
        
        // Usei um limite de tentativas para nao ter um loop infinito 
        while (!posicaoEncontrada && tentativas < 50) {// coloquei 50 tentativas para nao colocar muitos monstros muito rapido;
            // Sorteia uma linha e uma coluna aleatória na matriz
            int linhaAleatoria = rand() % j.linhas;
            int colunaAleatoria = rand() % j.colunas;
            
            // Se as coordenadas sorteadas caírem em um espaço vazio, coloca o monstro no mapa[linAle][colunaAle]
            if (mapa[linhaAleatoria][colunaAleatoria] == '.') {
                mapa[linhaAleatoria][colunaAleatoria] = 'M';
                j.monstrosVivos++; 
                posicaoEncontrada = true; // acaba o while
            }
            tentativas++;
        }
    }
    return 1;
}
// agora o loadConfig so le o arquivo config.txt, visto que o mapa nao poderia ser lido junto 
int loadConfig(Jogo &j, char mapa[MAX][MAX]){
    ifstream arqConfig("config.txt");
    if (!arqConfig){
        cout << "Erro ao abrir config.txt" << endl;
        return 0; 
    }
    arqConfig >> j.linhas >> j.colunas >> j.vida >> j.dano >> j.pocao >> j.pontosTesouro >> j.maxTurnos;
    j.vidaAtual = j.vida; 
    return carregarMapaAleatorio(j, mapa);// chama o mapa para ser processado
}

// Retorna 'true' se passou de dia, e 'false' se morreu ou apertou 'q'
bool game(Jogo &j, char mapa[MAX][MAX]){
    while (j.vidaAtual > 0 && j.turnos < j.maxTurnos) {
        exibirStatus(mapa, j);
        char comando = _getch();
        
        if (comando == 'q')
        { 
            cout<<"Jogador desistiu da caverna e foi embora!!!";    
            return false;} // coloquei um outro comando pro jogador poder desistir e acabar o jogo sem ele precisar morrer
        
        int nextX = j.pX, nextY = j.pY; 
        if (comando == 'w') nextX--; 
        else if (comando == 's') nextX++;
        else if (comando == 'a') nextY--;
        else if (comando == 'd') nextY++;
        else { 
            cout << "Comando invalido! Tente clicar somente as teclas w,s,a,d ou q para desistir!" << endl;
             _getch();// o jogo congela pois se não a mensagem é apagada instantaneamente
            continue;
        }
        
        if (nextX < 0 || nextX >= j.linhas || nextY < 0 || nextY >= j.colunas || mapa[nextX][nextY] == '#') {
            cout << "Movimento invalido!" << endl;
            _getch();// o jogo congela pois se não a mensagem é apagada instantaneamente
            continue;
        }
        
        char destino = mapa[nextX][nextY];
        if (destino == 'S') { 
            if (j.monstrosVivos > 0) { 
                cout << "Existem monstros! Derrote-os primeiro. Aperte qualquer tecla para continuar!" << endl;
                 _getch();// o jogo congela pois se não a mensagem é apagada instantaneamente
            } else {
                // Ao invés de acabar o jogo, ele avisa que o dia acabou e retorna true, pra ir para outro mapa e começar de novo
                cout << "Voce encontrou a saida! Preparando para o proximo dia..." << endl;
                cout << " (Aperte qualquer tecla para continuar)";
                _getch();// o jogo congela pois se não a mensagem é apagada instantaneamente
                return true; 
            }
        } else {
            if (destino == 'T') j.tesouros++; 
            else if (destino == 'P') j.vidaAtual += j.pocao; 
            else if (destino == 'M') {  
                j.vidaAtual -= j.dano; 
                j.monstrosVivos--;  
            }
            mapa[j.pX][j.pY] = '.'; 
            j.pX = nextX;
            j.pY = nextY;
            mapa[j.pX][j.pY] = '@'; 
            j.turnos++;
        }
    }
    
    // Se o while acabou, significa que a vida zerou ou os turnos acabaram
    cout << "--- FIM DE JOGO ---" << endl;
    cout << "Voce sobreviveu por " << j.diaAtual - 1 << " dias completos." << endl;// coloquei um contador de dias sobrevividos
    cout << "Pontuacao final: " << (j.tesouros * j.pontosTesouro) + (j.vidaAtual * 10) << endl;
    return false; // Retorna falso porque o jogador perdeu
}
int main() {
    // Inicializa o gerador de números aleatórios usando o relógio do sistema
    srand(time(NULL)); 

    Jogo j;
    char mapa[MAX][MAX];
    j.turnos = 0; j.tesouros = 0; j.monstrosVivos = 0,j.diaAtual = 1;// inicia o jogo no dia 1

    // Leitura do arquivo de configuração e mapa sorteado(nLInhas, nColunas, vida...)
    if(!loadConfig(j, mapa)) return 1;

    // O loop continua enquanto 'game' retornar true, ou seja, chegou na saída
    while (game(j, mapa)) {
        j.diaAtual++; // Aumenta o dia
        
        // Carrega um mapa novo para o próximo dia
        if (!carregarMapaAleatorio(j, mapa)) {
            break; // Se por algum erro a pasta mapas não abrir, encerra.
        }
    }

    return 0;
}