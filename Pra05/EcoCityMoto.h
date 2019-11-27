/* File:   EcoCityMoto.h
 * Author: Alemol
 * Created on 28 de octubre de 2019, 11:38
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "THashCliente.h"
#include <vector>
#include "Moto.h"
#include "Cliente.h"

using namespace std;

class EcoCityMoto {
private:
    unsigned idUltimo;
    vector <Moto> motos;
    THashCliente clientes;
    vector<string> dniClientes;
    
    //---FUNCIONES----------//
    void cargarMotos(string fileNameMotos);
    void cargarClientes(const string &fileNameClientes);
    void crearItinerarios(int num,const UTM &min,const UTM &max);
    void guardarClientesItinerarios(const string &fileName);   
//    THashCliente& getClientes();
    //bool nuevoCliente(Cliente& nuevoCli);
    

    
public:
    EcoCityMoto(const string &fileClientes,const string &fileMotos,unsigned long tamTabla );
    EcoCityMoto(const EcoCityMoto& orig);
    
    unsigned GetIdUltimo() const;
    void SetIdUltimo(unsigned nuevoIdUltimo);
    
    vector<Moto*> localizaMotosSinBateria();
    Moto* LocMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);   
    
    bool nuevoCliente(Cliente& nuevoCli);
    Cliente* buscarCliente(string dni);

    vector<Moto>& getMotos();
    bool eliminarCliente(std::string borrameid);
    bool proPracticaClientes();
    vector<string> getVecDNICli();
    void redispersarClientes(unsigned long tamTablaNuevo);
    
    virtual ~EcoCityMoto();
          
};

#endif /* ECOCITYMOTO_H */