" associate A with altr file switch
command! A call altr#forward()
" add ipp and tpp to list of cpp files
if exists('altr#define')
  call altr#define('%.c', '%.cpp', '%.cc', '%.m', '%.mm', '%.h', '%.hpp', '%.ipp', '%.tpp')
endif
