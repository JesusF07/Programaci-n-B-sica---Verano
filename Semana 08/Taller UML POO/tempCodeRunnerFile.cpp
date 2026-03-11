#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <regex>
#include <stdexcept>

using namespace std;

// ==================== EXCEPCIÓN PERSONALIZADA ====================
class EntidadNoEncontrada : public runtime_error {
public:
    EntidadNoEncontrada(const string& mensaje) : runtime_error(mensaje) {}
};

// ==================== CLASE PERSONA (BASE) ====================
class Persona {
protected:
    string nombre;
public:
    Persona(const string& nombre) : nombre(nombre) {}
    virtual ~Persona() = default;
    
    string getNombre() const { return nombre; }
    void setNombre(const string& n) { nombre = n; }
    
    virtual void mostrar() const = 0;
};

// ==================== CLASE ENTRADAHISTORIA ====================
class EntradaHistoria {
private:
    string fecha;
    string nota;
    string diagnostico;
public:
    EntradaHistoria(const string& fecha, const string& nota, const string& diagnostico)
        : fecha(fecha), nota(nota), diagnostico(diagnostico) {}
    
    void mostrar() const {
        cout << "    Fecha: " << fecha << endl;
        cout << "    Nota: " << nota << endl;
        cout << "    Diagnóstico: " << diagnostico << endl;
    }
};

// ==================== CLASE HISTORIACLINICA ====================
class HistoriaClinica {
private:
    vector<EntradaHistoria> entradas;
public:
    void agregarEntrada(const string& fecha, const string& nota, const string& diagnostico) {
        entradas.push_back(EntradaHistoria(fecha, nota, diagnostico));
    }
    
    void mostrar() const {
        if (entradas.empty()) {
            cout << "  Historia clínica vacía" << endl;
            return;
        }
        cout << "  HISTORIA CLÍNICA:" << endl;
        for (size_t i = 0; i < entradas.size(); i++) {
            cout << "  Entrada #" << i + 1 << ":" << endl;
            entradas[i].mostrar();
        }
    }
};

// ==================== CLASE PACIENTE ====================
class Paciente : public Persona {
private:
    string dni;
    int edad;
    string telefono;
    HistoriaClinica historia;
    
    void validarDatos() const {
        // Validar DNI (8 dígitos)
        if (dni.length() != 8 || !regex_match(dni, regex("\\d{8}"))) {
            throw invalid_argument("DNI debe tener exactamente 8 dígitos numéricos");
        }
        
        // Validar edad
        if (edad < 0 || edad > 120) {
            throw out_of_range("Edad debe estar entre 0 y 120 años");
        }
        
        // Validar teléfono (9 dígitos)
        if (telefono.length() != 9 || !regex_match(telefono, regex("\\d{9}"))) {
            throw invalid_argument("Teléfono debe tener 9 dígitos");
        }
    }
    
public:
    Paciente(const string& nombre, const string& dni, int edad, const string& telefono)
        : Persona(nombre), dni(dni), edad(edad), telefono(telefono) {
        validarDatos();
    }
    
    string getDni() const { return dni; }
    int getEdad() const { return edad; }
    string getTelefono() const { return telefono; }
    
    HistoriaClinica& getHistoria() { return historia; }
    
    void mostrar() const override {
        cout << "PACIENTE: " << nombre << endl;
        cout << "  DNI: " << dni << endl;
        cout << "  Edad: " << edad << endl;
        cout << "  Teléfono: " << telefono << endl;
    }
    
    void mostrarConHistoria() const {
        mostrar();
        historia.mostrar();
    }
};

// ==================== CLASE DOCTOR ====================
class Doctor : public Persona {
private:
    string codigo;
    string especialidad;
    double tarifa;
    
    void validarDatos() const {
        // Validar tarifa
        if (tarifa <= 0) {
            throw invalid_argument("La tarifa debe ser mayor a 0");
        }
        
        // Validar código (no vacío)
        if (codigo.empty()) {
            throw invalid_argument("El código del doctor no puede estar vacío");
        }
    }
    
public:
    Doctor(const string& nombre, const string& codigo, const string& especialidad, double tarifa)
        : Persona(nombre), codigo(codigo), especialidad(especialidad), tarifa(tarifa) {
        validarDatos();
    }
    
