#pragma once
#include "Opcode.h"
#include <Windows.h>
// 1byteָ���ָ�����������ѡ���ָ���ӦΨһ�Ĳ�������ϣ�
// Byte_xxx ->n*InstIndex-> Inst -> n * OperandGroup_xxx -> n * operand
//							|-> n * NameId	    ^
//				|-> n * Group_xxx  /
extern RegOrOperandGroup Operands[];
extern LPCSTR InstructionNames[];
extern unsigned char OperandGroup1[];
extern unsigned char OperandGroup2[][2];
extern unsigned char OperandGroup3[][3];
extern unsigned char OperandGroup4[][4];
extern OpcodeData HexTable1[];
extern OpcodeData HexTable2[];
extern ZipOpcodeData HexTable3Zip_38[];
extern ZipOpcodeData HexTable3Zip_3A[];
extern Hex_Inst HexInsts[];
extern InstChangeData InstChange[];