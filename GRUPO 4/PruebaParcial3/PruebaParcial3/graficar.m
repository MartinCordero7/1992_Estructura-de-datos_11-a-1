% Cargar los datos desde el archivo .txt output//datos_demostracion.txt
% Cargar los datos desde el archivo .txt
datos = readtable('C:\Users\neste\OneDrive\Documentos\Trabajo\datos_demostracion.txt');

% Extraer columnas
n = datos.n;
eLogN = datos.e_log_n_;
nVal = datos.n;

% Graficar las funciones
figure('Position', [100, 100, 800, 600]); % Set figure size to 800x600
plot(n, eLogN, 'b', 'LineWidth', 2); % Graficar e*log(n) en azul
hold on;
plot(n, nVal, 'r', 'LineWidth', 2); % Graficar n en rojo

% Calcular y mostrar el punto de intersección
interseccion_x = exp(1); % e
interseccion_y = exp(1); % e
plot(interseccion_x, interseccion_y, 'ko', 'MarkerSize', 10, 'LineWidth', 2); % Punto de intersección en negro
text(interseccion_x, interseccion_y, sprintf('  (e, e)'), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');

% Configuración de la gráfica
xlabel('n');
ylabel('Valor de la función');
title('Demostracion mediante la definicion de O: Comparación de e*log(n) y n');
legend('e*log(n)', 'n', 'Intersección (e, e)');
grid on;

% Agregar líneas entrecortadas para mostrar el eje de X
yline(0, 'k--');

% Mostrar la tabla de datos en la consola
disp(datos);

% Use uiwait to keep the plot window open
uiwait;