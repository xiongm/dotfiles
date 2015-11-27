export TERM='xterm-256color'
export EDITOR=vim
export HISTTIMEFORMAT="%h/%d - %H:%M:%S "

# disable start/stop flow control
# essentially disabling ctrl-q/ctrl-s
# because they are annoying
stty -ixon

if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

