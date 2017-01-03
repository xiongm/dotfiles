#!/bin/bash
# install dotfiles
# you might want to consider build latest vim from source first
# refer to build_vim.sh

function install_dot_file() {
  echo "Installing $1"
  if [[ `readlink -m ~/$1` == ~/dotfiles/$2 ]]; then
    echo "$1 already installed"
  else
    if [[ -e ~/$1 ]]; then
      mv ~/$1 ~/$1.bkup
    fi
    ln -sf ~/dotfiles/$2 ~/$1
    echo "Done"
  fi
}

install_dot_file .vimrc vimrc
ln -sf ~/dotfiles/local/vimrc_local ~/.vimrc_local
install_dot_file .vim vim
install_dot_file .tmux.conf tmux.conf
install_dot_file .tmux tmux
install_dot_file .bash bash

source_str="source ~/dotfiles/bashrc"
if !(grep -Fxq "$source_str" ~/.bashrc); then
 echo $source_str >> ~/.bashrc
fi

# emacs configs are not very actively maitnained
# so not enable it for now
#install_dot_file .emacs emacs

# install everything except for YouCompleteMe
# since YCM requires some manual installation
echo "Installing vim plugins"
vim +PlugInstall +qall
echo "Done"



