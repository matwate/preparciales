/*
La empresa Distribuidora Carruti se dedica a comercializar todos tipo de bienes importados. Cuenta con una flota de camiones para llevar sus productos. La empresa quiere contar con un sistema para confirmar que un camión sí pasó los puntos de entrega de mercancía, y necesita que ustedes diseñen tal funcionalidad.
Deben diseñar las siguientes clases en su programa:
-	Una clase Punto, que tiene como atributos latitud y longitud, y debe ser capaz de calcular la distancia entre el punto que invoca y un punto que recibe por parámetro. Además, debe tener un método que retorne el cuadrante en que se encuentra el punto: 
-	
2	1
3	4

-	Una clase Ruta que contiene una secuencia de puntos que muestran el recorrido de un vehículo. Esta clase debe ser capaz de:
o	Calcular la longitud total de la ruta
o	Dado un punto por parámetro, verificar si el camino pasa cerca del punto. Se debe recibir también por parámetro una distancia máxima de tolerancia para asumir que un punto está en un camino o no. 
Un objeto de esta clase se inicializa en el método constructor, recibiendo una cadena con el nombre del archivo que contiene la información que contiene los puntos. En este método de debe leer y cargar los datos en un arreglo de objetos tipo Punto. Tenga en cuenta que el vector de puntos es de tamaño 100.
	Ejemplo: Punto puntos[100]
	Implemente también un método para obtener el i-ésimo elemento del vector (get(int i))
-	Una clase Camión que tiene como atributos dos objetos de la clase Ruta. En su método constructor, recibe 2 cadenas con los nombres de los archivos para cada ruta: la ruta que siguió y la que contiene los puntos por donde debía pasar. Para la primera, use la cadena “carruti.csv” y la segunda “carruti2.csv”. Esta clase debe tener un método que, a partir de las dos clases Ruta, muestre por pantalla y guarde en un archivo “out.txt” los puntos por donde el camión no pasó o, si en efecto cumplió con todos los puntos, que escriba al final del archivo “Recorrido exitoso”. Además, escriba en la primera línea del archivo, los nombres del equipo de estudiantes.  
*/


#include <iostream> // Biblioteca para entrada/salida de datos
#include <vector> // Biblioteca para manejar vectores
#include <math.h> // Biblioteca para operaciones matemáticas
#include <fstream> // Biblioteca para manejar archivos
#include <string> // Biblioteca para manejar cadenas de texto

using namespace std; // Espacio de nombres estándar de C++


// Función para dividir una cadena en subcadenas (tokens) según un delimitador
vector<string> tokenize(string str, char del){
    vector<string> tokens; // Vector para almacenar los tokens
    string token; // Variable para almacenar el token actual
    for (int i = 0; i < str.size(); i++) // Recorremos la cadena
    {
        if (str[i] == del) // Si encontramos el delimitador
        {
            tokens.push_back(token); // Añadimos el token al vector
            token = ""; // Reseteamos el token
        }
        else
        {
            token += str[i]; // Si no es delimitador, añadimos el carácter al token
        }
    }
    tokens.push_back(token); // Añadimos el último token
    return tokens; // Devolvemos los tokens
}

// Clase para representar un punto con latitud y longitud
class Point{
    private:
        double lat; // Latitud
        double lon; // Longitud
    public:
        // Constructor que inicializa la latitud y longitud
        Point(double lat, double lon){
            this->lat = lat;
            this->lon = lon;
        }
        // Método para obtener la latitud
        double Lat(){
            return this-> lat;
        }
        // Método para obtener la longitud
        double Lon(){
            return this-> lon;
        }
        // Método para calcular la distancia a otro punto
        double Dist(Point other){
            return sqrt(pow(this->lat - other.Lat(), 2) + pow(this->lon - other.Lon(), 2));
        }
        // Método para determinar el cuadrante del punto
        double Quad(){
            double x = this->lat;
            double y = this->lon;
            // Devuelve 1 si el punto está en el primer cuadrante, 2 si está en el segundo, etc.
            return 1 ? (x > 0) && (y > 0) : 2 ? (x < 0) && (y > 0) : 3 ? (x < 0) && (y < 0) : 4;
        }
};

// Clase para representar una ruta compuesta por varios puntos
class Route{
    private:
        vector<Point> points; // Vector de puntos
    public:
        // Método para obtener los puntos
        vector<Point> Points(){
            return this->points;
        }
        // Método para obtener la longitud de la ruta (número de puntos)
        int Len(){
            return this->points.size();
        }
        // Método para verificar si un punto está cerca de la ruta
        bool Near(Point p, double tolerance){
            for(int i = 0; i < this->points.size(); i++){
                if(this->points[i].Dist(p) < tolerance){
                    return true;
                }
            }
            return false;
        }
        // Constructor por defecto
        Route(){
            this->points = vector<Point>();
        }
        // Constructor que inicializa la ruta a partir de un archivo
        Route(string file){
            ifstream f(file); // Abrimos el archivo
            double lat, lon;

            if (!f.is_open()){ // Si no se pudo abrir el archivo
                cout << "Error al abrir el archivo" << endl;
            }

            string line;
            while(getline(f, line )){ // Leemos cada línea del archivo
                vector<string> data = tokenize(line, ','); // Dividimos la línea en tokens
                lat = stod(data[0]); // Convertimos el primer token a double para la latitud
                lon = stod(data[1]); // Convertimos el segundo token a double para la longitud
                Point p(lat, lon); // Creamos un punto con la latitud y longitud
                this->points.push_back(p); // Añadimos el punto a la ruta
            }
        }
};

// Clase para representar un camión que sigue una ruta
class Truck{
    private:
        Route route1; // Ruta que siguió el camión
        Route route2; // Ruta que debía seguir el camión
    public:
        // Constructor que inicializa las rutas a partir de dos archivos
        Truck(string route1, string route2){
            this->route1 = Route(route1);
            this->route2 = Route(route2);     
        }
        // Método para verificar si el camión pasó por todos los puntos de la ruta
        void DidPassAll(){
            ofstream f("out.txt"); // Abrimos el archivo de salida
            for(int i = 0; i < this->route2.Len(); i++){ // Recorremos todos los puntos de la ruta
                if(!this->route1.Near(this->route2.Points()[i], 0.0001)){ // Si el camión no pasó cerca del punto
                    // Escribimos en el archivo que el camión no pasó por el punto
                    f << "El camion no paso por el punto: " << this->route2.Points()[i].Lat() << ", " << this->route2.Points()[i].Lon() << endl;
                }
            }
        }
};

int main(){
    Truck t("carruti.csv", "carruti2.csv"); // Creamos un camión con las rutas de los archivos
    t.DidPassAll(); // Verificamos si el camión pasó por todos los puntos

    return 0; // Terminamos el programa
}