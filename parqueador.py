 import time
from datetime import datetime

# Clase para representar un vehículo
class Vehiculo:
    def __init__(self, placa):
        self.placa = placa
        self.hora_entrada = datetime.now()

# Clase para representar el parqueadero
class Parqueadero:
    def __init__(self, filas=8, columnas=8):
        self.filas = filas
        self.columnas = columnas
        self.mapa = [[None for _ in range(columnas)] for _ in range(filas)]
        self.ocupados = {}  # placa -> (vehiculo, (fila, col))
        self.crear_vias_y_entradas()

    def crear_vias_y_entradas(self):
        for i in range(self.filas):
            self.mapa[i][0] = "V"  # vía vertical izquierda
        for j in range(self.columnas):
            self.mapa[0][j] = "V"  # vía horizontal superior
        self.entrada = (0, 0)
        self.salida = (self.filas - 1, self.columnas - 1)

    def mostrar_mapa(self):
        for fila in self.mapa:
            print(" ".join(cell if isinstance(cell, str) else "L" if cell is None else "X" for cell in fila))

    def registrar_vehiculo(self, placa):
        for i in range(1, self.filas):
            for j in range(1, self.columnas):
                if self.mapa[i][j] is None:
                    vehiculo = Vehiculo(placa)
                    self.mapa[i][j] = vehiculo
                    self.ocupados[placa] = (vehiculo, (i, j))
                    print(f"Vehículo con placa {placa} registrado en posición ({i}, {j}).")
                    return
        print("No hay espacios disponibles.")

    def retirar_vehiculo(self, placa):
        if placa not in self.ocupados:
            print("Vehículo no encontrado.")
            return

        vehiculo, (i, j) = self.ocupados[placa]
        self.mapa[i][j] = None
        tiempo = (datetime.now() - vehiculo.hora_entrada).total_seconds() / 60  # en minutos
        tarifa = self.calcular_tarifa(tiempo)
        del self.ocupados[placa]
        print(f"Vehículo con placa {placa} retirado. Tiempo: {tiempo:.2f} min. Total a pagar: ${tarifa:.2f}")

    def calcular_tarifa(self, minutos):
        tarifa_base = 2.0  # tarifa por minuto
        return minutos * tarifa_base

    def mostrar_disponibilidad(self):
        total = (self.filas - 1) * (self.columnas - 1)
        ocupados = len(self.ocupados)
        libres = total - ocupados
        print(f"Espacios totales: {total}, Ocupados: {ocupados}, Libres: {libres}")

# Menú de interacción
if __name__ == "__main__":
    parqueadero = Parqueadero()

    while True:
        print("\n--- Sistema de Parqueadero ---")
        print("1. Ver mapa")
        print("2. Ingresar vehículo")
        print("3. Retirar vehículo")
        print("4. Mostrar disponibilidad")
        print("5. Salir")
        opcion = input("Seleccione una opción: ")

        if opcion == "1":
            parqueadero.mostrar_mapa()
        elif opcion == "2":
            placa = input("Ingrese la placa del vehículo: ")
            parqueadero.registrar_vehiculo(placa)
        elif opcion == "3":
            placa = input("Ingrese la placa del vehículo: ")
            parqueadero.retirar_vehiculo(placa)
        elif opcion == "4":
            parqueadero.mostrar_disponibilidad()
        elif opcion == "5":
            break
        else:
            print("Opción inválida. Intente nuevamente.")
