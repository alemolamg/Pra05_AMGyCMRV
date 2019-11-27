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

unsigned long borrar1000Clientes(EcoCityMoto& eco){
    vector<string> vecDNI = eco.getVecDNICli();
    unsigned long paso=0, tam=eco.getVecDNICli().size(),borralos=1000;
    for(int i=0;i<borralos;i++){
        paso=tam-i;
        Cliente *cli= eco.buscarCliente(vecDNI[paso]);
        //bool borrado =eco.eliminarCliente(cli.GetDni();
        if (eco.eliminarCliente(cli->GetDni()))//ToDo:Cambiar por la linea de arriba
           cout << "Borrando cliente: " << cli->GetDni() << endl; 
        else
            cout<<"Error al borrar cliente num: "<<paso;
    }
    return paso;    
}

int main(){    
    unsigned long primo,numero=10000;
    /*primo=calPrimoCercanoMayor(numero);
    std::cout<<"el primo es: "<<primo<<std::endl;*/
    
    
    setlocale(LC_ALL,"es_ES.UTF8"); 
    srand(time(0));
     try{ 
        //0)creamos estructura y se cargan clientes y motos dentro
        cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;   
        EcoCityMoto eco("clientes_v2.csv","motos.txt",numero); 
        //EcoCityMoto eco("clientes_v5.csv","motos2.txt",numero); 
        //EcoCityMoto eco("prueba.txt","motos2.txt",numero);  
    
        //1) Añadir a la empresa un nuevo cliente que no exista previamente
        Cliente cliente("51617459W", "Pepito Hernandez" , "passph", "Universidad", 37.5, 3.5, &eco);
        
        //2) Localizar el cliente anterior en la empresa por su DNI y buscar una moto cercana
        if (!eco.nuevoCliente(cliente))
            throw invalid_argument("Cliente NO insertado: el cliente ya existe");
        
        Cliente *cliente1=eco.buscarCliente(cliente.GetDni());
             std::cout << "Cliente: " << cliente1->GetDni() << " Situado en: " << 
                    cliente1->getPosicion().GetLatitud() << "," <<
                    cliente1->getPosicion().GetLongitud() << std::endl;
             Moto *m=cliente1->buscarMotoCercana();
             std::cout << "Moto mas cercana: " << m->getId() << " situada en: " <<
                   m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;

        //3) Realizar un itinerario con la moto localizada
             std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
             cliente1->desbloquearMoto(m);
             
             std::cout << "Desbloqueamos la Moto: " << m->getId() << std::endl;
             cliente1->terminarTrayecto();
             std::cout << "Fin de la Ruta: " << cliente1->UltimoItinerario().GetFecha().cadena() <<
                     ", Minutos: " << cliente1->UltimoItinerario().GetMinutos() <<
                     ", Id: " << cliente1->UltimoItinerario().GetVehiculo()->getId() <<
                     ", Pos Fin: " << cliente1->UltimoItinerario().GetFin().GetLatitud() << "<-->" <<
                     cliente1->UltimoItinerario().GetFin().GetLongitud() << std::endl;

             
             //4) Localizar las motos sin batería e indicar si la moto utilizada está en esa situación.
             /*vector<Moto> v=eco.localizaMotosSinBateria();             
             vector<Moto>::iterator itMoto=v.begin();
             while (itMoto!=v.end()){
                 if ((itMoto)->getId()==m->getId()){
                     cout << "la moto Utilizada quedo sin bateria"<<endl;
                     break;
                 }
                 itMoto++;
             }*/
         
             //5) Borrar el cliente que se insertó en el punto 1 
             
             unsigned long nuevoTam= borrar1000Clientes(eco);
             eco.redispersarClientes(nuevoTam);
             
             
            //if (eco.eliminarCliente(cliente.GetDni()))                 
            //Cliente* cliente2=eco.buscarCliente(cliente.GetDni()); //comprobación
            
    
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
