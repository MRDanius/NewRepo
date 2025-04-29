#include <iostream>;

int main() {
    int a, b;
    char oper;

    std::cin >> a >> oper >> b;
    _asm
    {
        mov eax, a
        mov ebx, b
        mov cl, oper
        cmp cl, '+'
        jnz minus
        add eax, ebx
        jmp result
    minus :
        sub eax, ebx
    result :
        mov a, eax
    }
    std::cout << a << std::endl;
    return 0;
}
