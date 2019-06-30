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
#CC = /usr/bin/g++         # compilador
CC = g++         # compilador

#---------------------------------------------------------
# compilación y enlazado ("linkado"). Accede a las librerías de opencv requeridas

CPPFLAGS=`env PKG_CONFIG_PATH=/usr/local/opencv2/lib/pkgconfig pkg-config opencv --cflags`
LDFLAGS=`env PKG_CONFIG_PATH=/usr/local/opencv2/lib/pkgconfig pkg-config opencv --libs` -pthread


#---------------------------------------------------------
# vars
EJEC = imagen

all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o
	${CC} ${CPPFLAGS} ${EJEC}.o -o ${EJEC} ${LDFLAGS}

#---------------------------------------------------------
# compilar
${EJEC}.o: ${EJEC}.cpp
	${CC} ${CPPFLAGS} -c ${EJEC}.cpp 

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${EJEC}


