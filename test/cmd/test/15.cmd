touch read noread; chmod u-r noread
test -r read && echo ok || echo wrong
test -r noread && echo ok || echo wrong