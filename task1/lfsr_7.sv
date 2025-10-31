module lfsr_7 (
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [7:1] data_out
);

logic [7:1] sreg;

always_ff @(posedge clk or posedge rst) begin
    if (rst)
        sreg <= 7'b0000001;
    else if (en)
        sreg <= {sreg[6:1], sreg[3] ^ sreg[7]};
end

assign data_out = sreg;

endmodule
