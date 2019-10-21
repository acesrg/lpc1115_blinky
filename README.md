# LPC1115 Develpment

Repositorio de referencia para proyectos realizados utilizando el microcontrolador LPC1115

## Arbol de proyecto
Se espera que cada proyecto siga la siguente estructura:
```
+-- compilation
|   +-- inc
|       +-- (headers de ARM CMSIS)
|       +-- DEVICEFAM.h
|       +-- system_DEVICEFAM.h
|   +-- DEVICE.ld
|   +-- DEVICE.map
|   +-- startup_DEVICEFAM.c/s
|   +-- (otros archivos relevantes a la compilación)
+-- PROJECT1_NAME
|   +-- inc
|       +-- main.h
|       +-- (headers)
|   +-- src
|       +-- main.c (aquí la descripción del proyecto)
|       +-- (sources)
|   +-- makefile
.
.
.
+-- PROJECTN_NAME
```
## Reglas de código

* Variables y parámetros tienen tipos de datos completos.
* Expresiones para constantes #define están encerradas en paréntesis.
Se recomienda utilizar:
* Nombres en _MAYUSCULAS_ para identificar registros o instrucciones del procesador.
* Nombres en _CamelCase_ para identificar funciónes o rutinas de interrupciones.
* Prefijos Namespace_ para agrupar funciónes relacionadas (ej. cuando creamos una librería para periféricos).

## Compilación
### Linux:
```
cd PROJECT_NAME
make
```
#### Prequisitos
* arm-none-eabi-gcc
* GNU Make

## Flash
### Linux

#### Primer flash desde reset
```
cd PROJECT_NAME
make bootFlash
```

#### Proximos flash
```
cd PROJECT_NAME
make flash
```

#### Prequisitos
* dfu-util
* LPCXpresso (o el directorio bin de dicho software)

## Errores comunes

### Perder acceso de debug (aka: burguearla)

#### Síntomas
Al intentar cargar un programa obtenemos un error de programa corrupto.

#### Causas
En realidad, esto sucede porque el binario que quisimos cargar no fue escrito en la placa. Al comprobar esto, la herramienta de flash devuevle el error mencionado.
Lo mas probable es que esto sea así debido a una configuración erronea en nuestro programa, por ejemplo desconfigurando el clock o desactivando alguna función indispensable en el bus AHB.

#### Solución
Basta con,

* poner el pin P0.1 (en la placa es el pin FT/GPIO) a GND,
* dar reset (o desconectar y conectar el cable),
* liberar el pin P0.1,
* flashear la placa con un código sin configuraciónes erroneas.

El pin P0.1 habilita el modo de programación ISP, para el cual el microcontrolador configura automáticamente el clock y los buses escenciales, de forma correcta.
