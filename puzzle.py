from logic import *

AKnight = Symbol("A is a Knight")
AKnave = Symbol("A is a Knave")

BKnight = Symbol("B is a Knight")
BKnave = Symbol("B is a Knave")

CKnight = Symbol("C is a Knight")
CKnave = Symbol("C is a Knave")

# Puzzle 0
# A says "I am both a knight and a knave."
knowledge0 = And(
    Or(And(AKnight,Not(AKnave)), And(AKnave, Not(AKnight))),
    Implication(AKnight, And(AKnight,AKnave))

)

# Puzzle 1
# A says "We are both knaves."
# B says nothing.
knowledge1 = And(
    Or(And(AKnight,Not(AKnave)), And(AKnave, Not(AKnight))),
    Or(And(BKnight,Not(BKnave)), And(BKnave, Not(BKnight))),

    Implication(AKnight, And(AKnave,BKnave)),
    Implication(AKnave, Not(And(BKnave, AKnave)))
)

# Puzzle 2
# A says "We are the same kind."
# B says "We are of different kinds."
knowledge2 = And(
    Or(And(AKnight,Not(AKnave)), And(AKnave, Not(AKnight))),
    Or(And(BKnight,Not(BKnave)), And(BKnave, Not(BKnight))),
    # A said:
    Biconditional(AKnight,  Or(And(AKnight,BKnight), And(AKnave, BKnave))),
    # b said:
    Biconditional(BKnight, Or(And(AKnave,BKnight), And(AKnight, BKnave))),
)

# Puzzle 3
# A says either "I am a knight." or "I am a knave.", but you don't know which.
# B says "A said 'I am a knave'."
# B says "C is a knave."
# C says "A is a knight."
sentence0 = Or(And(AKnight,Not(AKnave)), And(AKnave, Not(AKnight))) # im a knight
sentence1 = Or(And(AKnight, AKnave), And(AKnave, Not(AKnave)))  # im a knave
knowledge3 = And(
    # Or(And(AKnight,Not(AKnave)), And(AKnave, Not(AKnight))),
    # Or(And(BKnight,Not(BKnave)), And(BKnave, Not(BKnight))),
    # Or(And(CKnight,Not(CKnave)), And(CKnave, Not(CKnight))),
    Or(AKnight, AKnave),
    Or(BKnight, BKnave),
    Or(CKnight, CKnave),

    Not(And(AKnight, AKnave)),
    Not(And(BKnight, BKnave)),
    Not(And(CKnight, CKnave)),
    # B said:
    Implication(BKnight, sentence1),
    Implication(BKnave, sentence0),
    # B said:
    Biconditional(BKnight, CKnave),
    Biconditional(BKnave, CKnight),
    # C said:
    Biconditional(CKnight, AKnight),
    Biconditional(CKnave, AKnave)
)


def main():
    symbols = [AKnight, AKnave, BKnight, BKnave, CKnight, CKnave]
    puzzles = [
        ("Puzzle 0", knowledge0),
        ("Puzzle 1", knowledge1),
        ("Puzzle 2", knowledge2),
        ("Puzzle 3", knowledge3)
    ]
    for puzzle, knowledge in puzzles:
        print(puzzle)
        if len(knowledge.conjuncts) == 0:
            print("    Not yet implemented.")
        else:
            for symbol in symbols:
                if model_check(knowledge, symbol):
                    print(f"    {symbol}")


if __name__ == "__main__":
    main()
