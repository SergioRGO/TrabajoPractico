/*2. Registro de Ventas Diarias (`ventas.cpp`)

 - Permitir cargar hasta **1000 ventas por d�a**.
 - Debe cargar la fecha en formato `AAAAMMDD`.
 - Cada venta debe registrar:
 - C�digo de vendedor
 - C�digo de producto
 - Monto de la venta
 - Guardar todas las ventas en `ventas_diarias.dat`.

 **Tip**: Validar que el vendedor exista al momento de registrar la venta.*/

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_VENTAS = 1000;
const int MAX_VENDEDORES = 100;


struct Vendedor {
	int codigo;
	char nombre[50];
	char sucursal[50];
};

struct Venta {
	int fecha;
	int codigo_vendedor;
	int codigo_producto;
	float monto_venta;
};
void cargarVendedores(Vendedor vec[], int& len) {
	FILE* arch;
	fopen_s(&arch,"Vendedores.dat", "rb");
	if (!arch) {
		len = 0;
		return;
	}
	len = 0;
	while (fread(&vec[len], sizeof(Vendedor), 1, arch) && len < MAX_VENDEDORES) {
		len++;
	}
	fclose(arch);
}
void guardarTodoEnArchivo(Venta ventas[], int lenVentas) {
	FILE* arch;
	fopen_s(&arch,"ventas_diarias.dat", "ab");
	if (!arch) {
		cout << "Error al abrir el archivo de ventas para guardar." << endl;
		return;
	}
	fwrite(ventas, sizeof(Venta), lenVentas, arch);
	fclose(arch);
	cout << "\nVentas registradas con exito." << endl;
}
bool vendedorExiste(int codigoext, Vendedor vec[], int len) {
	for (int i = 0; i < len; i++) {
		if (vec[i].codigo == codigoext)
			return true;
	}
	return false;
}
void cargarVentas() {

	Venta ventas[MAX_VENTAS];
	int lenVentas = 0;
	Vendedor vendedores[MAX_VENDEDORES];
	int lenVendedores = 0;

	cargarVendedores(vendedores, lenVendedores);

	if (lenVendedores == 0) {
		cout << "No hay vendedores registrados. No se puede cargar ventas."
			<< endl;
		return;
	}

	char seguir='s';

	do {
		if (lenVentas >= MAX_VENTAS) {
			cout << "Se alcanzo el limite maximo de ventas diarias." << endl;
			break;
		}
		Venta nueva;
		cout << "Ingrese fecha de la venta (AAAAMMDD): ";
		cin >> nueva.fecha;
		cout << "Ingrese codigo del vendedor: ";
		cin >> nueva.codigo_vendedor;
		if (!vendedorExiste(nueva.codigo_vendedor, vendedores, lenVendedores)) {
			cout << "Error: el codigo de vendedor no existe." << endl;
			continue;
		}
		cout << "Ingrese codigo del producto: ";
		cin >> nueva.codigo_producto;
		cout << "Ingrese monto de la venta: ";
		cin >> nueva.monto_venta;
		ventas[lenVentas++] = nueva;
		cout << "�Desea ingresar otra venta? (s/n): ";
		cin >> seguir;
		cin.ignore();
	} while (seguir == 's' || seguir == 'S');
	guardarTodoEnArchivo(ventas, lenVentas);
}
void mostrarVentas() {
	FILE* arch;
	fopen_s(&arch,"ventas_diarias.dat", "rb");
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
int main() {
	cargarVentas();
	mostrarVentas();
	return 0;
}