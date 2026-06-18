# Dungeon Crawler no Terminal 🎮⚔️

Trabalho prático desenvolvido para a disciplina **DC5199 - Algoritmos (Prática)** do Departamento de Ciência da Computação da **Universidade Federal de Juiz de Fora (UFJF)**.

## 📝 Sobre o Projeto

Este projeto consiste em uma versão simplificada de um jogo do tipo **Dungeon Crawler**, totalmente executado via terminal e desenvolvido em **C++**. O jogador controla um herói representado por uma matriz de caracteres, cujo objetivo é explorar uma masmorra, coletar tesouros, sobreviver a combates com monstros e gerenciar seus recursos até encontrar a saída.

O motor do jogo funciona baseado em turnos e processa arquivos de configuração dinâmicos, permitindo customizar completamente o mapa e os atributos da partida.

---

## 🛠️ Funcionalidades e Mecânicas

* Movimentação Baseada em Turnos**: Controle intuitivo utilizando as teclas clássicas `W`, `A`, `S`, `D`.
* Geração Dinâmica via Arquivos**: O mapa e as variáveis de jogo (vida inicial, dano, turnos máximos) são carregados de forma dinâmica através de arquivos de texto (`config.txt` e `mapa.txt`).
* Sistema de Validação Estrita**: O programa valida as dimensões da matriz e a presença de elementos obrigatórios (como herói, tesouro e saída única) antes de iniciar.
* **Elementos Interativos**:
  * 💰 **Tesouros (`T`)**: Incrementam a pontuação.
  * 🧪 **Poções (`P`)**: Recuperam a saúde do jogador.
  * 👾 **Monstros (`M`)**: Causam dano ao herói antes de serem derrotados.
  * 🚪 **Saída (`S`)**: Só permite a vitória se todos os monstros da masmorra forem eliminados.

---

## 🗺️ Representação do Mapa

A masmorra utiliza uma interface textual simples e limpa baseada nos seguintes elementos:

| Símbolo | Significado |
| :---: | :--- |
| `@` | Jogador |
| `#` | Parede (Obstáculo intransponível) |
| `.` | Caminho livre |
| `M` | Monstro |
| `T` | Tesouro |
| `P` | Poção |
| `S` | Saída da masmorra |

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
Certifique-se de ter um compilador que suporte C++11 ou superior (como o `g++`).

### Passos para compilação

1. Clone o repositório:
   ```bash
   git clone [https://github.com/joao-hribeiro/dungeon-crawler.git](https://github.com/joao-hribeiro/dungeon-crawler.git)
   cd dungeon-crawler

---

## 👥 Integrantes do Grupo

Desenvolvido por:

| Nome | GitHub |
| :--- | :---: |
| **João Humberto de Aquino Ribeiro** | [![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/joao-hribeiro) |
| **Humberto de Moraes Lanzieri Filho** | [![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/hlanzieri) |
| **Enzo Delgado Duque** | [![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/usuario-3) |