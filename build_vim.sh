set -x
echo "Begin installing vim"
echo "Downloading vim build dependencies"
echo "Installing git"
sudo apt-get install git
git clone https://github.com/vim/vim.git
# Compile vim:
cd vim
echo "Running configuration, preparing to compile vim"

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
  --enable-perlinterp=yes \
  --enable-luainterp=yes \
  --enable-gui=gtk2 \
  --enable-cscope \
  --prefix=/usr

echo "Compiling vim"
make && sudo make install
cd ..
echo "Cleanup..."
rm -fr vim
echo "Completed vim installation"
