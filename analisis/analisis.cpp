#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct Venta {
	int fecha;
	int codigo_vendedor;
	int codigo_producto;
	float monto_venta;
};

struct Vendedor {
	int codigo;
	char nombre[50];
	char sucursal[50];
};

struct Lista {
	Venta ventas[1000];
	int len_ventas = 0;
	Vendedor vendedores[100];
	int len_vendedores = 0;
};

void ordenarListaPorCodigo(Lista& lista) {
	for (int i = 0; i < lista.len_ventas - 1; i++) {
		for (int j = 0; j < lista.len_ventas - i - 1; j++) {
			if (lista.ventas[j].codigo_vendedor > lista.ventas[j + 1].codigo_vendedor) {
				Venta temp = lista.ventas[j];
				lista.ventas[j] = lista.ventas[j + 1];
				lista.ventas[j + 1] = temp;
			}
		}
	}
}
void ordenarListaPorSucursal(Lista& lista) {

	for (int i = 0; i < lista.len_vendedores-1; i++) {
		for(int j=i+1;j<lista.len_vendedores;j++)
			if (strcmp(lista.vendedores[i].sucursal , lista.vendedores[j].sucursal)==0) {
				Vendedor temp = lista.vendedores[j];
				lista.vendedores[j] = lista.vendedores[i + 1];
				lista.vendedores[i+1] = temp;
				continue;
			}
	}
	/* 
		for (int i = 0; i < lista.len_vendedores; i++) {
		cout << lista.len_vendedores<<endl;
		for (int j = 0; i < lista.len_vendedores - 1; j++) {
			if (strcmp(lista.vendedores[j].sucursal,lista.vendedores[j + 1].sucursal)==0) {
				Vendedor temp = lista.vendedores[j];
				lista.vendedores[j] = lista.vendedores[j + 1];
				lista.vendedores[j + 1] = temp;
			}
		}
	}*/
}
	

void dameVendedores(Lista& lista) {
	Vendedor vendedorGuardado;
	FILE* archivoVendedores;
	fopen_s(&archivoVendedores, "Vendedores.dat", "rb");
	if (archivoVendedores != NULL) {
		while (fread(&vendedorGuardado, sizeof(Vendedor), 1, archivoVendedores) == 1) {
			lista.vendedores[lista.len_vendedores] = vendedorGuardado;
			lista.len_vendedores++;
		}
		fclose(archivoVendedores);
	}
}
void dameVentas(Lista& lista) {
	Venta VentaGuardada;
	FILE* archivoVentas;
	fopen_s(&archivoVentas, "ventas_diarias.dat", "rb");
	if (archivoVentas != NULL) {
		while (fread(&VentaGuardada, sizeof(Venta), 1, archivoVentas) == 1) {
			lista.ventas[lista.len_ventas] = VentaGuardada;
			lista.len_ventas++;
		}
		fclose(archivoVentas);
	}
}
int buscarSec(Lista lista, int valor) {
	int i = 0;
	while (i < lista.len_vendedores && lista.vendedores[i].codigo != valor) {
		i++;
	}
	if (i == lista.len_vendedores) {
		return -1;
	}
	else {
		return i;
	}
}
string mostrarChars(char nombre[]) {
	int i = 0;
	string devolver = "";
	while (nombre[i] != '\0') {
		devolver += nombre[i];
		i++;
	}
	return devolver;
}
void vendedorMasDineroGenerado(Lista& lista) {

	int a = 0;
	int vendedorMaximo = lista.ventas[0].codigo_vendedor;
	int ventaMaxima = 0;
	//Corte de control

	while (a < lista.len_ventas) {
		int vendedor_actual = lista.ventas[a].codigo_vendedor;
		int sumaVentas = 0;
		while (a < lista.len_ventas && lista.ventas[a].codigo_vendedor == vendedor_actual) {
			sumaVentas += lista.ventas[a].monto_venta;
			a++;
		}
		if (sumaVentas > ventaMaxima) {
			ventaMaxima = sumaVentas;
			vendedorMaximo = vendedor_actual;
		}
	}
	cout << "El vendedor que mas dinero genero es " << mostrarChars(lista.vendedores[buscarSec(lista, vendedorMaximo)].nombre) << " con un total de: $" << ventaMaxima << " generados" << endl;
}

