#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Cliente.h"
#include "Moto.h"
#include "EcoCityMoto.h"


bool numEsPrimo(unsigned long& num) {
        for (unsigned i = 2; i <= num/2; i++)
            if (num % i == 0)
                return false;
        return true;
}

unsigned long calPrimoCercanoMayor (unsigned long num){
    
        unsigned long elPrimo=num;
    
        bool encontrado=false;
        do{
            ++elPrimo;
            bool wanda=numEsPrimo(elPrimo);
            if(wanda){
                float comparo =(float) num/elPrimo ;
                if(comparo>=0.60 && comparo<=0.66 )
                 encontrado=true;
                /*else
                    if(comparo>=0.70)
                        --elPrimo;*/     
            }   
            
        }while(!encontrado);
        return elPrimo;
}



int main(){    
    unsigned long primo,numero=10000;
        
    setlocale(LC_ALL,"es_ES.UTF8"); 
    srand(time(0));
    try{ 
         int modo=0; // modo=1-> entrenar; modo=0-> ejecutar normal;
         
         if(modo==1){
             EcoCityMoto ecoEntrena("clientes_v2.csv","motos.txt",numero);
             
             
             int tam[]={16890,16230};
             
             for(int i=0;i<2;i++){
                 for(int j=0;j<3;j++){
                     
                 }
             }
             
             
         }else{
            cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;   
            EcoCityMoto eco("clientes_v2.csv","motos.txt",numero); 
            //EcoCityMoto eco("clientes_v5.csv","motos2.txt",numero); 
            //EcoCityMoto eco("prueba.txt","motos2.txt",numero);
            
            //1) Añadir un nuevo cliente, rango (latitud, longitud): (37, 3) - (38, 4) 
            std::string dniCli="50617459W";
            Cliente clienteA("50617459W", "Alejandro Molero" , "antirrobo", "Universidad", 37.3, 38.4, &eco);
            eco.nuevoCliente(clienteA);
            
            //4) Buscar el cliente creado
            Cliente *pCli= eco.buscarCliente(dniCli);
            
            
            std::cout << "\nCliente: " << pCli->GetDni() << " Situado en: " << 
                    pCli->getPosicion().GetLatitud() << "," <<
                    pCli->getPosicion().GetLongitud() << std::endl;
            
            //5) Localizar la moto cercana
            //Moto* motoCerCli = eco.LocMotoCercana(pCli->getPosicion());
            Moto* motoCerCli =pCli->buscarMotoCercana(); 
            std::cout << "Moto mas cercana: " << motoCerCli->getId() << " situada en: " <<
            motoCerCli->getPosicion().GetLatitud() << "," << motoCerCli->getPosicion().GetLongitud() << std::endl;
            
            //6)Realizar un itinerario con la moto localizada con duración válida para la carga de batería de la moto
            std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
            motoCerCli->darAviso(); //esto es de la parte 7;
            pCli->desbloquearMoto(motoCerCli);
            std::cout << "Desbloqueamos la Moto: " << motoCerCli->getId() << std::endl;
            pCli->terminarTrayecto();
            std::cout << "Fin de la Ruta: " << pCli->UltimoItinerario().GetFecha().cadena() <<
                    ", Minutos: " << pCli->UltimoItinerario().GetMinutos() <<
                    ", Id: " << pCli->UltimoItinerario().GetVehiculo()->getId() <<
                    ", Pos Fin: " << pCli->UltimoItinerario().GetFin().GetLatitud() << "<-->" <<
                    pCli->UltimoItinerario().GetFin().GetLongitud() << std::endl;
            
            //7) mostrar en el display estado moto
            motoCerCli->darAviso();
            
            //8) Borrar el cliente
            if(eco.eliminarCliente(clienteA.GetDni()))
                cout<<"Cliente Borrado correctamente"<<std::endl;
            else{
                cout<<"Cliente no borrado"<<std::endl;
                throw invalid_argument ("Main.cpp: parte8:: cliente no borrado");
            }
            //9) insertar el mismo cliente de nuevo
            bool alemol=eco.nuevoCliente(clienteA); 
            if (!alemol)
                cout<<"Cliente no añadido correctamente"<<std::endl;
            
            //10) Eliminar 1000 clientes y redispersar si es necesario
            eco.borraTodosLosClientes(1000); 
            eco.redispersarClientes();
            
            //11) volver a cargar los ficheros como en la practica 4...
            
         }

                
     //Tratamiento de errores
     }catch (ErrorFechaIncorrecta &e){
            std::cerr << "Fecha Incorrecta: " << std::endl;
     }catch (std::runtime_error &e){ //std::ifstream::failure &e){
            std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
     }catch (std::bad_alloc &e){
            std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;     
     }catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
     } 
     
     
    return 0;
    
}
