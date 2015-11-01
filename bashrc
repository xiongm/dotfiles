#!/bin/bash

[ -e ~/.bash ] || echo "no $HOME/.bash exists"

for script in ~/.bash/*.sh
do
  [ -x "$script" ] || continue
  source $script
done
  

#--------------------------------------------------
#WELCOME SCREEN
#--------------------------------------------------
echo -ne "Hello, ${LIGHTBLUE}$USER${NO_COLOR}. today is "; date
echo -ne "${BLUE}Sysinfo:";uptime ;
echo -ne "${NO_COLOR}";
