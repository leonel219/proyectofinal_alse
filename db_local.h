#include "medicion.h"
#include <string>

using namespace std;

class DB_Local{

public:
  DB_Local( string url );
  bool Abrir_DB();
  bool Ingresar( const Medicion &med );
  bool Recuperar( Medicion &prom );
  bool Cerar_DB();




};
