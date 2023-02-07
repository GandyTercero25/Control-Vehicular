#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PARQUEADERO 100

struct historial {
    char nombre_propietario[100];
    char datos_placa[100];
    char marca_vehiculo[100];
    char placa[100];
    char informacion_contacto[100];
    char fecha_hora[20];
    char date_hora[20];
};

int control_vehicular = 0;
struct historial historial[MAX_PARQUEADERO];

void ingresar_vehiculo() {
    if (control_vehicular == MAX_PARQUEADERO) {
        printf("Lo siento, no se pueden ingresar más vehiculos en este momento. Por favor intente mas tarde.\n");
        return;
    }

    printf("Ingrese el nombre del propietario: ");
    scanf("%s", historial[control_vehicular].nombre_propietario);

    printf("Ingrese los datos de la placa: ");
    scanf("%s", historial[control_vehicular].datos_placa);

    printf("Ingrese la marca del vehiculo: ");
    scanf("%s", historial[control_vehicular].marca_vehiculo);

    printf("Ingrese la informacion de contacto del propieatrio (teléfono o correo electronico): ");
    scanf("%s", historial[control_vehicular].informacion_contacto);


    struct tm fecha;
    printf("Ingrese la fecha de ingreso del vehiculo (formato: dd/mm/yyyy): ");
    scanf("%d/%d/%d", &fecha.tm_mday, &fecha.tm_mon, &fecha.tm_year);
    fecha.tm_mon--;
    fecha.tm_year -= 1900;
    strftime(historial[control_vehicular].fecha_hora, sizeof(historial[control_vehicular].fecha_hora), "%d/%m/%Y", &fecha);

    struct tm date;
    printf("Ingrese la fecha de salida del vehiculo (formato: dd/mm/yyyy): ");
    scanf("%d/%d/%d", &date.tm_mday, &date.tm_mon, &date.tm_year);
    date.tm_mon--;
    date.tm_year -= 1900;
    strftime(historial[control_vehicular].date_hora, sizeof(historial[control_vehicular].date_hora), "%d/%m/%Y", &date);
    
    int i;
    for(i=0;i<control_vehicular;i++) {
        if(strcmp(historial[i].fecha_hora, historial[control_vehicular].fecha_hora) == 0) {
            printf("Ya existe un control vehicular con esta fecha, por favor seleccione otra fecha");
            return;
        }
    }
    
    int e;
    for(e=0;e<control_vehicular;e++) {
        if(strcmp(historial[e].date_hora, historial[control_vehicular].date_hora) == 0) {
            printf("Ya existe un control vehicular con esta fecha, por favor seleccione otra fecha");
            return;
        }
    }



    printf("Control vehicular aguardado exitosamente.\n", historial[control_vehicular].nombre_propietario);
    control_vehicular++;
}


void ver_Control() {
    int i;
    if (control_vehicular == 0) {
        printf("No hay historial almacenado.\n");
    } else {
        printf("Historial Guardado:\n");
        for (i = 0; i < control_vehicular; i++) {
            printf("\n-Propietario: %s, \n Contacto: %s, \n Fecha de ingreso: %s\n, Fecha de salida: %s\n", historial[i].nombre_propietario, historial[i].informacion_contacto, historial[i].fecha_hora,historial[i].date_hora);
        }
    }
}


void buscar_placa() {
    char placa[100];
    printf("Dato de placa registrada: ");
    scanf("%s", placa);

    int i, encontrado = 0;
    for (i = 0; i < control_vehicular; i++) {
        if (strcmp(historial[i].datos_placa, placa) == 0) {
            printf("Numero de placa encontrado: %s \n, Marca del vehiculo: %s \n", historial[i].datos_placa, historial[i].marca_vehiculo);
            int j;
            for (j = i; j < control_vehicular + 1; j++) {
                placa[j] = placa[j + 1];
            }
            control_vehicular++;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No se ha encontrado ninguna placa especificada.\n");
    }
}


void guardar_Control() {
    FILE *archivo;
    archivo = fopen("historial.txt", "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }

    int i;
    for (i = 0; i < control_vehicular; i++) {
        fprintf(archivo, "Nombre del propietario: %s, Datos de la placa: %s, Marca del vehiculo: %s, Contacto: %s, Fecha de ingreso: %s\n, Fecha de salida: %s\n", historial[i].nombre_propietario, historial[i].datos_placa, historial[i].marca_vehiculo, historial[i].informacion_contacto, historial[i].fecha_hora,historial[i].date_hora);
    }

    fclose(archivo);
    printf("Historial Almacenado exitosamente al archivo historial.txt.\n");
}

int main() {
    while (1) {
        printf("~~~~~~~~Menu de opciones~~~~~~~\n");
        printf("1. Ingresar vehiculo\n");
        printf("2. Ver control vehicular\n");
        printf("3. buscar vehiculo por placa\n");
        printf("4. Guardar control vehicular\n");
        printf("5. Salir\n");

        int opcion;
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresar_vehiculo();
                break;

            case 2:
                ver_Control();
                break;
            case 3:
                buscar_placa();
                break;
            case 4:
                guardar_Control();
                break;
            case 5:
                return 0;
            default:
                printf("Opcion invalida. Por favor seleccione una opcion valida del menu.\n");
                break;
        }
    }
}