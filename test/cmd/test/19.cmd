touch emptyfile; echo "not empty" > notempty
test -s emptyfile && echo ok || echo wrong
test -s notempty && echo ok || echo wrong