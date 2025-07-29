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

struct Lista{
	Venta ventas[1000];
	int len_ventas=0;
	Vendedor vendedores[100];
	int len_vendedores=0;
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
	for (int i = 0; i < lista.len_vendedores; i++) {
		for (int j = 0; i < lista.len_vendedores - 1; j++) {
			if (lista.vendedores[j].codigo > lista.vendedores[j + 1].codigo) {
				Vendedor temp = lista.vendedores[j];
				lista.vendedores[j] = lista.vendedores[j + 1];
				lista.vendedores[j + 1] = temp;
			}
		}
	}
}
void ordenarListaPorSucursal(Lista& lista) {
	for (int i = 0; i < lista.len_vendedores; i++) {
		for (int j = 0; i < lista.len_vendedores - 1; j++) {
			if (lista.vendedores[j].sucursal > lista.vendedores[j + 1].sucursal) {
				Vendedor temp = lista.vendedores[j];
				lista.vendedores[j] = lista.vendedores[j + 1];
				lista.vendedores[j + 1] = temp;
			}
		}
	}
}

void dameVendedores(Lista& lista) {
	Vendedor vendedorGuardado;
	FILE* archivoVendedores;
	fopen_s(&archivoVendedores, "vendedores.dat", "rb");
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
	fopen_s(&archivoVentas, "ventas.dat", "rb");
	if (archivoVentas != NULL) {
		while (fread(&VentaGuardada, sizeof(Venta), 1, archivoVentas) == 1) {
			lista.ventas[lista.len_ventas] = VentaGuardada;
			lista.len_ventas++;
		}
		fclose(archivoVentas);
	}
}

void vendedorMasDineroGenerado(Lista& lista){
	
	//Vendedor masVentas;
	int a = 0;
	int vendedorMaximo=lista.ventas[0].codigo_vendedor;
	int ventaMaxima=0;
	//Corte de control
	while (a < lista.len_ventas) {
		int vendedor_actual = lista.ventas[a].codigo_vendedor;
		int sumaVentas = 0;
		while (a < lista.len_ventas && lista.ventas[a].codigo_producto == vendedor_actual) {
			a++;
			sumaVentas += lista.ventas[a].monto_venta;
		}
		if (sumaVentas > ventaMaxima) {
			ventaMaxima = sumaVentas;
			vendedorMaximo = vendedor_actual;
		}
	}
	cout << "El vendedor que mas dinero generó es " << lista.vendedores[busquedaBinaria(lista, vendedorMaximo)].nombre << " con un total de: $" << ventaMaxima << " generados" << endl;
}

void  sucursalMasDineroGenerado(Lista lista) {
	Vendedor masVentas;
	int a = 0;
	int ventaMaxima = 0;


}
void copiarSucursal(Vendedor& vendedor,Vendedor asignar) {
	while (asignar.sucursal != '\0') {

	}
	for (int i = 0; i < 50; ++i) {
		vendedor.sucursal[i] = asignar.sucursal[i];
		if (asignar.sucursal[i] == '\0') break;
	}

}

int busquedaBinaria(Lista lista, int valor) {
	int izquierda = 0;
	int derecha = lista.len_vendedores - 1;
	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		if (lista.vendedores[medio].codigo == valor) {
			return medio;
		}
		else if (lista.vendedores[medio].codigo < valor) {
			izquierda = medio + 1;
		}
		else {
			derecha = medio - 1;
		}
	}
	return -1;
}

void mostrar(char nombre[], int cant) {
	cant = 0;
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
	
	dameVendedores(lista);
	dameVentas(lista);
	ordenarListaPorCodigo(lista);
	vendedorMasDineroGenerado(lista);
	ordenarListaPorSucursal(lista);
	sucursalMasDineroGenerado(lista);
	return 0;
}