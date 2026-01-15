import file_region_replacer
import opcode_spec_parser


def parse_low_level_opcodes(low_level_opcode_spec_file, high_level_opcode_spec_file):
    high_level_opcodes = opcode_spec_parser.parse_high_level_opcode_file(high_level_opcode_spec_file)
    high_level_opcode_dict = {op.name: op for op in high_level_opcodes}
    return opcode_spec_parser.parse_low_level_opcode_file(low_level_opcode_spec_file, high_level_opcode_dict)


def gen_low_level_opcode_enum(low_level_opcodes):
    lines = []
    padding = "    "
    for opcode in low_level_opcodes:
        line = f"{padding}{opcode.name},"
        lines.append(line)
    return "\n".join(lines)

def group_low_level_opcodes_by_prefix(low_level_opcodes):
    grouped = {}
    for opcode in low_level_opcodes:
        hl_name = opcode.prefix
        if hl_name not in grouped:
            grouped[hl_name] = []
        grouped[hl_name].append(opcode)
    return grouped

def gen_low_level_opcode_value(low_level_opcodes):
    lines = []
    padding = "    "
    for opcode in low_level_opcodes:
        line = f"{padding}{opcode.name} = 0x{opcode.code:02X},"
        lines.append(line)
    return "\n".join(lines)

def get_type_cpp_type_name(type_name):
    match type_name:
        case "u8":
            return "uint8_t"
        case "i8":
            return "int8_t"
        case "u16":
            return "uint16_t"
        case "i16":
            return "int16_t"
        case "u32":
            return "uint32_t"
        case "i32":
            return "int32_t"
        case "u64":
            return "uint64_t"
        case "i64":
            return "int64_t"
        case "f32":
            return "float"
        case "f64":
            return "double"
        case _:
            raise NotImplementedError(f"Type {type_name!r} is not supported")

def gen_low_level_opcode_structs(low_level_opcodes):
    lines = []
    for opcode in low_level_opcodes:
        lines.append(f"struct {opcode.name}")
        lines.append("{")
        if opcode.prefix != 0:
            lines.append(f"    uint8_t __prefix;")
        lines.append(f"    uint8_t __code;")
        for param in opcode.params:
            lines.append(f"    {get_type_cpp_type_name(param.type)} {param.name};")
        lines.append("};")
        lines.append("")
    return "\n".join(lines)


def gen_low_level_opcode_size(low_level_opcodes):
    lines = []
    padding = "    "
    for opcode in low_level_opcodes:
        lines.append(f"{padding}sizeof({opcode.name}),")
        # match opcode.name:
        #     case "Switch":
        #         lines.append(f"{padding}OpCodeEnum::{opcode.name} => sizeof(Switch) + (inst.get_num_targets() * sizeof(int32_t)),")
        #     case _:
        #         lines.append(f"{padding}OpCodeEnum::{opcode.name} => sizeof({opcode.name}),")
    return "\n".join(lines)

GENERIC_PARAM_NAMES = ["arg1", "arg2", "arg3", "ret", "res"]

def is_generic_param_name(param_name):
    return param_name in GENERIC_PARAM_NAMES

def gen_low_level_opcode_write_to_data(low_level_opcodes):
    lines = []
    padding = "    "
    for opcode in low_level_opcodes:
        lines.append(f"{padding}case OpCodeEnum::{opcode.name}:")
        lines.append(f"{padding}{{")
        lines.append(f"{padding}    auto ir = ({opcode.name}*)codes;")
        if opcode.prefix != 0:
            lines.append(f"{padding}    ir->__prefix = {opcode_spec_parser.PREFIX_START_CODE + opcode.prefix - 1};")
        lines.append(f"{padding}    ir->__code = {opcode.code};")
        for param in opcode.params:
            if param.name.startswith("__padding_"):
                continue
            if param.arg_kind == "stack":
                lines.append(f"{padding}    ir->{param.name} = ({get_type_cpp_type_name(param.type)})inst.get_var_{param.arg}_eval_stack_idx();")
            # elif is_generic_param_name(param.arg):
            #     lines.append(f"{padding}    ir.{param.name} = inst.get_{param.arg}_const() as {param.type};")
            else:
                lines.append(f"{padding}    ir->{param.name} = ({get_type_cpp_type_name(param.type)})inst.get_{param.arg}();")
        match opcode.name:
            case "Switch":
                lines.append(f"{padding}    auto targetsInfo = inst.get_switch_targets();")
                lines.append(f"{padding}    int32_t self_ir_offset = (int32_t)inst.get_ir_offset();")
                lines.append(f"{padding}    int32_t* target_offsets = (int32_t*)(ir + 1);")
                lines.append(f"{padding}    for (int i = 0; i < targetsInfo.count; i++)")
                lines.append(f"{padding}    {{")
                lines.append(f"{padding}        target_offsets[i] = (int32_t)targetsInfo.targets[i]->ir_offset - self_ir_offset;")
                lines.append(f"{padding}    }}")
                lines.append(f"{padding}    return codes + sizeof({opcode.name}) + (targetsInfo.count * sizeof(int32_t));")
            case _:
                lines.append(f"{padding}    return codes + sizeof({opcode.name});")
        lines.append(f"{padding}}}")
    return "\n".join(lines)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 5:
        print("Usage: python gen_low_level_opcodes.py <path_to_low_level_opcodes_xml> <path_to_high_level_opcodes_xml> <path_to_ll_opcodes_h> <path_to_ll_opcodes_cpp>")
        sys.exit(1)

    low_level_opcode_xml_file = sys.argv[1]
    high_level_opcode_xml_file = sys.argv[2]
    output_file_h = sys.argv[3]
    output_file_cpp = sys.argv[4]
    low_level_opcodes = parse_low_level_opcodes(low_level_opcode_xml_file, high_level_opcode_xml_file)
    frr_h = file_region_replacer.FileRegionReplacer(output_file_h)

    frr_h.replace_region("LOW_LEVEL_OPCODE_ENUM", gen_low_level_opcode_enum(low_level_opcodes))

    grouped_opcodes = group_low_level_opcodes_by_prefix(low_level_opcodes)
    for prefix, opcodes in grouped_opcodes.items():
        frr_h.replace_region(f"LOW_LEVEL_OPCODE{prefix}", gen_low_level_opcode_value(opcodes))
    frr_h.replace_region("LOW_LEVEL_INSTRUCTION_STRUCTS", gen_low_level_opcode_structs(low_level_opcodes))
    frr_h.save()
    print(f"Updated low-level opcode definitions in {output_file_h}")

    frr_cpp = file_region_replacer.FileRegionReplacer(output_file_cpp)
    frr_cpp.replace_region("LOW_LEVEL_INSTRUCTION_SIZES", gen_low_level_opcode_size(low_level_opcodes))
    frr_cpp.replace_region("LOW_LEVEL_INSTRUCTION_WRITE_TO_DATA", gen_low_level_opcode_write_to_data(low_level_opcodes))
    frr_cpp.save()
    print(f"Updated low-level opcode definitions in {output_file_cpp}")
