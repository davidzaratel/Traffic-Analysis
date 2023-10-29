#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Registro{
  private:
  //atributos de la clase
  string red;
  int accesos;
  int conexiones;
  int host1;
  int host2;
  vector<string> ips;
  bool state;

  public:
  //métodos de la clase
  Registro();
  Registro(string,string,int,int);
  void insertinVector(string,int,int);

  void setState(bool);
  bool getState();

  int getHost1();
  int getHost2();

  void setRed(string);
  string getRed();

  void printVector();
  void increaseAccesos();
  void increaseConexiones();

  int getAccesos();

  int getConexiones();
  void dameNumeros(int&,int&,string);
};

//Constructor de la clase, en caso de no recibir parametros
Registro :: Registro(){
  red = "";
  state = false;
  accesos = 0;
  conexiones = 0;
  host1 = 0;
  host2 = 0;
}

//Constructor de la clase, en caso de recibir parametros
Registro :: Registro(string r, string ip,int h1, int h2){
  red = r;
  accesos = 0;
  conexiones = 0;
  state = false;
  host1 = h1;
  host2 = h2;
}

//Se convierte el host dentro de la IP en numeros enteros
//Complejidad: O(n), ya que contiene ciclo for
void Registro :: dameNumeros(int& h1, int& h2, string ip){
  bool hostb = false;
  string host,red;
  int point = 0;

  for(int i = 0; i < ip.length(); i++){
        if(ip[i] != '.' && !hostb)
          red += ip[i];
        if(ip[i] == '.' && point < 2 && !hostb){
          if(point < 1){
            red += '.';
          }
          point++;
        }
        if(ip[i] != '.' && hostb)
          host += ip[i];
        if(ip[i] == '.' && point < 2 && hostb){
          if(point < 1)
            host += '.';
          point++;
        }
        if(point == 2){
          hostb = true;
          point = 0;
        }
  }
  point = 0;
  h1 = stoi(host);

  int j = 0;
  for(int i = 0; point < 1;i++){
    if(host[j] != '.')
      host.erase(0,1);
    else if(host[j] == '.'){
      point++;
      host.erase(0,1);
    }
  }

  h2 = stoi(host);
}

//Inserta las IPs dentro del vector cuando se tiene una coincidencia en las redes
//Complejidad: O(n), ya que tiene 1 ciclo for
void Registro:: insertinVector(string ip, int ihost1, int ihost2){
  int h1=0;
  int h2=0;
  bool menor = false;
  string aux;

  if(getConexiones()== 0){
    ips.push_back(ip);
    increaseConexiones();
  }
  else{
    for(int i = 0; i < ips.size(); i++ ){
      dameNumeros(h1,h2,ips[i]);
       if(ips[i] == ip){
          i = ips.size();
          return;
       }
       if(!menor){
        if(ihost1 < h1)
          menor = true;
        if(ihost1 == h1 && ihost2 < h2)
          menor = true;
       }
       if(menor){
        aux = ips[i];
        ips[i] = ip;
        ip = aux;
       }
    }
      ips.push_back(ip);
      increaseConexiones();
  }
}

void Registro:: setState(bool stateS){
  state = stateS;
}

//Se obtiene el estado del registro
bool Registro:: getState(){
  return state;
}

//Se establece la red
void Registro:: setRed(string redS){
  red = redS;
}

//Se obtiene la red
string Registro:: getRed(){
  return red;
}

//Función print: Imprime el vector
//Complejidad O(n), ya que incluye un ciclo for
void Registro:: printVector(){
  for(int i = 0; i < ips.size(); i++)
    cout<<ips[i]<<endl;
}

//Se obtiene el número de accesos
int Registro::getAccesos(){
  return accesos;
}

//Se obtiene el número de conexiones
int Registro::getConexiones(){
  return conexiones;
}

//Incrementa los accesos
void Registro:: increaseAccesos(){
  accesos++;
}

//Incrementa las conexiones
void Registro:: increaseConexiones(){
  conexiones++;
}

//Se obtiene la primera parte de host
int Registro:: getHost1(){
  return host1;
}
//Se obtiene la segunda parte de host
int Registro:: getHost2(){
  return host2;
}

#endif
