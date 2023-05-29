#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "db_local.h"
#include "db_local.cpp"
#include "sensor.h"
#include "conteomedidas.h"
#include "conteomedidas.cpp"
// Función para generar una marca de tiempo
std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Uso: ./aplicacion <path_base_datos>" << std::endl;
        return 1;
    }
    
    std::string dbPath = argv[1];
    
    // Apertura de la base de datos
    std::ofstream database(dbPath, std::ios::app);
    
    if (!database) {
        std::cout << "Error al abrir la base de datos." << std::endl;
        return 1;
    }
    
    float temperatura = 0.0f;
    float humedad = 0.0f;
    float precipitacion = 0.0f;
    float intensidadLuz = 0.0f;
    
    // Ciclo principal para realizar las mediciones cada 5 segundos
    while (true) {
        // Simulación de obtención de valores de los sensores
        temperatura = -10.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (45.0f - (-10.0f))));
        humedad = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
        precipitacion = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
        intensidadLuz = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2000.0f));
        
        // Cálculo del promedio cada minuto
        static int conteomedidas = 0;
        static float temperaturaSum = 0.0f;
        static float humedadSum = 0.0f;
        static float precipitacionSum = 0.0f;
        static float intensidadLuzSum = 0.0f;
        
        conteomedidas++;
        temperaturaSum += temperatura;
        humedadSum += humedad;
        precipitacionSum += precipitacion;
        intensidadLuzSum += intensidadLuz;
        
        if (conteomedidas== 12) { // 12 mediciones x 5 segundos = 1 minuto
            float temperaturaprom = temperaturaSum / conteomedidas;
            float humedadprom = humedadSum / conteomedidas;
            float precipitacionprom  = precipitacionSum / conteomedidas;
            float intensidadLuzprom = intensidadLuzSum / conteomedidas;
            
            // Registro de los datos promedio en la base de datos
            database << "Promedio - Temperatura: " << temperaturaprom
                     << " - Humedad: " << humedadprom
                     << " - Precipitación: " << precipitacionprom
                     << " - Intensidad de luz: " << intensidadLuzprom << std::endl;
            
            // Reiniciar los contadores y sumas
            conteomedidas = 0;
            temperaturaSum = 0.0f;
            humedadSum = 0.0f;
            precipitacionSum = 0.0f;
            intensidadLuzSum = 0.0f;
        }
        
        // Registro de la medición en la base de datos
        database << "Medición - Temperatura: " << temperatura
                 << " - Humedad: " << humedad
                 << " - Precipitación: " << precipitacion
                 << " - Intensidad de luz: " << intensidadLuz << std::endl;
        
        // Registro de la fecha y hora de inicio de la ejecución
        if (measurementCount == 1) { // Solo registrar una vez por minuto
            database << "Inicio de ejecución - " << getCurrentTimestamp() << std::endl;
        }
        
        // Esperar 5 segundos antes de la próxima medición

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
    // Cierre de la base de datos
    database.close();
    
    return 0;
}
