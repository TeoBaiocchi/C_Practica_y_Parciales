#!/bin/bash

[[ ! -e "$1" ]] && echo "El archivo no existe" && exit -1

CANTIDADLINEAS=$(wc -l < "$1")
ORIGINAL=$(tail -n 1 "$1")
INVERTIIDA=$(tail -n 2 "$1" | head -n 1)
CONTADOR=2

while [[ $CONTADOR -le $CANTIDADLINEAS ]]
do
  ((CONTADOR++))
  echo $ORIGINAL
  ORIGINAL=$INVERTIIDA
  INVERTIIDA=$(tail -n $CONTADOR "$1" | head -n 1)
done

echo $ORIGINAL
