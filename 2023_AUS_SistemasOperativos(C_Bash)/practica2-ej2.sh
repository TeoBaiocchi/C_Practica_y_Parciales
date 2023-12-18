#!/bin/bash

[[ ! $1 =~ ^[0-9]{2}-[0-9]{2}-[0-9]{4}$ ]] && echo "El formato de ingreso debe ser dd-mm-yyyy" && exit 1


# ${'variable':'desde donde comienza':'cuantos caracteres leer'}
DIA=${1:0:2}
MES=${1:3:2}
ANIO=${1:6:4}
OUTPUT=$(date -d "${ANIO}${MES}${DIA}")
# En caso de error, date lo devolvera, y el case salta al default
case ${OUTPUT:0:3} in

"Mon")
 echo "Ese dia cayo Lunes"
 ;;
"Tue")
 echo "Ese dia cayo Martes"
 ;;
"Wed")
 echo "Ese dia cayo Miercoles"
 ;;
"Thu")
 echo "Ese dia cayo Jueves"
 ;;
"Fri")
 echo "Ese dia cayo Viernes"
 ;;
"Sat")
 echo "Ese dia cayo Sabado"
 ;;
"Sun") 
  echo "Ese dia cayo Domingo"
  ;;
*)
  echo "La fecha ingresada no es valida."
  exit 1
  ;;
esac
exit 0