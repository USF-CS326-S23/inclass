import io
import pexpect
import sys

if len(sys.argv) < 2:
    print("Provide a command to execute.")
    sys.exit(-1)

child = pexpect.spawn('make qemu', encoding='utf-8')
#child.logfile_read = sys.stdout
child.expect_exact('$ ')
child.sendline(sys.argv[1])
child.expect_exact('$ ')
print(child.before)
child.sendcontrol('a')
child.send('x')
child.expect(pexpect.EOF)
