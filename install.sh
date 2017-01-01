#!/bin/bash

function install_dot_file() {
  if [[ `readlink ~/$1` == ~/dotfiles/$2 ]]; then
    echo "$1 already setup"
  else
    if [[ -e ~/$1 ]]; then
      mv ~/$1 ~/$1.bkup
    fi
    ln -sf ~/dotfiles/$2 ~/$1
  fi
}

echo "Installing dot files"
install_dot_file .vimrc vimrc
install_dot_file .vim vim
install_dot_file .tmux.conf tmux.conf
install_dot_file .tmux tmux
install_dot_file .bash bash
echo "Done"
# emacs configs are not very actively maitnained
# so not enable it for now
#install_dot_file .emacs emacs

# install everything except for YouCompleteMe
# since YCM requires some manual installation
echo "Installing vim plugins"
vim +PlugInstall +qall
echo "Done"



