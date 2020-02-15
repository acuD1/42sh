a='hello' b=''; unset c
test ${a} && echo ok || echo wrong
test ${b} && echo ok || echo wrong
test ${c} && echo ok || echo wrong
test -z ${a} && echo ok || echo wrong
test -z ${b} && echo ok || echo wrong
test -z ${c} && echo ok || echo wrong