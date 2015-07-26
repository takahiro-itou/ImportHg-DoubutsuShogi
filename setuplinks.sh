#! /bin/bash -x

LN_S='ln -sf '
RM_F='rm -f '

for  dir  in  Game  ; do
   (cd  Lib/${dir}/Tests  \
      &&  ${LN_S}  ../../Tests/.TestCommon/Makefile.am)
done

