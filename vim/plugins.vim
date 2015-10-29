" This is the main plugin list, sourced by modules/plugins.vim
" Configuration goes in the appropriate modules/plugins/*.vim file.

Plug 'Valloric/YouCompleteMe'
Plug 'scrooloose/nerdtree'
Plug 'scrooloose/syntastic'
Plug 'scrooloose/nerdcommenter'
Plug 'kien/ctrlp.vim'
Plug 'easymotion/vim-easymotion'
Plug 'tpope/vim-sensible'
Plug 'tpope/vim-surround'
Plug 'bling/vim-airline'
Plug 'majutsushi/tagbar'
Plug 'pangloss/vim-javascript'
Plug 'tpope/vim-fugitive'
"Extra steps to get this plugin to work
"1.Install node and npm
" 1.1sudo apt-get install npm 
"2.Install tern with npm
" 2.1 cd .vim/plugged/tern_for_vim && npm install
"3.Make a soft link to node. Tern uses node
"  to start tern server, but on ubuntu 14.04
"  node doesn't exist, only nodejs, so you
"  need to create one
" 3.1 sudo ln -sf /usr/bin/nodejs /usr/bin/node
"4.Create .tern-project file
"{
"  "libs": [
"    "browser",
"    "underscore",
"    "jquery"
"  ],
"  "plugins": {
"  }
"}
"
Plug 'marijnh/tern_for_vim'
Plug 'Raimondi/delimitMate'
"use <Leader>y, to trigger
Plug 'mattn/emmet-vim'
Plug 'xolox/vim-misc'
Plug 'xolox/vim-session'
Plug 'kana/vim-altr'
Plug 'ervandew/supertab'
Plug 'mileszs/ack.vim'
" ctags management
" important notice
" if no tags need to be generated
" touch a .notags file in the root
Plug 'ludovicchabant/vim-gutentags'
Plug 'terryma/vim-multiple-cursors'
