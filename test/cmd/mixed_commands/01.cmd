cd /tmp; cat << k > file; cd -; cat < /tmp/file | sed -e 's/L/00/g' > /tmp/newfile; cat < /tmp/newfile
LaLaLa
test
test2
k