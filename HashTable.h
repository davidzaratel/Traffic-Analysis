#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include "Registro.h"

using namespace std;

class HashTable{
  //Atributos de la clase
  private:
  Registro table[32749];

  public:
  //Métodos de la clase
  HashTable();
  void insertar(Registro, int,string,int,int);
  void search(int,string);
  void printTable();
};

//Constructor
HashTable:: HashTable(){
  Registro R;
  for(int i = 0; i < 32749; i++)
    table[i] = R;
}


//Funcion insertar, para poder insertar una nueva red dentro de la Hashtable
//Complejidad: mejor de los casos O(1) y peor de los casos O(n), ya que depende de si existen colisiones o no.
void HashTable :: insertar(Registro newRegistro, int key,string ip,int ihost1,int ihost2){
  bool done = false;

  if (table[key].getState() == false){ //si está vacío el lugar sólo se inserta
    table[key] = newRegistro; //se inserta la red en la tabla
    table[key].setState(true); //cambia el estado en la tabla
    table[key].insertinVector(ip,ihost1,ihost2); //se inserta toda la ip en el vector en la red de la tabla
    table[key].increaseAccesos();
    //cout<<table[key].getRed()<<" 1 "<<key <<endl;
    done = true;
  }
  else { //si no está vacío el lugar
    //si son exacatemente igualesl las ips ???
    for(int i = key;i < 32749;i++){
      if(newRegistro.getRed() == table[i].getRed()){ //si la red del registro y la red de la key son iguales
        table[i].insertinVector(ip,ihost1,ihost2); //se inserta toda la ip en el vector en la red de la tabla
        table[i].increaseAccesos();
        //cout<<table[i].getRed()<<" 2 " << i <<endl;
        done = true;
        return;
      }
      else if(table[i].getState() == false){
        table[i]= newRegistro; //se inserta la red en la tabla
        table[i].setState(true); //cambia el estado en la tabla
        table[i].insertinVector(ip,ihost1,ihost2); //se inserta toda la ip en el vector en la red de la tabla
        table[i].increaseAccesos();
        //cout<<table[i].getRed()<<" 3 "<< i <<endl;
        done = true;
        return;
      }
      if(done)
        i = 32749;
    }
    for(int i= 0;i<key;i++){
      if(newRegistro.getRed() == table[i].getRed()){ //si la red del registro y la red de la key son iguales
        table[i].insertinVector(ip,ihost1,ihost2); //se inserta toda la ip en el vector en la red de la tabla
        table[i].increaseAccesos();
        //cout<<table[i].getRed()<<" 4 "<< i <<endl;
        done = true;
        return;
      }
      else if(table[i].getState() == false){
        table[i]= newRegistro; //se inserta la red en la tabla
        table[i].setState(true); //cambia el estado en la tabla
        table[i].insertinVector(ip,ihost1,ihost2); //se inserta toda la ip en el vector en la red de la tabla
        table[i].increaseAccesos();
        //cout<<table[i].getRed()<<" 5 "<< i <<endl;
        done = true;
        return;
      }
    }
  }
  if(!done)
    cout<<"Tabla llena, imposible meter más datos"<<endl;
}

//Funcion search, para poder buscar y desplegar la informacion de una red  dentro de la Hashtable
//Complejidad: mejor de los casos O(1) y peor de los casos O(n), ya que depende de si existen colisiones o no.
void HashTable :: search(int key, string red){
  bool done = false;

  if(table[key].getState() == 1){ //si hay un dato verifico si es el que estoy buscando
    if(table[key].getRed() == red){ //si es igual se imprime
      cout<<table[key].getRed()<<endl;
      cout<<table[key].getAccesos()<<endl;
      cout<<table[key].getConexiones()<<endl;
      table[key].printVector();
      done = true;
      return;
    }
    else{
      for(int i = key; i < 32749 ; i++){ //si no, lo busca desde donde debería estar hasta el final
        if(table[i].getState() == 1 && table[i].getRed() == red){ //si lo encuentra en ese intervalo lo imprime
          cout<<table[i].getRed()<<endl;
          cout<<table[i].getAccesos()<<endl;
          cout<<table[i].getConexiones()<<endl;
          table[i].printVector();
          done = true;
          return;
        }
      }
      for(int i = 0; i < key ; i++){ //si no lo encontró, busca desde el inicio de la tabla
        if(table[i].getState() == 1 && table[i].getRed() == red){
          cout<<table[i].getRed()<<endl;
          cout<<table[i].getAccesos()<<endl;
          cout<<table[i].getConexiones()<<endl;
          table[i].printVector();
          done = true;
          return;
        }
      }
      if(done == false )
        cout<<"dato no encontrado"<<endl;
    }
  }
  else
    cout << "dato no encontrado" << endl;

}

//Funcion print, para poder imprimir la Hashtable
//Complejidad: O(n), ya que contiene un solo ciclo for
void HashTable::printTable(){
  for(int i = 0; i < 32749; i++)
    if(table[i].getState() == true)
      cout<<i<<" "<<table[i].getRed()<<endl;

}
#endif
