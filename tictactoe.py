"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    # count the number of X and O
    number_of_xs = 0
    for line in board:
        number_of_xs += line.count(X)
    number_of_os = 0
    for line in board:
        number_of_os += line.count(O)
    
    # if X and O have the same amount, this means that it's X time,else is O time
    if number_of_xs == number_of_os:
        return X
    else:
        return O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    possible_actions = set()
    for i, line in enumerate(board):
        for j, action in enumerate(line):
            if action == EMPTY:
                possible_actions.add((i,j)) 
    return possible_actions

def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    if action[0] < 0 or action[0] > 2 or action[1] < 0 or action[1] > 2 or board[action[0]][action[1]] != EMPTY:
        raise Exception
    board2 = copy.deepcopy(board)
    for i, line in enumerate(board2):
        if i != action[0]:
            continue
        for j, cell in enumerate(line):
            if (i,j) == action:
                board2[i][j] = player(board2)
                return board2
    


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    # check horizontally
    for i,line in enumerate(board):
        if line[0] == line[1] == line[2] and (line[0] != EMPTY):
            return line[0]
    # check vertically
    for j in range(3):
        if board[0][j] == board[1][j] == board[2][j] and (board[0][j] != EMPTY):
            return board[0][j]
    # check diagonally
    if board[1][1] == EMPTY:
        return None
    elif board[0][0] == board[1][1] == board[2][2] and board[0][0] != EMPTY:
        return board[0][0]
    elif board[0][2] == board[1][1] == board[2][0] and board[1][1] != EMPTY:
        return board[1][1]
    return None

def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    w = winner(board)
    if w != None:
        return True
    for line in board:
        if EMPTY in line:
            return False
    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    else:
        return 0

def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None
    if player(board) == X:
        max = max_value(board)
        for action in actions(board):
            if min_value(result(board,action)) == max:
                return action
    else:
        min = min_value(board)
        for action in actions(board):
            if max_value(result(board,action)) == min:
                return action
      
  


def max_value(board):
    if terminal(board):
        return utility(board)
    v = -math.inf
   
    for action in actions(board):
        v = max(v,min_value(result(board,action)))

    return v

def min_value(board):
    if terminal(board):
        return utility(board)
    v = math.inf
   
    for action in actions(board):
        v = min(v,max_value(result(board,action)))

    return v