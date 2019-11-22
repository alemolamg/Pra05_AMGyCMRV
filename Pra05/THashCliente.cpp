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

unsigned long hash1(int intento){
    
}