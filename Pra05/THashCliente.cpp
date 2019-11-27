/* 
 * File:   THashCliente.cpp
 * Author: Alemol 
 * Created on 19 de noviembre de 2019, 11:43
 */

#include <queue>
#include <limits>
#include "Cliente.h"
#include "THashCliente.h"

THashCliente::THashCliente(unsigned long tamTabla):
    tamFisico(THashCliente::calcPrimo(tamTabla)),tamLogico(0),totalColisiones(0),
    //tamFisico(tamTabla),tamLogico(0),totalColisiones(0),
    maxCol(0),tabla(tamFisico,Entrada()){
    //maxCol(0),tabla(tamTabla,Entrada()){
    //tamFisico=THashCliente::calcPrimo(tamTabla);
    primo=calcPrimo(tamTabla);
    
    
}

THashCliente::THashCliente(const THashCliente& orig):
    tamFisico(orig.tamFisico), tamLogico(orig.tamLogico),totalColisiones(orig.totalColisiones),
    maxCol(orig.maxCol),primo(orig.primo) ,tabla(orig.tabla){}

THashCliente::~THashCliente() {
}

unsigned long THashCliente::calcPrimo(unsigned long& tam) {
    unsigned long elPrimo=tam+1;
    bool encontrado=false;
    do{
        ++elPrimo;
        bool wanda=esprimo(elPrimo);
        if(wanda){
            float comparo =(float) tam/elPrimo ;
            if(comparo>=0.60 && comparo<=0.70){
                encontrado=true;
                //return elPrimo;
            }    
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
    return tamLogico;
}

unsigned int THashCliente::maxColisiones(){
    return maxCol;
}

unsigned long THashCliente::hash1(unsigned long& clave, int intento) {
    int fun=1;
     unsigned long hashGen;//,nuevoPrimo=calcPrimoMenor(primo);
    switch(fun){
        case 0:
            hashGen=(clave)+ (intento*(clave%primo));
            return hashGen;
            break;
        case 1:
            hashGen= (clave+(intento*intento)) % tamFisico;
            break;
        case 2:
            unsigned long modulo = clave % tamFisico;   // mejor FUNCION DE DISPERSION        
            hashGen = (modulo + (intento* (primo-(clave % (primo))))) % tamFisico;
            break;
    }
    return hashGen;
    
    //hashGen=(clave)+ (intento*(clave%nuevoPrimo));
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

bool THashCliente::insertar(const std::string& dni, Cliente &cli) {
    unsigned int intento=0,y=0;
    bool encontrado=false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());
    
    while (!encontrado /*&& intento<20*/) {
        
            y=hash1(clave,intento); 
            //std::cout<<"calculada posición: "<<y<<std::endl;
        
            if (tabla[y].marca==VACIA || tabla[y].marca==DISPONIBLE) {                
                tamLogico++;
                this->tabla[y].dni=dni;
                this->tabla[y].clave=clave;                             
                this->tabla[y].cliDatos=cli;  //push_back(dato);                                                
                this->tabla[y].marca=OCUPADA;
                encontrado = true;   //Encontre un sitio libre  
            }else               
                ++intento;   //No he dado aun con una posicion libre
        }
    
    totalColisiones= totalColisiones+intento;
    if(intento>maxCol)
        maxCol=intento;
    return encontrado;
}

bool THashCliente::buscar(string& dni, Cliente* &cli) {
    bool encontrado=false;
    unsigned long intento=0;
    unsigned long y=0, clave = djb2((unsigned char*)dni.c_str());
    
    while (!encontrado){
        y=hash1(clave,intento);
        
        if(tabla[y].marca==VACIA || tabla[y].marca==DISPONIBLE){
            cli=nullptr;
            return encontrado;
        }else                
            if(tabla[y].marca==OCUPADA && tabla[y].dni==dni){
                cli=&(tabla[y].cliDatos);
                encontrado=true;
            }else
                ++intento;
    }
    return encontrado;   
}

float THashCliente::promedioColisiones() {
    return (float) totalColisiones/tamLogico;
    //return totalCol;
}

float THashCliente::factorCarga() {
    return (float) tamLogico/tamFisico;
}

void THashCliente::redispersar() {
    
    tamFisico=calcPrimo(tamLogico);
    primo=tamFisico;
    vector<Entrada> nueva(tamFisico,Entrada());
    unsigned long numClientes=0;
    
    for (int i=0; i<tabla.size(); i++){       
        bool encontrado = false;
        unsigned posNueva=0, intento=0;
        
        if (tabla[i].marca==OCUPADA){
            unsigned long clave=djb2((unsigned char*)tabla[i].dni.c_str());
            
            while (!encontrado && intento<15) {
            posNueva=hash1(clave,intento);           
            if (nueva[posNueva].marca==VACIA || nueva[posNueva].marca==DISPONIBLE) {
                nueva[posNueva].dni=tabla[i].dni;
                nueva[posNueva].clave=clave;
                nueva[posNueva].cliDatos=tabla[i].cliDatos;
                nueva[posNueva].marca=OCUPADA;
                numClientes++;
                encontrado = true;    
            }else               
                ++intento;   
        }
    
    totalColisiones+=intento;
    if(intento>maxCol)
        maxCol=intento;    
        }
    }
    tabla=nueva;
    tamLogico=numClientes;
    cout<<"Nueva tabla terminada"<<endl;
}

unsigned int THashCliente::tamaTabla() {
    return tamFisico;
}

vector<string> THashCliente::getVectorDNI() {
    vector<string> vecDNI;
    int pos=0, i=0;
    bool acabado=false;
    Cliente *cli;
    
    //while (i<tabla.size()){
    while (i<tamFisico){
        
        if(tabla[i].marca==VACIA || tabla[i].marca==DISPONIBLE){
            cli=nullptr;
        }else                
            if(tabla[i].marca==OCUPADA ){
                cli=&(tabla[i].cliDatos);
                acabado=true;
            }
        if(cli){
            vecDNI.push_back(cli->GetDni());
            ++pos;
        }
        ++i;
    }
    return vecDNI;
}

void THashCliente::setTamLogico(unsigned long tamLogico) {
    this->tamLogico = tamLogico;
}

bool THashCliente::borrar(std::string& dni) {
    unsigned long clave=djb2((unsigned char*)dni.c_str());
    Cliente *cli;
    bool existe=buscar(dni,cli);
    unsigned long y=0,intento=0;
    
    while(existe){
        unsigned long y=hash1(clave,intento);
        
        if(tabla[y].marca==VACIA || tabla[y].marca==DISPONIBLE){// No deberia entrar
            cli=nullptr;
        }else                
            if(tabla[y].marca==OCUPADA && tabla[y].dni==dni){
                cli=&(tabla[y].cliDatos);
                tabla[y].marca=DISPONIBLE;
                existe=false;
            }else
                ++intento;
    }
    //return !existe;
    //lo siente es para comprobar que funciona
    existe=buscar(dni,cli);
    if (existe)
        throw invalid_argument ("THashCliente::borrar: no borrado correctamente");
    else
        return true;
}

