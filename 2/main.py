"""
Un supermercado les ha pedido que creen un sistema para analizar sus ventas. Con base en los 3 archivos propuestos, que incluyen información de los clientes, los productos y las compras, cree un programa en Python que debe:
1.	Cargar todos los datos de los archivos en listas, teniendo en cuenta los tipos de datos asociados a los valores
2.	Listar todas las compras de todos los clientes, uno por uno, a partir de la lista de clientes
3.	Crear funciones para:
a.	Calcular el total de compras por género biológico, y mostrar la comparación, mostrando cuál fue mayor
b.	Calcular el cliente que más compró
c.	Calcular producto que más se vendió
d.	Calcular el producto que más valor real representó (el mayor total de venta en dinero acumulado)
e.	Mostrar el total de ventas de clientes cuyo apellido comience con una letra especificada por parámetro


"""


# Inicializamos las listas vacías para almacenar los datos de los archivos
compras = []
clientes = []
productos = []

# Abrimos y leemos el archivo de compras, añadiendo cada línea a la lista de compras
with open("comp.csv", "r") as f:
    for line in f:
        if line.startswith("id"):  # Ignoramos la línea de encabezado
            continue
        compras.append(line.strip().split(","))  # Añadimos cada línea (como una lista) a la lista de compras

# Hacemos lo mismo para los archivos de clientes y productos
with open("pers.csv","r") as f:
    for line in f:
        if line.startswith("id"):
            continue
        clientes.append(line.strip().split(","))

with open("prod.csv","r") as f:
    for line in f:
        if line.startswith("id"):
            continue
        productos.append(line.strip().split(","))

# Definimos una clase Cliente para almacenar la información de cada cliente
class Cliente:
    def __init__(self, id, nombreC, genero):
        self.id = id
        self.nombreC = nombreC
        self.genero = genero
        self.compras = []  # Inicializamos una lista vacía para almacenar las compras de cada cliente

    # Método para añadir una compra a la lista de compras de un cliente
    def add_compra(self, compra):
        self.compras.append(compra)

# Creamos una lista de objetos Cliente a partir de los datos en la lista de clientes
clientes_obj: list[Cliente] = []   
for c in clientes:
    clientes_obj.append(Cliente(c[0],c[1],c[2]))

# Asociamos cada compra con su respectivo cliente
for compra in compras:
    for c in clientes_obj:
        if compra[0] == c.id:
            c.add_compra(compra)

# Función para listar todas las compras de todos los clientes
def listar_compras():
    for cliente in clientes_obj:
        print(f"Cliente: {cliente.nombreC}")
        for compra in cliente.compras:
            print(f"Compra: {productos[int(compra[1])-1][1]}")
        print("\n")            

# Función para calcular y comparar el total de compras por género
def total_generos():
    total_f = 0
    total_m = 0
    for cliente in clientes_obj:
        if cliente.genero == "F":
            total_f += len(cliente.compras)
        else:
            total_m += len(cliente.compras)
    if total_f > total_m:
        print(f"El género femenino ha realizado más compras: {total_f}")
    else:
        print(f"El género masculino ha realizado más compras: {total_m}")

# Función para calcular el cliente que más compró
def cliente_mas_compras():
    mas_compras = 0
    cliente = None
    for c in clientes_obj:
        if len(c.compras) > mas_compras:
            mas_compras = len(c.compras)
            cliente = c
    print(f"El cliente que más compró fue: {cliente.nombreC} con {mas_compras} compras")

# Función para calcular el producto que más se vendió
def producto_mas_vendido():
    mas_vendido = 0
    producto = None
    for p in productos:
        total = 0
        for compra in compras:
            if compra[1] == p[0]:
                total += int(compra[2])
        if total > mas_vendido:
            mas_vendido = total
            producto = p
    print(f"El producto que más se vendió fue: {producto[1]} con {mas_vendido} unidades vendidas")

# Función para calcular el producto que más valor real representó
def producto_mas_valor():
    mas_valor = 0
    producto = None
    for p in productos:
        total = 0
        for compra in compras:
            if compra[1] == p[0]:
                total += int(compra[2]) * int(p[2])
        if total > mas_valor:
            mas_valor = total
            producto = p
    print(f"El producto que más valor real representó fue: {producto[1]} con un total de {mas_valor}")

# Función para mostrar el total de ventas de clientes cuyo apellido comienza con una letra especificada
def total_ventas_apellido(letra):
    total = 0
    for cliente in clientes_obj:
        if cliente.nombreC.split(" ")[1].startswith(letra):
            total += len(cliente.compras)
    print(f"El total de ventas de los clientes cuyo apellido comienza con {letra} es de: {total}") 

# Llamamos a las funciones para ejecutarlas
listar_compras()
total_generos()
cliente_mas_compras()
producto_mas_vendido()
producto_mas_valor()
total_ventas_apellido("A")