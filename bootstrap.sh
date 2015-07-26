#! /bin/bash -x

./setuplinks.sh

mkdir -p .config  \
  &&  aclocal  -I  .config  \
  &&  autoheader  \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

