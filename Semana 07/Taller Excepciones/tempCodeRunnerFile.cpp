/*
Explicacion breve de que excepciones implemento y por que:

Implemente las excepciones estandar y una personalizada para garantizar la robustez del sistema:

- std::invalid_argument: La uso en los metodos depositar y retirar para validar que los montos sean positivos. Si el usuario ingresa un numero negativo, lanzo esta excepcion para indicar que el argumento proporcionado no es valido para la operacion.

- std::runtime_error: La utilizo en el metodo retirar cuando el saldo es insuficiente. Es una excepcion de tiempo de ejecucion que indica que la operacion no puede completarse debido al estado actual del objeto.

- std::out_of_range: La implemento en el menu principal cuando el usuario selecciona una opcion fuera del rango permitido (1-6). Esto evita accesos invalidos a las opciones del menu.

- CuentaNoEncontrada (excepcion personalizada que hereda de std::runtime_error): La cree para manejar especificamente el caso en que se busca una cuenta que no existe en el banco. Al heredar de runtime_error, mantengo la jerarquia de excepciones estandar de C++ y proporciono un mensaje descriptivo del error especifico del dominio bancario.

Todas las excepciones se capturan por referencia constante (const&) para evitar copias innecesarias y preservar el polimorfismo. Los bloques catch estan ordenados de mas especificos a mas generales, comenzando con las excepciones personalizadas y estandar especificas, y terminando con catch(...) como ultimo recurso para cualquier excepcion no esperada.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <memory>

using namespace std;

// Excepcion personalizada que hereda de runtime_error
class CuentaNoEncontrada : public runtime_error {
public:
    CuentaNoEncontrada(const string& mensaje) : runtime_error(mensaje) {}
};

class CuentaBancaria {
private:
    int numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(int numero, const string& nombreTitular, double saldoInicial = 0.0) 
        : numeroCuenta(numero), titular(nombreTitular), saldo(saldoInicial) {
        if (saldoInicial < 0) {
            throw invalid_argument("El saldo inicial no puede ser negativo");
        }
    }

    void depositar(double monto) {
        if (monto <= 0) {
            throw invalid_argument("El monto a depositar debe ser positivo");
        }
        saldo += monto;
        cout << "Deposito exitoso. Nuevo saldo: $" << saldo << endl;
    }

    void retirar(double monto) {
        if (monto <= 0) {
            throw invalid_argument("El monto a retirar debe ser positivo");
        }
        if (monto > saldo) {
            throw runtime_error("Saldo insuficiente para realizar el retiro");
        }
        saldo -= monto;
        cout << "Retiro exitoso. Nuevo saldo: $" << saldo << endl;
    }

    double consultarSaldo() const {
        return saldo;
    }

    int getNumeroCuenta() const {
        return numeroCuenta;
    }

    string getTitular() const {
        return titular;
    }

    void mostrarInfo() const {
        cout << "Cuenta #" << numeroCuenta << " | Titular: " << titular << " | Saldo: $" << saldo << endl;
    }
};

class Banco {
private:
    vector<CuentaBancaria> cuentas;

public:
    void agregarCuenta() {
        try {
            int numero;
            string titular;
            double saldoInicial;

            cout << "Ingrese numero de cuenta: ";
            cin >> numero;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido para la cuenta");
            }

            cout << "Ingrese nombre del titular: ";
            cin.ignore();
            getline(cin, titular);

            cout << "Ingrese saldo inicial (opcional, presione 0 para omitir): ";
            cin >> saldoInicial;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido para el saldo");
            }

            CuentaBancaria nuevaCuenta(numero, titular, saldoInicial);
            cuentas.push_back(nuevaCuenta);
            cout << "Cuenta creada exitosamente!" << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error al crear cuenta: " << e.what() << endl;
        }
    }

    CuentaBancaria* buscarCuenta(int numero) {
        for (auto& cuenta : cuentas) {
            if (cuenta.getNumeroCuenta() == numero) {
                return &cuenta;
            }
        }
        throw CuentaNoEncontrada("No existe una cuenta con el numero: " + to_string(numero));
    }

    void realizarDeposito() {
        try {
            int numero;
            double monto;

            cout << "Ingrese numero de cuenta: ";
            cin >> numero;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido");
            }

            CuentaBancaria* cuenta = buscarCuenta(numero);

            cout << "Ingrese monto a depositar: $";
            cin >> monto;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido para el monto");
            }

            cuenta->depositar(monto);
        }
        catch (const CuentaNoEncontrada& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error de validacion: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Error de operacion: " << e.what() << endl;
        }
    }

    void realizarRetiro() {
        try {
            int numero;
            double monto;

            cout << "Ingrese numero de cuenta: ";
            cin >> numero;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido");
            }

            CuentaBancaria* cuenta = buscarCuenta(numero);

            cout << "Ingrese monto a retirar: $";
            cin >> monto;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido para el monto");
            }

            cuenta->retirar(monto);
        }
        catch (const CuentaNoEncontrada& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error de validacion: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Error de operacion: " << e.what() << endl;
        }
    }

    void consultarSaldoCuenta() {
        try {
            int numero;

            cout << "Ingrese numero de cuenta: ";
            cin >> numero;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido");
            }

            CuentaBancaria* cuenta = buscarCuenta(numero);
            cout << "Saldo actual de la cuenta " << numero << ": $" << cuenta->consultarSaldo() << endl;
        }
        catch (const CuentaNoEncontrada& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error de validacion: " << e.what() << endl;
        }
    }

    void mostrarCuentas() {
        if (cuentas.empty()) {
            cout << "No hay cuentas registradas en el sistema." << endl;
            return;
        }

        cout << "\n=== LISTADO DE CUENTAS ===" << endl;
        for (const auto& cuenta : cuentas) {
            cuenta.mostrarInfo();
        }
        cout << "==========================\n" << endl;
    }
};

int main() {
    Banco miBanco;
    int opcion;

    cout << "=== SISTEMA BANCARIO ===" << endl;

    do {
        try {
            cout << "\nMENU PRINCIPAL:" << endl;
            cout << "1. Crear cuenta" << endl;
            cout << "2. Depositar dinero" << endl;
            cout << "3. Retirar dinero" << endl;
            cout << "4. Consultar saldo" << endl;
            cout << "5. Mostrar todas las cuentas" << endl;
            cout << "6. Salir" << endl;
            cout << "Seleccione una opcion: ";
            
            cin >> opcion;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero valido");
            }

            if (opcion < 1 || opcion > 6) {
                throw out_of_range("Opcion no valida. Debe seleccionar entre 1 y 6");
            }

            switch (opcion) {
                case 1:
                    miBanco.agregarCuenta();
                    break;
                case 2:
                    miBanco.realizarDeposito();
                    break;
                case 3:
                    miBanco.realizarRetiro();
                    break;
                case 4:
                    miBanco.consultarSaldoCuenta();
                    break;
                case 5:
                    miBanco.mostrarCuentas();
                    break;
                case 6:
                    cout << "Gracias por usar el sistema bancario!" << endl;
                    break;
            }
        }
        catch (const CuentaNoEncontrada& e) {
            // Esta excepcion se maneja primero porque es mas especifica
            cout << "Error de cuenta: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "Error de menu: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error de entrada: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Error en tiempo de ejecucion: " << e.what() << endl;
        }
        catch (...) {
            cout << "Error desconocido. El sistema continuara operando." << endl;
        }

    } while (opcion != 6);

    return 0;
}