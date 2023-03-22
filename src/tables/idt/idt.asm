[extern intHandler]
[global intVector]

%macro isrStub 1
intStub%+%1:
	push 0
    push %1
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    mov rdi, rsp
    call intHandler

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 16
    iretq
%endmacro

%macro irqStub 1
intStub%+%1:
    push 0
    push %1
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    mov rdi, rsp
    call intHandler

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 16
    iretq
%endmacro

%assign i 0
%rep 32
    isrStub i
    %assign i i+1
%endrep

%assign j 32
%rep 16
    irqStub j
    %assign j j+1
%endrep

%assign k 48
%rep 224
    isrStub k
    %assign k k+1
%endrep

intVector:
    %assign l 0
    %rep 256
        dq intStub%+l
        %assign l l+1
    %endrep
