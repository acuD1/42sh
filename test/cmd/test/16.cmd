touch write nowrite; chmod u-w nowrite
test -w write && echo ok || echo wrong
test -w nowrite && echo ok || echo wrong