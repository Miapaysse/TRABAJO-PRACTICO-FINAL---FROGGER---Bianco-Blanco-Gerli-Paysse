CC:= gcc
OPTIONS := -g -Wall 
# Le decimos al compilador en qué carpetas buscar los archivos .h
INCLUDES = -Iconfig -Ibackend -Ifrontend -Idata

# Flags necesarias para poder usar Allegro
ALLEGRO_FLAGS = $(shell pkg-config --libs allegro-5.0 allegro_font-5.0 allegro_primitives-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_image-5.0)

# Objetos del backend (compartidos por ambas plataformas)
BACKEND_OBJS := backend/game.o backend/entities.o backend/collision.o backend/levels.o

# Objetos comunes (menús, puntaje, persistencia)
COMMON_OBJS := main.o data/score.o data/top10.o

.PHONY: allegro raspi backend clean

# --- Backend ---

backend: ${BACKEND_OBJS}

backend/collision.o: backend/collision.c backend/collision.h backend/entities.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/collision.c -o backend/collision.o

backend/entities.o: backend/entities.c backend/entities.h config/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/entities.c -o backend/entities.o

backend/levels.o: backend/levels.c backend/levels.h config/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/levels.c -o backend/levels.o

backend/game.o: backend/game.c backend/game.h backend/entities.h backend/collision.h backend/levels.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/game.c -o backend/game.o

# --- Datos: puntaje y top10 ---

data/score.o: data/score.c data/score.h backend/game.h
	$(CC) $(OPTIONS) $(INCLUDES) -c data/score.c -o data/score.o

data/top10.o: data/top10.c data/top10.h
	$(CC) $(OPTIONS) $(INCLUDES) -c data/top10.c -o data/top10.o


# --- main.c ---
main.o: main.c backend/game.h frontend/frontend.h config/config.h
	${CC} ${OPTIONS} -c main.c -o main.o


# --- Frontend (Allegro) ---
allegro: $(BACKEND_OBJS) $(COMMON_OBJS) frontend/allegroFrontend.o
	$(CC) $(OPTIONS) $(BACKEND_OBJS) main.o data/score.o data/top10.o frontend/allegroFrontend.o -o pc $(ALLEGRO_FLAGS)

frontend/allegroFrontend.o: frontend/allegroFrontend.c frontend/frontend.h backend/game.h
	$(CC) $(OPTIONS) $(INCLUDES) -c frontend/allegroFrontend.c -o frontend/allegroFrontend.o

# --- Frontend Raspi---
raspi: $(BACKEND_OBJS) main.o data/score.o data/top10.o frontend/raspiFrontend.o frontend/disdrv.o frontend/joydrv.o
	$(CC) $(OPTIONS) $(BACKEND_OBJS) main.o data/score.o data/top10.o frontend/raspiFrontend.o frontend/disdrv.o frontend/joydrv.o -o raspi -lpthread

frontend/raspiFrontend.o: frontend/raspiFrontend.c frontend/frontend.h backend/game.h
	$(CC) $(OPTIONS) $(INCLUDES) -c frontend/raspiFrontend.c -o frontend/raspiFrontend.o

# --- Limpieza ---
clean:
	rm -f pc raspi main.o backend/*.o data/*.o frontend/*.o
