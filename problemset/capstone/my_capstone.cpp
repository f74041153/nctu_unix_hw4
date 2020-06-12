#include <capstone/capstone.h>
#include <cstdio>
#include <iostream>
#include <cstring> 
#include <inttypes.h>

using namespace std;

string disassembly(uint8_t *bytearray, long size, uint64_t startAddress){
    csh handle;
    cs_insn *insn;
    size_t count;
    string output;
    cs_opt_skipdata skipdata = {
       .mnemonic = "db",
    };
    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) == CS_ERR_OK){
        cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
        cs_option(handle, CS_OPT_SKIPDATA, CS_OPT_ON);
        cs_option(handle, CS_OPT_SKIPDATA_SETUP, (size_t)&skipdata);
        count = cs_disasm(handle, bytearray, size, startAddress, 0, &insn);
        if (count > 0) {
            size_t j;
            for (j = 0; j < count; j++) {
                char buffer[512];
                int i=0;
                i = sprintf(buffer, "0x%" PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic,insn[j].op_str);
                output += buffer;
            }
            cs_free(insn, count);
        } else {
            output = "ERROR: Failed to disassemble given code!\n";
        }
    }
    cs_close(&handle);
    return output;
}

int main(){
//    static csh cshandle = 0;
//   if(cs_open(CS_ARCH_X86, CS_MODE_64, &cshandle) != CS_ERR_OK) return -1;

    string quiz;
    cin >> quiz;
    cout << disassembly((uint8_t*)&quiz[0], quiz.length(),0) << endl;
/*    cs_insn *insn;
    size_t count;
    if((count = cs_disasm(cshandle,(uint8_t*)&quiz, bufszm, rip, 0, &insn)) > 0){
        int i;
        for(i=0;i<count;i++){
            instruction in;
            in.size = insn[i].size;
            in.opr = insn[i].mnemonic;
            in.opnd = i
            nsn[i].op_str;
            memcpy(in.bytes, insn[i].bytes, insn[i].size);
        }
        cs_free(insn,count);
    }
    cs_close(&cshandle);*/
}