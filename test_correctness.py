import random, string, subprocess, sys, os

def run_prog(prog_input):
    proc = subprocess.run(['./code'], input=prog_input.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return proc.stdout.decode()

def run_ref(prog_input):
    lines = prog_input.strip().split('\n')
    n = int(lines[0])
    mp = {}
    out = []
    idx = 1
    for _ in range(n):
        parts = lines[idx].split()
        idx += 1
        cmd = parts[0]
        if cmd == 'insert':
            i = parts[1]; v = int(parts[2])
            mp.setdefault(i, set()).add(v)
        elif cmd == 'delete':
            i = parts[1]; v = int(parts[2])
            if i in mp:
                mp[i].discard(v)
                if not mp[i]:
                    del mp[i]
        else:  # find
            i = parts[1]
            if i in mp and mp[i]:
                out.append(' '.join(map(str, sorted(mp[i]))) + '\n')
            else:
                out.append('null\n')
    return ''.join(out)

random.seed(1)
for test in range(20):
    n = 2000
    ops = []
    indices = [''.join(random.choices(string.ascii_lowercase, k=5)) for _ in range(100)]
    for _ in range(n):
        typ = random.choice(['insert', 'delete', 'find'])
        idx = random.choice(indices)
        if typ == 'find':
            ops.append(f'find {idx}')
        else:
            val = random.randint(0, 1000)
            ops.append(f'{typ} {idx} {val}')
    inp = str(n) + '\n' + '\n'.join(ops) + '\n'
    out1 = run_prog(inp)
    out2 = run_ref(inp)
    if out1 != out2:
        print('Mismatch on test', test)
        sys.exit(1)
print('All good')
