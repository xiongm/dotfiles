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
"molokai's visual selection color scheme is not good
"override to just use white
:hi Visual   ctermfg=0    ctermbg=222

"had to add this line for some environment
"otherwise the background color is not quite right
hi Normal ctermbg=NONE

"let explorer to always browse
"directory of current file
autocmd BufEnter * lcd %:p:h

"we need vim-snippets but we don't want to use
"the snippets that come with it
let g:UltiSnipsSnippetDirectories=["MyUltiSnips"]

"indent=2 for python
"autocmd FileType python setlocal sw=2 sts=2 expandtab

"Quick vim cheat sheat
" refer to README

