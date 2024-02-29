#include <iostream>

#include <fstream>

#include <string>

using namespace std;

int main() {
    int midaCapcalera = 13;
    char* capcalera = new char[midaCapcalera];
    string nom;
    unsigned int versio, ample, alcada, colors;
    char head1, head2, head3;
    int duplicat;

    cout << "Analitzador de GIFs" << endl;
    cout << "Introdueix el nom del GIF (recorda posar .gif al final): ";
    getline(cin, nom);

    ifstream arxiu(nom.c_str(), ifstream::binary);
    if (arxiu.fail())
        cout << " ERROR no s'ha detectat cap fitxer amb aquest nom" << endl;
    else {
        head1 = arxiu.get();
        head2 = arxiu.get();
        head3 = arxiu.get();
        if ((head1 == 'G') && (head2 == 'I') && (head3 == 'F')) {
            cout << "Fitxer detectat com un gif: " << head1 << head2 << head3 << endl;
            arxiu.seekg(0, arxiu.beg);
            arxiu.read(capcalera, midaCapcalera);
            arxiu.close();

            char versioChar[4];
            versioChar[0] = capcalera[3];
            versioChar[1] = capcalera[4];
            versioChar[2] = capcalera[5];
            versioChar[3] = '\0';

            cout << "Versio del GIF: " << versioChar << endl;

            ample = (unsigned char)capcalera[6] + (unsigned char)(capcalera[7]) * 256;
            cout << "Amplada del GIF: " << ample << endl;

            alcada = (unsigned char)capcalera[8] + (unsigned char)(capcalera[9]) * 256;
            cout << "Alcada del GIF: " << alcada << endl;

            colors = (unsigned char)capcalera[11] + (unsigned char)(capcalera[12]) * 256;
            cout << "Quantitat de colors del GIF: " << colors << endl;
        }
        else
            cout << "ERROR aquest fitxer no es un GIF" << endl;
    }

    cout << "Vols fer duplicar el GIF? 1.Si 2.No" << endl;
    cin >> duplicat;
    if (duplicat == 1) {

        ifstream file(nom.c_str(), ios::binary | ios::ate);
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);

        char* copia = new char[size];

        file.read(copia, size);
        file.close();

        string nouNom = nom.substr(0, nom.size() - 4) + "-2.gif";
        ofstream nouGif(nouNom.c_str(), ios::binary);
        nouGif.write(copia, size);
        nouGif.close();

        delete[] copia;
        cout << "El fitxer s'ha duplicat sense problemes." << endl;
    }
    else {
        cout << "ERROR no s'ha pogut duplicar el fitxer." << endl;
    }

    return 0;
}