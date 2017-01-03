read -p "This operation will replace existing vim, type 'y' to continue:" answer
if [[ $answer != 'y' ]]; then
 exit 0
fi
set -x
sudo apt-get -y install libncurses5-dev libgnome2-dev libgnomeui-dev \
    libgtk2.0-dev libatk1.0-dev libbonoboui2-dev \
    libcairo2-dev libx11-dev libxpm-dev libxt-dev python-dev \
    python3-dev ruby-dev libperl-dev git
mkdir -p build
cd build
git clone https://github.com/vim/vim.git
# Compile vim:
cd vim
# ubuntu 16.04 forbids building both python2 and python3
# so you have to choose one.
# leave the option for future reference

#--enable-python3interp=yes \
#--with-python3-config-dir=/usr/lib/python3.5/config* \

./configure \
  --prefix=/usr \
  --with-features=huge \
  --enable-multibyte \
  --enable-rubyinterp=yes \
  --enable-pythoninterp=yes \
  --with-python-config-dir=/usr/lib/python2.7/config* \
  --enable-gui=gtk2 \
  --enable-cscope \
  --prefix=/usr

echo "Compiling vim"
make && sudo make install
cd ../..
echo "Cleanup..."
rm -fr build
echo "Completed vim installation"
