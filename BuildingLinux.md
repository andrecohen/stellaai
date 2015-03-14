# Building StellaAI in Linux #

StellaAI requires:

  * SDL
  * Lua
  * RL-Glue 3.0
  * RL-Glue C codec

Note: if you do not have root access to the machine you're installing StellaAI on, ask your system administrator to install SDL and Lua as well as their development packages. In some Linux distributions they are already installed by default, so they may not need to be installed. If they can't be installed for you, you may have no choice but to install the dependencies manually in your home directory.

### SDL ###

StellaAI has some dependencies. Stella requires SDL, which is easy to obtain using most modern Linux distributions by using the package managers (apt for Debian-based distros, yum for Redhat-based distros, emerge on Gentoo, etc.). You will need both the library and its development package usually suffixed with `-dev`.

If you can't find a standard package using the paclage managers, you should be able to download the SDL source and build/install it yourself. This is not recommended as it means you may have to manually install all of its dependencies, and all of the dependencies' dependencies, and so on. That's what package managers do for you.

### RL-Glue, C codec, and Lua ###

Lua is another standard package available from most Linux distributions as well. You will also need its development package.

Installing RL-Glue and the C codec is documented in [RLGluev3](RLGluev3.md) wiki page.

### Installation ###

Once the dependencies are installed, installing StellaAI is simple:

```
./configure
make
```

You don't need to install it using `make install` because the stella binary will be created and can be run from the build directory, but of course you can install it if you like. Note that if you do this, you'll have to install StellaAI every time it is recompiled. Note that using `--prefix=$HOME` allows you to install it in your home directory as a non-root user.

## Known problems ##

### Link to lua fails ###

At least on Ubuntu (may be true for other distros), there is no `liblua.so` symbolic link created for the lua 5.1 library upon installation. So when compiling, you may see something like:

```
/usr/bin/ld: cannot find -llua
```

So you need to create the symlink yourself. As root, do

```
cd /usr/lib
ln -s liblua5.1.so liblua.so
```

If you don't have root access, create the link in $HOME/lib instead.






