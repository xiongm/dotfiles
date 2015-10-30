set expandtab
set shiftwidth=2
set softtabstop=2
set backspace=2
"enable line number
set number
"enable cursor line highlight
set cursorline
"enable incremental search
set incsearch
"enable search highlight
set hlsearch
"confirm file save instead of unsuccesful
"quit
set confirm

colo solarized

if has('gui_running')
else
  " use degraded 256 colorscheme for term use
  let g:solarized_termcolors=256
  set guioptions+=c
endif

set background=dark


"let explorer to always browse
"directory of current file
autocmd BufEnter * lcd %:p:h


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

