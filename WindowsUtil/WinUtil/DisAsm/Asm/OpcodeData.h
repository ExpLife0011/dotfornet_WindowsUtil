#pragma once
#include "Opcode.h"
#include <Windows.h>
// 1byteָ���ָ�����������ѡ���ָ���ӦΨһ�Ĳ�������ϣ�
// Byte_xxx -> n * Inst -> n * OperandGroup_xxx -> n * operand
//					|-> n * NameId	    ^
//					|-> n * Group_xxx  /
extern RegOrOperandGroup Operands[];
extern LPCSTR InstructionNames[];
extern unsigned char OperandGroup1[];
extern unsigned char OperandGroup2[][2];
extern unsigned char OperandGroup3[][3];
extern unsigned char OperandGroup4[][4];
extern OpcodeData Byte1[];
extern OpcodeData Byte2[];
extern ZipOpcodeData Byte3Zip_38[];
extern ZipOpcodeData Byte3Zip_3A[];

