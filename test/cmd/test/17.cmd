touch exec noexec; chmod u+x exec
test -x exec && echo ok || echo wrong
test -x noexec && echo ok || echo wrong