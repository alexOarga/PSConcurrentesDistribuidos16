#*****************************************************************
# File:   Makefile
# Author: PSCD-Unizar
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

# #################### #
# FLAGS DE COMPILACION #
# #################### #
CPPFLAGS=-I. -O2 -pthread -std=c++11 -lsockets # Flags compilacion
LDFLAGS=-pthread # Flags linkado threads
SOCKETSFLAGS=-lsocket -lnsl # Flags linkado sockets (Solaris SunOS)

.PHONY:all

all: ${CLIENT} ${SERVER}

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
	${CC} ${LDFLAGS} ${SOCKET}.o ${CLIENT}.o -o ${CLIENT} ${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------
# SERVIDOR
# Compilacion
${SERVER}.o: ${SERVER}.cpp 
	${CC} -c ${CPPFLAGS} ${SERVER}.cpp

# Linkado
${SERVER}: ${SOCKET}.o ${SERVER}.o
	${CC} ${LDFLAGS} ${SOCKET}.o ${SERVER}.o -o ${SERVER} ${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------

# LIMPIEZA
clean:
	$(RM) ${SOCKET}.o
	$(RM) ${CLIENT} ${CLIENT}.o
	$(RM) ${SERVER} ${SERVER}.o
