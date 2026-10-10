import random, string, sys, subprocess, os, time
n=100000
ops=[]
indices=[''.join(random.choices(string.ascii_letters, k=5)) for _ in range(1000)]
for _ in range(n):
    typ=random.choice(['insert','delete','find'])
    idx=random.choice(indices)
    if typ=='find':
        ops.append(f'find {idx}')
    else:
        val=random.randint(0,1000000)
        ops.append(f'{typ} {idx} {val}')
input_data=str(n)+'\n'+'\n'.join(ops)+'\n'
# run program and measure time
start=time.time()
proc=subprocess.run(['./code'],input=input_data.encode(),stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=30)
print('return',proc.returncode,'time',time.time()-start,'output lines',len(proc.stdout.splitlines()))
