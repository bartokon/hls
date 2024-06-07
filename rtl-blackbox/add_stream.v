`timescale 1ns/1ps

module add_stream (
    input [31:0] a,
    input a_empty_flag,
    output a_read_enable,

    input [31:0] b,
    input b_empty_flag,
    output b_read_enable,

    output [31:0] c,
    input c_full_flag,
    output c_write_enable,

    output ap_idle,
    input ap_start,
    output ap_ready,
    output ap_done,
    input ap_continue,

    input ap_ce,
    input ap_rst,
    input ap_clk
);
    reg a_read_enable_d;
    reg b_read_enable_d;
    reg c_write_enable_d;
    reg [31:0] c_d;

    assign a_read_enable = a_read_enable_d;
    assign b_read_enable = b_read_enable_d;
    assign c_write_enable = c_write_enable_d;
    assign c = c_d;

    assign ap_idle = !ap_start;
    assign ap_ready = ap_start;
    assign ap_done = ap_start;

    //Flags are negated...
    assign flags_good = a_empty_flag && b_empty_flag && c_full_flag;
    assign hs_good = ap_start && ap_continue;

    always @(posedge ap_clk) begin
        if (ap_rst == 1'b1) begin
            a_read_enable_d <= 0;
            b_read_enable_d <= 0;
            c_write_enable_d <= 0;
            c_d <= 0;
        end else if (ap_ce == 1'b1) begin
            a_read_enable_d <= flags_good && hs_good;
            b_read_enable_d <= flags_good && hs_good;
            c_write_enable_d <= flags_good && hs_good;
            c_d <= a + b;
        end
    end

endmodule
