"""
Clase Coche para gestion de coches:
COntexto: imagina que estas desarrollando un sistema de gestion de flotas de vehiculos para una empresa de transporte: Necesitas una clase para representar cada coche en la flota
Implementa un constructor que inicialice todos los atributos del coche, como la matricula, marca, kilometros recorridos,y cantidad de gasolina
Asegurate de que el metodo avanzar() reste correctamente la cantidad de gasolina segun los kilometros recorridos
En el metodo repostar(), maneja adecuadamente la adicion de gasolina a la cantidad existente
Controla que la gasolina nunca sea negativa y muestra un mensaje si se intenta avanzar sin gasolina suficiente.

"""


class Coche:
    
    def __init__(self, matricula, marca, km, gasolina):
        self.matricula = matricula
        self.marca = marca
        self.km = km
        self.gasolina = gasolina
        self.galones_por_km = 0.1
        
    def avanzar(self, kms):
        if kms * self.galones_por_km > self.gasolina:
            print("No hay suficiente gasolina para recorrer esa distancia")
        else:
            self.km += kms
            self.gasolina -= kms * self.galones_por_km
            
    def repostar(self, amount):
        self.gasolina += amount
        print(f"Se han añadido {amount} galones de gasolina. La cantidad actual es de {self.gasolina} galones")