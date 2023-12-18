#!/bin/bash

read -p "Ingrese un directorio: " DIRECTORIO
[[ ! -d $DIRECTORIO ]] && echo "Eso no estaria siendo un directorio." && exit 1

read -p "Ingrese una extension: " EXTENSION

read -p "Ingrese patron de renombre: " PATRON
ARCHIVOS=$(ls $DIRECTORIO/*.$EXTENSION)

CONTADOR=1
for ARCHIVO in $ARCHIVOS
do
  mv ${ARCHIVO} "$DIRECTORIO/${PATRON}${CONTADOR}"."${EXTENSION}"
  ((CONTADOR++))
  echo "Se renombra ${ARCHIVO} a $DIRECTORIO/${PATRON}${CONTADOR}"."${EXTENSION}"
done

echo "Se muestra contenido:"
echo $(ls $DIRECTORIO/*.$EXTENSION) 