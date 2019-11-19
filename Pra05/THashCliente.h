/* 
 * File:   THashCliente.h
 * Author: molej
 * Created on 19 de noviembre de 2019, 11:43
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H
#include <vector>
#include <set>
#include <string>

#include "Cliente.h"

//#define limite 20

enum EstadoCaja {VACIA,OCUPADA,DISPONIBLE};

//clave para dispersion de cadenas
inline unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
        return hash;
    }


class THashCliente {
private:
    class Entrada{
    public:
        unsigned long clave;
        std::string dni;
        EstadoCaja marca;
        Cliente dato;
        Entrada(): marca(VACIA),clave(0),dni(""),dato(Cliente()){}
        ~Entrada(){}
    };
    
    unsigned long tamFisico;
    unsigned long tamLogico;
    unsigned long totalColisiones;
    unsigned long maxColisiones;
    unsigned long primo;//ToDo: preguntar si funciona 
    std::vector<Entrada> tabla;
    
public:
    THashCliente();
    THashCliente(const THashCliente& orig);
    virtual ~THashCliente();


};

#endif /* THASHCLIENTE_H */

