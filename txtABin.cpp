// make_dict.cpp — Convierte <input.txt> (una línea por valor, UTF-8) a <output.bin> con registros fijos
#include <bits/stdc++.h>
using namespace std;

// Ajustá según lo largo de tus nombres/apellidos/países.
// 48 suele alcanzar para nombres con acentos; si querés margen, subilo a 64.
static constexpr size_t REC_SIZE = 48;

// ¿Es un byte de continuación UTF-8? (10xxxxxx)
static inline bool is_cont(unsigned char c){ return (c & 0xC0) == 0x80; }

// Trunca por bytes sin “cortar” en el medio de un código UTF-8
static string utf8_truncate(const string& s, size_t max_bytes){
    if (s.size() <= max_bytes) return s;
    size_t cut = max_bytes;
    while (cut > 0 && is_cont(static_cast<unsigned char>(s[cut-1]))) cut--;
    if (cut == 0) return ""; // caso patológico
    return s.substr(0, cut);
}

// Recorta \r y \n finales
static void rstrip_newlines(string& s){
    while(!s.empty() && (s.back()=='\n' || s.back()=='\r')) s.pop_back();
}

int main(int argc, char** argv){
    if (argc != 3){
        cerr << "Uso: " << argv[0] << " <input.txt> <output.bin>\n";
        return 1;
    }
    ifstream in(argv[1]);
    if (!in){ perror("input"); return 2; }
    ofstream out(argv[2], ios::binary);
    if (!out){ perror("output"); return 2; }

    string line; size_t count = 0;
    while (getline(in, line)){
        rstrip_newlines(line);
        // podés saltear líneas vacías si querés
        if (line.empty()) continue;

        // dejamos 1 byte libre por si querés garantizar '\0' al leer
        string t = utf8_truncate(line, REC_SIZE - 1);

        array<char, REC_SIZE> rec{}; // relleno con ceros
        memcpy(rec.data(), t.data(), t.size()); // copia bytes (UTF-8)
        out.write(rec.data(), rec.size());
        count++;
    }
    cerr << "Escribí " << count << " registros de " << REC_SIZE
         << " bytes en " << argv[2] << "\n";
    return 0;
}

