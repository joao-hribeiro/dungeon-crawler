// --- SEÇÃO MULTIPLATAFORMA ---
#ifdef _WIN32
    #include <conio.h> // Para Windows
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>

    // Função para simular o _getch() do Windows no Linux
    char _getch() {
        struct termios oldt, newt;  
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);          // Salva as configurações atuais do terminal
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);        // Desativa o buffer de linha e o eco das teclas
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica as novas configurações
        ch = getchar();                          // Lê o caractere
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura as configurações originais
        return ch;
    }
#endif