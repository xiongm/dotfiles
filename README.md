Summary
===========

These are my personal dotfiles. feel free to use if you find them useful

Checkout
-----------
```console
$ cd ~
$ git clone https://github.com/xiongm/dotfiles.git
```

Install
-----------
To install vim/tmux/bash, use this helper script
```console
bash ./install.sh
```


Vim
-----------
```console
$ ln -sf $HOME/dotfiles/vimrc $HOME/.vimrc
$ ln -sf $HOME/dotfiles/vim $HOME/.vim
$ ln -sf $HOME/dotfiles/local/vimrc_local.home.ubuntu $HOME/.vimrc_local
```

Tmux
----------
```console
$ ln -sf $HOME/dotfiles/tmux.conf $HOME/.tmux.conf
$ ln -s $HOME/dotfiles/tmux $HOME/.tmux
```

Bash
-----------
```console
$ ln -sf $HOME/dotfiles/bash/ $HOME/.bash
echo "source ~/dotfiles/bashrc" >> $HOME/.bashrc
```

Emacs
-----------
```console
$ ln -sf $HOME/dotfiles/emacs $HOME/.emacs
```

Git
-----------
```console
$ mv $HOME/.gitconfig $HOME/.gitconfig_local
$ ln -sf $HOME/dotfiles/gitconfig $HOME/.gitconfig
```

