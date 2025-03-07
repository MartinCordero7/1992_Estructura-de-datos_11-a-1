% script.m

% Leer datos desde el archivo de texto
datos = dlmread('BigO.txt', ',');

% Graficar los datos
plot(datos(:,1), datos(:,2), 'b-o');
xlabel('Número de Dato');
ylabel('Tiempo de Ejecución (ms)');
title('Gráfico de Tiempos de Búsqueda');

% Obtener la fecha y hora actual para el nombre del archivo
fechaHora = datestr(now, 'yyyy-mm-dd_HH-MM-SS');
nombreArchivo = fullfile('graficasM', ['Grafico_' fechaHora '.png']);

% Guardar el gráfico como imagen PNG
saveas(gcf, nombreArchivo, 'png');

% Realizar pruebas y análisis con los datos
% Por ejemplo, calcular promedio, desviación estándar, etc.
promedio = mean(datos(:,2));
desviacion_estandar = std(datos(:,2));

fprintf('Promedio de tiempos: %.2f ms\n', promedio);
fprintf('Desviación estándar: %.2f ms\n', desviacion_estandar);