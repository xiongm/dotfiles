
"automatically displays all buffers when there's only one tab open
"let g:airline#extensions#tabline#enabled = 1
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
" or
" `s{char}{char}{label}`
" Need one more keystroke, but on average, it may be more comfortable.
nmap s <Plug>(easymotion-s2)
" replace vim default search with easymotion search
map  / <Plug>(easymotion-sn)

" Turn on case insensitive feature
"let g:EasyMotion_smartcase = 1

" JK motions: Line motions
map <Leader>j <Plug>(easymotion-j)
map <Leader>k <Plug>(easymotion-k)

