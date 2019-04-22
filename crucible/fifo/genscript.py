#!/usr/bin/python3

import argparse

def Generate(pkt_size, file_name):
    with open(file_name, 'w') as fw:
        fw.write('let miter_setup = do {\n')
        #fw.write('\tlet pkt_num_v = crucible_term {{ {size} : [32] }};\n'.format(size=pkt_size))
        fw.write('\tlet pkt_num_v = crucible_term {{ ')
        fw.write(str(pkt_size))
        fw.write(' : [32] }};\n')
        fw.write('\n')

        for i in range (2, pkt_size):
            fw.write('\tx{0} <- crucible_fresh_var "pkt{0}" (llvm_int 32);\n'.format(i))

        fw.write('\n')
        fw.write('\tpkt_arr <- crucible_alloc (llvm_array {0} (llvm_int 32));\n'.format(pkt_size))
        fw.write('\n')

        fw.write('\tcrucible_points_to (crucible_elem pkt_arr 0) (crucible_term {{ 0 : [32] }});\n')
        fw.write('\tcrucible_points_to (crucible_elem pkt_arr 1) pkt_num_v;\n')

        for i in range (2, pkt_size):
            fw.write('\tcrucible_points_to (crucible_elem pkt_arr {0}) (crucible_term x{0});\n'.format(i))

        fw.write('\n')
        fw.write('\tcrucible_execute_func [pkt_arr, pkt_num_v];\n')
        fw.write('\tcrucible_return (crucible_term {{ 0 : [32] }});\n')
        fw.write('};\n')

        fw.write('\n')

        fw.write('let main : TopLevel () = do {\n')
        fw.write('\tm <- llvm_load_module "miter.bc";\n')
        fw.write('\ttime (crucible_llvm_verify m "miter" [] false miter_setup z3);\n')
        fw.write('\tprint "Done";\n')
        fw.write('};\n')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Generate proof script")
    parser.add_argument('pktsize', type=int, help='packet size')
    parser.add_argument('output', type=str, help='output file')

    args = parser.parse_args()

    Generate(args.pktsize, args.output)

