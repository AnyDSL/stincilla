#usable in the root directory of anydsl
#setup ctags and configures vim
FILE=.ctags
if [ $(dpkg-query -W -f='${Status}' exuberant-ctags 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
    apt-get install exuberant-ctags;
    grep -q -x -F 'set tags=./tags;' ~/.vimrc || echo 'set tags=./tags;' >> ~/.vimrc
    if [ -f ~/$FILE ]; then
        echo '--langdef=impala' >> ~/$FILE
        echo '--langmap=impala:.impala' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*type[ \t]([a-zA-Z0-9_]+)[ \t]*=.+/\1/t,typedef/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*struct[ \t]([a-zA-Z0-9_]+)/\1/s,struct/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*fn[ \t]([a-zA-Z0-9_]+)/\1/f,function/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*let[ \t]+([a-zA-Z0-9_]+)[ \t]*=/\1/c,constant/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*let[ \t]+mut[ \t]+([a-zA-Z0-9_]+)[ \t]*=/\1/v,variable/' >> ~/$FILE
    else
        touch ~/$FILE
        echo '--langdef=impala' >> ~/$FILE
        echo '--langmap=impala:.impala' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*type[ \t]([a-zA-Z0-9_]+)[ \t]*=.+/\1/t,typedef/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*struct[ \t]([a-zA-Z0-9_]+)/\1/s,struct/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*fn[ \t]([a-zA-Z0-9_]+)/\1/f,function/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*let[ \t]+([a-zA-Z0-9_]+)[ \t]*=/\1/c,constant/' >> ~/$FILE
        echo '--regex-impala=/^[ \t]*let[ \t]+mut[ \t]+([a-zA-Z0-9_]+)[ \t]*=/\1/v,variable/' >> ~/$FILE
    fi
fi

ctags -R --exclude=impala --exclude=llvm --exclude=llvm_install --exclude=llvm_build --exclude=traversal --exclude=half --exclude=anyseq --exclude=thorin .
