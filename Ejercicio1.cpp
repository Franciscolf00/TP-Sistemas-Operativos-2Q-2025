#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <bits/stdc++.h>

using namespace std;

static constexpr size_t REC_SIZE = 48;

// CONTAR LA CANTIDAD DE REGISTROS DEL ARCHIVO
static size_t contarRegistros(ifstream& f){
    auto cur = f.tellg();               // 1) Guarda la posición de lectura actual.
    f.seekg(0, ios::end);               // 2) Salta al final del archivo.
    size_t bytes = (size_t)f.tellg();   // 3) Lee la posición (=> tamaño en bytes).
    f.seekg(cur);                       // 4) Vuelve a donde estaba.
    return bytes / REC_SIZE;            // 5) #registros = bytes / tamaño_fijo_por_registro.
}

//LEER DEL ARCHIVO SEGÚN INDICE
static string read_by_index(ifstream& f, size_t idx){
    f.seekg(static_cast <streamoff>(idx * REC_SIZE), ios::beg);
    array<char, REC_SIZE> rec{};
    f.read(rec.data(), rec.size());
    //construimos string hasta el primer '\0' o REC_SIZE
    return string(rec.data()); // se corta en '\0' si lo hay
}

//CREAR UN DNI RANDOM
static int random_dni(mt19937& rng){
    uniform_int_distribution<int> dist(10'000'000, 60'000'000);
    return dist(rng);
}

int main(int argc, char** argv){
    int N = 5; // cuántas filas imprimir

    if (argc == 2) 
        N = std::atoi(argv[1]);
    
    random_device rd;
    mt19937 rng(rd());

    ifstream fn("nombres.bin", ios::binary); //leo archivos
    ifstream fa("apellidos.bin", ios::binary);
    ifstream fp("provincias.bin", ios::binary);

    if (!fn || !fa || !fp)
    {
        cerr << "Faltan .bin\n";
        return 1;
    }

    size_t cn = contarRegistros(fn); //cuento registros
    size_t ca = contarRegistros(fa);
    size_t cp = contarRegistros(fp);

    
    if (!cn || !ca || !cp){ 
        cerr << "Algún .bin está vacío o mal formado\n"; 
        return 2; 
    }
    
    uniform_int_distribution<size_t> dn(0, cn-1), da(0, ca-1), dp(0, cp-1); //distribución de 0 a cantidad de registros por archivos

    for (int i=0; i<N; ++i){
        string nom = read_by_index(fn, dn(rng));
        string ape = read_by_index(fa, da(rng));
        string pai = read_by_index(fp, dp(rng));
        cout << nom << ',' << ape << ',' << random_dni(rng) << ',' << pai << "\n";
    }

    return 0;


}