    string getCodigo() const { return codigo; }
    string getEspecialidad() const { return especialidad; }
    double getTarifa() const { return tarifa; }
    
    void mostrar() const override {
        cout << "DOCTOR: " << nombre << endl;
        cout << "  Código: " << codigo << endl;
        cout << "  Especialidad: " << especialidad << endl;
        cout << "  Tarifa: S/." << fixed << setprecision(2) << tarifa << endl;
    }
};

// ==================== CLASE CITA ====================
class Cita {
private:
    int id;
    Paciente* paciente;
    Doctor* doctor;
    string fecha;
    string hora;
    string motivo;
    bool activa;
    
    void validarFormatoFecha(const string& f) const {
        // Formato YYYY-MM-DD
        regex formato("\\d{4}-\\d{2}-\\d{2}");
        if (!regex_match(f, formato)) {
            throw invalid_argument("Formato de fecha debe ser YYYY-MM-DD");
        }
    }
    
    void validarFormatoHora(const string& h) const {
        // Formato HH:MM
        regex formato("\\d{2}:\\d{2}");
        if (!regex_match(h, formato)) {
            throw invalid_argument("Formato de hora debe ser HH:MM");
        }
    }
    
public:
    Cita(int id, Paciente* p, Doctor* d, const string& fecha, const string& hora, const string& motivo)
        : id(id), paciente(p), doctor(d), fecha(fecha), hora(hora), motivo(motivo), activa(true) {
        
        if (!p || !d) {
            throw invalid_argument("Paciente y Doctor no pueden ser nulos");
        }
        
        validarFormatoFecha(fecha);
        validarFormatoHora(hora);
        
        if (motivo.empty()) {
            throw invalid_argument("El motivo de la cita no puede estar vacío");
        }
    }
    
    int getId() const { return id; }
    Paciente* getPaciente() const { return paciente; }
    Doctor* getDoctor() const { return doctor; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    bool estaActiva() const { return activa; }
    
    void cancelar() { activa = false; }
    
    void mostrar() const {
        cout << "CITA #" << id << " - " << (activa ? "ACTIVA" : "CANCELADA") << endl;
        cout << "  Paciente: " << paciente->getNombre() << " (DNI: " << paciente->getDni() << ")" << endl;
        cout << "  Doctor: " << doctor->getNombre() << " (" << doctor->getEspecialidad() << ")" << endl;
        cout << "  Fecha: " << fecha << " - Hora: " << hora << endl;
        cout << "  Motivo: " << motivo << endl;
    }
    
    bool mismaFechaHora(const string& f, const string& h) const {
        return activa && fecha == f && hora == h;
    }
};

// ==================== CLASE CLINICA ====================
class Clinica {
private:
    vector<unique_ptr<Persona>> personas;
    vector<Cita> citas;
    int nextCitaId;
    
public:
    Clinica() : nextCitaId(1) {}
    
    void registrarPaciente() {
        try {
            string nombre, dni, telefono;
            int edad;
            
            cout << "\n--- REGISTRAR PACIENTE ---" << endl;
            cout << "Nombre: ";
            getline(cin, nombre);
            
            cout << "DNI (8 dígitos): ";
            getline(cin, dni);
            
            cout << "Edad: ";
            cin >> edad;
            cin.ignore();
            
            cout << "Teléfono (9 dígitos): ";
            getline(cin, telefono);
            
            auto paciente = make_unique<Paciente>(nombre, dni, edad, telefono);
            personas.push_back(move(paciente));
            cout << "Paciente registrado exitosamente!" << endl;
            
        } catch (const exception& e) {
            cout << "Error al registrar paciente: " << e.what() << endl;
        }
    }
    
