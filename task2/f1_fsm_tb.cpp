#include "Vf1_fsm.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYCLE 1000000

int main (int argc, char **argv) {
    int simcyc; // simulation clock count
    int tick; // ecah clock cycle has two ticks for two edges (rising and falling)

    Verilated::commandArgs(argc, argv);
    Vf1_fsm* top = new Vf1_fsm;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1_fsm.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("L3T2: F1 FSM");
    vbdSetMode(1);    // set Vbuddy to mode 1

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    for (simcyc =0; simcyc<MAX_SIM_CYCLE; simcyc++){
        for (tick=0; tick<2; tick++){
            tfp->dump(2*simcyc + tick);
            top->clk = !top->clk; // toggle clock
            top->eval(); // evaluate model
        }

        top->rst = (simcyc < 2) ; // assert reset for first two cycles and at cycle 15
        top->en = vbdFlag(); // get enable signal from Vbuddy

        vbdBar(top->data_out & 0xFF);

        if ((Verilated::gotFinish()) || (vbdGetkey()=='q'))
            exit(0);
    }
    
    vbdClose();
    tfp->close();
    exit(0);
    
}