from pwn import *
import binascii as b
from capstone import *

conn = remote('aup.zoolab.org',2530)

for i in range(6):
    conn.recvline()
    
while True:
    recv = conn.recvline().decode()
    if recv.split(' ')[0] =='Flag:':
        print(recv)
        break
    quiz = conn.recvline().decode().split(' ')[1].strip()
    print(quiz)
    _quiz = b.a2b_hex(quiz)
    print(_quiz)
    
    md = Cs(CS_ARCH_X86, CS_MODE_64)
    answer = ''
    for i in md.disasm(_quiz, 0x1000):
        answer = answer + i.mnemonic + ((' '+ i.op_str) if i.op_str else '') + '\n' 
    print(answer)
    _answer = b.b2a_hex(answer.encode('utf-8')).decode("utf-8") + '\n'
    print(_answer)

    print(conn.recv().decode())
    conn.send(_answer.encode(encoding="utf-8"))
    print(conn.recvline().decode())
#696d756c207264690a6f72207261782c207264690a7374630a6d756c207261780a636c630a
#696d756c207264690a6f72207261782c207264690a7374630a6d756c207261780a636c630a