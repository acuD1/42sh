cd /tmp
touch notfifo && mkfifo fifo
test -p fifo && echo ok || echo wrong
test -p notfifo && echo ok || echo wrong