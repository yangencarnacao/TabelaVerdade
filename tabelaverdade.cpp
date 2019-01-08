#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


bool compLen(string &a, string &b){ //tamanho
    return a.size() <= b.size();
}

bool compLex(string &a, string &b){ // lexixografica
    for(int i = 0, len = a.size(); i < len; i++){
        if(a[i] < b[i]) return true;
        if(a[i] > b[i]) return false;
    }
    return false;
}


void selectionSort(vector<string> &str){ // ordem de tamanho
    for(int i=0,len=str.size()-1; i<len; i++){
        for(int j=i+1,len2=str.size(); j<len2; j++){
            if(!compLen(str[i], str[j])) swap(str[i], str[j]);
        }
    }



    for(int i=0,len=str.size()-1; i<len; i++){ // ordem lexixografica caso o tamanho seja o msm
        for(int j=i+1,len2=str.size(); j<len2; j++){
            if(str[i].size() != str[j].size()) continue;
            if(!compLex(str[i], str[j])) swap(str[i], str[j]);
        }
    }
}



string tamanho(int n){
    string s="";
    --n;
    while(n--) s+= " ";


    return s;
}

void replaceAll(string& s, char antigo, char novo)
{
    for (int i = 0, len = s.size(); i < len; i++)
        if (s[i] == antigo)
            s[i] = novo;
}

vector<char> parentesis;
vector<char> operadores;

char resolverAtomica(char m, char op, char n)
{
    int a = m == '0' ? 0 : 1;
    int b = n == '0' ? 0 : 1;

    if (op == '.')
        return (a && b) ? '1' : '0';
    if (op == '+')
        return (a || b) ? '1' : '0';
    if (op == '>')
        return ((!a) || b) ? '1' : '0';
}

char resolver(string exp)
{
    for (int i = 0, len = exp.size(); i < len; i++) {
        if (exp[i] == '(') {
            parentesis.push_back('(');
        }
        else if (exp[i] == ')') {
            if (operadores[(int)operadores.size() - 2] == '-') {
                char resultado = operadores[(int)operadores.size() - 1] == '0' ? '1' : '0';
                operadores.pop_back();
                operadores.pop_back();
                parentesis.pop_back();
                operadores.push_back(resultado);
            }
            else {
                char resultado = resolverAtomica(operadores[operadores.size() - 3], operadores[operadores.size() - 2], operadores[operadores.size() - 1]);
                operadores.pop_back();
                operadores.pop_back();
                operadores.pop_back();
                parentesis.pop_back();
                operadores.push_back(resultado);
            }
        }
        else {
            operadores.push_back(exp[i]);
        }
    }

    return operadores[0];
}

char validade(string exp, int x, int y, int z, int t)
{
    replaceAll(exp, 'x', x == 0 ? '0' : '1');
    replaceAll(exp, 'y', y == 0 ? '0' : '1');
    replaceAll(exp, 'z', z == 0 ? '0' : '1');
    replaceAll(exp, 't', t == 0 ? '0' : '1');

    parentesis.clear();
    operadores.clear();

    return resolver(exp);
}

int main()
{
    int numeroTabela=1;
    std::string entrada, saida, subexpressao,qntdexpress;
    freopen("Expressoes.in", "r", stdin);
    freopen("Expressoes.out", "w", stdout);
    std::getline (std::cin,qntdexpress);
    int nconvertido = std::stoi(qntdexpress);
    while(nconvertido--){
        std::getline (std::cin,entrada);
        std::vector<std::string> strVector;
        string reserva = entrada;
        int segundaParada, primeiraParada;
        bool temx = false, temy = false, temz = false, temt = false;
        for (int i = 0; i < entrada.length(); i++) {
            if (entrada[i] == 'x') {
                temx = true;
            }
            else if (entrada[i] == 'y') {
                temy = true;
            }
            else if (entrada[i] == 'z') {
                temz = true;
            }
            else if (entrada[i] == 't') {
                temt = true;
            }
        }

        while (1) {
            primeiraParada = entrada.find_first_of(')');
            if (primeiraParada == -1)
                break;
            for (int desce = primeiraParada - 1; desce >= 0; desce--) {
                if (entrada[desce] == '(') {
                    segundaParada = desce;
                    break;
                }
            }

            entrada[segundaParada] = '_', entrada[primeiraParada] = '_';
            subexpressao = reserva.substr(segundaParada, primeiraParada - segundaParada + 1);
            strVector.push_back(subexpressao);
        }
        selectionSort(strVector);
        int pos=0;
        bool duplicado=true;
        while(duplicado){
            duplicado=false;
            for(int i=0,len=strVector.size()-1; i<len; i++){
                if(strVector[i] == strVector[i+1]){
                    duplicado=true;
                    pos=i;
                }
            }
            if(duplicado)strVector.erase(strVector.begin()+pos);
        }
        int c=0;
        cout<<"Tabela #"<<numeroTabela<<endl;
        if(temx) strVector.insert(strVector.begin() +(c++),"x");
        if(temy) strVector.insert(strVector.begin() +(c++),"y");
        if(temz) strVector.insert(strVector.begin() +(c++),"z");
        if(temt) strVector.insert(strVector.begin() +(c++),"t");
        int tam=0;
        for(int i = 0; i < strVector.size(); i++){
            tam+=strVector[i].size();
        }
        tam += strVector.size()+1;
        string sep(tam,'-');
        cout<<sep<<endl;
        cout<<"|";
        for(auto i:strVector)cout<<i<<"|"; cout<<endl<<sep<<endl;
        bool tem0=false,tem1=false;
        std::vector<char> respostas;
        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                for (int z = 0; z < 2; z++)
                    for (int t = 0; t < 2; t++)
                        for (int i = 0; i < strVector.size(); i++) {
                            if(!temx && x == 1) continue;
                            if(!temy && y == 1) continue;
                            if(!temz && z == 1) continue;
                            if(!temt && t == 1) continue;
                            if(!i) cout<<"|";
                            char r = validade(strVector[i], x, y, z, t);
                            cout<<tamanho(strVector[i].size())<<r<<"|";
                            if(i==strVector.size()-1){
                                tem0 = tem0 || (r == '0');
                                tem1 = tem1 || (r == '1');
                                cout<<endl<<sep<<endl;
                            }
                        }
        if(tem1 && tem0)cout<<"satisfativel e refutavel"<<endl;
        else if(tem1)cout<<"satisfativel e tautologia"<<endl;
        else cout<<"insatisfativel e refutavel"<<endl;
        numeroTabela++;
        cout<<endl;
    }
}