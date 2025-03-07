# Lee los datos
datos <- read.csv("BigO.txt", header = FALSE, sep = ",")

# Define los datos x y y
x <- datos$V1
y <- datos$V2
plot(x, y, type = "l", xlab = "Datos", ylab = "Tiempo", main = "Gráfico BigO")

# Define la ruta y el nombre del archivo basado en la fecha y hora
# Asegúrate de que la carpeta 'graficas' ya exista o crea una antes de ejecutar el código
nombre_archivo <- paste0("graficasR/", Sys.Date(), "_", format(Sys.time(), "%H%M%S"), ".png")

# Especifica que el gráfico se guarde como PNG en la ruta definida
png(filename = nombre_archivo, width = 800, height = 600)

# Crea el gráfico
plot(x, y, type = "l", xlab = "Datos", ylab = "Tiempo", main = "Gráfico BigO")

# Guarda y cierra el archivo de imagen
dev.off()
