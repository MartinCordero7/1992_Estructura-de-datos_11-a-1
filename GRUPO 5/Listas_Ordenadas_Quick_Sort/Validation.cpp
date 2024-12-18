#include <iostream>
#include <string.h>
#include "Validation.h"

using namespace std;

template <typename T>
Validation<T>::Validation(){}


// *******************INPUTS DE DATOS*********************
template <typename T>
T Validation<T>::enter_a_number(char *data_type){
    char cad[20], c;
    int i = 0;
    bool validation_decimal=false;

    while(((c = getch())!=13)){
        
        if (c>='0' && c <= '9' ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c == '.' && (validation_decimal==false) && !(strcmp(data_type, "float"))){
            printf("%c", c);
            cad[i++] = c;
            validation_decimal=true;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
            if(cad[i]=='.'){
                validation_decimal=false;
            }
        }
    }
    cad[i++]='\0';
    T return_data = data_convertion_to_number(cad, data_type);   
    return return_data;
}

template <typename T>
T Validation<T>::enter_a_char_or_string(int data_size){
    char cad[data_size], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z') || (c==' ') ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    return cad;
}

template <typename T>
T Validation<T>::enter_a_char_or_string_only_nums(int data_size){
    char cad[data_size], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='0' && c <= '9') ){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    return cad;
}

template <typename T> 
T Validation<T>::enter_a_char_or_string_with_may_and_nums(int data_size){ 
    char cad[data_size], c;
    int i = 0;
    while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z') || (c>='0' && c<='9')){
            
            if(c>='a' && c <= 'z') {
                if((i == 0 || cad[i-1]==' ')){
                c = c-32;//A mayúsculas 
              }
            }else if((c>='A'&&c<='Z')){
                if(cad[i-1]!=' ' && i!=0){
                    c =c+32;//A minúsculas 
                }
            }
            printf("%c", c);
            cad[i++] = c;
        }else if(c == ' '){
            printf("%c", c);
            cad[i++] = c;
        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }

    cad[i++]='\0';
    return cad;
}

