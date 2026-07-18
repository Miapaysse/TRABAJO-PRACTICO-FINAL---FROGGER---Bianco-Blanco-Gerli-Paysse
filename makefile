CC:= gcc
OPTIONS := -g -Wall 
# Le decimos al compilador en qué carpetas buscar los archivos .h
INCLUDES = -Ibackend -Ifrontend -Ifrontend/raspi -Ifrontend/raspi/libs

# Flags necesarias para poder usar Allegro
ALLEGRO_FLAGS = $(shell pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5)

# Objetos del backend (compartidos por ambas plataformas)
BACKEND_OBJS := backend/game.o backend/entities.o backend/interactions.o backend/levels.o backend/top10.o

# Objetos comunes (menús, puntaje, persistencia)
COMMON_OBJS := main.o

.PHONY: allegro raspi backend clean

# --- Backend ---

backend: ${BACKEND_OBJS}

backend/interactions.o: backend/interactions.c backend/interactions.h backend/entities.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/interactions.c -o backend/interactions.o

backend/entities.o: backend/entities.c backend/entities.h backend/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/entities.c -o backend/entities.o

backend/levels.o: backend/levels.c backend/levels.h backend/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/levels.c -o backend/levels.o

backend/game.o: backend/game.c backend/game.h backend/entities.h backend/interactions.h backend/levels.h
	$(CC) $(OPTIONS) $(INCLUDES) -include backend/interactions.h -c backend/game.c -o backend/game.o

# --- Datos: puntaje y top10 ---

backend/top10.o: backend/top10.c backend/top10.h backend/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c backend/top10.c -o backend/top10.o

# --- main.c ---
main.o: main.c backend/game.h frontend/frontend.h backend/config.h
	${CC} ${OPTIONS} -c main.c -o main.o


# --- Frontend (Allegro) ---
allegro: $(BACKEND_OBJS) $(COMMON_OBJS) frontend/allegroFrontend.o
	$(CC) $(OPTIONS) $(BACKEND_OBJS) main.o frontend/allegroFrontend.o -o pc $(ALLEGRO_FLAGS)

frontend/allegroFrontend.o: frontend/allegroFrontend.c frontend/frontend.h backend/game.h
	$(CC) $(OPTIONS) $(INCLUDES) $(ALLEGRO_FLAGS) -c frontend/allegroFrontend.c -o frontend/allegroFrontend.o

# --- Frontend Raspi---
raspi: $(BACKEND_OBJS) main.o frontend/raspi/raspiFrontend.o frontend/raspi/raspiDraw.o
	$(CC) $(OPTIONS) $(BACKEND_OBJS) main.o frontend/raspi/raspiFrontend.o frontend/raspi/raspiDraw.o frontend/raspi/libs/disdrv.o frontend/raspi/libs/joydrv.o -o raspi -lpthread

frontend/raspi/raspiFrontend.o: frontend/raspi/raspiFrontend.c frontend/raspi/raspiFrontend.h frontend/raspi/raspiDraw.h backend/game.h
	$(CC) $(OPTIONS) $(INCLUDES) -c frontend/raspi/raspiFrontend.c -o frontend/raspi/raspiFrontend.o

frontend/raspi/raspiDraw.o: frontend/raspi/raspiDraw.c frontend/raspi/raspiDraw.h frontend/raspi/raspiFrontend.h
	$(CC) $(OPTIONS) $(INCLUDES) -c frontend/raspi/raspiDraw.c -o frontend/raspi/raspiDraw.o

# --- Limpieza ---
clean:
	rm -f pc raspi main.o backend/*.o frontend/*.o frontend/raspi/*.o
