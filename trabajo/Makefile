#*****************************************************************
# File:   Makefile
# Author: PSCD-Unizar
# Date:   Enero 2017
# Coms:   Genera sockets, cliente, servidor, image, monitor y anuncio para la práctica 5
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
#	* ImageDonloader	   #
# ######################## #
SOCKET=Socket
CLIENT=Cliente
SERVER=Servidor
MULTISERVER=ServidorMulticliente
IMAGE = ImageDownloader
ARBOL_RES = arbolRestaurantes
ARBOL_MON = arbolMonumentos
MONITOR = monitorClientes
PAR = par
LATLONG = LatLong-UTMconversion

# #################### #
# FLAGS DE COMPILACION #
# #################### #
CPPFLAGS=-I. -I/usr/local/include -O2 -std=c++11 -lsockets # Flags compilacion
LDFLAGS=-L/usr/X11R6/lib -L/usr/local/lib -lm -lpthread -lcurl # Flags linkado threads
LATFLAGS = -fmax-errors=1 -Werror
SOCKETSFLAGS=-lsocket -lnsl # Flags linkado sockets (Solaris SunOS)

.PHONY:all

all: ${CLIENT} ${IMAGE} ${SERVER} 

# SOCKETS
# Compilacion libreria de Sockets
${SOCKET}.o: ${SOCKET}.h ${SOCKET}.cpp
	${CC} -c ${CPPFLAGS} ${SOCKET}.cpp
#-----------------------------------------------------------
# ARBOL_RES
#Compilacion del arbol de restaurantes
${ARBOL_RES}.o: ${ARBOL_RES}.h ${ARBOL_RES}.cpp
	${CC} -c ${CPPFLAGS} ${ARBOL_RES}.cpp 
	
#-----------------------------------------------------------
# ARBOL_MON
#Compilacion del arbol de monumentos
${ARBOL_MON}.o: ${ARBOL_MON}.h ${ARBOL_MON}.cpp
	${CC} -c ${CPPFLAGS} ${ARBOL_MON}.cpp 
	
#-----------------------------------------------------------
# LATLONG
#Compilacion del convertidor de latitud, longitud
${LATLONG}.o: ${LATLONG}.h ${LATLONG}.cpp
	${CC} -c ${CPPFLAGS} ${LATFLAGS} ${LATLONG}.cpp 
	
#-----------------------------------------------------------
# MONITOR
#Compilacion del monitor de clientes
${MONITOR}.o: ${MONITOR}.h ${MONITOR}.cpp
	${CC} -c ${CPPFLAGS} ${LDFLAGS} ${MONITOR}.cpp 
	
#-----------------------------------------------------------
# PAR
#Compilacion del par
${PAR}.o: ${PAR}.h ${PAR}.cpp
	${CC} -c ${CPPFLAGS} ${PAR}.cpp 
	
#-----------------------------------------------------------
# CLIENTE
# Compilacion
${CLIENT}.o: ${CLIENT}.cpp
	${CC} -c ${CPPFLAGS} ${CLIENT}.cpp

# Linkado
${CLIENT}: ${SOCKET}.o ${LATLONG}.o ${CLIENT}.o  
	${CC} ${LDFLAGS} ${SOCKET}.o ${LATLONG}.o ${CLIENT}.o -o ${CLIENT} ${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------
# IMAGE DOWNLOADER
${IMAGE}: ${IMAGE}.h ${IMAGE}.cpp
	${CC} -c ${CPPFLAGS} ${IMAGE}.cpp
#-----------------------------------------------------------
# SERVIDOR
# Compilacion
${SERVER}.o: ${SERVER}.cpp 
	${CC} -c ${CPPFLAGS} ${SERVER}.cpp

# Linkado
${SERVER}: ${SOCKET}.o ${SERVER}.o ${IMAGE}.o ${ARBOL_RES}.o ${ARBOL_MON}.o ${MONITOR}.o ${PAR}.o
	${CC} ${LDFLAGS}  ${IMAGE}.o ${SOCKET}.o ${ARBOL_RES}.o ${ARBOL_MON}.o ${MONITOR}.o ${PAR}.o ${SERVER}.o -o ${SERVER} ${SOCKETSFLAGS} #descomentar para Hendrix
#-----------------------------------------------------------



# LIMPIEZA
clean:
	$(RM) ${SOCKET}.o
	$(RM) ${CLIENT} ${CLIENT}.o
	$(RM) ${SERVER} ${SERVER}.o
