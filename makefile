# Compilador y opciones generales
CC := gcc
CFLAGS := -g -Wall

# Directorios del proyecto (Con las mayúsculas exactas de tus carpetas)
BACKEND_DIR := backend
FRONTEND_DIR := frontend
ALLEGRO_DIR := $(FRONTEND_DIR)/allegro
RASPI_DIR := $(FRONTEND_DIR)/raspi
RASPI_LIBS_DIR := $(RASPI_DIR)/libs

# Directorios donde se buscan los archivos .h
INCLUDES := \
	-I$(BACKEND_DIR) \
	-I$(ALLEGRO_DIR) \
	-I$(RASPI_DIR) \
	-I$(RASPI_LIBS_DIR)

# Allegro: flags de compilacion y de enlazado por separado
ALLEGRO_PACKAGES := \
	allegro-5 \
	allegro_main-5 \
	allegro_font-5 \
	allegro_ttf-5 \
	allegro_primitives-5 \
	allegro_image-5

ALLEGRO_CFLAGS := $(shell pkg-config --cflags $(ALLEGRO_PACKAGES))
ALLEGRO_LIBS := $(shell pkg-config --libs $(ALLEGRO_PACKAGES))

# Backend compartido por las dos plataformas
BACKEND_OBJS := \
	$(BACKEND_DIR)/game.o \
	$(BACKEND_DIR)/entities.o \
	$(BACKEND_DIR)/interactions.o \
	$(BACKEND_DIR)/levels.o \
	$(BACKEND_DIR)/top10.o \
	$(BACKEND_DIR)/errors.o

# main.c se compila de forma diferente para cada plataforma.
MAIN_ALLEGRO_OBJ := main-allegro.o
MAIN_RASPI_OBJ := main-raspi.o

# Frontend Allegro para PC
ALLEGRO_OBJS := \
	$(ALLEGRO_DIR)/allegroFrontend.o \
	$(ALLEGRO_DIR)/allegroMenus.o \
	$(ALLEGRO_DIR)/allegroPlay.o

# Frontend Raspberry Pi
RASPI_OBJS := \
	$(RASPI_DIR)/raspiFrontend.o \
	$(RASPI_DIR)/raspiDraw.o

# Objetos precompilados de las librerias especificas de Raspberry Pi
RASPI_LIB_OBJS := \
	$(RASPI_LIBS_DIR)/disdrv.o \
	$(RASPI_LIBS_DIR)/joydrv.o

.PHONY: all allegro raspi backend clean raspi-libs

all: allegro

# -----------------------------------------------------------------------------
# Backend
# -----------------------------------------------------------------------------

backend: $(BACKEND_OBJS)

$(BACKEND_DIR)/game.o: \
	$(BACKEND_DIR)/game.c \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/interactions.h \
	$(BACKEND_DIR)/levels.h \
	$(BACKEND_DIR)/top10.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/entities.o: \
	$(BACKEND_DIR)/entities.c \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/config.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/levels.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/interactions.o: \
	$(BACKEND_DIR)/interactions.c \
	$(BACKEND_DIR)/interactions.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/levels.o: \
	$(BACKEND_DIR)/levels.c \
	$(BACKEND_DIR)/levels.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/top10.o: \
	$(BACKEND_DIR)/top10.c \
	$(BACKEND_DIR)/top10.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BACKEND_DIR)/errors.o: \
	$(BACKEND_DIR)/errors.c \
	$(BACKEND_DIR)/errors.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -----------------------------------------------------------------------------
# main.c
# -----------------------------------------------------------------------------

$(MAIN_ALLEGRO_OBJ): \
	main.c \
	$(BACKEND_DIR)/game.h \
	$(ALLEGRO_DIR)/allegroFrontend.h \
	$(RASPI_DIR)/raspiFrontend.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ALLEGRO_CFLAGS) -include allegro5/allegro.h -c $< -o $@

$(MAIN_RASPI_OBJ): \
	main.c \
	$(BACKEND_DIR)/game.h \
	$(ALLEGRO_DIR)/allegroFrontend.h \
	$(RASPI_DIR)/raspiFrontend.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -----------------------------------------------------------------------------
# Frontend Allegro
# -----------------------------------------------------------------------------

allegro: $(BACKEND_OBJS) $(MAIN_ALLEGRO_OBJ) $(ALLEGRO_OBJS)
	$(CC) $(CFLAGS) $(BACKEND_OBJS) $(MAIN_ALLEGRO_OBJ) $(ALLEGRO_OBJS) -o frogger $(ALLEGRO_LIBS)

$(ALLEGRO_DIR)/allegroFrontend.o: \
	$(ALLEGRO_DIR)/allegroFrontend.c \
	$(ALLEGRO_DIR)/allegroFrontend.h \
	$(ALLEGRO_DIR)/allegroFrontendInternal.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ALLEGRO_CFLAGS) -c $< -o $@

$(ALLEGRO_DIR)/allegroMenus.o: \
	$(ALLEGRO_DIR)/allegroMenus.c \
	$(ALLEGRO_DIR)/allegroFrontendInternal.h \
	$(ALLEGRO_DIR)/allegroFrontend.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ALLEGRO_CFLAGS) -c $< -o $@

$(ALLEGRO_DIR)/allegroPlay.o: \
	$(ALLEGRO_DIR)/allegroPlay.c \
	$(ALLEGRO_DIR)/allegroFrontendInternal.h \
	$(BACKEND_DIR)/game.h \
	$(BACKEND_DIR)/entities.h \
	$(BACKEND_DIR)/config.h
	$(CC) $(CFLAGS) $(INCLUDES) $(ALLEGRO_CFLAGS) -c $< -o $@

# -----------------------------------------------------------------------------
# Frontend Raspberry Pi
# -----------------------------------------------------------------------------

raspi: $(BACKEND_OBJS) $(MAIN_RASPI_OBJ) $(RASPI_OBJS) $(RASPI_LIB_OBJS)
	$(CC) $(CFLAGS) $(BACKEND_OBJS) $(MAIN_RASPI_OBJ) $(RASPI_OBJS) $(RASPI_LIB_OBJS) -o frogger -lpthread

$(RASPI_DIR)/raspiFrontend.o: \
	$(RASPI_DIR)/raspiFrontend.c \
	$(RASPI_DIR)/raspiFrontend.h \
	$(RASPI_DIR)/raspiDraw.h \
	$(RASPI_LIBS_DIR)/disdrv.h \
	$(RASPI_LIBS_DIR)/joydrv.h \
	$(BACKEND_DIR)/game.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(RASPI_DIR)/raspiDraw.o: \
	$(RASPI_DIR)/raspiDraw.c \
	$(RASPI_DIR)/raspiDraw.h \
	$(RASPI_DIR)/raspiFrontend.h \
	$(RASPI_LIBS_DIR)/disdrv.h \
	$(BACKEND_DIR)/levels.h \
	$(BACKEND_DIR)/entities.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -----------------------------------------------------------------------------
# Pruebas de las librerias de Raspberry Pi
# -----------------------------------------------------------------------------

raspi-libs:
	$(MAKE) -C $(RASPI_LIBS_DIR)

# -----------------------------------------------------------------------------
# Limpieza
# -----------------------------------------------------------------------------

clean:
	rm -f frogger $(MAIN_ALLEGRO_OBJ) $(MAIN_RASPI_OBJ)
	rm -f $(BACKEND_DIR)/*.o
	rm -f $(ALLEGRO_DIR)/*.o
	rm -f $(RASPI_DIR)/*.o
