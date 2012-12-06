#!/bin/bash
# yong input method
# author dgod

usage()
{
	echo "yong-tool.sh [OPTION]"
	echo "  --install		install yong at system"
	echo "  --uninstall		uninstall yong from system"
	echo "  --select		select yong as default IM"
}

fedora_install()
{
	if [ -e /usr/bin/imsettings-start ] ; then
		CFG=/etc/X11/xinit/xinput.d/yong.conf

	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS=""
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
ICON="`pwd`/skin/tray1.png"
SHORT_DESC="yong"
PREFERENCE_PROGRAM="/usr/bin/yong-config"
EOF

	elif [ -e /etc/X11/xinit/xinputrc ] ; then
		CFG=/etc/X11/xinit/xinput.d/yong.conf

	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS=""
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
SHORT_DESC="yong"
PREFERENCE_PROGRAM="/usr/bin/yong-config"
EOF

	else
		CFG=/etc/X11/xinit/xinitrc.d/yong.sh

	cat >$CFG <<EOF
[ -z "$XIM" ] && export XIM=yong
[ -z "$XMODIFIERS" ] && export XMODIFIERS="@im=$XIM"
[ -z "$GTK_IM_MODULE" ] && export GTK_IM_MODULE=xim
[ -z "$QT_IM_MODULE" ] && export QT_IM_MODULE=xim
[ -z "$XIM_PROGRAM" ] && export XIM_PROGRAM=yong
[ -z "$XIM_ARGS" ] && export XIM_ARGS="-d"
$XIM_PROGRAM $XIM_ARGS
EOF

		chmod +x $CFG
	fi
}

fedora_uninstall()
{
	CFG=/etc/X11/xinit/xinput.d/yong.conf
	rm -rf $CFG
	CFG=/etc/X11/xinit/xinitrc.d/yong.sh
	rm -rf $CFG
}

fedora_select()
{
	CFG=/etc/X11/xinit/xinput.d/yong.conf
	if [ -e $CFG ] ; then
		ln -sf $CFG ~/.xinputrc
	fi
}

debian_install()
{
	CFG=/etc/X11/xinit/xinput.d/yong
	
	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS="-d"
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
SHORT_DESC="yong"
PREFERENCE_PROGRAM="/usr/bin/yong-config"
EOF

	update-alternatives \
	       	--install /etc/X11/xinit/xinput.d/zh_CN xinput-zh_CN \
       		/etc/X11/xinit/xinput.d/yong 20
}

debian_uninstall()
{
	CFG=/etc/X11/xinit/xinput.d/yong

	update-alternatives --remove xinput-zh_CN /etc/X11/xinit/xinput.d/yong
	rm -rf $CFG
}

debian_select()
{
	im-switch -s yong
}

suse_install()
{
	CFG=/etc/X11/xim.d/yong

	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS=""
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
SHORT_DESC="yong"
PREFERENCE_PROGRAM="/usr/bin/yong-config"
EOF

}

suse_uninstall()
{
	CFG=/etc/X11/xim.d/yong
	rm -rf $CFG
}

suse_select()
{
	CFG=~/.xim

	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS=""
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
yong -d
EOF

}

legacy_install()
{
	CFG=~/.xinitrc
}

legacy_uninstall()
{
	CFG=~/.xinitrc
}

legacy_select()
{
	CFG=~/.xinitrc
	echo "add IM config yourself"
}

mandriva_install()
{
	CFG=~/.i18n
}

mandriva_uninstall()
{
	CFG=~/.i18n
	rm -rf $CFG
}

mandriva_select()
{
	CFG=~/.i18n
	
	cat >$CFG <<EOF
XMODIFIERS="@im=yong"
XIM="yong"
XIM_PROGRAM="/usr/bin/yong"
XIM_ARGS=""
GTK_IM_MODULE="xim"
QT_IM_MODULE="xim"
EOF

}

ibus_install()
{
	IBUS_D=/usr/share/ibus/component
	if [ -d $IBUS_D ] ; then
		sed "s%\/usr\/share\/yong%`pwd`%" yong.xml >$IBUS_D/yong.xml
	fi
}

ibus_uninstall()
{
	if [ -f /usr/share/ibus/component/yong.xml ] ; then
		rm -f /usr/share/ibus/component/yong.xml
	fi
}

