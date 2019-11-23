/* 
 * File:   THashCliente.h
 * Author: Alemol
 * Created on 19 de noviembre de 2019, 11:43
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include "Cliente.h"
//#include "EcoCityMoto.h"
#include <vector>
#include <set>
#include <string>
#include <iostream>


//#define limite 20

enum EstadoCaja {VACIA,OCUPADA,DISPONIBLE};

//class Cliente;

class THashCliente {
private:
    //friend class Entrada;
    class Entrada{
        friend class Cliente;
    public:
        unsigned long clave;
        std::string dni;
        EstadoCaja marca;
        Cliente* cliDatos;
        Entrada(): marca(VACIA),clave(0),dni(""),cliDatos(0){}
        //Entrada(): marca(VACIA),clave(0),dni(""){};
        ~Entrada(){};
    };
    
    unsigned long tamFisico;
    unsigned long tamLogico;
    unsigned long totalColisiones;
    unsigned long maxCol;
    unsigned long primo;// Primo usado para la tabla=tam
    std::vector<Entrada> tabla;
    
    //--------Funciones--------//
    unsigned long calcPrimo(unsigned long& tam);
    unsigned long calcPrimoMenor(unsigned long& primer);
    unsigned long hash1(unsigned long& clave, int intento); 
    unsigned long hash2(unsigned long& clave, int intento);
    
    
public:
    bool esprimo(unsigned long& n);
    
    inline unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
        return hash;
    }
    //-----Funciones--THash--------//
    THashCliente(unsigned long tamTabla=1);
    virtual ~THashCliente();
    
    unsigned int numClientes();
    
    
    //---Funciones-Extra----//
    unsigned int maxColisiones();
    
    //-----Sin-Implementar---------//
    
    THashCliente(const THashCliente& orig); //ToDo: preguntar organización
       
    bool insertar(const std::string& dni,Cliente& cli);
    bool buscar (string &dni, Cliente* &cli);
    void redispersar (unsigned tamaNuevo);
    
    //---Funciones-Extra----//
    unsigned int promedioColisiones();
    float factorCarga();
    unsigned int tamaTabla();    

};


#endif /* THASHCLIENTE_H */