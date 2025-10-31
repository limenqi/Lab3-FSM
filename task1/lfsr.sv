module lfsr(
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [4:1] data_out // Changed from [3:0] to [4:1] for easier indexing
);

logic [4:1] sreg;

always_ff @(posedge clk or posedge rst) begin
    if (rst)
        sreg <= 4'b0001;
    else if (en)
        sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};
end

assign data_out = sreg;

endmodule
