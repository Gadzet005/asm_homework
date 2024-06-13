section .text

; f(x) = 2 ** x + 1
global f1
f1:
    enter 2, 0

    ; округление к меньшему
    finit
    fstcw word [esp]
    or word [esp], 0x0c00
    fldcw word [esp]

                            ; Пояснения для x = 12.3
    fld qword [ebp + 8]     ; 12.3
    fld st0                 ; 12.3 12.3
    frndint                 ; 12.3 12
    fsub st1, st0           ; 0.3 12
    fld1
    fscale                  ; 0.3 12 2**12
    fxch                    ; 0.3 2**12 12
    fstp st0                ; 0.3 2**12
    fxch                    ; 2**12 0.3
    f2xm1                   ; 2**12 2**0.3 - 1
    fld1
    fadd                    ; 2**12 2**0.3
    fmulp                   ; 2**12.3
    fld1
    faddp                   ; 2**12.3 + 1

    leave
    ret

; 1 производная f1: f(x) = 2**x * ln2
global df1
df1:
    enter 8, 0

    finit
    fld qword [ebp+8]
    fst qword [esp]
    call f1

    fld1
    fsubp
    fldln2
    fmulp

    leave
    ret

; 2 производная f1: f(x) = 2**x * ln2 ** 2
global d2f1
d2f1:
    enter 8, 0

    finit
    fld qword [ebp+8]
    fst qword [esp]
    call df1

    fldln2
    fmulp

    leave
    ret

; f(x) = x**5
global f2
f2:
    enter 0, 0

    finit
    fld qword [ebp + 8]     ; x
    fld st0                 ; x x
    fmul st0                ; x x**2
    fmul st0                ; x x**4
    fmulp                   ; x**5

    leave
    ret

; 1 производная f2: f(x) = 5*x**4
global df2
df2:
    enter 4, 0
    mov dword [esp], 5

    finit
    fld qword [ebp + 8]     ; x
    fmul st0                ; x**2
    fmul st0                ; x**4
    fild dword [esp]
    fmulp

    leave
    ret

; 2 производная f2: f(x) = 20*x**3
global d2f2
d2f2:
    enter 4, 0
    mov dword [esp], 20

    finit
    fld qword [ebp + 8]     ; x
    fld st0                 ; x x
    fmul st0                ; x x**2
    fmulp                   ; x**3
    fild dword [esp]
    fmulp

    leave
    ret

; f(x) = (1 - x) / 3
global f3
f3:
    enter 4, 0
    mov dword [esp], 3
    
    finit
    fld1
    fsub qword [ebp + 8]
    fild dword [esp]
    fdivp

    leave
    ret

; 1 производная f3: f(x) = -1/3
global df3
df3:
    enter 4, 0
    mov dword [esp], -3

    finit
    fld1
    fild dword [esp]
    fdivp

    leave
    ret

; 2 производная f3: f(x) = 0
global d2f3
d2f3:
    finit
    fldz
    ret