CC := gcc
OPTIONS := -g -Wall

# Carpetas del proyecto
BACKEND_DIR := backend
FRONTEND_DIR := frontend
RASPI_DIR := frontend/raspi
RASPI_LIBS_DIR := frontend/raspi/libs

# Le decimos al compilador en qué carpetas buscar los archivos .h
INCLUDES := -I$(BACKEND_DIR) -I$(FRONTEND_DIR) -I$(RASPI_DIR) -I$(RASPI_LIBS_DIR)

# Flags necesarias para poder usar Allegro
ALLEGRO_FLAGS = $(shell pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5)

# Objetos del backend (compartidos por ambas plataformas)
BACKEND_OBJS := \
	$(BACKEND_DIR)/game.o \
	$(BACKEND_DIR)/entities.o \
	$(BACKEND_DIR)/interactions.o \
	$(BACKEND_DIR)/levels.o \
	$(BACKEND_DIR)/top10.o

# Objetos comunes (menús, puntaje, persistencia)
COMMON_OBJS := main.o

.PHONY: allegro raspi backend clean

# --- Backend ---

backend: ${BACKEND_OBJS}

$(BACKEND_DIR)/interactions.o: $(BACKEND_DIR)/interactions.c $(BACKEND_DIR)/interactions.h $(BACKEND_DIR)/entities.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(BACKEND_DIR)/interactions.c -o $@

$(BACKEND_DIR)/entities.o: $(BACKEND_DIR)/entities.c $(BACKEND_DIR)/entities.h $(BACKEND_DIR)/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(BACKEND_DIR)/entities.c -o $@

$(BACKEND_DIR)/levels.o: $(BACKEND_DIR)/levels.c $(BACKEND_DIR)/levels.h $(BACKEND_DIR)/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(BACKEND_DIR)/levels.c -o $@

$(BACKEND_DIR)/game.o: $(BACKEND_DIR)/game.c $(BACKEND_DIR)/game.h $(BACKEND_DIR)/entities.h $(BACKEND_DIR)/interactions.h $(BACKEND_DIR)/levels.h
	$(CC) $(OPTIONS) $(INCLUDES) -include $(BACKEND_DIR)/interactions.h -c $(BACKEND_DIR)/game.c -o $@

# --- Datos: puntaje y top10 ---

$(BACKEND_DIR)/top10.o: $(BACKEND_DIR)/top10.c $(BACKEND_DIR)/top10.h $(BACKEND_DIR)/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(BACKEND_DIR)/top10.c -o $@

# --- main.c ---
main.o: main.c $(BACKEND_DIR)/game.h $(FRONTEND_DIR)/frontend.h $(BACKEND_DIR)/config.h
	$(CC) $(OPTIONS) $(INCLUDES) -c main.c -o $@


# --- Frontend (Allegro) ---
allegro: $(BACKEND_OBJS) $(COMMON_OBJS) $(FRONTEND_DIR)/allegroFrontend.o
	$(CC) $(OPTIONS) $(BACKEND_OBJS) $(COMMON_OBJS) $(FRONTEND_DIR)/allegroFrontend.o -o pc $(ALLEGRO_FLAGS)

$(FRONTEND_DIR)/allegroFrontend.o: $(FRONTEND_DIR)/allegroFrontend.c $(FRONTEND_DIR)/frontend.h $(BACKEND_DIR)/game.h
	$(CC) $(OPTIONS) $(INCLUDES) $(ALLEGRO_FLAGS) -c $(FRONTEND_DIR)/allegroFrontend.c -o $@

# --- Frontend Raspi---
RASPI_OBJS := \
	$(RASPI_DIR)/raspiFrontend.o \
	$(RASPI_DIR)/raspiDraw.o

RASPI_LIB_OBJS := \
	$(RASPI_LIBS_DIR)/disdrv.o \
	$(RASPI_LIBS_DIR)/joydrv.o

raspi: $(BACKEND_OBJS) $(COMMON_OBJS) $(RASPI_OBJS) $(RASPI_LIB_OBJS)
	$(CC) $(OPTIONS) $(BACKEND_OBJS) $(COMMON_OBJS) $(RASPI_OBJS) $(RASPI_LIB_OBJS) -o raspi -lpthread

$(RASPI_DIR)/raspiFrontend.o: $(RASPI_DIR)/raspiFrontend.c $(RASPI_DIR)/raspiFrontend.h $(RASPI_DIR)/raspiDraw.h $(BACKEND_DIR)/game.h $(RASPI_LIBS_DIR)/disdrv.h $(RASPI_LIBS_DIR)/joydrv.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(RASPI_DIR)/raspiFrontend.c -o $@

$(RASPI_DIR)/raspiDraw.o: $(RASPI_DIR)/raspiDraw.c $(RASPI_DIR)/raspiDraw.h $(RASPI_DIR)/raspiFrontend.h $(RASPI_LIBS_DIR)/disdrv.h
	$(CC) $(OPTIONS) $(INCLUDES) -c $(RASPI_DIR)/raspiDraw.c -o $@

# --- Limpieza ---
clean:
	rm -f pc raspi main.o $(BACKEND_DIR)/*.o $(FRONTEND_DIR)/*.o $(RASPI_DIR)/*.o
