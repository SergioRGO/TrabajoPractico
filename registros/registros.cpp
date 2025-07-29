#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct Vendedor {
    int codigo;
    char nombre[50];
    char sucursal[50];
};

Vendedor dameVendedor() {
    Vendedor vendedor;
    cout << "Ingrese codigo de vendedor, nombre y sucursal a la que pertenece."<<endl;
    cin >> vendedor.codigo;
    cin.ignore();
    cin.getline(vendedor.nombre, sizeof(vendedor.nombre));
    cin.getline(vendedor.sucursal, sizeof(vendedor.sucursal));
    return vendedor;
}
bool existeVendedor(Vendedor vendedor) {
    Vendedor vendedorGuardado;
    bool existe = false;
    FILE* archivo;
    fopen_s(&archivo,"vendedores.dat", "rb");
    if (archivo != NULL) {
        while (fread(&vendedorGuardado, sizeof(Vendedor), 1, archivo) == 1) {
            if (vendedorGuardado.codigo == vendedor.codigo) {
                existe = true;
                cout << endl<<"El vendedor ya existe" << endl<<endl;
            }
        }
        fclose(archivo);
    }
    else {
        cerr << "No existe archivo, creando..." << endl;
        existe=false;
    }
    return existe;
}
bool continuar() {
    char op;
    bool ok = false;
    do {
        cout << "Continuar? y/n" << endl;
        cin >> op;
    } while (op != 'y' && op != 'n');
    if (op == 'y') {
        return true;
    }
    else {
        return false;
    }
}

int mostrarVendedores() {
    FILE* archivo;
    fopen_s(&archivo, "vendedores.dat", "rb");
    if (archivo != NULL) {
        Vendedor vendedor;
        int i = 0;
        while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
            i++;
            cout << endl << "Vendedor " << i << " :" << endl;
            cout << "Codigo: " << vendedor.codigo << endl;
            cout << "Nombre: " << vendedor.nombre << endl;
            cout << "Sucursal: " << vendedor.sucursal << endl;
        }
        fclose(archivo);
    }
    else {
        cout << "Archivo creado." << endl;
    }
    return 0;
};

int main()
{
    char op = 'y';
    Vendedor vendedor;
    cout << "Para dejar de ingresar vendedores ingrese 'n'" << endl<<endl;
    do {
        vendedor = dameVendedor();
        if (!existeVendedor(vendedor)) {
            FILE* archivo;
            fopen_s(&archivo,"vendedores.dat", "ab");
            if (archivo != NULL) {

                fwrite(&vendedor, sizeof(Vendedor), 1, archivo);
                fclose(archivo);
                cout <<endl<< "Vendedor guardado." << endl<<endl;
            }
            else {
                cerr << "Archivo creado." << endl;
            }
        }   
    }while (continuar());
    mostrarVendedores();
    return 0;
}