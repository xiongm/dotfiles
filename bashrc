#!/bin/bash

[ -d ~/.bash ] || echo "Warning: no $HOME/.bash exists! Did you create symbolic link?" 

for script in ~/.bash/*.sh
do
  [ -x "$script" ] || continue
  source $script
done
  

#--------------------------------------------------
#WELCOME SCREEN
#--------------------------------------------------
if [[ $- == *i* ]]
then
  echo -ne "Hello,${LIGHTBLUE}$USER${NO_COLOR}. Today is "; date
  echo -ne "${BLUE}Sysinfo:";uptime ;
  echo -ne "${NO_COLOR}";
fi
