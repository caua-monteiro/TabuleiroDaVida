#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

#define L 6
#define C 6
    
using namespace std;

char MinaAparente[L+1][C+1];
int MinaReal[L][C] = {0};
vector <char> Identificador;
vector <string> Nomes;
vector <int> Pontos;


//Funcao para os nomes dos jogadores
void Selecao(int i) {
    string ID;
    cout << "Jogador " << i + 1 << " insira seu nome" << endl;
    cin >> ID;
    
    char inicial = toupper(ID[0]);

    while (find(Identificador.begin(), Identificador.end(), ID[0]) != Identificador.end()) {
        cout << "Nome invalido, inicial ja escolhida, tente outro por favor" << endl;
        cin >> ID;
        inicial = toupper(ID[0]);
    }

    Identificador.push_back(inicial);
    Nomes.push_back(ID);
    Pontos.push_back(10);
}

//Inicializacao MinaAparente
void ComecoAparente(){
    for(int i = 0; i < L+1; i++){
        for(int j = 0; j < C+1; j++){
            if(i == 0 && j == 0)
                MinaAparente[i][j] = ' ';
            else{
                if(i == 0)
                    MinaAparente[i][j] = j + 48;
                else{
                    if(j == 0)
                        MinaAparente[i][j] = i + 48;
                    else{
                        MinaAparente[i][j] = 254;
                    }
                }
                    
            }
        }
    }
}

//inicializacao MinaReal
void ComecoReal(){
    float Premios = ((L * C) * 0.35), Sabio = 2, Perdas = ((L*C) * 0.15), Golpista = 2, Ladrao = 1, Cassino = 1; 
    srand(time(NULL));
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            MinaReal[i][j] = 0;
        }
    }

    auto distribuir = [&](int quantidade, int valor) {
        for (int i = 0; i < quantidade; i++) {
            int Linha = rand() % L, Coluna = rand() % C;
            if (MinaReal[Linha][Coluna] == 0) {
                MinaReal[Linha][Coluna] = valor;
            } else {
                i--;
            }
        }
    };

    distribuir(Premios, 1);
    distribuir(Sabio, 2);
    distribuir(Perdas, 3);
    distribuir(Golpista, 4);
    distribuir(Ladrao, 5);
    distribuir(Cassino, 6);

}

//Funcoes para os possiveis eventos na Mina ate l-193;
void Premio(int i){
    srand(time(NULL));
    int TipoGanho = (rand() % 3) + 1, Ganhos;
    switch (TipoGanho){
    case 1:
        Ganhos = (rand()%5) +1;
        cout << "Voce achou uma nota de " << Ganhos << " R$, Como diz o ditado: Achado nao e roubado" << endl;
        Pontos[i] += Ganhos;
        break;
    
    case 2:
        Ganhos = (rand()%10) +1;
        cout << "Voce Ganhou uma raspadinha e seu lucro foi de " << Ganhos << " R$, espero que essa sorte continue com voce" << endl;
        Pontos[i] += Ganhos;
        break;

    case 3:
        
        Ganhos = (rand()%15) +1;
        cout << "Voce ganhou uma partida de poker contra seus amigos, voce lucrou " << Ganhos << " R$" << endl;
        Pontos[i] += Ganhos;
        break;
    default:
        Ganhos = 0;
        cout << "Erro inesperado na geracao de premios" << endl;
    }
}
void Sabio(){
    cout << "Voce encontrou um sabio, deseja ouvir o que ele tem a dizer?" << endl;
    string resposta;
    cin >> resposta;
    if(resposta == "Sim" || resposta == "sim"){
        cout << "Sabio:" << endl    
             << "Escute bem, nao confie em qualquer um por ai, existem muitos golpistas disfarcados por ai." << endl
             << "Alem disso eu nao recomendo que voce entre no cassino se nao estiver com dinheiro de sobra, e como dizem, A casa sempre ganha." << endl;
    }
}
void Perdas(int i){
    srand(time(NULL));
    int TipoPerda = rand()%3, preju;
    switch (TipoPerda){
    case 0:
        preju = rand()%3;
        cout << "Voce percebeu que perdeu " << preju << " R$ durante dua caminhada matinal" << endl;
        Pontos[i] -= preju;
        break;
    
    case 1:
        preju = rand() % 5;
        cout << "Voce jogou uma partida de sinuca apostado e perdeu " << preju << " R$ para seu amigo"<<endl;
        Pontos[i] -= preju;
        break;
    default:
        preju = rand() % 8;
        cout << "Chegou a hora de pagar o imposto de renda. Voce deve " << preju << " R$ para o governo" << endl;
        Pontos[i] -= preju;
        break;
    }
}
void Golpista(int i){
    cout << "Voce encontrou um influencer." << endl
         << "Influencer:" << endl
         << "Ei, voce gostaria de multiplicar seu dinehiro em ate 5x de maneira rapida e simples? voce so precisa me mandar 10 R$ no pix que eu te devolverei 30 R$."<<endl
         << "Voce aceita a proposta?" <<endl;
    string resposta;
    cin >> resposta;
    if(resposta == "Sim" || resposta == "sim"){
        cout << "A foto de perfil do influencer sumiu e ele nao responde mais suas mensagens, acho que era um golpe" << endl;
        Pontos[i] -= 10;
    }
    else{
        cout << "Talvez tenha sido uma boa escolha, mas vai que era verdade ne?" << endl;
    }
}
void Ladrao(int i){
    cout << "Voce foi parado por dois caras em uma moto e eles levaram seus bens, voce perdeu 15 R$" << endl;
    Pontos[i] -= 15;
}
void Cassino(int i){
    srand(time(NULL));
    cout << "Voce encontrou um Cassino enquanto caminhava, deseja entrar?"<< endl;
    string resposta;
    cin >> resposta;
    if(resposta == "Sim" || resposta == "sim"){
        cout << "Agora que vc entrou, vai apostar quanto? saiba que as chances de de ganhar aq sao de aproximadamente 40%, mas se ganhar o valor investido dobrara"<< endl;
        int aposta, result = rand()%10;
        cin >> aposta;
        while (aposta > Pontos[i]){
            cout << "Seu saldo nao e suficiente para fazer essa aposta, tente novamente" << endl;
            cin >> aposta;
        }
        if(result > 5){
            cout << "Olha so, parece que a sorte esta do seu lado" << endl;
            Pontos[i] += aposta;
        }
        else{
            cout << "Acho que hoje nao e seu dia, voce acaba de perder a sua aposta" << endl;
            Pontos[i] -= aposta;
        }
    }
}


