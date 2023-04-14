MAX_SIZE = 10
# Taking the input an separating it into a list
x = [int(x) for x in input('Enter the x(n) -> ').split()]
h = [int(x) for x in input('Enter the h(n) -> ').split()]

n = len(x)
m = len(h)

#Initialising row vector and column vector
row_vec = [0] * MAX_SIZE
col_vec = [0] * MAX_SIZE
out = [0] * MAX_SIZE
circular_shift_mat = [[0 for i in range(MAX_SIZE)]for j in range(MAX_SIZE)] 
                            

size = max(n, m)

#Resizing the row vector and column vectors
for i in range(size):
    if(i >= n):
        row_vec[i] = 0
    else:
        row_vec[i] = x[i]

for i in range(size):
    if (i >= m):
        col_vec[i] = 0
    else:
        col_vec[i] = h[i]


d = 0
 
for i in range(size):
    curIndex = size - d
    for j in range(size):
        circular_shift_mat[j][i] = row_vec[curIndex % size]
        curIndex += 1
     
    
    d += 1
 

for i in range(size):
    for j in range(size):
        out[i] += circular_shift_mat[i][j] * col_vec[j]
         
    print(out[i], end = " ")

