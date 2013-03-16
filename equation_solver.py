from fractions import Fraction

equations = [#a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s
             [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38],
             [0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38],
             [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 38],
             [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 38],
             [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 38],
             [1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 38],
             [0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 38],
             [0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 38],
             [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 38],
             [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 38],
             [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 38],
             [0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 38],
             [1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 38],
             [0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 38],
             [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 38]]

n = len(equations)
m = len(equations[0])

for i in range(n):
    for j in range(m):
        equations[i][j] = Fraction(equations[i][j]) 

# For debugging
def print_eq():
    for row in equations:
        for value in row:
            print(str(value).rjust(4), end=' ')
        print()

# Gaussian Elimination

def swap(i, j):
    equations[i], equations[j] = equations[j], equations[i]

def multiply(i, c):
    for j in range(m):
        equations[i][j] = c * equations[i][j]

def add(i, j, c):
    for x in range(m):
        equations[i][x] = equations[i][x] + c * equations[j][x]

row_index = 0
col_index = 0
while row_index < n and col_index < m - 1:
    for j in range(row_index, n):
        if equations[j][col_index]:
            swap(row_index, j)
            break
    else:
        col_index += 1
        continue

    row = equations[row_index]
    leading_value = row[col_index]
    multiply(row_index, 1/leading_value)

    for j in range(0, n):
        if j == row_index:
            continue
        add(j, row_index, -equations[j][col_index])

    row_index += 1
    col_index += 1
    
#print_eq()

variables = 'abcdefghijklmnopqrs'
for row in equations:
    result = ''
    first = True
    count = 0
    constant = row[-1]
    for coeff, variable in zip(row, variables):
        if coeff:
            if not count:
                result += variable + ' = ' 
                if constant:
                    result += str(constant) 
            else:
                coeff = -coeff
                if coeff > 0:
                    if count > 1 or constant:
                        result += ' + '
                else:
                    result += ' - '
                if abs(coeff) != 1:
                    result += str(abs(coeff))
                result += variable
            count += 1
    print(result)