    void registrarDoctor() {
        try {
            string nombre, codigo, especialidad;
            double tarifa;
            
            cout << "\n--- REGISTRAR DOCTOR ---" << endl;
            cout << "Nombre: ";
            getline(cin, nombre);
            
            cout << "Código: ";
            getline(cin, codigo);
            
            cout << "Especialidad: ";
            getline(cin, especialidad);
            
            cout << "Tarifa: S/.";
            cin >> tarifa;
            cin.ignore();
            
            auto doctor = make_unique<Doctor>(nombre, codigo, especialidad, tarifa);
            personas.push_back(move(doctor));
            cout << "Doctor registrado exitosamente!" << endl;
            
        } catch (const exception& e) {
            cout << "Error al registrar doctor: " << e.what() << endl;
        }
    }
    
    Paciente* buscarPaciente(const string& dni) {
        for (auto& p : personas) {
            Paciente* paciente = dynamic_cast<Paciente*>(p.get());
            if (paciente && paciente->getDni() == dni) {
                return paciente;
            }
        }
        return nullptr;
    }
    
    Doctor* buscarDoctor(const string& codigo) {
        for (auto& p : personas) {
            Doctor* doctor = dynamic_cast<Doctor*>(p.get());
            if (doctor && doctor->getCodigo() == codigo) {
                return doctor;
            }
        }
        return nullptr;
    }
    
    void listarPersonas() const {
        cout << "\n--- LISTA DE PERSONAS ---" << endl;
        for (size_t i = 0; i < personas.size(); i++) {
            personas[i]->mostrar();
            cout << endl;
        }
    }
    
    void agendarCita() {
        try {
            string dniPaciente, codDoctor, fecha, hora, motivo;
            
            cout << "\n--- AGENDAR CITA ---" << endl;
            
            // Buscar paciente
            cout << "DNI del paciente: ";
            getline(cin, dniPaciente);
            Paciente* paciente = buscarPaciente(dniPaciente);
            if (!paciente) {
                throw EntidadNoEncontrada("No se encontró paciente con DNI: " + dniPaciente);
            }
            
            // Buscar doctor
            cout << "Código del doctor: ";
            getline(cin, codDoctor);
            Doctor* doctor = buscarDoctor(codDoctor);
            if (!doctor) {
                throw EntidadNoEncontrada("No se encontró doctor con código: " + codDoctor);
            }
            
            cout << "Fecha (YYYY-MM-DD): ";
            getline(cin, fecha);
            
            cout << "Hora (HH:MM): ";
            getline(cin, hora);
            
            cout << "Motivo: ";
            getline(cin, motivo);
            
            // Verificar cita duplicada
            for (const auto& cita : citas) {
                if (cita.mismaFechaHora(fecha, hora) && cita.getDoctor()->getCodigo() == codDoctor) {
                    throw runtime_error("Ya existe una cita activa con este doctor en la misma fecha y hora");
                }
            }
            
            Cita nuevaCita(nextCitaId++, paciente, doctor, fecha, hora, motivo);
            citas.push_back(nuevaCita);
            
            cout << "Cita agendada exitosamente! ID: " << nuevaCita.getId() << endl;
            
        } catch (const exception& e) {
            cout << "Error al agendar cita: " << e.what() << endl;
        }
    }
    
    void cancelarCita() {
        try {
            int id;
            cout << "\n--- CANCELAR CITA ---" << endl;
            cout << "ID de la cita: ";
            cin >> id;
            cin.ignore();
            
            for (auto& cita : citas) {
                if (cita.getId() == id) {
                    if (!cita.estaActiva()) {
                        throw runtime_error("La cita ya está cancelada");
                    }
                    cita.cancelar();
                    cout << "Cita cancelada exitosamente!" << endl;
                    return;
                }
            }
            
            throw EntidadNoEncontrada("No se encontró cita con ID: " + to_string(id));
            
        } catch (const exception& e) {
            cout << "Error al cancelar cita: " << e.what() << endl;
        }
    }
    
