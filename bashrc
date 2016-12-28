#!/bin/bash

[ -d ~/.bash ] || echo "Warning: no $HOME/.bash exists! Did you create symbolic link?"

for script in ~/.bash/*.sh
do
  [ -x "$script" ] || continue
  source $script
done

if [ -e ~/.bashrc_local ]
then
  source ~/.bashrc_local
fi

export PATH=$PATH:~/dotfiles/bin
#--------------------------------------------------
#WELCOME SCREEN
#--------------------------------------------------
if [[ $- == *i* ]]
then
  echo -ne "Hello,$USER. Today is "; date
  echo -ne "Sysinfo:";uptime ;
fi