void sucursalMasDineroGenerado(Lista& lista) {
	int a = 0;
	string sucursalMaxima = mostrarChars(lista.vendedores[0].sucursal);
	int ventaMaxima = 0;
	//Corte de control
	while (a < lista.len_vendedores) {
		int sucursal_actual = lista.ventas[a].codigo_vendedor;
		int sumaVentas = 0;
		while (a < lista.len_ventas && lista.ventas[a].codigo_vendedor == vendedor_actual) {
			sumaVentas += lista.ventas[a].monto_venta;
			a++;
		}
		if (sumaVentas > ventaMaxima) {
			ventaMaxima = sumaVentas;
			vendedorMaximo = vendedor_actual;
		}
	}
	cout << "El vendedor que mas dinero genero es " << mostrarChars(lista.vendedores[buscarSec(lista, vendedorMaximo)].nombre) << " con un total de: $" << ventaMaxima << " generados" << endl;
}
}

// Mostrares
void mostrarArchivo() {
	FILE* arch;
	fopen_s(&arch, "Vendedores.dat", "rb");
	if (!arch) {
		cout << "Archivo vacio o no encontrado." << endl;
		return;
	}

	Vendedor v;
	while (fread(&v, sizeof(Vendedor), 1, arch)) {
		cout << "Codigo: " << v.codigo << endl;
		cout << "Nombre: " << v.nombre << endl;
		cout << "Sucursal: " << v.sucursal << endl;
		cout << "-----------------------------" << endl;
	}

	fclose(arch);
}

void mostrarVentas() {
	FILE* arch;
	fopen_s(&arch, "ventas_diarias.dat", "rb");
	if (!arch) {
		cout << "Archivo de ventas vacio o no encontrado." << endl;
		return;
	}
	Venta v;
	cout << "\nVentas registradas:\n";
	while (fread(&v, sizeof(Venta), 1, arch)) {
		cout << "Fecha: " << v.fecha << endl;
		cout << "Vendedor: " << v.codigo_vendedor << endl;
		cout << "Producto: " << v.codigo_producto << endl;
		cout << "Monto: $" << v.monto_venta << endl;
		cout << "-----------------------------" << endl;
	}
	fclose(arch);
}

void mostrarVentas(Lista lista) {

	cout << "\nVentas registradas:\n";
	for (int i=0; i < lista.len_ventas;i++) {
		cout << "Fecha: " << lista.ventas[i].fecha << endl;
		cout << "Vendedor: " << lista.ventas[i].codigo_vendedor << endl;
		cout << "Producto: " << lista.ventas[i].codigo_producto << endl;
		cout << "Monto: $" << lista.ventas[i].monto_venta << endl;
		cout << "-----------------------------" << endl;
	}
}

void mostrarArchivo(Lista lista) {

	for (int i = 0; i < lista.len_vendedores; i++) {
		cout << "Codigo: " << lista.vendedores[i].codigo << endl;
		cout << "Nombre: " << lista.vendedores[i].nombre << endl;
		cout << "Sucursal: " << lista.vendedores[i].sucursal << endl;
		cout << "-----------------------------" << endl;
	}
}
int main() {


	/*
	- Determinar **el vendedor que más dinero generó** (mostrar su nombre y monto total).
	- Determinar **la sucursal que más dinero generó** (sumando las ventas de todos los vendedores de esa sucursal).
	- Mostrar **un ranking de los productos más vendidos** (por cantidad de veces que se vendió cada código de producto).

	- Agrupar ventas por vendedor y sucursal usando **corte de control** o acumulación.
	- Para ranking de productos, contar ocurrencias y luego ordenar.
	*/

	//Array de vendedores

	Lista lista;
	mostrarArchivo();
	mostrarVentas();
	dameVendedores(lista);
	dameVentas(lista);
	ordenarListaPorCodigo(lista);
	vendedorMasDineroGenerado(lista);
	ordenarListaPorSucursal(lista);
	mostrarArchivo(lista);
	return 0;
}