    void listarCitasPaciente() {
        try {
            string dni;
            cout << "\n--- CITAS POR PACIENTE ---" << endl;
            cout << "DNI del paciente: ";
            getline(cin, dni);
            
            Paciente* paciente = buscarPaciente(dni);
            if (!paciente) {
                throw EntidadNoEncontrada("No se encontró paciente con DNI: " + dni);
            }
            
            bool encontradas = false;
            for (const auto& cita : citas) {
                if (cita.getPaciente()->getDni() == dni) {
                    cita.mostrar();
                    cout << endl;
                    encontradas = true;
                }
            }
            
            if (!encontradas) {
                cout << "No hay citas para este paciente." << endl;
            }
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    void listarCitasDoctor() {
        try {
            string codigo;
            cout << "\n--- CITAS POR DOCTOR ---" << endl;
            cout << "Código del doctor: ";
            getline(cin, codigo);
            
            Doctor* doctor = buscarDoctor(codigo);
            if (!doctor) {
                throw EntidadNoEncontrada("No se encontró doctor con código: " + codigo);
            }
            
            bool encontradas = false;
            for (const auto& cita : citas) {
                if (cita.getDoctor()->getCodigo() == codigo) {
                    cita.mostrar();
                    cout << endl;
                    encontradas = true;
                }
            }
            
            if (!encontradas) {
                cout << "No hay citas para este doctor." << endl;
            }
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    vector<Cita>& getCitas() { return citas; }
};

// ==================== CLASE REPORTE ====================
class Reporte {
public:
    static void generarPorEspecialidad(Clinica& clinica) {
        cout << "\n--- REPORTE POR ESPECIALIDAD ---" << endl;
        
        map<string, int> citasPorEspecialidad;
        map<string, double> ingresosPorEspecialidad;
        
        for (auto& cita : clinica.getCitas()) {
            if (cita.estaActiva()) {
                string especialidad = cita.getDoctor()->getEspecialidad();
                double tarifa = cita.getDoctor()->getTarifa();
                
                citasPorEspecialidad[especialidad]++;
                ingresosPorEspecialidad[especialidad] += tarifa;
            }
        }
        
        if (citasPorEspecialidad.empty()) {
            cout << "No hay citas activas para generar reporte." << endl;
            return;
        }
        
        cout << left << setw(20) << "Especialidad" 
             << setw(15) << "Citas" 
             << "Ingresos" << endl;
        cout << string(50, '-') << endl;
        
        for (const auto& par : citasPorEspecialidad) {
            cout << left << setw(20) << par.first
                 << setw(15) << par.second
                 << "S/." << fixed << setprecision(2) 
                 << ingresosPorEspecialidad[par.first] << endl;
        }
    }
};

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    Clinica clinica;
    int opcion;
    
    cout << "======================================" << endl;
    cout << "   CLÍNICA SALUD+ - SISTEMA DE CITAS  " << endl;
    cout << "======================================" << endl;
    
    do {
        try {
            cout << "\n--- MENÚ PRINCIPAL ---" << endl;
            cout << "1. Registrar paciente" << endl;
            cout << "2. Registrar doctor" << endl;
            cout << "3. Agendar cita" << endl;
            cout << "4. Cancelar cita" << endl;
            cout << "5. Listar citas por paciente" << endl;
            cout << "6. Listar citas por doctor" << endl;
            cout << "7. Reporte por especialidad" << endl;
            cout << "8. Salir" << endl;
            cout << "Opción: ";
            
            cin >> opcion;
            cin.ignore();
            
            if (opcion < 1 || opcion > 8) {
                throw out_of_range("Opción no válida. Ingrese un número entre 1 y 8.");
            }
            
            switch (opcion) {
                case 1: clinica.registrarPaciente(); break;
                case 2: clinica.registrarDoctor(); break;
                case 3: clinica.agendarCita(); break;
                case 4: clinica.cancelarCita(); break;
                case 5: clinica.listarCitasPaciente(); break;
                case 6: clinica.listarCitasDoctor(); break;
                case 7: Reporte::generarPorEspecialidad(clinica); break;
                case 8: cout << "¡Gracias por usar el sistema!" << endl; break;
            }
            
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "Error inesperado: " << e.what() << endl;
        }
        
    } while (opcion != 8);
    
    return 0;
}