//Funcao do ranking
void ranking(int Njogadores){
    
    vector<int> indices;
    for (int i = 0; i < Njogadores; ++i) {
        indices.push_back(i);
    }

    // Ordenação dos índices com base nas pontuações
    sort(indices.begin(), indices.end(), [&Pontos](int a, int b) {
        return Pontos[a] > Pontos[b];
    });
    
    for (int i = 0; i < Njogadores; i++) {
        cout << i + 1 << ". " << Nomes[indices[i]] << ": " << Pontos[indices[i]] << " R$" << endl;
    }
}


//funcoes de modelo de jogo
void JogoBinario(int i){
    cout << "--- Rodada " << (i/2) + 1<< " ---" << endl;
    cout << endl;

    for(int j = 0; j < L+1; j++){
        for(int k = 0; k < C+1; k++){
            cout<< setw(3) << MinaAparente[j][k];
        }
        cout << endl;
    }
    
    cout << endl;
    cout << endl;

    ranking(2);

    cout << endl;
    int Linha, Coluna;
    cout << Nomes[i%2] << ", escolha a posicao que voce quer minerar: ";
    cin >> Linha >> Coluna;

    unsigned char aux = MinaAparente[Linha][Coluna];

    if(aux == 254){
        if(i%2==0){
            MinaAparente[Linha][Coluna] = Identificador[0];
            switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(0);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(0);
                break;
            case 4:
                Golpista(0);
                break;
            case 5:
                Ladrao(0);
                break;
            case 6:
                Cassino(0);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
        }
        else{
            MinaAparente[Linha][Coluna] = Identificador[1];
            switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(1);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(1);
                break;
            case 4:
                Golpista(1);
                break;
            case 5:
                Ladrao(1);
                break;
            case 6:
                Cassino(1);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
        }
    }
    else{
        cout << "Posicao ja escolhida, tente novamente" << endl;
        JogoBinario(i);
    }

    cout << endl;

    system("pause");
    system("cls");

}

void JogoTernario(int i){
    cout << "--- Rodada " << (i/3) + 1<< " ---" << endl;
cout << endl;

    for(int j = 0; j < L+1; j++){
        for(int k = 0; k < C+1; k++){
            cout<< setw(3) << MinaAparente[j][k];
        }
        cout << endl;
    }
    
    cout << endl;
    cout << endl;

    ranking(3);

    cout << endl;
    int Linha, Coluna;
    cout << Nomes[i%3] << ", escolha a posicao que voce quer minerar: ";
    cin >> Linha >> Coluna;

    unsigned char aux = MinaAparente[Linha][Coluna];

    if(aux == 254){
        if(i%3 == 0){
            MinaAparente[Linha +1][Coluna +1] = Identificador[0];
            switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(0);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(0);
                break;
            case 4:
                Golpista(0);
                break;
            case 5:
                Ladrao(0);
                break;
            case 6:
                Cassino(0);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
        }
        else{
            if(i%3 == 1){
                MinaAparente[Linha +1][Coluna +1] = Identificador[1];
                switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(1);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(1);
                break;
            case 4:
                Golpista(1);
                break;
            case 5:
                Ladrao(1);
                break;
            case 6:
                Cassino(1);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
            }
            else{
                MinaAparente[Linha +1][Coluna +1] = Identificador[2];
                switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(2);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(2);
                break;
            case 4:
                Golpista(2);
                break;
            case 5:
                Ladrao(2);
                break;
            case 6:
                Cassino(2);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
            } 
        }
    }
    else{
        cout << "Posicao ja escolhida, tente novamente" << endl;
        JogoTernario(i);
    }
    
    cout << endl;

    system("pause");
    system("cls");

}

