"change default <leader> key to ',' 
let mapleader=","

"unmap Q currently mapped to ex mode
"its very annoying
map Q <Nop>

"map tn to new tab
nmap <leader>tn :tabnew<cr>
"map td to close tab
nmap <leader>td :tabclose<cr>
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

" map Ctrl-s to save file. this might not 
" work due to c-s mapped to other system
" functions
nmap <Ctrl-s> :w<CR>
imap <Ctrl-s> <Esc>:w<CR>a

" in insert mode, insert a semi colon at
" the end of line. <C-o> here is used
" to input a single normal mode command
inoremap <leader>; <C-o>A;
" quick way to insert ; for normal mode
nnoremap <leader>; A;<ESC>

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
nnoremap <leader>qa :qa<CR>

" source vimrc file
nnoremap <leader>v :so $MYVIMRC<CR>

"select all
nnoremap <leader>a ggVG

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

" map F2 to save the file in normal mode
nmap <F2> :w<CR>
imap <F2> <Esc>:w<CR>
"NERDTree
nmap <silent> <F3> :NERDTreeToggle <cr>
"vim-session 
nmap <F4> :OpenSession<Space>
"search word at current cursor
nmap <F5> :Ack<Space><C-R><C-W>
"tagbar
nmap <F8> :TagbarToggle<CR>
"an alternative way to toggle tagbar
nmap <leader>ot :TagbarToggle<CR>



"map ,r to find current file in NERDTree
map <leader>r :NERDTreeFind<cr>

"place cusor on any word, and press
"<leader>g will put that word to 
"command line with global replace
"syntax 
vmap <leader>g :s/<C-R><C-W>/
nmap  <leader>g :%s/<C-R><C-W>/

"close quicklist window
nnoremap <leader>cq :ccl<CR>

"shortcut to edit this file
:command! EditMyMapping :e ~/.vim/modules/mappings.vim
<<<<<<< HEAD

"open definition in new tab
map <C-\> :tab split<CR>:exec("tag ".expand("<cword>"))<CR>
=======
>>>>>>> 4fdc083ded168020caeb76d5f1e5c0fb2ecbb0c5

" DISABLED 

"when popup menu is visible, the white space will
"simply select the highlighted menu
"helps tab auto-completion
"Note: this doesn't seem to work very well w/
"YouCompleteMe. So disable it for now
"inoremap <expr> <Space> pumvisible() ? "\<C-y>" : " "


