TGT_DIR=~/lab1release
rm -rf $TGT_DIR
mkdir $TGT_DIR
git archive master | tar -x -C $TGT_DIR

