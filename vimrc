"change default <leader> key to ',' 
let mapleader=","

"map ,a to test if leader works
nmap <leader>a :echo("\<leader\> works! It is set to <leader>")<CR>

"map ,r to find current file in NERDTree
map <leader>r :NERDTreeFind<cr>
"map F3 to toggle NERDTree
nmap <silent> <F3> :NERDTreeToggle <cr>
"always show bookmarks
"let NERDTreeShowBookmarks=1

"map ,h to disable the hlsearch
"used in conjunction with set hlsearch
nmap <silent> ,h :nohlsearch<cr>
"toggle tagbar plugin
nmap <F8> :TagbarToggle<CR>

set expandtab
set shiftwidth=2
set softtabstop=2
set backspace=2
"enable line number
"set number
"enable incremental search
set incsearch
"enable search highlight
set hlsearch

" seoul256 (dark):
"   Range: 233(darkest) ~ 239 (lightest)
"   Default:237
let g:seoul256_background = 234
" seoul256 (light):
"   Range: 252 (darkest) ~ 256 (lightest)
"   Default:253
"let g:seoul256_background = 252

" apply color scheme
" file is in .vim/color
colo seoul256
colo seoul256-light

"switch between dark and light
"schemes of the two choices
"loaded above
set background=dark


"let explorer to always browse
"director of current file
autocmd BufEnter * lcd %:p:h

let g:ycm_key_list_select_completion = ['<TAB>', '<Down>']
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_autoclose_preview_window_after_insertion = 1

"automatically displays all buffers when there's only one tab open
let g:airline#extensions#tabline#enabled = 1
"change vim airline theme
"let g:airline_theme='solarized'

let g:EasyMotion_do_mapping = 0 " Disable default mappings

"map single <Leader> to easymotion prefix
"default map is double <Leader>
map <Leader> <Plug>(easymotion-prefix)

" Bi-directional find motion
" Jump to anywhere you want with minimal keystrokes, with just one key binding.
" `s{char}{label}`
  "nmap s <Plug>(easymotion-s)
nmap <silent> <F3> :NERDTreeToggle <cr>
" or
" `s{char}{char}{label}`
" Need one more keystroke, but on average, it may be more comfortable.
nmap s <Plug>(easymotion-s2)

" Turn on case insensitive feature
"let g:EasyMotion_smartcase = 1

" JK motions: Line motions
map <Leader>j <Plug>(easymotion-j)
map <Leader>k <Plug>(easymotion-k)

" map Enter to break the line
" without entering insert mode
map <CR> o<ESC>
" map S+Enter to break the line
" without entering insert mode
map <S-CR> O<ESC>

let g:user_emmet_install_global = 0
autocmd FileType html,css EmmetInstall


"vim-plug sections
call plug#begin()

Plug 'Valloric/YouCompleteMe'
Plug 'scrooloose/nerdtree'
Plug 'scrooloose/syntastic'
Plug 'scrooloose/nerdcommenter'
Plug 'kien/ctrlp.vim'
Plug 'easymotion/vim-easymotion'
Plug 'junegunn/seoul256.vim'
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
call plug#end()


"override LineNr color scheme in color shceme file
"only effective when number line is enabled
hi LineNr ctermfg=Grey ctermbg=DarkBlue

"Quick vim cheat sheat
"a - append after cursor
"J - join line below to the current line
". - repeat last command
"o - in NORMAL mode, go to the next line


"Useful vim commands for my reference
"1.copy from system clipboard
"  1.1 Insert Mode,Ctrl+Shift+V 
"2.comment multiple lines
"  2.1 Ctrl+V to select
"  2.2 Shift + I + <your comment character>
"  2.3 exit insert mode, it will be there
"3.comment multiple lines alternative
"  3.1 Ctrl+V to select
"  3.2 s/^/<your comment character>/g
"

