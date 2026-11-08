#!/bin/sh
if [ -z "$1" ]; then
  echo "First argument '$1' is null"
  exit
fi
echo "call clean_directories.sh file"

echo "First arg: $1"
obj_dir=$1

# shellcheck disable=SC2034
file_o="AdressePostale.o"

if [ -d "$obj_dir" ]; then
  echo "$obj_dir exist."
  # shellcheck disable=SC2164
  cd "$obj_dir"
  # shellcheck disable=SC2035
  if [ -f "${file_o}" ]; then
     # shellcheck disable=SC2035
     rm *.o
  else
    echo "file *.o not found in $1 directory"
    exit
  fi

else
  echo "$obj_dir does not exist."
fi