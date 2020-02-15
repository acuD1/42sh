socketfile=/var/run/cupsd
test -S ${socketfile} && echo ok || echo wrong
test -S /dev/null && echo ok || echo wrong