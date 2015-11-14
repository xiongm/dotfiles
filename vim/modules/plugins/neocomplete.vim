
" Disable AutoComplPop.
let g:acp_enableAtStartup = 0
" Use neocomplete.
let g:neocomplete#enable_at_startup = 1

" use neocomplete
" input patterns
if !exists('g:neocomplete#force_omni_input_patterns')
  let g:neocomplete#force_omni_input_patterns = {}
endif

" for c and c++
let g:neocomplete#force_omni_input_patterns.c =  '[^.[:digit:] *\t]\%(\.\|->\)\w*'
let g:neocomplete#force_omni_input_patterns.cpp =  '[^.[:digit:] *\t]\%(\.\|->\)\w*\|\h\w*::\w*'


" Plugin key-mappings.
inoremap <expr><C-g>     neocomplete#undo_completion()
inoremap <expr><C-l>     neocomplete#complete_common_string()

" this is a neoinclude setting
" we are using gutentags, so ctags
" is not needed here. it slows
" down auto-completion for large
" projects
" change this to ctags if you 
" want to enable it
let g:neoinclude#ctags_command = ''
