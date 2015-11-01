" enable auto load/save of vim-session
let g:session_autosave = 'yes'
let g:session_autoload = 'yes'
" don't save color scheme or fonts
let g:session_persist_colors = 0
let g:session_persist_font = 0
" disable all session locking
let g:session_lock_enabled = 0
set sessionoptions-=buffers
" default to last session used
let g:session_default_to_last = 1
