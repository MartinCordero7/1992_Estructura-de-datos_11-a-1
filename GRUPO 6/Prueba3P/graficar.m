try
    % Leer los datos especificando las opciones de importación
    opts = detectImportOptions('output/datos.txt');
    opts.VariableNamingRule = 'preserve';  % Preservar los nombres originales
    datos = readtable('output/datos.txt', opts);
    
    % Extraer columnas usando los nombres exactos del archivo
    n = datos.n;
    eLogN = datos.("e*log(n)");
    
    % Crear una nueva figura
    figure('Name', 'Análisis de Complejidad');
    
    % Graficar las funciones
    plot(n, eLogN, 'r-o', 'LineWidth', 2, 'DisplayName', 'e*log(n)');
    hold on;
    plot(n, n, 'b-s', 'LineWidth', 2, 'DisplayName', 'n');
    
    % Configuración de la gráfica
    xlabel('Tamaño de entrada (n)');
    ylabel('Valor de la función');
    title('Comparación de e*log(n) y n');
    legend('show');
    grid on;
    
    % Ajustar los límites de los ejes
    axis tight;
    
catch e
    disp('Error al cargar o graficar los datos:');
    disp(e.message);
end