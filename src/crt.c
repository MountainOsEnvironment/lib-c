extern int main();
extern void exit(int);

void static start1 (at) int at; {
    exit(main((&at)[11], (&at)[12], (&at)[13]));
}
void _start () {
    start1();
}