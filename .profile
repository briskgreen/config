#export LANG="en.utf8"
#export LANGUAGE="en"
#export LC_MESSAGES="en_GB.UTF-8"
PS1='${debian_chroot:+($debian_chroot)}\[\033[00;34m\][\[\033[01;36m\]\u\[\033[00;32m\]@\[\033[01;31m\]\h \[\033[01;32m\]\w\[\033[00;34m\]]\[\033[00;37m\]\$'
alias ls='ls --color=auto'
alias dir='dir --color=auto'
alias vdir='vdir --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'
alias netstat='netstat -n | grep tcp'
#alias mocp='mocp -T transparent-background' 
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias zhcon='zhcon --drv=fb'
alias w3m='TERM=jfbterm w3m'
if ps | grep tty > /dev/null;then
	fbterm
else
	echo "Hello" > /dev/null
fi
