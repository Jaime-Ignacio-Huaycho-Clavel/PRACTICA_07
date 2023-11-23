// Materia: Programación I, Paralelo 4
// Autor: Jaime Ignacio Huaycho Clavel
// Fecha creación: 21/11/2023
// Fecha modificación: 22/10/2023
// Número de ejericio: 1
// Problema planteado: *******
#include <iostream>
#include <fstream>
#include <wchar.h>
#include <cstring>
using namespace std;

const char* NOMBRE_ARCHIVO = "EquiposLPFB.bin";
const char* NOMBRE_RESULTADOS = "ResultadosLPFB.bin";

struct structEquiposLPFB{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
}; 

struct structResultadosLPFB{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[10];
};

void leerArchivoBinario(structEquiposLPFB equipo)
{
    ifstream archivoLectura;
    archivoLectura.open(NOMBRE_ARCHIVO,ios::in | ios::binary);
    cout << "\nLISTADO DE DATOS" << endl;
    cout << "================" << endl;
    while (archivoLectura.read((char*)&equipo, sizeof(structEquiposLPFB)))
    {
        cout << "Nombre del equipo: " << equipo.nombreEquipo << endl;
        cout << "Color de camiseta: " << equipo.colorCamiseta << endl;
        cout << "Departamento: " << equipo.departamento << endl;
        cout << "Anio de creacion: " << equipo.anioCreacion << endl;
        cout<<"\n";
    }
    archivoLectura.close();
}

bool buscarDatoArchivoBinario(char buscar[50])
{
    ifstream archivoLectura;
    structEquiposLPFB equipo;
    archivoLectura.open(NOMBRE_ARCHIVO,ios::in | ios::binary);
    while (archivoLectura.read((char*)&equipo, sizeof(structEquiposLPFB)))
    {
        if (strcmp(buscar, equipo.nombreEquipo) == 0)
            return true;
    }
    archivoLectura.close();
    return false;
}

structEquiposLPFB ingreso_datos_equipo()
{
    structEquiposLPFB equipo,bas;
    
    cout << "INGRESO DE DATOS" << endl;
    cout << "================" << endl;
    cout << "Ingrese el nombre del equipo: ";
    cin.ignore();
    cin.getline(equipo.nombreEquipo, 50);
    cout<<"Color de camiseta: ";
    cin.getline(equipo.colorCamiseta,50);
    cout<<"Departamento: ";
    cin.getline(equipo.departamento,30);
    cout<<"Anio de creacion: ";
    cin>>equipo.anioCreacion;
    if (buscarDatoArchivoBinario(equipo.nombreEquipo)==false){
        return equipo;
    }else{
        cout<<"El nobre del equipo ingresado ya existe"<<endl;
        *bas.nombreEquipo='0';
        return bas;
    }
}

void escribirArchivoBinario(structEquiposLPFB equipo)
{
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO,ios::app | ios::binary);
    archivoEscritura.write((char*)&equipo, sizeof(structEquiposLPFB));
    archivoEscritura.close();
}

structResultadosLPFB ingreso_datos_equipoR(){
    structResultadosLPFB equipoR,bor;
    cout << "INGRESO DE DATOS" << endl;
    cout << "================" << endl;
    cout << "Ingrese el nombre del equipo local: ";
    cin.ignore();
    cin.getline(equipoR.nombreEquipoLocal,50);
    cout<<" Ingese el nombre del equipo visitante: ";
    cin.getline(equipoR.nombreEquipoVisitante,50);
    cout<<"Fecha del partido: ";
    cin.getline(equipoR.fechaPartido,10);
    cout<<"Goles equipo local: ";cin>>equipoR.golesEquipoLocal;
    cout<<"Goles equipo visitante: ";cin>>equipoR.golesEquipoVisitante;
    if ((buscarDatoArchivoBinario(equipoR.nombreEquipoLocal)==true) && (buscarDatoArchivoBinario(equipoR.nombreEquipoVisitante)==true)){
        return equipoR;
    }else{
        *bor.nombreEquipoLocal='0';
        cout<<"Ingrese equipos existentes"<<endl;
        return bor;
    }
}

void escribirArchivoBinarioR(structResultadosLPFB equipoR){
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_RESULTADOS,ios::app | ios::binary);
    archivoEscritura.write((char*)&equipoR, sizeof(structResultadosLPFB));
    archivoEscritura.close();
}

void menu(){
    while (true){
        int op_sis;
        cout<<"\n------------------- Menu -------------------"<<endl;
        cout<<"1) Ingreso de datos de los equipo de la LPFB\n2) Ingreso los resultados de los partidos.\n3) Reporte de la tabla de posiciones\n0) Salir"<<endl;
        cout<<"--------------------------------------------"<<endl;
        cout<<"Opcion: ";cin>>op_sis;
        if (op_sis==0)
            break;
        switch(op_sis){
            case 1:
                structEquiposLPFB equipo;
                equipo=ingreso_datos_equipo();
                if (equipo.nombreEquipo[0]!='0'){
                    escribirArchivoBinario(equipo);
                }
                break;
            case 2:
                structResultadosLPFB equipoR;
                equipoR=ingreso_datos_equipoR();
                if (equipoR.nombreEquipoLocal[0]!='0')
                    escribirArchivoBinarioR(equipoR);
                break;
            case 3:
                leerArchivoBinario(equipo);
                cout<<"\nPerdon inge no es com oes un tabl de reportes\n"<<endl;
                break;
        }
    }
}

int main(){
    menu();
    return 0;
}