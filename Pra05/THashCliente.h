/* 
 * File:   THashCliente.h
 * Author: Alemol
 * Created on 19 de noviembre de 2019, 11:43
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "Cliente.h"

//#define limite 20

enum EstadoCaja {VACIA,OCUPADA,DISPONIBLE};

//clave para dispersion de cadenas



class THashCliente {
private:
    class Entrada{
    public:
        unsigned long clave;
        std::string dni;
        EstadoCaja marca;
        //Cliente dato;
        //Entrada(): marca(VACIA),clave(0),dni(""),dato(Cliente()){}
        ~Entrada(){}
    };
    
    unsigned long tamFisico;
    unsigned long tamLogico;
    unsigned long totalColisiones;
    unsigned long maxColisiones;
    unsigned long primo;//ToDo: preguntar si funciona 
    std::vector<Entrada> tabla;
    
    //--------Funciones--------//
    unsigned long calcPrimo(unsigned long tam);
    
    
public:
    bool esprimo(unsigned long n);
    
    inline unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
        return hash;
    }
    //-----Funciones--THash--------//
    
    
    
    //-----Sin-Implementar---------//
    THashCliente();
    THashCliente(unsigned long tamTabla=1);
    THashCliente(const THashCliente& orig);
    virtual ~THashCliente();
    
    unsigned long hash1(int intento); 
    unsigned long hash2(int intento);
    bool insertar(const std::string& dni,Cliente& cli);
    bool buscar (string &dni, Cliente* &cli);
    unsigned int numClientes();
    void redispersar (unsigned tamaNuevo);
    
    //---Funciones-Extra----//
    unsigned int calMaxColisiones();
    unsigned int promedioColisiones();
    float factorCarga();
    unsigned int tamaTabla();    

};


#endif /* THASHCLIENTE_H */