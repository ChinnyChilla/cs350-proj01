#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint 
sys_uptime2(void)
{
  uint xticks;
  int x;
  argint(0, &x);

  acquire(&tickslock);
  if (x == 1) {
    xticks = ticks;
  } else if (x == 2) {
    xticks = ticks / 100;
  } else {
    xticks = ticks / 6000;
  }

  release(&tickslock);
  return xticks;
}


void
sys_shutdown(void) {
	outw(0xB004, 0x0|0x2000);
    outw(0x604, 0x0|0x2000);
	return;
}

void
sys_exit2(int position)
{
  argint( 0 , &position);
  cprintf("%d\n", position);
  exit();
}

int
sys_age(void) {
	int age;
	if (argint(0, &age) < 0) return -1;
	cprintf("You have 5200 weeks in your life\n");
	int weeksLeft = 5200 - (age * 52);
	cprintf("That means your have %d weeks left\n", weeksLeft);
	cprintf("Therefore you are: ");
	if (age < 20) {
		cprintf("young\n");
	} else {
		cprintf("old\n");
	}
}

int
sys_shutdown2(void) {
  char *msg;
  if(argptr(0, (void*)&msg, sizeof(char*)) < 0){
    return -1;
  }
  cprintf("Shutting Down: %s\n", msg);
  outw(0xB004, 0x0|0x2000);
  outw(0x604, 0x0|0x2000);
  return 0;

}