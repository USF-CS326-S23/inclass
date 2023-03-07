import os
import pexpect.popen_spawn
import sys

child = None

if len(sys.argv) < 2:
    print("Provide an xv6 command to execute.")
    sys.exit(-1)

gpid = os.getpgid(os.getpid())

child = pexpect.popen_spawn.PopenSpawn('make qemu', encoding='utf-8', timeout=300)

child.expect_exact('$ ')
child.sendline(sys.argv[1])
child.expect_exact('$ ')
print(child.before)
child.send('\x01')
child.send('x')
child.expect(pexpect.EOF)
