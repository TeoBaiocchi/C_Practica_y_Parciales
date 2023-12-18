#!/bin/bash

[[ ! $1 =~ ^[0-9]{2}-[0-9]{2}-[0-9]{4}$ ]] && echo "El formato de ingreso debe ser dd-mm-yyyy" && exit 1

MIN=153
MAX=8671
RESTANTES=$((RANDOM%($MAX-$MIN+1)+$MIN))
# ${'variable':'desde donde comienza':'cuantos caracteres leer'}
DIA=${1:0:2}
MES=${1:3:2}
ANIO=${1:6:4}
FECHA=${ANIO}${MES}${DIA}
[[ ! $(date -d "$FECHA" 2>/dev/null) ]] && echo "Fecha invalida" && exit 1

DIAS=$(( ($(date -d "00:00" +%s) - $(date +%s -ud $FECHA)) / 3600 / 24 ))

echo "Usted lleva vivo $DIAS dias, y le quedan $RESTANTES. Aprovechelos bien!"
