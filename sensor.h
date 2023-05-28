#ifndef SENSOR_H
#define SENSOR_H

#include "conteomedidas.h"

class Sensor{
private:
    float temperatura;
    float humedad;
    float precipitacion;
    float intensidadLuz;
public:
  bool actualizar(conteomedidas);


};

#endif
