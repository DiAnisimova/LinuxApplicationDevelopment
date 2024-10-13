break 22 if i % 5 == 0
set $_exitcode = -1
tty /dev/null
run
while $_exitcode == -1
    echo @@@
    print m
    echo @@@
    print n
    echo @@@
    print s
    echo @@@
    print i
    continue
end
quit
