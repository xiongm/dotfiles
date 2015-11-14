map <silent> <F11> <Esc>:ClangCloseWindow<CR>

let g:clang_exec = 'clang'

"disable auto completion for vim-clang
let g:clang_auto = 0
" default 'longest' can not work with neocomplete
let g:clang_c_completeopt = 'menuone,preview'
let g:clang_cpp_completeopt = 'menuone,preview'

" disable diagnostic window by default
let g:clang_diagsopt = ''

