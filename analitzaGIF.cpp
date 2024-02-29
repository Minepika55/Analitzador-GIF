#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    int midaCapcalera = 13;//Aqui poso un int que guardara la capcalera del GIF la qual consisteix de 13 bytes
    char* capcalera = new char[midaCapcalera];//Aqui utilitzo un punter per guardar la capcalera a la RAM
    string nom;
    unsigned int versio, ample, alcada, colors;
    char marca1, marca2, marca3;
    int duplicat;

    //Faig la benvinguda a l'ususari i li demano el nom del GIF que vol analitzar
    cout << "Analitzador de GIFs" << endl;
    cout << "Introdueix el nom del GIF (recorda posar .gif al final): ";
    getline(cin, nom);//Guardo el nom del GIF

    ifstream arxiu(nom.c_str(), ifstream::binary);//Obro el GIF
    if (arxiu.fail())//Si el fitxer no es pot obrir salta un error
        cout << " ERROR no s'ha detectat cap fitxer amb aquest nom" << endl;
    else {
        marca1 = arxiu.get();//Llegeixo el principi del fitxer per veure si es un GIF o no
        marca2 = arxiu.get();
        marca3 = arxiu.get();
        if ((marca1 == 'G') && (marca2 == 'I') && (marca3 == 'F')) {//Si el header comenca per les lletres GIF vol dir que es un GIF
            cout << "Fitxer detectat com un gif: " << marca1 << marca2 << marca3 << endl;//Mostro que s'ha detectat el GIF sense problemes
            arxiu.seekg(0, arxiu.beg);
            arxiu.read(capcalera, midaCapcalera);
            arxiu.close();//Tenco el fitxer

            //Llegeixo els caracters del header per localitzar la versio del GIF
            char versioChar[4];
            versioChar[0] = capcalera[3];
            versioChar[1] = capcalera[4];
            versioChar[2] = capcalera[5];
            versioChar[3] = '\0';//He de acabaramb un caracter zero perque sino mostraba caracters erronis

            cout << "Versio del GIF: " << versioChar << endl;//Mostro la versio del gif

            ample = (unsigned char)capcalera[6] + (unsigned char)(capcalera[7]) * 256;//Busco i mostro l'amplada del GIF
            cout << "Amplada del GIF: " << ample << endl;

            alcada = (unsigned char)capcalera[8] + (unsigned char)(capcalera[9]) * 256;//Busco i mostro l'alcada del GIF
            cout << "Alcada del GIF: " << alcada << endl;

            colors = (unsigned char)capcalera[11] + (unsigned char)(capcalera[12]) * 256;//Busco i mostro els colors que te el GIF
            cout << "Quantitat de colors del GIF: " << colors << endl;
        }
        else
            cout << "ERROR aquest fitxer no es un GIF" << endl;//Mostro un error si no es detecta el GIF o el fitxer esta malmes
    }

    cout << "Vols fer duplicar el GIF? 1.Si 2.No" << endl;//Aqui afegeixo la opcio per fer un duplicat del GIF seleccionat
    cin >> duplicat;
    if (duplicat == 1) {//Si l'usuari ha seleccionat que si comenca el process de clonacio del GIF

        ifstream file(nom.c_str(), ios::binary | ios::ate);//Obro el fitxer
        streamsize size = file.tellg();//Guardo la mida del fitxer
        file.seekg(0, ios::beg);//Li dic que llegeixi el fitxer desde el principi

        char* copia = new char[size];//Faig un punter on es guardaran les dades

        file.read(copia, size);//Llegeixo el fitxer
        file.close();//Tenco el fitxer

        string nouNom = nom.substr(0, nom.size() - 4) + "-2.gif";//Faig un nou fitxer amb el nom de l'original i un 2
        ofstream nouGif(nouNom.c_str(), ios::binary);
        nouGif.write(copia, size);//Escric les dades del fitxr antic al duplicat
        nouGif.close();//Tanco el nou duplicat del GIF original

        delete[] copia;
        cout << "El fitxer s'ha duplicat sense problemes." << endl;//Aviso que el fitxer s'ha clonat sense problemes
    }
    else {
        cout << "ERROR no s'ha pogut duplicar el fitxer." << endl;//Salta un error si per qualsevol rao no s'ha pogut completar la clonacio
    }

    return 0;
}