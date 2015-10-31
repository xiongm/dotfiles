"change default <leader> key to ',' 
let mapleader=","

"unmap Q currently mapped to ex mode
"its very annoying
map Q <Nop>

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
" end of line in normal mode
nnoremap <C-e> $
" non blank text of line in normal mode
nnoremap <C-a> ^

" exit vim emacs way
nnoremap <C-x><C-c> :qa<CR>
inoremap <C-x><C-c> <ESC>:qa<CR>
" save current buffer
nnoremap <C-x><C-w> :w<CR>
inoremap <C-x><C-w> <ESC>:w<CR>
" exit current window
nnoremap <leader>q :q<CR>

" source vimrc file
nnoremap <leader>v :so $MYVIMRC<CR>

"when popup menu is visible, the white space will
"simply select the highlighted menu
"helps tab auto-completion
inoremap <expr> <Space> pumvisible() ? "\<C-y>" : " "


"ctrl+kjhl navigation between windows
nmap <silent> <C-h> :wincmd h<CR>
nmap <silent> <C-j> :wincmd j<CR>
nmap <silent> <C-k> :wincmd k<CR>
nmap <silent> <C-l> :wincmd l<CR>

"resize window using Alt + arrow
nmap <silent> <A-Up> <C-W>+
nmap <silent> <A-Down> <C-W>-
nmap <silent> <A-Left> <C-W><
nmap <silent> <A-Right> <C-W>>