if [ $# != 1 ] ; then
	usage
	exit 0
fi

if [ -n "$DIST" ] ; then
	echo $DIST forced
else

	DIST=none

	# detect mandriva first, fo mandriva provides redhat-release
	if [ -f /etc/mandriva-release ] ; then
		DIST=mandriva
	elif [ -f /etc/fedora-release ] ; then
		DIST=fedora
	elif [ -f /etc/redhat-release ] ; then
		DIST=fedora
	elif [ -f /etc/centos-release ] ; then
		DIST=fedora
	elif [ -f /etc/redflag-release ] ; then
		DIST=fedora
	elif [ -f /etc/debian-release ] ; then
		DIST=debian
	elif [ -f /etc/SuSE-release ] ; then
		DIST=suse
	elif [ -f /etc/debian_version ] ; then
		DIST=debian
	elif [ `cat /etc/issue | grep Ubuntu | wc -l` != 0 ] ; then
		DIST=debian
	elif [ `cat /etc/issue | grep Mint | wc -l` != 0 ] ; then
		DIST=debian
	else
		DIST=legacy
	fi

	echo DIST $DIST found

	if [ $DIST = "none" ] ; then
		exit 1
	fi

fi

if [ $1 = "--install" ] ; then
	ln -sf `pwd`/yong /usr/bin/yong
	ln -sf `pwd`/yong-config /usr/bin/yong-config
	if [ `uname -m | grep 64 |wc -l` = 0 ] ; then
		ln -sf `pwd`/libl.so /usr/lib/libl.so
	else
		if [ -d  /usr/lib32 ] ; then
			ln -sf `pwd`/libl.so /usr/lib32/libl.so
		else
			ln -sf `pwd`/libl.so /usr/lib/libl.so
		fi
	fi
	ibus_install
	if [ $DIST = "fedora" ] ; then
		fedora_install
	elif [ $DIST = "debian" ] ; then
		debian_install
	elif [ $DIST = "suse" ] ; then
		suse_install
	elif [ $DIST = "mandriva" ] ; then
		mandriva_install
	elif [ $DIST = "legacy" ] ; then
		legacy_install
	fi
elif [ $1 = "--install64" ] ; then
	if [ `uname -m | grep 64 |wc -l` = 0 ] ; then
		echo "not 64bit system"
		exit 1
	fi 
	if ! [ -d l64 ] ; then
		echo "no l64 found"
		exit 1
	fi
	cp -f l64/* ./
	ln -sf `pwd`/yong /usr/bin/yong
	ln -sf `pwd`/yong-config /usr/bin/yong-config
	if [ -d  /usr/lib64 ] ; then
		ln -sf `pwd`/libl.so /usr/lib64/libl.so
	else
		ln -sf `pwd`/libl.so /usr/lib/libl.so
	fi
	ibus_install
	if [ $DIST = "fedora" ] ; then
		fedora_install
	elif [ $DIST = "debian" ] ; then
		debian_install
	elif [ $DIST = "suse" ] ; then
		suse_install
	elif [ $DIST = "mandriva" ] ; then
		mandriva_install
	elif [ $DIST = "legacy" ] ; then
		legacy_install
	fi
elif [ $1 = "--uninstall" ] ; then
	rm -rf /usr/bin/yong
	rm -rf /usr/bin/yong-config
	rm -rf /usr/lib/libl.so
	rm -rf /usr/lib32/libl.so
	rm -rf /usr/lib64/libl.so
	ibus_uninstall
	if [ $DIST = "fedora" ] ; then
		fedora_uninstall
	elif [ $DIST = "debian" ] ; then
		debian_uninstall
	elif [ $DIST = "suse" ] ; then
		suse_uninstall
	elif [ $DIST = "mandriva" ] ; then
		mandriva_uninstall
	elif [ $DIST = "legacy" ] ; then
		legacy_uninstall
	fi
elif [ $1 = "--select" ] ; then
	if [ $DIST = "fedora" ] ; then
		fedora_select
	elif [ $DIST = "debian" ] ; then
		debian_select
	elif [ $DIST = "suse" ] ; then
		suse_select
	elif [ $DIST = "mandriva" ] ; then
		mandriva_select
	elif [ $DIST = "legacy" ] ; then
		legacy_select
	fi
fi

echo "$1 Done"
