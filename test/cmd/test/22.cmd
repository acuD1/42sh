test 0 -eq 1 && echo ok || echo wrong
test -1 -eq 1 && echo ok || echo wrong
test -1 -eq -1 && echo ok || echo wrong
first='12' second='34'
test ${first} -ne ${second} && echo ok || echo wrong
test -1 -gt -2 && echo ok || echo wrong
test 2 -ge 2 && echo ok || echo wrong
test -2 -lt -2 && echo ok || echo wrong
test 3 -le +2 && echo ok || echo wrong