Algoritmo SistemaDeInventario
	
	Definir nombres Como Caracter
	Definir precios, cantidades Como Real
	Definir opcion, i, totalProductos Como Entero
	
	totalProductos <- 0
	
	Dimension nombres[0]
	Dimension precios[0]
	Dimension cantidades[0]
	
	Repetir
		Escribir "====== SISTEMA DE INVENTARIO ======"
		Escribir "1. Registrar producto"
		Escribir "2. Mostrar inventario"
		Escribir "3. Actualizar stock"
		Escribir "4. Salir"
		Leer opcion
		
		Mientras opcion < 1 O opcion > 4 Hacer
			Escribir "Opción inválida. Intente nuevamente:"
			Leer opcion
		FinMientras
		
		Segun opcion Hacer
			
			1:
				totalProductos <- totalProductos + 1
				
				Redimension nombres[totalProductos]
				Redimension precios[totalProductos]
				Redimension cantidades[totalProductos]
				
				Escribir "Ingrese nombre del producto:"
				Leer nombres[totalProductos]
				
				Repetir
					Escribir "Ingrese precio del producto:"
					Leer precios[totalProductos]
				Hasta Que precios[totalProductos] > 0
				
				Repetir
					Escribir "Ingrese cantidad del producto:"
					Leer cantidades[totalProductos]
				Hasta Que cantidades[totalProductos] >= 0
				
				Escribir "Producto registrado correctamente."
				
			2:
				Si totalProductos = 0 Entonces
					Escribir "No hay productos en el inventario."
				SiNo
					Para i <- 1 Hasta totalProductos Hacer
						Escribir "Producto ", i
						Escribir "Nombre: ", nombres[i]
						Escribir "Precio: ", precios[i]
						Escribir "Cantidad: ", cantidades[i]
						Escribir "----------------------"
					FinPara
				FinSi
				
			3:
				Si totalProductos = 0 Entonces
					Escribir "No hay productos para actualizar."
				SiNo
					Escribir "Ingrese el número del producto (1 - ", totalProductos, "):"
					Leer i
					
					Mientras i < 1 O i > totalProductos Hacer
						Escribir "Número inválido. Intente nuevamente:"
						Leer i
					FinMientras
					
					Repetir
						Escribir "Ingrese nueva cantidad:"
						Leer cantidades[i]
					Hasta Que cantidades[i] >= 0
					
					Escribir "Stock actualizado."
				FinSi
				
			4:
				Escribir "Saliendo del sistema..."
				
		FinSegun
		
	Hasta Que opcion = 4
	
FinAlgoritmo
