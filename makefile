# Compilador y opciones
CC := gcc
OPTIONS := -g -Wall

# Carpetas del proyecto
BACKEND_DIR := backend
FRONTEND_DIR := frontend
RASPI_DIR := frontend/raspi
RASPI_LIBS_DIR := frontend/raspi/libs

# Incluir directorios para los archivos .h
INCLUDES := -I$(BACKEND_DIR) -I$(FRONTEND_DIR) -I$(RASPI_DIR) -I$(RASPI_LIBS_DIR)

# Flags para Allegro
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5)

# Objetos del backend
BACKEND_OBJS := \
    $(BACKEND_DIR)/game.o \
    $(BACKEND_DIR)/entities.o \
    $(BACKEND_DIR)/interactions.o \
    $(BACKEND_DIR)/levels.o \
    $(BACKEND_DIR)/top10.o

# Objetos comunes
COMMON_OBJS := main.o

# Objetos del frontend para Raspberry Pi
RASPI_OBJS := \
    $(RASPI_DIR)/raspiFrontend.o \
    $(RASPI_DIR)/raspiDraw.o

RASPI_LIB_OBJS := \
    $(RASPI_LIBS_DIR)/disdrv.o \
    $(RASPI_LIBS_DIR)/joydrv.o

# Declaración de objetivos phony
.PHONY: allegro raspi backend clean

# --- Backend ---
backend: $(BACKEND_OBJS)

$(BACKEND_DIR)/interactions.o: $(BACKEND_DIR)/interactions.c $(BACKEND_DIR)/interactions.h $(BACKEND_DIR)/entities.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/entities.o: $(BACKEND_DIR)/entities.c $(BACKEND_DIR)/entities.h $(BACKEND_DIR)/config.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/levels.o: $(BACKEND_DIR)/levels.c $(BACKEND_DIR)/levels.h $(BACKEND_DIR)/config.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/game.o: $(BACKEND_DIR)/game.c $(BACKEND_DIR)/game.h $(BACKEND_DIR)/entities.h $(BACKEND_DIR)/interactions.h $(BACKEND_DIR)/levels.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/top10.o: $(BACKEND_DIR)/top10.c $(BACKEND_DIR)/top10.h $(BACKEND_DIR)/config.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

# --- main.c ---
main.o: main.c $(BACKEND_DIR)/game.h $(FRONTEND_DIR)/frontend.h $(BACKEND_DIR)/config.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

# --- Frontend (Allegro) ---
allegro: $(BACKEND_OBJS) $(COMMON_OBJS) $(FRONTEND_DIR)/allegroFrontend.o
    $(CC) $(OPTIONS) $(BACKEND_OBJS) $(COMMON_OBJS) $(FRONTEND_DIR)/allegroFrontend.o -o pc $(ALLEGRO_FLAGS)

$(FRONTEND_DIR)/allegroFrontend.o: $(FRONTEND_DIR)/allegroFrontend.c $(FRONTEND_DIR)/frontend.h $(BACKEND_DIR)/game.h
    $(CC) $(OPTIONS) $(INCLUDES) $(ALLEGRO_FLAGS) -c $< -o $@

# --- Frontend Raspberry Pi ---
raspi: $(BACKEND_OBJS) $(COMMON_OBJS) $(RASPI_OBJS) $(RASPI_LIB_OBJS)
    $(CC) $(OPTIONS) $(BACKEND_OBJS) $(COMMON_OBJS) $(RASPI_OBJS) $(RASPI_LIB_OBJS) -o raspi -lpthread

$(RASPI_DIR)/raspiFrontend.o: $(RASPI_DIR)/raspiFrontend.c $(RASPI_DIR)/raspiFrontend.h $(RASPI_DIR)/raspiDraw.h $(BACKEND_DIR)/game.h $(RASPI_LIBS_DIR)/disdrv.h $(RASPI_LIBS_DIR)/joydrv.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(RASPI_DIR)/raspiDraw.o: $(RASPI_DIR)/raspiDraw.c $(RASPI_DIR)/raspiDraw.h $(RASPI_DIR)/raspiFrontend.h $(RASPI_LIBS_DIR)/disdrv.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(RASPI_LIBS_DIR)/disdrv.o: $(RASPI_LIBS_DIR)/disdrv.c $(RASPI_LIBS_DIR)/disdrv.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

$(RASPI_LIBS_DIR)/joydrv.o: $(RASPI_LIBS_DIR)/joydrv.c $(RASPI_LIBS_DIR)/joydrv.h
    $(CC) $(OPTIONS) $(INCLUDES) -c $< -o $@

# --- Limpieza ---
clean:
    rm -f pc raspi main.o $(BACKEND_DIR)/*.o $(FRONTEND_DIR)/*.o $(RASPI_DIR)/*.o $(RASPI_LIBS_DIR)/*.o