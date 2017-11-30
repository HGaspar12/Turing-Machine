#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<time.h>
using namespace std;

struct Transicao {
    string estadoQueSeEncontra;
    char simboloLido;
    char simboloEscrito;
    char direcao;
    string estadoQueVai;
};
typedef Transicao Transicao;

string nomeArquivo = "";
string estadoInicial;
vector<string> estadosFinais;
vector<string> entradas;
vector<Transicao> transicoes;
char vazio;
char inicial;
clock_t begin, end;

void executar();
bool fazParteDosFinais(string estado);
void lerEntradas();
void lerConfiguracoes();
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

int main(){
    double time_spent;
    lerConfiguracoes();
    lerEntradas();
    executar();
    end = clock();
    time_spent = (double)(1000*(end-begin)/CLOCKS_PER_SEC);
    cout << time_spent << endl;
}

void executar(){
    string saida = "";
    int j;
    int tamanho;
    string aux = nomeArquivo + ".out";
    const char *c = aux.c_str();
    ofstream arq(c);
    string estado;
    for(int i=0;i<entradas.size();i++){
        bool parar = false;
        j=0;
        estado = estadoInicial;
        tamanho = entradas[i].size();
        saida = entradas[i];
        while(parar==false){
            bool achou = false;
            for(int k=0;k<transicoes.size();k++){
                if(transicoes[k].estadoQueSeEncontra==estado && transicoes[k].simboloLido==saida[j]){
                    achou = true;
                    //cout << transicoes[k].estadoQueSeEncontra << " -> ";
                    estado = transicoes[k].estadoQueVai;
                    //cout << estado << "  ||  ";
                    //cout << saida << "  --  " << saida[j] << endl;
                    saida[j] = transicoes[k].simboloEscrito;
                    if(transicoes[k].direcao=='D'){
                        j++;
                        if(j==tamanho){
                            saida += vazio;
                        }
                    }
                    else{
                        j--;
                    }
                    break;
                }
            }
            if(achou==false){
                parar = true;
            }
        }
        if(fazParteDosFinais(estado)){
            cout << "Aceito" << endl;
            arq << saida << ";1" << endl;
        }
        else{
            cout << "N foi Aceito" << endl;
            arq << saida << ";0" << endl;
        }
    }
    arq.close();
}

bool fazParteDosFinais(string estado){
    for(int i=0;i<estadosFinais.size();i++){
        if(estado==estadosFinais[i]){
            return true;
        }
    }
    return false;
}

void lerConfiguracoes(){
    cin >> nomeArquivo;
    begin = clock();
    string aux = nomeArquivo + ".mt";
    const char *c = aux.c_str();
    string linha;
    fstream arq;
    arq.open(c,ios::in);
    getline(arq, estadoInicial);
    string estadosFinaisAux;
    getline(arq,estadosFinaisAux);
    estadosFinais = split(estadosFinaisAux,',');
    getline(arq,linha);
    vazio = linha[0];
    getline(arq,linha);
    inicial = linha[0];
    while(arq.good()){
        getline(arq, linha);
        Transicao transicao;
        vector<string> strings = split(linha,',');
        transicao.estadoQueSeEncontra = strings[0];
        transicao.simboloLido = strings[1][0];
        transicao.simboloEscrito = strings[2][0];
        transicao.direcao = strings[3][0];
        transicao.estadoQueVai = strings[4];
        transicoes.push_back(transicao);
    }
}

void lerEntradas(){
    string linha;
    fstream arq;
    string aux = nomeArquivo + ".in";
    const char *c = aux.c_str();
    arq.open(c,ios::in);
    while(arq.good()){
        getline(arq,linha);
        //cout << inicial << linha << endl;
        entradas.push_back(inicial + linha);
    }
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
