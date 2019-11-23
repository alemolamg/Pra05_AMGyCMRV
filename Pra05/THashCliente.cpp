/* 
 * File:   THashCliente.cpp
 * Author: molej
 * 
 * Created on 19 de noviembre de 2019, 11:43
 */

#include <queue>
#include "Cliente.h"
#include "THashCliente.h"

THashCliente::THashCliente(unsigned long tamTabla):
    tamFisico(tamTabla),tamLogico(0),totalColisiones(0),
    maxCol(0),tabla(tamTabla,Entrada()){
    primo=calcPrimo(tamFisico);
}

THashCliente::THashCliente(const THashCliente& orig):
    tamFisico(orig.tamFisico), tamLogico(orig.tamLogico),totalColisiones(orig.totalColisiones),
    maxCol(orig.maxCol), tabla(orig.tamFisico,Entrada()){
    primo=calcPrimo(tamFisico);
}

THashCliente::~THashCliente() {
}

unsigned long THashCliente::calcPrimo(unsigned long& tam) {
    unsigned long elPrimo; 
    elPrimo=tam+1;
    bool encontrado=false;
    do{
        bool wanda=esprimo(elPrimo);
        if(wanda){
            if(tam/elPrimo>=0.60)
                encontrado=true;
            else
                if(tam/elPrimo>=0.70)
                    --elPrimo;
                else
                    ++elPrimo;
        }           
    }while(!encontrado);
    return elPrimo;
}

bool THashCliente::esprimo(unsigned long& num) {
        for (unsigned i = 2; i <= num/2; i++)
            if (num % i == 0)
                return false;
        return true;
}

unsigned int THashCliente::numClientes(){
    return tamFisico;
}

unsigned int THashCliente::maxColisiones(){
    return maxCol;
}

unsigned long THashCliente::hash1(unsigned long& clave, int intento) {
    unsigned long hashGen,nuevoPrimo=calcPrimoMenor(primo);
    
    hashGen=(clave)+ (intento*(clave%nuevoPrimo));
    return hashGen;
}

unsigned long THashCliente::calcPrimoMenor(unsigned long& primer) {
    unsigned long elPrimo; 
    elPrimo=primer+1;
    bool encontrado=false;
    do{
        bool wanda=esprimo(elPrimo);
        if(wanda)
            encontrado=true;
        else
            --elPrimo;                  
    }while(!encontrado);
    return elPrimo;
}

bool THashCliente::insertar(const std::string& dni, Cliente *cli) {
    unsigned int intento=0,y=0;
    
    bool encontrado=false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());
    
    while (!encontrado) {
            y=hash1(clave,intento);           
            if (tabla[y].marca==VACIA || tabla[y].marca==DISPONIBLE) {                
                tamLogico++;
                tabla[y].dni=dni;
                tabla[y].marca=OCUPADA;
                tabla[y].clave=clave;                             
                tabla[y].cliDatos=cli;  //push_back(dato);                                                
                encontrado = true;   //Encontre un sitio libre  
            }else               
                ++intento;   //No he dado aun con una posicion libre
        }
    
    totalColisiones+=intento;
    if(intento>maxCol)
        maxCol=intento;
    return encontrado;
    
}

bool THashCliente::buscar(string& dni, Cliente*& cli) {
    bool encontrado=false;
    
}