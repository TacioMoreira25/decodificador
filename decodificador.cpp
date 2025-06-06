#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

// stoi (string to integer) é uma função da <string> que converte uma string para int
// O segundo argumento (nullptr) indica que não queremos armazenar a posição do primeiro caractere inválido
// O terceiro argumento (2) indica que a string está na base binária (2)
char binarioParaChar(const string &binario) 
{
    return stoi(binario, nullptr, 2); 
}

int main()
{
    ifstream arquivo("entrada.txt");
    if (!arquivo) 
    {
        cerr << "Erro ao abrir o arquivo para leitura.\n";
        return 1;
    }

    stack <char> PilhaBits;   
    string GrupoDeBinarios, avisos;  
    char bit;

    while (arquivo >> bit)
    {
        if (bit != '0' && bit != '1') 
        {
            avisos += "Aviso: Caractere inválido ignorado -> '";
            avisos += bit;
            avisos += "'\n";
            continue;
        }

        PilhaBits.push(bit); 

        if (PilhaBits.size() == 8)
        {
            while (!PilhaBits.empty())
            {
                GrupoDeBinarios = PilhaBits.top() + GrupoDeBinarios;
                PilhaBits.pop();
            }
            cout << binarioParaChar(GrupoDeBinarios);
            GrupoDeBinarios.clear();
        }
    }

    // Se sobrar bits que não formam um grupo de 8
    if (!PilhaBits.empty())
    {
        GrupoDeBinarios.clear();
        while (!PilhaBits.empty())
        {
            PilhaBits.pop();
        }
        cerr << "\nAviso: Bits restantes ignorados! Entrada não era múltiplo de 8.\n";
    }

    if (!avisos.empty())
    {
        cout << "\n" << avisos;
    }

    arquivo.close();
    cout << "\n";
    return 0;
}
