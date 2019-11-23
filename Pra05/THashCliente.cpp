/* 
 * File:   THashCliente.cpp
 * Author: molej
 * 
 * Created on 19 de noviembre de 2019, 11:43
 */

#include <queue>

#include "THashCliente.h"

THashCliente::THashCliente(unsigned long tamTabla):
    tamFisico(tamTabla),tamLogico(0),totalColisiones(0),
    maxColisiones(0),tabla(tamTabla,Entrada()){
    primo=calcPrimo(tamFisico);
}

THashCliente::THashCliente(const THashCliente& orig) {
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
                ++elPrimo;
        }              
    }while(!encontrado);
    return elPrimo;
}

bool THashCliente::esprimo(unsigned long& n) {
        for (unsigned i = 2; i <= n/2; ++i)
            if (n % i == 0)
                return false;
        return true;
    }

THashCliente& EcoCityMoto::getClientes() {
    return clientes ;
};


