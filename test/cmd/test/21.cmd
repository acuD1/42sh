test 'abc' = 'def' && echo ok || echo wrong
test 'abc' = 'abc' && echo ok || echo wrong
test 'abc' != 'def' && echo ok || echo wrong
test 'abc' != 'abc' && echo ok || echo wrong