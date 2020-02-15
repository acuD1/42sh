foo=foobarfoo; echo ${foo%foo}
t=aabbcc123; echo ${t#*2} ${t#2*} ${t#*bb*} ${t#*a*}
echo ${t%%fo*} ${t##123} ${t%%123} ${t%%$PATH} ${t%%${t##aa}} 
