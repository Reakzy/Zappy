#!/bin/bash

REPO='zappy_gui'

echo -e "\033[0;32mCloning ${REPO}...\033[0m"

git clone git@git.epitech.eu:/wery_p/${REPO} &> /dev/null
if [ "$?" != "0" ]; then
    (>&2 echo -e "\033[0;31m[Error] Cannot clone repository ${REPO}.\n[Error] Check your internet connection or maybe the repository already exists!\033[0m")
    exit 1
fi

cd ${REPO};
if [ "$?" != "0" ]; then
    (>&2 echo -e "\033[0;31m[Error] Cannot change directory!\033[0m")
    exit 1
fi

echo -e "\033[0;32mInstalling ${REPO}...\033[0m"

make re &> /dev/null
if [ "$?" != "0" ]; then
    (>&2 echo -e "\033[0;31m[Error] ${REPO} compilation failed!\033[0m")
    exit 1
fi

echo -e "\033[0;32m[OK] ${REPO} installed!\033[0m"
