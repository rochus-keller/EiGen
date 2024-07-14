// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "Mandelbrot.h"

void Mandelbrot$Mandelbrot$init$(struct Mandelbrot$Mandelbrot* inst){
    inst->class$ = &Mandelbrot$Mandelbrot$class$;
}
struct Mandelbrot$Mandelbrot * Mandelbrot$create() {
    struct Mandelbrot$Mandelbrot * b;
    struct Mandelbrot$Mandelbrot * $t0;
    b = 0;
    $t0 = OBX$Alloc(sizeof(struct Mandelbrot$Mandelbrot));
    memset($t0,0,sizeof(struct Mandelbrot$Mandelbrot));
    b = $t0;
    Mandelbrot$Mandelbrot$init$($t0);
    return b;
}

struct Benchmark$Result * Mandelbrot$Mandelbrot$benchmark(void* this) {
    struct Mandelbrot$Mandelbrot* this$ = this;
    assert(0);
    return 0;
}

uint8_t Mandelbrot$Mandelbrot$verifyResult(void* this, struct Benchmark$Result * result) {
    struct Mandelbrot$Mandelbrot* this$ = this;
    assert(0);
    return 0;
}

uint8_t Mandelbrot$Mandelbrot$innerBenchmarkLoop(void* this, int32_t innerIterations) {
    struct Mandelbrot$Mandelbrot* this$ = this;
    return Mandelbrot$verifyResult2(Mandelbrot$mandelbrot(innerIterations), innerIterations);
}

uint8_t Mandelbrot$verifyResult2(int32_t result, int32_t innerIterations) {
    if( (innerIterations == 500) ) {
        return (result == 191);
    } 
    if( (innerIterations == 750) ) {
        return (result == 50);
    } 
    if( (innerIterations == 1) ) {
        return (result == 128);
    } 
    Out$String((const struct OBX$Array$1){28,0,OBX$FromUtf("No verification result for ",28,0)});
    Out$Int(innerIterations, 0);
    Out$String((const struct OBX$Array$1){7,0,OBX$FromUtf(" found",7,0)});
    Out$Ln();
    Out$String((const struct OBX$Array$1){12,0,OBX$FromUtf("Result is: ",12,0)});
    Out$Int(result, 0);
    Out$Ln();
    return 0;
}

int32_t Mandelbrot$mandelbrot(int32_t size) {
    int32_t sum;
    int32_t byteAcc;
    int32_t bitNum;
    int32_t y;
    int32_t z;
    int32_t x;
    int32_t escape;
    double ci;
    double zr;
    double zrzr;
    double zi;
    double zizi;
    double cr;
    uint8_t notDone;
    sum = 0;
    byteAcc = 0;
    bitNum = 0;
    y = 0;
    z = 0;
    x = 0;
    escape = 0;
    ci = 0;
    zr = 0;
    zrzr = 0;
    zi = 0;
    zizi = 0;
    cr = 0;
    notDone = 0;
    sum = 0;
    byteAcc = 0;
    bitNum = 0;
    y = 0;
    while(1) {
        if( (y < size) ) {
            ci = ((2.0000000e+00 * (double)OBX$Div32(y,size)) - 1.0000000e+00);
            x = 0;
            while(1) {
                if( (x < size) ) {
                    zr = 0.0000000e+00;
                    zrzr = 0.0000000e+00;
                    zi = 0.0000000e+00;
                    zizi = 0.0000000e+00;
                    cr = ((2.0000000e+00 * (double)OBX$Div32(x,size)) - 1.5000000e+00);
                    z = 0;
                    notDone = 1;
                    escape = 0;
                    while(1) {
                        if( (notDone && (z < 50)) ) {
                            zr = ((zrzr - zizi) + cr);
                            zi = (((2.0000000e+00 * zr) * zi) + ci);
                            zrzr = (zr * zr);
                            zizi = (zi * zi);
                            if( ((zrzr + zizi) > 4.0000000e+00) ) {
                                notDone = 0;
                                escape = 1;
                            } 
                            z++;
                        } else {
                            break;
                        }
                    }
                    byteAcc = (OBX$Lsl32(byteAcc,1) + escape);
                    bitNum++;
                    if( (bitNum == 8) ) {
                        sum = (sum ^ byteAcc);
                        byteAcc = 0;
                        bitNum = 0;
                    } else if( (x == (size - 1)) ) {
                        byteAcc = OBX$Lsl32(byteAcc,(8 - bitNum));
                        sum = (sum ^ byteAcc);
                        byteAcc = 0;
                        bitNum = 0;
                    } 
                    x++;
                } else {
                    break;
                }
            }
            y++;
        } else {
            break;
        }
    }
    return sum;
}

struct Mandelbrot$Mandelbrot$Class$ Mandelbrot$Mandelbrot$class$ = { 
    &Benchmark$Benchmark$class$,
    Mandelbrot$Mandelbrot$benchmark,
    Mandelbrot$Mandelbrot$verifyResult,
    Mandelbrot$Mandelbrot$innerBenchmarkLoop,
};

static int initDone$ = 0;
void Mandelbrot$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    Benchmark$init$();
    Out$init$();
}
OBX$Cmd Mandelbrot$cmd$(const char* name) {
    if( name == 0 ) return Mandelbrot$init$;
    return 0;
}