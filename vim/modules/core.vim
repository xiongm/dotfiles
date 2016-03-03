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
"swp file is annoying to me
set noswapfile

let $BASH_ENV="~/.bashrc"

colo molokai
"let g:rehash256 = 1

if has('gui_running')
  set guioptions+=c
else
  " use degraded 256 colorscheme for term use
  let g:solarized_termcolors=256
endif

set background=dark

"molokai's matchparen scheme drives me crazy programming c++
"so im changing it to just use underscore
:hi MatchParen cterm=underline ctermbg=none ctermfg=none


"let explorer to always browse
"directory of current file
autocmd BufEnter * lcd %:p:h

"we need vim-snippets but we don't want to use
"the snippets that come with it
let g:UltiSnipsSnippetDirectories=["MyUltiSnips"]

"Quick vim cheat sheat
"a - append after cursor
"J - join line below to the current line
". - repeat last command
"o - in NORMAL mode, go to the next line
"G - end of file
"gg - beginning of file


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

