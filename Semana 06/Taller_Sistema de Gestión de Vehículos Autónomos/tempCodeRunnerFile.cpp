#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Paso 1: Clase abstracta Vehiculo
class Vehiculo {
protected:
    string id;
    int velocidad;
    
public:
    Vehiculo(string _id, int _vel) : id(_id), velocidad(_vel) {}
    
    virtual void moverse() = 0;  // Método virtual puro
    
    virtual void mostrarInfo() {
        cout << "ID: " << id << ", Velocidad: " << velocidad << " km/h";
    }
    
    // Declaración de clase amiga
    friend class Reporte;
    
    virtual ~Vehiculo() {
        cout << "Destructor de Vehiculo" << endl;
    }
};

// Paso 2: Clases derivadas
class Auto : public Vehiculo {
private:
    string modelo;
    
public:
    Auto(string _id, int _vel, string _modelo) 
        : Vehiculo(_id, _vel), modelo(_modelo) {}
    
    void moverse() override {
        cout << "Auto " << modelo << " circulando por carretera" << endl;
    }
    
    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << ", Modelo: " << modelo << " (Auto)" << endl;
    }
};

class Drone : public Vehiculo {
private:
    double alturaMaxima;
    
public:
    Drone(string _id, int _vel, double _altura) 
        : Vehiculo(_id, _vel), alturaMaxima(_altura) {}
    
    void moverse() override {
        cout << "Drone volando a altura maxima de " << alturaMaxima << " metros" << endl;
    }
    
    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << ", Altura Max: " << alturaMaxima << " m (Drone)" << endl;
    }
};

class Camion : public Vehiculo {
private:
    double capacidadCarga;
    
public:
    Camion(string _id, int _vel, double _carga) 
        : Vehiculo(_id, _vel), capacidadCarga(_carga) {}
    
    void moverse() override {
        cout << "Camion transportando " << capacidadCarga << " toneladas" << endl;
    }
    
    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << ", Capacidad: " << capacidadCarga << " ton (Camion)" << endl;
    }
};

// Paso 4: Polimorfismo estático con template
template <typename T>
T calcularEficiencia(T consumo, T distancia) {
    return distancia / consumo;
}

// Paso 5: Clase amiga Reporte
class Reporte {
public:
    void generarReporte(Vehiculo* v) {
        cout << "\n=== REPORTE DEL VEHICULO ===" << endl;
        cout << "ID (acceso directo): " << v->id << endl;
        cout << "Velocidad (acceso directo): " << v->velocidad << " km/h" << endl;
        cout << "===========================\n" << endl;
    }
};

/* 
   PASO 6: REFLEXIÓN ACTIVA - MIS RESPUESTAS
   
   1. ¿Qué ocurre si eliminamos virtual del destructor?
      R: Si quito el 'virtual' del destructor, cuando elimine un objeto derivado 
      usando un puntero de la clase base, solo se llamará al destructor de Vehiculo 
      y no al de Auto, Drone o Camion. Esto causaría fugas de memoria porque los 
      atributos específicos de cada vehículo no se liberarían correctamente. 
      Me pasó una vez y no entendía por qué mi programa consumía cada vez más memoria.
   
   2. ¿Qué sucede si quitamos override?
      R: Si quito 'override', el programa sigue funcionando porque igual estoy 
      sobrescribiendo el método virtual. Pero pierdo la protección que me da el 
      compilador para asegurarme de que realmente estoy sobrescribiendo algo. 
      Una vez cometí el error de escribir "moverse()" con mayúscula sin querer 
      y el compilador no me avisó porque había quitado el override. El programa 
      compilaba pero no funcionaba como esperaba.
   
   3. ¿Qué diferencia existe entre usar punteros y objetos directos?
      R: Con objetos directos (como 'Auto miAuto') todo se crea en la pila, 
      es más rápido pero no puedo aprovechar el polimorfismo. Con punteros 
      puedo tratar a todos los vehículos por igual en un vector y llamar a 
      sus métodos específicos, aunque tengo que acordarme de liberar la memoria 
      con delete. Personalmente prefiero usar punteros cuando necesito flexibilidad,
      pero hay que ser cuidadoso con la gestión de memoria.
*/

// Función main para probar todo
int main() {
    // Paso 3: Polimorfismo dinámico
    vector<Vehiculo*> flota;
    
    // Crear vehículos
    flota.push_back(new Auto("A001", 120, "Tesla Model 3"));
    flota.push_back(new Drone("D001", 60, 100.5));
    flota.push_back(new Camion("C001", 80, 20.0));
    
    cout << "=== MOVIMIENTO DE VEHICULOS ===" << endl;
    for(auto v : flota) {
        v->moverse();
        v->mostrarInfo();
        cout << endl;
    }
    
    // Probar polimorfismo estático
    cout << "\n=== POLIMORFISMO ESTATICO (TEMPLATES) ===" << endl;
    cout << "Eficiencia Auto (int): " << calcularEficiencia<int>(10, 100) << " km/L" << endl;
    cout << "Eficiencia Drone (double): " << calcularEficiencia<double>(5.5, 150.0) << " km/kWh" << endl;
    
    // Probar clase amiga
    cout << "\n=== CLASE AMIGA ===" << endl;
    Reporte reporte;
    reporte.generarReporte(flota[0]);
    
    // Liberar memoria
    cout << "\n=== DESTRUCTORES ===" << endl;
    for(auto v : flota) {
        delete v;
    }
    
    return 0;
}