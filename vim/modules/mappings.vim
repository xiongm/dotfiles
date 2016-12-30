"change default <leader> key to ','
let mapleader=","

nnoremap n nzz

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

"map ,l to toggle line number
"useful when needing to copy
"something from vim window
nmap <silent> ,l :set nu!<cr>

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

" open last file
nnoremap <leader>b :e#<CR>

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

" in insert mode, press ctrl-o to insert new line
imap <C-o> <esc>o

" exit vim emacs way
nnoremap <C-x><C-c> :qa<CR>
inoremap <C-x><C-c> <ESC>:qa<CR>
" save current buffer
nnoremap <C-x><C-w> :w<CR>
inoremap <C-x><C-w> <ESC>:w<CR>
" exit current window
nnoremap <leader>q :q<CR>
nnoremap <leader>qa :qa<CR>

" remap gp to visually select last past/yanked text
" `[ goes to start of last changed text
" `] goes to end of last changed text
nnoremap gp `[v`]

"select all
nnoremap <leader>a ggvG

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

"search word at current cursor
nmap <F5> :Ack<Space><C-R><C-W>
"tagbar
nmap <F8> :TagbarToggle<CR>
"an alternative way to toggle tagbar
nmap <leader>ot :TagbarToggle<CR>
"map ,d to find current file in NERDTree
nmap <leader>d :NERDTreeFind<cr>
",v to vertical split window
nmap <leader>v :vsplit<cr>
",s to split window
nmap <leader>s :split<cr>

"place cusor on any word, and press
"<leader>g will put that word to
"command line with global replace
"syntax
vmap <leader>r :s/<C-R><C-W>//gc<left><left><left>
nmap  <leader>r :%s/<C-R><C-W>//gc<left><left><left>

" For local replace
nnoremap gr gd[{V%::s/<C-R>///gc<left><left><left>

" For global replace
nnoremap gR gD:%s/<C-R>///gc<left><left><left>

"open quicklist window
nnoremap <leader>co :Copen<CR>
"close quicklist window
nnoremap <leader>cq :ccl<CR>

" just a short cut to do argdo
nnoremap <leader>ad :argdo %s/<C-R><C-W>//ge \| update<left><left><left><left><left><left><left><left><left><left><left><left>

"commands to edit vim config (and tmux's since tmux is so popular with vim)
:command! EditMyMapping :e ~/.vim/modules/mappings.vim
:command! EditMyCore :e ~/.vim/modules/core.vim
:command! EditMyPlugin :e ~/.vim/plugins.vim
:command! EditMyVimHelp :e ~/.vim/README
:command! EditMyLocalVim :e ~/.vimrc_local



:command! EditMyTmuxHelp :e ~/dotfiles/tmux/README
:command! GetFullFileName :echo expand('%:p')

" source vimrc file
:command! ReloadMyVim :so $MYVIMRC

" YouCompleteMe mappings
nnoremap <leader>gd :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
:command! Compile :YcmDiags
:command! FixIt :YcmCompleter FixIt

"open definition in new tab
map <C-\> :tab split<CR>:exec("tag ".expand("<cword>"))<CR>


"help Qargs command to set the arglist to contain each of the files
"referenced by quicklist
"this is especially helpful after using ack to find references
"and you want to do a search and replace across files
command! -nargs=0 -bar Qargs execute 'args' QuickfixFilenames()
function! QuickfixFilenames()
  " Building a hash ensures we get each buffer only once
  let buffer_numbers = {}
  for quickfix_item in getqflist()
    let bufnr = quickfix_item['bufnr']
    " Lines without files will appear as bufnr=0
    if bufnr > 0
      let buffer_numbers[bufnr] = bufname(bufnr)
    endif
  endfor
  return join(map(values(buffer_numbers),'fnameescape(v:val)'))
endfunction


" DISABLED

"when popup menu is visible, the white space will
"simply select the highlighted menu
"helps tab auto-completion
"Note: this doesn't seem to work very well w/
"YouCompleteMe. So disable it for now
"inoremap <expr> <Space> pumvisible() ? "\<C-y>" : " "


