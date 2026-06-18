# Dungeon Crawler no Terminal 🎮⚔️

[cite_start]Trabalho prático desenvolvido para a disciplina **DC5199 - Algoritmos (Prática)** do Departamento de Ciência da Computação da **Universidade Federal de Juiz de Fora (UFJF)**[cite: 1].

## 📝 Sobre o Projeto

[cite_start]Este projeto consiste em uma versão simplificada de um jogo do tipo **Dungeon Crawler**, totalmente executado via terminal e desenvolvido em **C++**[cite: 8]. [cite_start]O jogador controla um herói representado por uma matriz de caracteres, cujo objetivo é explorar uma masmorra, coletar tesouros, sobreviver a combates com monstros e gerenciar seus recursos até encontrar a saída[cite: 9, 10].

[cite_start]O motor do jogo funciona baseado em turnos e processa arquivos de configuração dinâmicos, permitindo customizar completamente o mapa e os atributos da partida[cite: 28, 41].

---

## 🛠️ Funcionalidades e Mecânicas

* [cite_start]**Movimentação Baseada em Turnos**: Controle intuitivo utilizando as teclas clássicas `W`, `A`, `S`, `D`[cite: 13, 116].
* [cite_start]**Geração Dinâmica via Arquivos**: O mapa e as variáveis de jogo (vida inicial, dano, turnos máximos) são carregados de forma dinâmica através de arquivos de texto (`config.txt` e `mapa.txt`)[cite: 41, 43, 61].
* [cite_start]**Sistema de Validação Estrita**: O programa valida as dimensões da matriz e a presença de elementos obrigatórios (como herói, tesouro e saída única) antes de iniciar[cite: 71, 75, 113, 114].
* **Elementos Interativos**:
  * [cite_start]💰 **Tesouros (`T`)**: Incrementam a pontuação[cite: 12, 32].
  * [cite_start]🧪 **Poções (`P`)**: Recuperam a saúde do jogador[cite: 12, 33].
  * [cite_start]👾 **Monstros (`M`)**: Causam dano ao herói antes de serem derrotados[cite: 12, 34].
  * [cite_start]🚪 **Saída (`S`)**: Só permite a vitória se todos os monstros da masmorra forem eliminados[cite: 12, 35].

---

## 🗺️ Representação do Mapa

[cite_start]A masmorra utiliza uma interface textual simples e limpa baseada nos seguintes elementos[cite: 11]:

| Símbolo | Significado |
| :---: | :--- |
| `@` | [cite_start]Jogador [cite: 12] |
| `#` | [cite_start]Parede (Obstáculo intransponível) [cite: 12, 30] |
| `.` | [cite_start]Caminho livre [cite: 12] |
| `M` | [cite_start]Monstro [cite: 12] |
| `T` | [cite_start]Tesouro [cite: 12] |
| `P` | [cite_start]Poção [cite: 12] |
| `S` | [cite_start]Saída da masmorra [cite: 12] |

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
Certifique-se de ter um compilador que suporte C++11 ou superior (como o `g++`).

### Passos para compilação

1. Clone o repositório:
   ```bash
   git clone [https://github.com/seu-usuario/dungeon-crawler-terminal.git](https://github.com/seu-usuario/dungeon-crawler-terminal.git)
   cd dungeon-crawler-terminal