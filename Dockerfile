# To Build
# > docker build - < ./Dockerfile --no-cache -t mydockertest
# To Run
# > docker run -it mydockertest:latest

FROM ubuntu:18.04

ENV HOME /root
WORKDIR $HOME

RUN apt-get update \
   && apt-get install -y git vim make build-essential python3-dev cmake tmux zsh wget

RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

RUN git clone http://github.com/xiongm/dotfiles $HOME/dotfiles


RUN $HOME/dotfiles/install.sh

RUN cd $HOME/.vim/plugged/YouCompleteMe && python3 install.py --clang-completer


# start zsh
CMD [ "zsh" ]

