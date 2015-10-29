"change default <leader> key to ',' 
let mapleader=","

"map tn to new tab
nmap tn :tabnew<cr>
"map td to close tab
nmap td :tabclose<cr>
"H to move to previous tab 
nnoremap H gT
"L to move to next tab
nnoremap L gt

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

" in insert mode, insert a semi colon at
" the end of line. <C-o> here is used
" to input a single normal mode command
inoremap <leader>; <C-o>A;

" copy and cut
vmap <C-c> "+yi<ESC>
vmap <C-x> "+c<ESC>

" Ctrl-e to move the end of line in insert mode
inoremap <C-e> <C-o>$
" Ctrl-a to move the the first non blank text of the line in insert mode
inoremap <C-a> <C-o>^