template <typename T>
T Validation<T>::enter_a_char_or_string_with_may(int data_size){
    char cad[data_size], c;
    int i = 0;
    while(((c = getch())!=13)){
        if ((c>='a' && c <= 'z') || (c>='A'&&c<='Z')){
            
            if(c>='a' && c <= 'z') {
                if((i == 0 || cad[i-1]==' ')){
                c = c-32;//A mayúsculas 
              }
            }else if((c>='A'&&c<='Z')){
                if(cad[i-1]!=' ' && i!=0){
                    c =c+32;//A minúsculas 
                }
            }
            printf("%c", c);
            cad[i++] = c;
        }else if(c == ' '){
            printf("%c", c);
            cad[i++] = c;
        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }

    cad[i++]='\0';
    return cad;
}


// *******************DATA CONVERTION**********************
template <typename T>
T Validation<T>::data_convertion_to_number(char *value, char *data_type){
    if(!strcmp(data_type, "int")){
        int int_value = atoi(value);
        return int_value;
    }else if(!strcmp(data_type, "float")) {
        float float_value = atof(value);
        return float_value;
    }   
    return 0;
}


// *******************OTHER VALIDATIONS********************

template <typename T>
T Validation<T>::validation_buckup(){
    char cad[20], c;
    int i = 0;
     while(((c = getch())!=13)){
        if ((c>='0' && c <= '9') || (c=='.')){
            printf("%c", c);
            cad[i++] = c;

        }else if(c==8 && i > 0){
            printf("\b \b");
            i--;
        }
    }
    cad[i++]='\0';
    return cad;
}


template <typename T>
bool Validation<T>::validar_id_autor(string id_autor){
    string aux = id_autor;
    aux[0]='0';
    int parte_numerica_id = stoi(aux);

    if((id_autor[0] == 'A') && parte_numerica_id<999 && (id_autor.length()==4)){
        return true;
    }

    return false;
}

template <typename T>
bool Validation<T>::validate_isbn(const string &isbn) {
    int length = isbn.length();

    // Validación de ISBN-10
    if (length == 10) {
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (!isdigit(isbn[i])) return false; // Solo dígitos
            sum += (isbn[i] - '0') * (10 - i);
        }
        char last_char = isbn[9];
        if (last_char != 'X' && !isdigit(last_char)) return false;

        sum += (last_char == 'X') ? 10 : (last_char - '0');
        return (sum % 11 == 0);
    }
    // Validación de ISBN-13
    else if (length == 13) {
        int sum = 0;
        for (int i = 0; i < 13; i++) {
            if (!isdigit(isbn[i])) return false; // Solo dígitos
            int digit = isbn[i] - '0';
            sum += (i % 2 == 0) ? digit : digit * 3;
        }
        return (sum % 10 == 0);
    }

    // Longitud inválida
    return false;

    
}
template <typename T>
string Validation<T>::enter_date() {
    char cad[11];
    int i = 0;
    bool esperando_espacio = false;
    
    cout << "\nIngrese la fecha (DD MM AAAA): ";
    
    while (true) {
        char c = getch();
        
        // Tecla Enter finaliza la entrada
        if (c == 13) {
            cad[i] = '\0';
            break;
        }
        
        // Manejo de Backspace
        if (c == 8 && i > 0) {
            printf("\b \b");
            i--;
            esperando_espacio = false;
            continue;
        }
        
        // Solo permite números y espacios
        if ((c >= '0' && c <= '9') || c == ' ') {
            // Control de longitud máxima
            if (i < 10) {
                // Si es un espacio
                if (c == ' ') {
                    // Solo permite espacios en posiciones específicas
                    if ((i == 2 || i == 5) && !esperando_espacio) {
                        printf("%c", c);
                        cad[i++] = c;
                        esperando_espacio = true;
                    }
                }
                // Si es un número
                else {
                    // Validación de posición para números
                    if (!esperando_espacio || 
                        (i > 2 && i < 5) || 
                        (i > 5 && i < 10)) {
                        printf("%c", c);
                        cad[i++] = c;
                        esperando_espacio = false;
                    }
                }
            }
        }
    }

    if (!validarFecha(cad)) {
        cout << "\nFecha invalida. Intente de nuevo." << endl;
        return enter_date();
    }
    
    return string(cad);
}

template <typename T>
bool Validation<T>::validarFecha(const string& fechaStr) {
    // Verificar longitud y formato
    if (fechaStr.length() != 10 || 
        fechaStr[2] != ' ' || 
        fechaStr[5] != ' ') {
        return false;
    }

    // Parsear fecha manualmente para asegurar precisión
    int dia = stoi(fechaStr.substr(0, 2));
    int mes = stoi(fechaStr.substr(3, 2));
    int anio = stoi(fechaStr.substr(6));

    // Validaciones básicas de rango
    if (dia < 1 || dia > 31 || 
        mes < 1 || mes > 12|| 
        anio < 1500 || anio > 9999) {
        return false;
    }

    // Días por mes (considerando años bisiestos)
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Ajustar febrero para años bisiestos
    if (mes == 2) {
        int diasFebrero = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) ? 29 : 28;
        if (dia > diasFebrero) return false;
    } else {
        // Validar días para otros meses
        if (dia > diasEnMes[mes]) return false;
    }

    // Verificar que la fecha no sea posterior a la fecha actual
    if (esFechaPosterior(dia, mes, anio)) {
        return false;
    }

    return true;
}

template <typename T>
bool Validation<T>::esFechaPosterior(int dia, int mes, int anio) {
    // Obtener fecha actual
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Fecha actual
    int diaActual = ltm->tm_mday;
    int mesActual = 1 + ltm->tm_mon;
    int anioActual = 1900 + ltm->tm_year;

    // Comparar año
    if (anio > anioActual) return true;
    if (anio < anioActual) return false;

    // Si el año es igual, comparar mes
    if (mes > mesActual) return true;
    if (mes < mesActual) return false;

    // Si el mes es igual, comparar día
    return (dia > diaActual);
}