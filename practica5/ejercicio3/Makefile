#*****************************************************************
# File:   Makefile
# Author: Oarga Hategan, Alexandru - 718123
# Date:   noviembre 2015
# Coms:   Genera sockets, cliente y servidor para la práctica 5
#         Ejecutar como "make"
#         Para compilar en Hendrix (Solaris OS), descomentar
#         "#${SOCKETSFLAGS}"
#*****************************************************************

# ######## #
# COMANDOS #
# ######## #
RM = rm -f # Comando de limpieza
CC = g++ # Comando de compilacion

# ######################## # 
# VARIABLES GLOBALES       #
# Definimos:               #
#   * Librería de sockets  # 
#   * Cliente              #
#   * Servidor             #
#   * ServidorMulticliente #
# ######################## #
SOCKET=Socket
CLIENT=Cliente
SERVER=Servidor
MULTISERVER=ServidorMulticliente

imageDownloader=ImageDownloader
ANUNCIO=anuncio
MONITOR=monitor
# #################### #
# FLAGS DE COMPILACION #
# #################### #
CPPFLAGS=-I. -O2 -std=c++11 -lsockets # Flags compilacion
LDFLAGS=-pthread # Flags linkado threads
SOCKETSFLAGS=-lsocket -lnsl # Flags linkado sockets (Solaris SunOS)

CPPFLAGSIDOW=-I. -I/usr/local/include -O2 -std=c++11
LDFLAGSIDOW=-L/usr/X11R6/lib -L/usr/local/lib -lm -pthread -lcurl -lX11 

CPPFLAGSMON=-std=c++11 -pthread
CPPFLAGS11=-std=c++11 

.PHONY:all

all: ${CLIENT} ${SERVER}
#----------------------------------------------------------
${ANUNCIO}.o: ${ANUNCIO}.h ${ANUNCIO}.cpp 
	${CC} -c ${CPPFLAGS11} ${ANUNCIO}.cpp
#----------------------------------------------------------
${MONITOR}.o: ${MONITOR}.h ${MONITOR}.cpp 
	${CC} -c ${CPPFLAGSIDOW} ${MONITOR}.cpp
#----------------------------------------------------------
${imageDownloader}.o: ${imageDownloader}.h ${imageDownloader}.cpp
	${CC} -c ${CPPFLAGSIDOW} ${imageDownloader}.cpp
#----------------------------------------------------------
# SOCKETS
# Compilacion libreria de Sockets
${SOCKET}.o: ${SOCKET}.h ${SOCKET}.cpp
	${CC} -c ${CPPFLAGS} ${SOCKET}.cpp
#-----------------------------------------------------------
# CLIENTE
# Compilacion
${CLIENT}.o: ${CLIENT}.cpp
	${CC} -c ${CPPFLAGS} ${CLIENT}.cpp

# Linkado
${CLIENT}: ${SOCKET}.o ${CLIENT}.o  
	${CC} ${LDFLAGS} ${SOCKET}.o ${CLIENT}.o -o ${CLIENT} #${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------
# SERVIDOR
# Compilacion
${SERVER}.o: ${SERVER}.cpp 
	${CC} -c ${CPPFLAGS} ${SERVER}.cpp

# Linkado
${SERVER}: ${SOCKET}.o ${SERVER}.o ${imageDownloader}.o ${ANUNCIO}.o ${MONITOR}.o
	${CC} ${LDFLAGS} ${SOCKET}.o ${imageDownloader}.o ${ANUNCIO}.o ${MONITOR}.o ${SERVER}.o -o  ${SERVER} ${LDFLAGSIDOW}#${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------

# LIMPIEZA
clean:
	$(RM) ${ANUNCIO}.o
	$(RM) ${MONITOR}.o
	$(RM) ${SOCKET}.o
	$(RM) ${imageDownloader}.o
	$(RM) ${CLIENT} ${CLIENT}.o
	$(RM) ${SERVER} ${SERVER}.o
