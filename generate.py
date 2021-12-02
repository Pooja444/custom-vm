# s = """mov reg1 0
# mov reg2 0
# add reg2 reg1
# mov reg3 1
# add reg1 reg3
# mov reg3 10
# cmp reg1 reg3
# mov reg3 6
# mov reg4 30
# je reg4 reg3"""

s = """mov reg1 22
mov reg2 0
mov dp 1086
add dp reg2
lea reg3 dp
lfr reg4 reg2
mov reg5 95
sub reg4 reg5
mov reg5 10
mul reg4 reg5
cmp reg3 reg4
mov reg4 1068
mov reg5 1108
je reg4 reg5
mov reg4 1
add reg2 reg4
cmp reg1 reg2
mov reg4 1032
mov reg5 1108
je reg5 reg4
100 50 0
190 20 210
90 60 190
0 30 60
0 210 190
20 230 60
130 100 150 80
mov reg4 22
cmp reg2 reg4"""

instructionLines = s.split("\n")

instrDict = {
    "mov": 101,
    "add": 102,
    "sub": 103,
    "mul": 104,
    "div": 105,
    "cmp": 106,
    "je": 107,
    "lea": 108,
    "lfr": 109,
    "reg1":	202,
    "reg2":	203,
    "reg3":	204,
    "reg4":	205,
    "reg5":	206,
    "reg6":	207,
    "dp": 208
}

instrList = []

for instructionLine in instructionLines:
    instructions = instructionLine.split(" ")
    for index, instruction in enumerate(instructions):
        if(instruction.isnumeric()):
            instrList.append(int(instruction))
        else:
            if instruction == "mov" and not instructions[index + 2].isnumeric():
                opCode = instrDict[instruction] - 1;
            else:
                opCode = instrDict[instruction]
            instrList.append(opCode)

print("Instructions: ")
print(instrList)

flag = "id_rather_be_traveling"
flagValues= []

for c in flag:
    flagValues.append((ord(c) - 95) * 10)

print("Flag values:")
print(flagValues)
print(len(flagValues))

flag = "He unaffected sympathize discovered at no am conviction principles. Girl ham very how yet hill four show. Meet lain on he only size. Branched learning so subjects mistress do appetite jennings be in. Esteems up lasting no village morning do offices. Settled wishing ability musical may another set age. Diminution my apartments he attachment is entreaties announcing estimating. And total least her two whose great has which. Neat pain form eat sent sex good week. Led instrument sentiments she simplicity. Advanced extended doubtful he he blessing together. Introduced far law gay considered frequently entreaties difficulty. Eat him four are rich nor calm. By an packages rejoiced exercise. To ought on am marry rooms doubt music. Mention entered an through company as. Up arrived no painful between. It declared is prospect an insisted pleasure. Warmly little before cousin sussex entire men set. Blessing it ladyship on sensible judgment settling outweigh. Worse linen an of civil jokes leave offer. Parties all clothes removal cheered calling prudent her. And residence for met the estimable disposing. Mean if he they been no hold mr. Is at much do made took held help. Latter person am secure of estate genius at."

flag = "".join(flag.split(" "))

flagValues= []
for c in flag:
    flagValues.append((ord(c) - 34) * 6)