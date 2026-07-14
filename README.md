# TRABAJO-PRACTICO-FINAL---FROGGER---Bianco-Blanco-Gerli-Paysse
## Frogger - Proyecto Final Programación en C

## Descripción

Este proyecto consiste en el desarrollo de una versión del clásico **Frogger** implementada en lenguaje C con una arquitectura **multiplataforma**.

El objetivo principal fue separar completamente la **lógica del juego (Back-End)** de la **representación gráfica (Front-End)**, permitiendo ejecutar exactamente el mismo motor tanto en una PC utilizando Allegro como en una Raspberry Pi utilizando una matriz LED y joystick.

---
# Organización del proyecto

```
src/

│
|__config.h: constantes de configuracion del juego, alto, ancho, etc.
├── game.c: Se definen las funciones de navegacion 
├── game.h: Se define la estructura principal Game, enums de opciones de menus y funciones de navegacion
│
├── entities.c: Se definen las funciones relacionadas con las entidades del juego
├── entities.h: Se definen las estructuras que caracterizan a las entidades del juego, ej: Frog
│
├── levels.c: Se definen las funciones relacionadas con 
├── levels.h
|
|__ collision.c: Funciones relacionadas con las interacciones entre las entidades del juego, ej: frogOnFloater
|__ collision.h: Se definen las estrucutras relacionadas con las interacciones entre las entidades del juego
│
├── frontend/
│   ├── allegro/
│   └── raspberry/
│
├── main.c
│
└── Makefile: Make file generico con dos targets distintos para cada plataforma
```

# Arquitectura del proyecto


El proyecto fue dividido en cuatro módulos principales:

```
                +--------------------+
                |       main.c       |
                +---------+----------+
                          |
                          v
                +--------------------+
                |      game.c        |
                |  Motor del juego   |
                +---------+----------+
                          |
      +-------------------+-------------------+
      |                                       |
      v                                       v
+--------------+                     +----------------+
| entities.c   |                     | levels.c       |
| Colisiones   |                     | Mapas/Niveles  |
|              |                     | Zonas          |
+--------------+                     +----------------+

                          ^
                          |
                 Interfaz abstracta

          +---------------+---------------+
          |                               |
          v                               v
  Front-End Allegro               Front-End Raspberry
```

---

# Filosofía del proyecto

El Back-End nunca conoce:

- Allegro
- Raspberry Pi
- LEDs
- Teclado
- Joystick

El motor únicamente trabaja con:

- estructuras de datos
- posiciones
- entidades
- estados del juego

Los Front-End únicamente traducen:

```
Usuario
      ↓
Teclado / Joystick
      ↓
Input
      ↓
updateGame()
      ↓
Nuevo estado del juego
      ↓
Renderizado
```

Esto permite utilizar exactamente el mismo motor sobre distintas plataformas.

---

# Flujo principal

Cada iteración del juego sigue siempre la misma secuencia.

```
while (game.state != EXIT)
{
    Input input = frontendGetInput();

    updateGame(&game, input);

    frontendRender(&game);
}
```

1. El Front-End obtiene la acción del usuario.
2. El Back-End actualiza completamente el estado del juego.
3. El Front-End dibuja el nuevo estado.

---

# Estructura Game

Toda la información del juego se encuentra encapsulada en una única estructura `Game`.

Esta estructura contiene:

- Rana
- Entidades
- Nivel actual
- Puntaje
- Vidas
- Zona actual
- Estado del juego

De esta manera el motor puede trabajar únicamente modificando esta estructura.

---

# Máquina de estados

El motor está implementado mediante una máquina de estados finitos.

Estados principales:

- MENU
- PLAYING
- PAUSED
- VICTORY
- GAME_OVER
- POINTS
- EXIT

Cada estado posee su propia lógica de procesamiento de entrada. :contentReference[oaicite:1]{index=1} :contentReference[oaicite:2]{index=2}

---

# Menús

Los distintos menús del juego (principal, pausa, victoria, game over y puntajes) utilizan una estructura genérica denominada `MenuState`, que almacena:

- opción seleccionada
- cantidad de opciones disponibles

Esto permite reutilizar la misma lógica de navegación para todos los menús mediante las funciones:

- menuNext()
- menuPrevious()

:contentReference[oaicite:3]{index=3} :contentReference[oaicite:4]{index=4}

---

# Entidades

Todas las entidades dinámicas del juego son administradas por el Back-End.

Entre ellas:

- Autos
- Camiones
- Troncos
- Tortugas

Cada entidad almacena información como:

- posición
- velocidad
- dirección
- tamaño
- tipo

Durante cada actualización del juego las entidades se desplazan automáticamente según su velocidad.

---

# Colisiones

El sistema de colisiones es completamente independiente del Front-End.

El Back-End determina:

- atropellos
- ahogamiento
- interacción con troncos
- llegada a zonas seguras

Las funciones de detección únicamente responden consultas (por ejemplo, si la rana está sobre un tronco), mientras que las consecuencias (perder una vida, avanzar de nivel, etc.) son resueltas por el motor del juego.

---

# Niveles

Cada nivel contiene:

- zonas del mapa
- entidades
- identificador del nivel

Las zonas indican el tipo de terreno:

- ROAD
- WATER
- SAFE
- START

:contentReference[oaicite:5]{index=5}

El módulo `levels` es responsable de:

- creación del nivel
- cambio de nivel
- verificación de llegada a la meta

:contentReference[oaicite:6]{index=6} :contentReference[oaicite:7]{index=7}

---

# Sistema de entrada

El Back-End nunca recibe teclas específicas.

Cada Front-End traduce su dispositivo de entrada al tipo abstracto:

```
Input
```

Por ejemplo:

PC: Flecha arriba = INPUT: UP
``````
```
Raspberry: Joystick arriba = INPUT: UP
```

El motor recibe exactamente el mismo dato independientemente de la plataforma. 

---

# Front-End Allegro

La versión para PC utiliza la biblioteca Allegro.

Responsabilidades:

- abrir la ventana
- dibujar sprites
- reproducir sonidos
- leer teclado
- llamar periódicamente al motor del juego

---

# Front-End Raspberry Pi

La versión Raspberry implementa una interfaz mínima utilizando:

- matriz LED
- joystick

El código reutiliza exactamente el mismo Back-End que la versión de PC.

Únicamente cambia la representación gráfica y el dispositivo de entrada.

---

# Compilación multiplataforma

El proyecto está diseñado para generar dos ejecutables distintos a partir del mismo motor.

```
                    Código común

        game.c
        entities.c
        levels.c

                |
        ------------------
        |                |
        v                v

 Allegro            Raspberry

 Ejecutable PC      Ejecutable RasPi
```

El `Makefile` define distintos **targets**, cada uno de los cuales enlaza el motor común con el Front-End correspondiente.

De esta manera:

- el Back-End se compila una única vez,
- cada plataforma incorpora únicamente sus propios archivos y bibliotecas,
- no existe código duplicado entre versiones.

Conceptualmente:

```make
make pc      -> Compila Back-End + Front-End Allegro

make raspi   -> Compila Back-End + Front-End Raspberry
```

El motor del juego permanece idéntico en ambos casos; únicamente cambia la implementación del Front-End y las bibliotecas enlazadas durante la compilación.

---

# Principios de diseño

Durante el desarrollo se siguieron los siguientes principios:

- Separación entre lógica y representación.
- Independencia de plataforma.
- Modularidad.
- Bajo acoplamiento entre módulos.
- Reutilización del código del motor.
- Máquina de estados para el control del flujo del juego.
- Encapsulamiento del estado completo del juego mediante la estructura `Game`.
