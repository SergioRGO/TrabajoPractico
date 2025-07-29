#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct Venta {
	int codigo_vendedor;
	int codigo_producto;
	float monto_venta;
};

struct Vendedor {
    int codigo;
    char nombre[50];
    char sucursal[50];
};

Venta dameVenta() {
    Venta venta;
    cout << "Ingrese codigo de vendedor, codigo de producto y monto total de la venta" << endl;
    cin >> venta.codigo_vendedor;
    cin >> venta.codigo_producto;
    cin >> venta.monto_venta;
    return venta;
}

bool existeVendedor(Venta venta) {
    Vendedor vendedorGuardado;
    bool existe = false;
    FILE* archivo;
    fopen_s(&archivo,"vendedores.dat", "rb");
    if (archivo != NULL) {
        while (fread(&vendedorGuardado, sizeof(Vendedor), 1, archivo) == 1) {
            if (vendedorGuardado.codigo == venta.codigo_vendedor) {
                existe = true;
                cout << endl<<"El vendedor existe" << endl<<endl;
            }
        }
        fclose(archivo);
    }
    else {
        cerr << "No se pudo abrir archivo vendedor." << endl;
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
int mostrarVentas() {
    FILE* archivo;
    fopen_s(&archivo, "ventas.dat", "rb");
    if (archivo != NULL) {
        Venta venta;
        int i = 0;
        while (fread(&venta, sizeof(Venta), 1, archivo) == 1) {
            i++;
            cout << endl << "Venta n°" << i << " :" << endl;
            cout << "Codigo vendedor: " << venta.codigo_vendedor << endl;
            cout << "Codigo producto: " << venta.codigo_producto << endl;
            cout << "Monto total: " << venta.monto_venta << endl;
        }
        fclose(archivo);
    }
    else {
        cout << "Archivo creado." << endl;
    }
    return 0;
};
int main() {
    Venta venta;
    do {
        venta = dameVenta();
        if (existeVendedor(venta)){

            FILE* archivoVentas;
            fopen_s(&archivoVentas, "ventas.dat", "ab");

            if (archivoVentas != NULL) {

                fwrite(&venta, sizeof(Venta), 1, archivoVentas);
                fclose(archivoVentas);
                cout << endl << "Venta guardada." << endl << endl;
            }
            else {
                cout << "Archivo creado." << endl;
            }
        }
    } while (continuar());
    mostrarVentas();
	return 0;
}