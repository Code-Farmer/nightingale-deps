#!/bin/bash

set -e

export DIR="$(cd -P "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export SB_VENDOR_BINARIES_CO_ROOT=$DIR
export SB_VENDOR_BUILD_ROOT=$DIR

# Currently, we build both debug and release, which takes a lot longer,
# especially on xulrunner... TODO: make it optional to build debug

rm -rf build
mkdir build

case $OSTYPE in
	# linux is easy, as all it requires right now is xulrunner, sqlite, and taglib
	# we'll get to a point where this is unnecessary on linux altogether in the future
	linux*)
		export CXXFLAGS="-fpermissive"
		export CFLAGS=$CXXFLAGS
		export CCFLAGS=$CXXFLAGS

		if [ ! -d "linux-$(uname -m)" ]; then
			mkdir -p "linux-$(uname -m)"
			mkdir -p "checkout/linux-$(uname -m)"
			mkdir "build"
		fi

		cd "xulrunner-1.9.2"
		# fix for kernels > 3.X on versions of xul without security setup for them
		if [ ! -f mozilla/security/coreconf/Linux$(uname -r|sed -e 's/\-.*//'|grep -o "[0-9]\.[0-9]").mk ]; then
			ln -s $(pwd)/mozilla/security/coreconf/Linux2.6.mk $(pwd)/mozilla/security/coreconf/Linux$(uname -r|sed -e 's/\-.*//'|grep -o "[0-9]\.[0-9]").mk
		fi
		cd ../

		echo -e "Building xulrunner 1.9.2...\n"
		make -C xulrunner-1.9.2 -f Makefile.songbird xr-all

		echo -e "Building sqlite...\n"
		make -C sqlite -f Makefile.songbird
		
		echo -e "Building taglib...\n"
		make -C taglib -f Makefile.songbird
		
		echo -e "Done! Provided there were no errors, you can \nfind your deps in the linux-$(uname -m) directory. Copy or link it into [nightingale build directory]/dependencies and you're ready to build!\n"
	;;
    darwin*)
		# on OSX, we want 32 bit builds
		arch_flags="-m32 -arch i386"
		export CFLAGS="$arch_flags"
		export CXXFLAGS="$arch_flags"
		export CPPFLAGS="$arch_flags"
		export LDFLAGS="$arch_flags"
		export OBJCFLAGS="$arch_flags"

		if [ ! -d "macosx-i686" ]; then
			mkdir -p "macosx-i686"
			mkdir -p "checkout/macosx-i686"
			mkdir "build"
		fi

        echo -e "Building gettext..."
        make CC=gcc CXX=g++ -C gettext -f Makefile.songbird
        echo -e "Building glib..."
        make CC=gcc CXX=g++ -C glib -f Makefile.songbird
        echo -e "Building libidl..."
        make CC=gcc CXX=g++ -C libidl -f Makefile.songbird
        echo -e "Building flac..."
        make CC=gcc CXX=g++ -C flac -f Makefile.songbird
        echo -e "Building libjpeg..."
        make CC=gcc CXX=g++ -C libjpeg -f Makefile.songbird
        echo -e "libogg gettext..."
        make CC=gcc CXX=g++ -C libogg -f Makefile.songbird
        echo -e "Building libtheora..."
        make CC=gcc CXX=g++ -C libtheora -f Makefile.songbird
        echo -e "Building libtool..."
        make CC=gcc CXX=g++ -C libtool -f Makefile.songbird
        echo -e "Building libvorbis..."        
        make CC=gcc CXX=g++ -C libvorbis -f Makefile.songbird
        echo -e "Building sqlite..."
        make CC=gcc CXX=g++ -C sqlite -f Makefile.songbird
        echo -e "Building taglib..."        
        make CC=gcc CXX=g++ -C taglib -f Makefile.songbird

        echo -e "Building xulrunner and crossing our fingers..." xr-build-debug
        make CC=gcc-4.2 CXX=g++-4.2 -C xulrunner-1.9.2 -f Makefile.songbird xr-all
        echo -e "Building gstreamer bits..."
        make CC=gcc-4.2 CXX=g++-4.2 -C gstreamer -f Makefile.songbird
        echo -e "Building gst plugins...here's hoping these all build!"
        make CC=gcc-4.2 CXX=g++-4.2 -C gst-plugins-base -f Makefile.songbird
        make CC=gcc-4.2 CXX=g++-4.2 -C gst-plugins-good -f Makefile.songbird
        make CC=gcc-4.2 CXX=g++-4.2 -C gst-plugins-bad -f Makefile.songbird
        make CC=gcc-4.2 CXX=g++-4.2 -C gst-plugins-ugly -f Makefile.songbird
        echo "Done!"

    ;;
    msys*)
		if [ ! -d "windows-i686-msvc8" ]; then
			mkdir -p "windows-i686-msvc8"
			mkdir -p "checkout/windows-i686-msvc8"
			mkdir "build"
		fi

		make
    ;;
	*)
		echo "Lazy buildscript for your OS coming soon."
	;;
esac
