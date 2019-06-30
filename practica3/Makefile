#*****************************************************************
# File:   Makefile
# Author: PSCD-Unizar
# Date:   octubre 2016
# Coms:   Ejecutar "make" para compilar (o "make -f Makefile")
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# compilación y enlazado ("linkado")
CPPFLAGS=-I. -O2 -std=c++11 -fmax-errors=1 # opciones compilación
LDFLAGS=-pthread                           # opciones de "linkado"
#---------------------------------------------------------
# vars
EJEC = ejercicio2
SEM = Semaphore

all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o ${SEM}.o
	${CC} ${EJEC}.o ${SEM}.o -o ${EJEC} ${CPPFLAGS} ${LDFLAGS}

#---------------------------------------------------------
# compilar
${EJEC}.o: ${EJEC}.cpp ${SEM}.h ${SEM}.cpp
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}

${SEM}.o: ${SEM}.h ${SEM}.cpp
	${CC} -c ${SEM}.cpp ${CPPFLAGS}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${SEM}.o ${EJEC}.o ${EJEC}
