break 22 if (i > m + 26 * s && i < m + 35 * s)
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
