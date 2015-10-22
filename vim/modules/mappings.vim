"change default <leader> key to ',' 
let mapleader=","

"map ,a to test if leader works
nmap <leader>a :echo("\<leader\> works! It is set to <leader>")<CR>



"map ,h to disable the hlsearch
"used in conjunction with set hlsearch
nmap <silent> ,h :nohlsearch<cr>


" map Enter to break the line
" without entering insert mode
map <CR> o<ESC>
" map S+Enter to break the line
" without entering insert mode
map <S-CR> O<ESC>

" map F2 to save the file in normal mode
nmap <F2> :w<CR>
imap <F2> <Esc>:w<CR>a

" map Ctrl-s to save file. this might not 
" work due to c-s mapped to other system
" functions
nmap <Ctrl-s> :w<CR>
imap <Ctrl-s> <Esc>:w<CR>a

