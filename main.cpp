//Programa  que almacena los datos de un archivo de bitácora en una tabla hash, cuya llave es el dominio y el valor un resumen de ese dominio.  El tamaño de la tabla es de 32749.El main contiene un método que dado un nombre de un dominio regrese el valor asociado a él desplegando la información de una manera adecuada

//Sahid Emmanuel Rosas Maas A01734211
//David Zárate López A01329785
//Karen Rugerio Armmenta A01733228
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"

using namespace std;

/*
La funcion getKey() recibe un string y devuelve un int. Es la función hash de la hash table, y
realiza una serie de divisiones y multiplicaciones, y un mod para obtener la llave hash.
Complejidad: O(n)
*/
int getKey(string redString){
  int asciiValue=0;
  for(int i=0;i<redString.size();i++){
    if(redString[i]!='.'){
      asciiValue+=((redString[i])/redString[i])*redString[i]*20;
    }
  }
  asciiValue*=100;
  return asciiValue%32749;
}

//Funcion insert, para poder insertar una nueva red dentro de la Hashtable
//Complejidad: O(1), ya que no contiene ciclos for
void insert(HashTable &table, string red, string host, int ihost1, int ihost2){
  int key;
  string ip;
  ip = red + "." + host;
  key = getKey(red);
  Registro Reg(red,ip,ihost1,ihost2);
  table.insertar(Reg,key,ip,ihost1,ihost2);
}

//Funcion search, para poder buscar una red dentro de la Hashtable
//Complejidad: O(1), ya que no contiene ciclos for
void search(HashTable &table, string red){
  int key;
  key = getKey(red);
  table.search(key, red);
}

//Funcion print, para poder desplegar la Hashtable
//Complejidad: O(1), ya que no contiene ciclos for
void print(HashTable table){
  table.printTable();
}


int main() {
  HashTable table;
  string name = "bitacora2.txt";
  string word,mes,dia,hora,ip,razon,mensaje,red,host;
  int ired1,ired2,ihost1,ihost2,n;
  string input;
  fstream file;
  bool hostb = false;
  int point = 0;
  file.open(name.c_str());
  //Se leen los datos del archivo
  while (file >> word){
      mes=word;
      file>>word;
      dia=word;
      file>>word;
      hora=word;
      file>>word;
      ip=word;
      getline(file,razon);
      //Se divide la IP en Red y Host
      for(int i = 0; ip[i] != ':'; i++){
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
      ired1 = stoi(red);
      red.erase(0,4);
      ired2 = stoi(red);
      ihost1 = stoi(host);
      host.erase(0,4);
      ihost2 = stoi(host);
      red = to_string(ired1) + "." + to_string(ired2);
      host = to_string(ihost1) + "." + to_string(ihost2);
      insert(table,red,host,ihost1,ihost2);
      red.erase();
      host.erase();
      point = 0;
      hostb = false;
    }
    cin>>n;
    while(n > 0){
      cin>>input;
      search(table,input);
      n--;
    }
  return 0;
}
