rm -rf tempdir; test ! -d tempdir && echo "tempdir removed"
test zzz -eq 123 && echo ok || echo wrong