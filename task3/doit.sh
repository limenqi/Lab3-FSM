#!/bin/sh/

rm -rf obj_dir
rm -f delay.vcd

verilator -Wall --cc --trace delay.sv --exe delay_tb.cpp

make -j -C obj_dir/ -f Vdelay.mk Vdelay       

obj_dir/Vdelay