void JogoQuaternario(int i){
    cout << "--- Rodada " << (i/4) + 1<< " ---" << endl;
    cout << endl;

    for(int j = 0; j < L+1; j++){
        for(int k = 0; k < C+1; k++){
            cout<< setw(3) << MinaAparente[j][k];
        }
        cout << endl;
    }
    
    cout << endl;
    cout << endl;

    ranking(4);

    cout << endl;
    int Linha, Coluna;
    cout << Nomes[i%4] << ", escolha a posicao que voce quer minerar: ";
    cin >> Linha >> Coluna;

    unsigned char aux = MinaAparente[Linha][Coluna];

    if(aux == 254){
        if(i%4 == 0){
            MinaAparente[Linha][Coluna] = Identificador[0];
            switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(0);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(0);
                break;
            case 4:
                Golpista(0);
                break;
            case 5:
                Ladrao(0);
                break;
            case 6:
                Cassino(0);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
        }
        else{
            if(i%4 == 1) {
                MinaAparente[Linha][Coluna] = Identificador[1];
                switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(1);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(1);
                break;
            case 4:
                Golpista(1);
                break;
            case 5:
                Ladrao(1);
                break;
            case 6:
                Cassino(1);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
            }
            else{
                if(i%4 == 2){
                    MinaAparente[Linha][Coluna] = Identificador[2];
                    switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(2);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(2);
                break;
            case 4:
                Golpista(2);
                break;
            case 5:
                Ladrao(2);
                break;
            case 6:
                Cassino(2);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
                } 
                    else{
                        MinaAparente[Linha][Coluna] = Identificador[3];
                        switch (MinaReal[Linha-1][Coluna-1]){
            case 1:
                Premio(3);
                break;
            case 2:
                Sabio();
                break;
            case 3:
                Perdas(3);
                break;
            case 4:
                Golpista(3);
                break;
            case 5:
                Ladrao(3);
                break;
            case 6:
                Cassino(3);
                break;
            default:
                cout << "Parece que nao tem nada por essas bandas" <<endl;
                break;
            }
                    }
                } 
        }
    }
    else{
        cout << "Posicao ja escolhida, tente novamente" << endl;
        JogoTernario(i);
    }

    cout << endl;

    system("pause");
    system("cls");

}


//Codigo principal
int main(){   
    int Njogadores;
    cout << "Selecione o numero de jogadores (2 a 4)" << endl;
    cin >> Njogadores;

    ComecoAparente();
    ComecoReal();

    

    for(int i = 0; i < Njogadores; i++){
        Selecao(i);
    }

    string ModoJogo;
    cout << "Escolha o modo de jogo (Padrao ou Rapido)" << endl; 
    cin >> ModoJogo;

    cout << endl;

    system("pause");
    system("cls");


    if(ModoJogo == "Padrao"){
        for(int i = 0; i < L*C; i++){

            switch(Njogadores){
                case 2:
                    JogoBinario(i);

                    break;
                case 3:
                    JogoTernario(i);

                    break;
                case 4:
                    JogoQuaternario(i);

                    break;
            }
        }
    }
    else{
        for(int i = 0; i < Njogadores*5 ; i++){

        switch(Njogadores){
            case 2:
                JogoBinario(i);

                break;
            case 3:
                JogoTernario(i);

                break;
            case 4:
                JogoQuaternario(i);

                break;
        }

        //escrita da matriz
        for(int j = 0; j < L+1; j++){
            for(int k = 0; k < C+1; k++){
                cout<< setw(3) << MinaAparente[j][k];
            }
            cout << endl;
        }
    }
    }
        cout << "agora vamos dar uma olhadinha em como estava nosso tabuleiro!!!" << endl;
        for(int j = 0; j < L; j++){
            for(int k = 0; k < C; k++){
                cout<< setw(3) << MinaReal[j][k];
            }
        cout << endl;
    }


    return 0;
}
