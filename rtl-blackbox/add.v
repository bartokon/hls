`timescale 1ns/1ps
module add (
    input [31:0] a,
    input [31:0] b,
    output [31:0] c,
    output c_vld,
    input ap_ce,
    input ap_rst,
    input ap_clk
);
    reg [31:0] c_d;
    reg c_vld_d;
    assign c = c_d;
    assign c_vld = c_vld_d;
    always @(posedge ap_clk) begin
        if (ap_rst == 1'b1) begin
            c_d <= 32'b0;
            c_vld_d <= 1'b0;
        end else begin
            c_d <= (a + b) & {32{ap_ce}};
            c_vld_d <= ap_ce;
        end
    end
endmodule