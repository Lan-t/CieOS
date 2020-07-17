.intel_syntax noprefix

#struct TaskRegisterState {

#    uint64_t cr3;  // 0x00

#    uint64_t rax;  // 0x08
#    uint64_t rcx;  // 0x10
#    uint64_t rdx;  // 0x18
#    uint64_t rbx;  // 0x20
#    uint64_t rsi;  // 0x28
#    uint64_t rdi;  // 0x30
#    uint64_t rbp;  // 0x38
#    uint64_t rsp;  // 0x40
#    uint64_t r8;   // 0x48
#    uint64_t r9;   // 0x50
#    uint64_t r10;  // 0x58
#    uint64_t r11;  // 0x60
#    uint64_t r12;  // 0x68
#    uint64_t r13;  // 0x70
#    uint64_t r14;  // 0x78
#    uint64_t r15;  // 0x80

#    uint64_t rflags;  // 0x88
#    uint64_t ss;  // 0x90
#    uint64_t cs;  // 0x98
#    uint64_t rip;  // 0xa0
#};

.extern dump

.global restore_context
restore_context:
    push qword ptr [rdi + 0x90] # ss
    push qword ptr [rdi + 0x40] # rsp
    push qword ptr [rdi + 0x88] # rflags
    push qword ptr [rdi + 0x98] # cs
    push qword ptr [rdi + 0xa0] # rip
    
    # raxは後
    mov rcx, [rdi + 0x10]
    mov rdx, [rdi + 0x18]
    mov rbx, [rdi + 0x20]
    mov rsi, [rdi + 0x28]
    # rdiは後
    mov rbp, [rdi + 0x38]
    mov r8,  [rdi + 0x48]
    mov r9,  [rdi + 0x50]
    mov r10, [rdi + 0x58]
    mov r11, [rdi + 0x60]
    mov r12, [rdi + 0x68]
    mov r13, [rdi + 0x70]
    mov r14, [rdi + 0x78]
    mov r15, [rdi + 0x80]

    mov rax, [rdi + 0x00]  # cr3
    mov cr3, rax
    mov rax, [rdi + 0x08]
    mov rdi, [rdi + 0x30]

    mov al, 0x20
    out 0x20, al  # master pic EOI

    iretq


.extern int_32_handler_schedule
.global int_32_handler
int_32_handler:
    push rbp
    mov rbp, rsp

    push qword ptr [rbp + 0x8] # rip
    push qword ptr [rbp + 0x10] # cs
    push qword ptr [rbp + 0x28] # ss
    push qword ptr [rbp + 0x18] # rflags

    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push qword ptr [rbp + 0x20] # rsp
    push qword ptr [rbp] # rbp
    push rdi
    push rsi
    push rbx
    push rdx
    push rcx
    push rax

    mov rax, cr3
    push rax

    mov rdi, rsp

    jmp int_32_handler_schedule

